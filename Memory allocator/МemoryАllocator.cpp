#include <array>
#include <assert.h>
#include <barrier>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <vector>

#if __linux__ != 0
#include <time.h>

static uint64_t timer_nsec() {
#if defined(CLOCK_MONOTONIC_RAW)
	const clockid_t clockid = CLOCK_MONOTONIC_RAW;

#else
	const clockid_t clockid = CLOCK_MONOTONIC;

#endif

	timespec t;
	clock_gettime(clockid, &t);

	return t.tv_sec * 1000000000UL + t.tv_nsec;
}

#elif _WIN64 != 0
#define NOMINMAX
#include <Windows.h>

static struct TimerBase {
	LARGE_INTEGER freq;
	TimerBase() {
		QueryPerformanceFrequency(&freq);
	}
} timerBase;

// the order of global initialisaitons is non-deterministic, do
// not use this routine in the ctors of globally-scoped objects
static uint64_t timer_nsec() {
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);

	return 1000000000ULL * t.QuadPart / timerBase.freq.QuadPart;
}

#elif __APPLE__ != 0
#include <mach/mach_time.h>

static struct TimerBase {
	mach_timebase_info_data_t tb;
	TimerBase() {
		mach_timebase_info(&tb);
	}
} timerBase;

// the order of global initialisaitons is non-deterministic, do
// not use this routine in the ctors of globally-scoped objects
static uint64_t timer_nsec() {
	const uint64_t t = mach_absolute_time();
	return t * timerBase.tb.numer / timerBase.tb.denom;
}

#endif

struct MemoryBlock
{
	void* ptr = nullptr;
	size_t len = 0;

	MemoryBlock() = default;
	MemoryBlock(void* ptr, size_t len) : ptr(ptr), len(len)
	{}
	inline operator bool() const
	{
		return len && ptr;
	}
};

class AllocatorBase
{
protected:
	size_t usedMemory = 0;
	size_t maxUsedMemory = 0;

	void* malloc(size_t size)
	{
		usedMemory += size;
		if (usedMemory > maxUsedMemory)
		{
			maxUsedMemory = usedMemory;
		}
		return std::malloc(size);
	}
	void free(void* ptr, size_t size)
	{
		usedMemory -= size;
		return std::free(ptr);
	}

public:
	inline MemoryBlock alloc(size_t size)
	{
		return MemoryBlock();
	}
	inline void free(MemoryBlock& block)
	{}
	size_t getMaxUsedMemory() const
	{
		return maxUsedMemory;
	}
};

class DefaultAllocator : public AllocatorBase
{
public:
	MemoryBlock alloc(size_t size)
	{
		return MemoryBlock(AllocatorBase::malloc(size), size);
	}

	void free(MemoryBlock& block)
	{
		AllocatorBase::free(block.ptr, block.len);
	}
};

