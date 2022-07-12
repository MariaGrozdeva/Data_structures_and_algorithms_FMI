#pragma once
#include "TieredVector.hpp"

bool compareTieredVectors(const TieredVector<int>& lhs, const TieredVector<int>& rhs)
{
	if (lhs.getSize() != rhs.getSize())
		return false;
	
	for (size_t i = 0; i < lhs.getSize(); i++)
		if (lhs[i] != rhs[i])
			return false;
	return true;
}

bool test_resize_and_shrink()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 16; i++)
		v1.push_back(i);

	v1.push_back(16); // should resize (size = 17, capacity*capacity = 16)
	if (v1.getSize() != 17)
		return false;

	TieredVector<int> v2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	if (!compareTieredVectors(v1, v2))
		return false;

	for (size_t i = 0; i < 8; i++)
		v1.pop_back();

	v1.pop_back(); // should shrink (size = 8, capacity*capacity = 64)
	if (v1.getSize() != 8)
		return false;	

	v2 = { 0, 1, 2, 3, 4, 5, 6, 7 };
	return compareTieredVectors(v1, v2);
}

bool test_push_back()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 10; i++)
		v1.push_back(i);

	if (v1.getSize() != 10)
		return false;

	TieredVector<int> v2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	return compareTieredVectors(v1, v2);
}

bool test_push_front()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 10; i++)
		v1.push_front(i);

	if (v1.getSize() != 10)
		return false;

	TieredVector<int> v2 = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	return compareTieredVectors(v1, v2);
}

bool test_push_back_push_front()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v1.push_front(i);
	}

	if (v1.getSize() != 20)
		return false;

	TieredVector<int> v2 = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	return compareTieredVectors(v1, v2);
}

bool test_push_and_pop()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 10; i++)
	{
		v1.push_front(i);
		v1.push_back(i);
	}
	for (size_t i = 0; i < 5; i++)
	{
		v1.pop_back();
		v1.pop_front();
	}

	if (v1.getSize() != 10)
		return false;

	TieredVector<int> v2 = { 4, 3, 2, 1, 0, 0, 1, 2, 3, 4};

	return compareTieredVectors(v1, v2);
}

bool test_insert_at()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 100; i++)
		v1.push_back(i);
	for (size_t i = 0; i < 10; i++)
		v1.insertAt(0, 111);
	for (size_t i = 0; i < 10; i++)
		v1.insertAt(v1.getSize(), 555);

	if (v1.getSize() != 120)
		return false;

	TieredVector<int> v2;
	for (size_t i = 0; i < 10; i++)
		v2.push_back(111);
	for (size_t i = 0; i < 100; i++)
		v2.push_back(i);
	for (size_t i = 0; i < 10; i++)
		v2.push_back(555);

	return compareTieredVectors(v1, v2);
}

bool test_erase_at()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 100; i++)
		v1.push_back(i);
	for (size_t i = 0; i < 10; i++)
		v1.eraseAt(0);
	for (size_t i = 0; i < 20; i++)
		v1.eraseAt(v1.getSize() - 1);
	v1.eraseAt(6);

	if (v1.getSize() != 69)
		return false;

	TieredVector<int> v2;
	for (size_t i = 10; i < 16; i++)
		v2.push_back(i);
	for (size_t i = 17; i < 80; i++)
		v2.push_back(i);

	return compareTieredVectors(v1, v2);
}

bool make_empty_then_fill_again()
{
	TieredVector<int> v1;
	for (size_t i = 0; i < 100; i++)
		v1.push_back(i);

	for (size_t i = 0; i < 99; i++)
		v1.eraseAt(1);
	if (v1.getSize() != 1)
		return false;

	v1.eraseAt(0);
	if (!v1.empty())
		return false;

	v1.push_front(10);
	for (size_t i = 1; i < 10; i++)
		v1.insertAt(1, i);

	TieredVector<int> v2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	return compareTieredVectors(v1, v2);
}

void runTests()
{
	std::cout << "Test 1: " << test_resize_and_shrink() << std::endl;
	std::cout << "Test 2: " << test_push_back() << std::endl;
	std::cout << "Test 3: " << test_push_front() << std::endl;
	std::cout << "Test 4: " << test_push_back_push_front() << std::endl;
	std::cout << "Test 5: " << test_push_and_pop() << std::endl;
	std::cout << "Test 6: " << test_insert_at() << std::endl;
	std::cout << "Test 7: " << test_erase_at() << std::endl;
	std::cout << "Test 8: " << make_empty_then_fill_again() << std::endl;
}