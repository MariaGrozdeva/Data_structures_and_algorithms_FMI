#include "FixedDeque.hpp"
#include "Deque.hpp"

template <typename T>
class TieredVector
{
private:
	Deque<FixedDeque<T>> deques;
	size_t capacity;

	size_t elementsCount = 0;
	size_t firstDequeSize = 0;
	size_t lastDequeSize = 0;

	void copyFrom(const TieredVector<T>&);
	void moveFrom(TieredVector<T>&&);

	void resize(size_t);

	void incrementFirstDequeSize();
	void incrementLastDequeSize();
	void decrementFirstDequeSize();
	void decrementLastDequeSize();

	size_t pushPopFromDown(const T&);
	size_t pushPopFromUp(const T&);

	int findPotentialDeque(const T&) const;
	const T& getElementByIndexAndDequeIndex(size_t, size_t&) const;

public:
	TieredVector();
	TieredVector(size_t);
	TieredVector(std::initializer_list<T>);

	TieredVector(const TieredVector<T>&);
	TieredVector(TieredVector<T>&&);
	TieredVector<T>& operator=(const TieredVector<T>&);
	TieredVector<T>& operator=(TieredVector<T>&&);

	void insert(const T&); // O(sqrt(n))
	bool erase(const T&); // O(sqrt(n))
	bool contains(const T&); // O(log(sqrt(n)))

	const T& operator[](size_t) const;

	size_t size() const;
};
		
template <typename T>
void TieredVector<T>::insert(const T& el)
{
	if (elementsCount == 0)
	{
		deques.back().insert(el, capacity);
		incrementLastDequeSize();
	}
	else if (deques[deques.size() / 2].back(capacity) > el)
	{
		if (firstDequeSize == capacity)
		{
			if (deques.size() == capacity)
				resize(capacity * 2);

			if (firstDequeSize == capacity)
			{
				deques.push_front(FixedDeque<T>(capacity));
				firstDequeSize = 0;
			}
		}

		size_t index = pushPopFromUp(el);
		deques[index].insert(el, capacity);
		incrementFirstDequeSize();
	}
	else
	{
		if (lastDequeSize == capacity)
		{
			if (deques.size() == capacity)
				resize(capacity * 2);

			if (lastDequeSize == capacity)
			{
				deques.push_back(FixedDeque<T>(capacity));
				lastDequeSize = 0;
			}
		}

		size_t index = pushPopFromDown(el);
		deques[index].insert(el, capacity);
		incrementLastDequeSize();
	}
	elementsCount++;
}
template <typename T>
bool TieredVector<T>::erase(const T& el)
{
	assert(elementsCount > 0);

	int index = findPotentialDeque(el);
	if (index == -1)
		return false;

	bool successfulRemoval = deques[index].erase(el, capacity);
	if (!successfulRemoval)
		return false;

	if (index == 0)
	{
		decrementFirstDequeSize();
		if (firstDequeSize == 0 && deques.size() > 1)
		{
			deques.pop_front();
			if (deques.size() == 1)
				firstDequeSize = lastDequeSize;
			else
				firstDequeSize = capacity;
		}
	}
	else if (index == deques.size() - 1)
	{
		decrementLastDequeSize();
		if (lastDequeSize == 0 && deques.size() > 1)
		{
			deques.pop_back();
			if (deques.size() == 1)
				lastDequeSize = firstDequeSize;
			else
				lastDequeSize = capacity;
		}
	}
	else if (index < deques.size() / 2)
	{
		for (size_t i = index; i != 0; i--)
		{
			deques[i].push_front(deques[i - 1].back(capacity), capacity);
			deques[i - 1].pop_back(capacity);
		}
		decrementFirstDequeSize();
		if (firstDequeSize == 0 && deques.size() > 1)
		{
			deques.pop_front();
			if (deques.size() == 1)
				firstDequeSize = lastDequeSize;
			else
				firstDequeSize = capacity;
		}
	}
	else
	{
		for (size_t i = index; i < deques.size() - 1; i++)
		{
			deques[i].push_back(deques[i + 1].front(), capacity);
			deques[i + 1].pop_front(capacity);
		}
		decrementLastDequeSize();
		if (lastDequeSize == 0 && deques.size() > 1)
		{
			deques.pop_back();
			if (deques.size() == 1)
				lastDequeSize = firstDequeSize;
			else
				lastDequeSize = capacity;
		}
	}

	elementsCount--;
	if (elementsCount * 8 == capacity * capacity)
		resize(capacity / 2);
	return true;
}
template <typename T>
bool TieredVector<T>::contains(const T& el)
{
	if (elementsCount == 0)
		return false;

	int index = findPotentialDeque(el);
	if (index == -1)
		return false;

	return deques[index].contains(el, capacity) != -1;
}

template <typename T>
const T& TieredVector<T>::operator[](size_t index) const
{
	size_t dequeIndex = 0;
	return getElementByIndexAndDequeIndex(index, dequeIndex);
}

template <typename T>
size_t TieredVector<T>::size() const
{
	return elementsCount;
}