static size_t align(size_t n)
{
	const size_t sizeOfIntptr = sizeof(intptr_t);
	if ((sizeOfIntptr == 4 && n <= 4) || (sizeOfIntptr == 8 && n <= 8))
	{
		return sizeOfIntptr;
	}

	size_t v = n;
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

class MemoryAllocator : public AllocatorBase
{
private:
	struct Header
	{
		Header* prev = nullptr;
		Header* next = nullptr; // here we store if the block is used
		size_t size;
		size_t physicalPrevSize = 0;

		void setUsed(bool used)
		{
			unsigned mask = used;
			next = reinterpret_cast<Header*>(reinterpret_cast<intptr_t>(next) | mask);
		}
		bool isUsed() const
		{
			unsigned mask = 1;
			return mask & (reinterpret_cast<intptr_t>(next));
		}
		Header* getPrev() const
		{
			return prev;
		}
		Header* getNext() const
		{
			unsigned mask = 1;
			mask = ~mask;
			return reinterpret_cast<Header*>(reinterpret_cast<intptr_t>(next) & mask);
		}
	};

	void* memory = nullptr;
	Header* begin = nullptr;
	size_t memorySize = 0;

	Header* initHeader(void* memory, size_t size) const
	{
		Header* initializedHeader = reinterpret_cast<Header*>(memory);
		initializedHeader->prev = initializedHeader->next = nullptr;
		initializedHeader->size = size;
		initializedHeader->physicalPrevSize = 0;
		return initializedHeader;
	}

	Header* findFirstNeededChunk(size_t size) const
	{
		Header* current = begin;
		while (current && current->size < size)
		{
			current = current->next;
		}
		return current;
	}

	Header* getPhysicalPrevBlock(Header* chunk) const
	{
		if (chunk == memory)
		{
			return nullptr;
		}
		char* currentIt = reinterpret_cast<char*>(chunk);
		currentIt -= (chunk->physicalPrevSize + sizeof(Header));
		return reinterpret_cast<Header*>(currentIt);
	}

	Header* getPhysicalNextBlock(Header* chunk) const
	{
		char* currentIt = reinterpret_cast<char*>(chunk) + chunk->size + sizeof(Header);
		if (currentIt >= reinterpret_cast<char*>(memory) + memorySize)
		{
			return nullptr;
		}
		return reinterpret_cast<Header*>(currentIt);
	}

	void mergeBlocksRightWasTaken(Header* left, Header* right)
	{
		left->size = left->size + right->size + sizeof(Header);
		setPhysicalPrevOnNext(left);
	}

	void mergeBlocksLeftWasTaken(Header* left, Header* right)
	{
		left->size = left->size + right->size + sizeof(Header);
		setPhysicalPrevOnNext(left);

		left->next = right->next;
		left->prev = right->prev;
		if (right->next)
		{
			right->next->prev = left;
		}
		if (right->prev)
		{
			right->prev->next = left;
		}
		if (right == begin)
		{
			begin = left;
		}
	}

	void mergeThree(Header* first, Header* mid, Header* last) // first and last were free
	{
		first->size = first->size + mid->size + last->size + 2 * sizeof(Header);
		setPhysicalPrevOnNext(first);
		removeFromFreeList(first);
		removeFromFreeList(last);

		first->next = begin;
		begin = first;
	}

	void split(Header* chunk, size_t neededBytes)
	{
		const size_t remainingMemoryWithoutTheNewHeader = chunk->size - sizeof(Header);
		const size_t minChunkSize = 16;
		if (chunk->size == neededBytes || chunk->size <= minChunkSize || remainingMemoryWithoutTheNewHeader <= neededBytes * 2)
		{
			return; // no splitting needes
		}

		chunk->size = neededBytes;
		Header* rightChunk = initHeader(
			reinterpret_cast<Header*>(reinterpret_cast<char*>(chunk) + neededBytes + sizeof(Header)),
			remainingMemoryWithoutTheNewHeader - chunk->size);

		rightChunk->prev = chunk;
		rightChunk->next = chunk->next;
		rightChunk->physicalPrevSize = neededBytes;
		chunk->next = rightChunk;

		if (rightChunk->next)
		{
			rightChunk->next->prev = rightChunk;
		}

		Header* rightPhysicalNext = getPhysicalNextBlock(rightChunk);
		if (rightPhysicalNext)
		{
			rightPhysicalNext->physicalPrevSize = rightChunk->size;
		}
	}

	void removeFromFreeList(Header* chunk)
	{
		Header*& prev = chunk->prev;
		Header*& next = chunk->next;

		if (prev)
		{
			prev->next = next;
		}
		else
		{
			begin = next; // chunk is first in the free list
		}

		if (next)
		{
			next->prev = prev;
		}
		prev = next = nullptr;
	}

	void setPhysicalPrevOnNext(Header* chunk)
	{
		Header* next = getPhysicalNextBlock(chunk);
		if (next)
		{
			next->physicalPrevSize = chunk->size;
		}
	}

public:
	MemoryAllocator(size_t size = 1024 * 1024 * 512)
	{
		memory = AllocatorBase::malloc(size);
		begin = initHeader(memory, size - sizeof(Header));
		memorySize = size;
	}

	~MemoryAllocator()
	{
		AllocatorBase::free(memory, memorySize);
	}

	MemoryBlock alloc(size_t size)
	{
		size = align(size);
		Header* chunk = findFirstNeededChunk(size);
		if (!chunk)
		{
			throw std::exception("No memory");
		}

		split(chunk, size);
		removeFromFreeList(chunk);
		chunk->setUsed(1);
		return MemoryBlock(reinterpret_cast<char*>(chunk) + sizeof(Header), chunk->size);
	}

	void free(MemoryBlock& block)
	{
		if (!block.ptr)
		{
			return;
		}

		Header* toFree = reinterpret_cast<Header*>(reinterpret_cast<char*>(block.ptr) - sizeof(Header));
		toFree->setUsed(0);

		Header* prev = getPhysicalPrevBlock(toFree);
		Header* next = getPhysicalNextBlock(toFree);

		if (prev && !prev->isUsed() && next && !next->isUsed())
		{
			mergeThree(prev, toFree, next);
		}
		else if (prev && !prev->isUsed())
		{
			mergeBlocksRightWasTaken(prev, toFree);
		}
		else if (next && !next->isUsed())
		{
			mergeBlocksLeftWasTaken(toFree, next);
		}
		else
		{
			toFree->next = begin;
			begin->prev = toFree;
			begin = toFree;
		}
	}
};

////////////////////
// Tests
////////////////////

template <typename Allocator>
struct Test1
{
	static void test(Allocator& allocator, size_t testSize = 1000)
	{
		std::vector<MemoryBlock> results;
		results.reserve(testSize);

		for (size_t i = 0; i < testSize; i++)
		{
			results.push_back(allocator.alloc(128 * (1 + i % 4)));
		}
		for (auto& block : results)
		{
			allocator.free(block);
		}
	}
};

template <typename Allocator>
struct Test2
{
	static void test(Allocator& allocator, size_t testSize = 1000)
	{
		std::vector<MemoryBlock> results;
		results.reserve(testSize * 1.1f);

		for (size_t i = 0; i < testSize; i++)
		{
			results.push_back(allocator.alloc(i % 2 ? 32 : 64));

			if (i % 10 == 0)
			{
				results.push_back(allocator.alloc(4096 * 1024));
			}
		}
		for (auto& block : results)
		{
			allocator.free(block);
		}
	}
};

template <typename Allocator>
struct Test3
{
	static void test(Allocator& allocator, size_t testSize = 1000)
	{
		std::vector<MemoryBlock> results;
		results.reserve(testSize);

		for (size_t i = 0; i < testSize; i++)
		{
			results.push_back(allocator.alloc(i % 2 ? 32 : 2000));

			// for every 10 blocks free the first 5 of them
			if (i % 10 == 4)
			{
				for (size_t j = 0; j < 5; j++)
				{
					allocator.free(results[i - j]);
					results[i - j].ptr = nullptr;
				}
			}
		}
		for (auto& block : results)
		{
			if (block)
			{
				allocator.free(block);
			}
		}
	}
};

template <typename Allocator>
struct Test4
{
	static void test(Allocator& allocator, size_t testSize = 1000)
	{
		std::vector<MemoryBlock> results;
		results.reserve(testSize * 1.1f);

		for (size_t i = 0; i < testSize; ++i)
		{
			results.push_back(allocator.alloc(i % 2 ? 32 : 64));

			if (i % 10 == 0)
			{
				results.push_back(allocator.alloc(4096 * 1024));
			}
			// for every 10 blocks free first 5 of them
			if (i % 10 == 4) {
				for (size_t j = 0; j < 5; j++)
				{
					allocator.free(results[i - j]);
					results[i - j].ptr = nullptr;
				}
			}
		}
		for (auto& block : results)
		{
			if (block)
			{
				allocator.free(block);
			}
		}
	}
};

template <template <typename> typename Tester, typename Allocator>
void executeSingleThreadTest(Allocator& allocator) {
	DefaultAllocator defAllocator;

	auto time1 = timer_nsec();
	Tester<DefaultAllocator>::test(defAllocator);
	auto time2 = timer_nsec();
	const auto defTime = time2 - time1;

	time1 = timer_nsec();
	Tester<Allocator>::test(allocator);
	time2 = timer_nsec();
	const auto yoursTime = time2 - time1;

	std::cout << "Time: " << defTime << "/" << yoursTime << "(" << double(defTime) / double(yoursTime) << ")";
	std::cout << " max mem: " << defAllocator.getMaxUsedMemory() << "/" << allocator.getMaxUsedMemory();
	std::cout << "(" << double(defAllocator.getMaxUsedMemory()) / double(allocator.getMaxUsedMemory()) << ")" << std::endl;
}

int main()
{
	{
		MemoryAllocator custom;
		executeSingleThreadTest<Test1, MemoryAllocator>(custom);
	}

	{
		MemoryAllocator custom;
		executeSingleThreadTest<Test2, MemoryAllocator>(custom);
	}

	{
		MemoryAllocator custom;
		executeSingleThreadTest<Test3, MemoryAllocator>(custom);
	}

	{
		MemoryAllocator custom;
		executeSingleThreadTest<Test4, MemoryAllocator>(custom);
	}

	return 0;
}