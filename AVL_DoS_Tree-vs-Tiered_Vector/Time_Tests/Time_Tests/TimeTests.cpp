#include "AVL.hpp"
#include "TieredVector.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <random>

template <typename T>
void testPushBack(const std::string& name)
{
	std::ofstream file("pushBackInto" + name + ".txt");
	if (!file.is_open())
		throw "Error";

	const int maxOperations = 1'000'000;
	int dontOptimize = 0x1234;

	file << "Count:, Average:, Per element:" << std::endl;

	using namespace std::literals;
	const auto tester = [&](unsigned int elements)
	{
		const int maxRepeats = maxOperations / elements;
		const int repeats = std::min(maxRepeats, 100);
		auto total = 0ns;

		for (size_t r = 0; r < repeats; r++)
		{
			T container;

			std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
			for (size_t c = 0; c < elements; c++)
			{
				container.insert(c);
			}
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			const auto duration = end - start;

			total += duration;
			dontOptimize ^= container.size();
		}

		const auto average = std::chrono::duration_cast<std::chrono::nanoseconds>(total).count() / repeats;
		const auto perElement = average / elements;
		file << elements << ',' << average << ',' << perElement << std::endl;

		if (elements % 1100 == 0)
			std::cout << elements << ',' << average << ',' << perElement << std::endl;
	};

	for (size_t elements = 1; elements < 1000; elements += 1)
	{
		tester(elements);
	}
	for (size_t elements = 1000; elements < 10'000; elements += 10)
	{
		tester(elements);
	}
	for (size_t elements = 10'000; elements < 1'000'000; elements += 1000)
	{
		tester(elements);
	}
	std::cout << dontOptimize;
}
template <typename T>
void testInsert(const std::string& name)
{
	std::ofstream file("insertInto" + name + ".txt");
	if (!file.is_open())
		throw "Error";

	const int maxOperations = 1'000'000;
	int dontOptimize = 0x1234;

	file << "Count:, Average:, Per element:" << std::endl;

	using namespace std::literals;
	const auto tester = [&](unsigned int elements)
	{
		const int maxRepeats = maxOperations / elements;
		const int repeats = std::min(maxRepeats, 100);
		auto total = 0ns;

		for (size_t r = 0; r < repeats; r++)
		{
			T container;

			std::mt19937 rand(5);
			std::uniform_int_distribution<int> ud(0, elements);

			std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
			for (size_t c = 0; c < elements; c++)
			{
				container.insert(ud(rand));
			}
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			const auto duration = end - start;

			total += duration;
			dontOptimize ^= container.size();
		}

		const auto average = std::chrono::duration_cast<std::chrono::nanoseconds>(total).count() / repeats;
		const auto perElement = average / elements;
		file << elements << ',' << average << ',' << perElement << std::endl;

		if (elements % 1100 == 0)
			std::cout << elements << ',' << average << ',' << perElement << std::endl;
	};

	for (size_t elements = 1; elements < 1000; elements += 1)
	{
		tester(elements);
	}
	for (size_t elements = 1000; elements < 10'000; elements += 10)
	{
		tester(elements);
	}
	for (size_t elements = 10'000; elements < 1'000'000; elements += 1000)
	{
		tester(elements);
	}
	std::cout << dontOptimize;
}

template <typename T>
void testPopFront(const std::string& name)
{
	std::ofstream file("popFrontFrom" + name + ".txt");
	if (!file.is_open())
		throw "Error";

	const int maxOperations = 1'000'000;
	int dontOptimize = 0x1234;

	file << "Count:, Average:, Per element:" << std::endl;

	using namespace std::literals;
	const auto tester = [&](unsigned int elements)
	{
		const int maxRepeats = maxOperations / elements;
		const int repeats = std::min(maxRepeats, 100);
		auto total = 0ns;

		for (size_t r = 0; r < repeats; r++)
		{
			T container;
			for (size_t c = 0; c < elements; c++) // for this test the elements in the container don't matter
			{
				container.insert(c);
			}

			std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
			for (size_t c = 0; c < elements; c++)
			{
				container.erase(c);
			}
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			const auto duration = end - start;

			total += duration;
			dontOptimize ^= container.size();
		}

		const auto average = std::chrono::duration_cast<std::chrono::nanoseconds>(total).count() / repeats;
		const auto perElement = average / elements;
		file << elements << ',' << average << ',' << perElement << std::endl;

		if (elements % 1100 == 0)
			std::cout << elements << ',' << average << ',' << perElement << std::endl;
	};

	for (size_t elements = 1; elements < 1000; elements += 1)
	{
		tester(elements);
	}
	for (size_t elements = 1000; elements < 10'000; elements += 10)
	{
		tester(elements);
	}
	for (size_t elements = 10'000; elements < 1'000'000; elements += 1000)
	{
		tester(elements);
	}
	std::cout << dontOptimize;
}
template <typename T>
void testErase(const std::string& name)
{
	std::ofstream file("eraseFrom" + name + ".txt");
	if (!file.is_open())
		throw "Error";

	const int maxOperations = 1'000'000;
	int dontOptimize = 0x1234;

	file << "Count:, Average:, Per element:" << std::endl;

	using namespace std::literals;
	const auto tester = [&](unsigned int elements)
	{
		const int maxRepeats = maxOperations / elements;
		const int repeats = std::min(maxRepeats, 100);
		auto total = 0ns;

		for (size_t r = 0; r < repeats; r++)
		{
			std::mt19937 rand(5);
			std::uniform_int_distribution<int> ud(0, elements);

			std::vector<int> v;
			for (size_t c = 0; c < elements; c++)
			{
				v.push_back(ud(rand));
			}

			T container;
			for (size_t c = 0; c < elements; c++)
			{
				container.insert(v[c]);
			}

			std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
			for (size_t c = 0; c < elements; c++)
			{
				container.erase(v[c]);
			}
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			const auto duration = end - start;

			total += duration;
			dontOptimize ^= container.size();
		}

		const auto average = std::chrono::duration_cast<std::chrono::nanoseconds>(total).count() / repeats;
		const auto perElement = average / elements;
		file << elements << ',' << average << ',' << perElement << std::endl;

		if (elements % 1100 == 0)
			std::cout << elements << ',' << average << ',' << perElement << std::endl;
	};

	for (size_t elements = 1; elements < 1000; elements += 1)
	{
		tester(elements);
	}
	for (size_t elements = 1000; elements < 10'000; elements += 10)
	{
		tester(elements);
	}
	for (size_t elements = 10'000; elements < 1'000'000; elements += 1000)
	{
		tester(elements);
	}
	std::cout << dontOptimize;
}

template <typename T>
void testIndex(const std::string& name)
{
	std::ofstream file("index" + name + ".txt");
	if (!file.is_open())
		throw "Error";

	const int maxOperations = 1'000'000;
	int dontOptimize;

	file << "Count:, Average:, Per element:" << std::endl;

	using namespace std::literals;
	const auto tester = [&](unsigned int elements)
	{
		const int maxRepeats = maxOperations / elements;
		const int repeats = std::min(maxRepeats, 100);
		auto total = 0ns;

		for (size_t r = 0; r < repeats; r++)
		{
			T container;
			for (size_t c = 0; c < elements; c++) // for this test the elements in the container don't matter
			{
				container.insert(c);
			}

			std::mt19937 rand(5);
			std::uniform_int_distribution<int> ud(0, elements - 1);

			std::vector<int> v;
			for (size_t c = 0; c < elements; c++) // generate random indices in [0...elements-1]
			{
				v.push_back(ud(rand));
			}

			std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
			for (size_t c = 0; c < elements; c++)
			{
				dontOptimize = container[v[c]]; // get element at random index
			}
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			const auto duration = end - start;

			total += duration;
			dontOptimize ^= container.size();
		}

		const auto average = std::chrono::duration_cast<std::chrono::nanoseconds>(total).count() / repeats;
		const auto perElement = average / elements;
		file << elements << ',' << average << ',' << perElement << std::endl;

		if (elements % 1100 == 0)
			std::cout << elements << ',' << average << ',' << perElement << std::endl;
	};

	for (size_t elements = 1; elements < 1000; elements += 1)
	{
		tester(elements);
	}
	for (size_t elements = 1000; elements < 10'000; elements += 10)
	{
		tester(elements);
	}
	for (size_t elements = 10'000; elements < 1'000'000; elements += 1000)
	{
		tester(elements);
	}
	std::cout << dontOptimize;
}

int main()
{
	testIndex<AVL<int>>("AVL");
	testIndex<TieredVector<int>>("TieredVector");
}