template <typename T>
size_t TieredVector<T>::pushPopFromDown(const T& element)
{
	size_t i = deques.size() - 1;
	for (; i > 1 && deques[i - 1].back(capacity) > element; i--)
	{
		deques[i].push_front(deques[i - 1].back(capacity), capacity);
		deques[i - 1].pop_back(capacity);
	}
	return i;
}
template <typename T>
size_t TieredVector<T>::pushPopFromUp(const T& element)
{
	size_t i = 0;
	for (; i < deques.size() - 1 && deques[i + 1].front() < element; i++)
	{
		deques[i].push_back(deques[i + 1].front(), capacity);
		deques[i + 1].pop_front(capacity);
	}
	return i;
}

template <typename T>
int TieredVector<T>::findPotentialDeque(const T& el) const
{
	size_t low = 0;
	size_t high = deques.size() - 1;

	while (low <= high)
	{
		size_t mid = (low + high) / 2;

		if (deques[mid].front() == el || deques[mid].back(capacity) == el)
			return mid;

		if (deques[mid].front() > el)
			high = mid - 1;
		else if (deques[mid].back(capacity) < el)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}
template <typename T>
const T& TieredVector<T>::getElementByIndexAndDequeIndex(size_t index, size_t& dequeIndex) const
{
	assert(index < elementsCount);

	if (index < firstDequeSize)
	{
		dequeIndex = 0;
		return deques[0].getElementByIndex(index, capacity);
	}
	index -= firstDequeSize;

	dequeIndex = index / capacity + 1;
	return deques[dequeIndex].getElementByIndex(index % capacity, capacity);
}

template <typename T>
void TieredVector<T>::incrementFirstDequeSize()
{
	assert(firstDequeSize < capacity);
	firstDequeSize++;
	if (deques.size() == 1)
		lastDequeSize++;
}
template <typename T>
void TieredVector<T>::incrementLastDequeSize()
{
	assert(lastDequeSize < capacity);
	lastDequeSize++;
	if (deques.size() == 1)
		firstDequeSize++;
}
template <typename T>
void TieredVector<T>::decrementFirstDequeSize()
{
	assert(firstDequeSize > 0);
	firstDequeSize--;
	if (deques.size() == 1)
		lastDequeSize--;
}
template <typename T>
void TieredVector<T>::decrementLastDequeSize()
{
	assert(lastDequeSize > 0);
	lastDequeSize--;
	if (deques.size() == 1)
		firstDequeSize--;
}

template <typename T>
void TieredVector<T>::resize(size_t newCapacity)
{
	TieredVector resized(newCapacity);
	size_t lastDequeUsed = 0;

	for (size_t i = 0; i < elementsCount; i++)
	{
		size_t currentDeque;
		resized.insert(getElementByIndexAndDequeIndex(i, currentDeque));

		if (currentDeque != lastDequeUsed)
			deques[lastDequeUsed].free();
	}
	*this = std::move(resized);
}

template <typename T>
TieredVector<T>::TieredVector() : TieredVector(4)
{}
template <typename T>
TieredVector<T>::TieredVector(size_t capacity)
{
	this->capacity = capacity;
	deques.setCapacity(capacity);
	deques.push_back(FixedDeque<T>(capacity));
}
template <typename T>
TieredVector<T>::TieredVector(std::initializer_list<T> iList) : TieredVector()
{
	for (const T& el : iList)
		insert(el);
}

template <typename T>
TieredVector<T>::TieredVector(const TieredVector<T>& other)
{
	copyFrom(other);
}
template <typename T>
TieredVector<T>::TieredVector(TieredVector<T>&& other)
{
	moveFrom(std::move(other));
}
template <typename T>
TieredVector<T>& TieredVector<T>::operator=(const TieredVector<T>& other)
{
	if (this != &other)
	{
		deques.free();
		copyFrom(other);
	}
	return *this;
}
template <typename T>
TieredVector<T>& TieredVector<T>::operator=(TieredVector<T>&& other)
{
	if (this != &other)
	{
		deques.free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
void TieredVector<T>::copyFrom(const TieredVector<T>& other)
{
	capacity = other.capacity;
	elementsCount = other.elementsCount;
	firstDequeSize = other.firstDequeSize;
	lastDequeSize = other.lastDequeSize;

	deques.setCapacity(other.deques.getCapacity());
	for (size_t i = 0; i < other.deques.size(); i++)
	{
		deques.push_back(FixedDeque<T>());
		deques.back().copyFrom(other.deques[i], capacity);
	}
}
template <typename T>
void TieredVector<T>::moveFrom(TieredVector<T>&& other)
{
	capacity = other.capacity;
	elementsCount = other.elementsCount;
	firstDequeSize = other.firstDequeSize;
	lastDequeSize = other.lastDequeSize;

	deques.setCapacity(other.deques.getCapacity());
	for (size_t i = 0; i < other.deques.size(); i++)
		deques.push_back(FixedDeque<T>(std::move(other.deques[i])));

	other.capacity = other.elementsCount = other.firstDequeSize = other.lastDequeSize = 0;
}