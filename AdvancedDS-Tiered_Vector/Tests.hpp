#pragma once
#include "TieredVector.hpp"

bool testInitialize()
{
	TieredVector<int> tv = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	if (tv.size() != 10)
		return false;

	for (size_t i = 0; i < tv.size(); i++)
		if (tv[i] != i)
			return false;
	return true;
}

bool testInsertBack()
{
	TieredVector<int> tv;

	for (size_t i = 0; i <= 200; i++)
		tv.insert(i);
	if (tv.size() != 201)
		return false;

	for (size_t i = 0; i < tv.size(); i++)
		if (tv[i] != i)
			return false;
	return true;
}

bool testInsertFront()
{
	TieredVector<int> tv;

	for (size_t i = 200; i != 0; i--)
		tv.insert(i);
	if (tv.size() != 200)
		return false;

	for (size_t i = 0; i < tv.size(); i++)
		if (tv[i] != i + 1)
			return false;
	return true;
}

bool testInsertBackAndFront()
{
	TieredVector<int> tv;

	for (size_t i = 0; i < 150; i += 2)
	{
		tv.insert(i);
		tv.insert(300 - i);
		tv.insert(300 - i - 1);
		tv.insert(i + 1);
	}
	tv.insert(150);
	if (tv.size() != 301)
		return false;

	for (size_t i = 0; i < tv.size(); i++)
		if (tv[i] != i)
			return false;
	return true;
}

bool testEraseBackAndFront()
{
	TieredVector<int> tv;

	for (size_t i = 0; i < 300; i++)
		tv.insert(i);

	for (size_t i = 0; i < 50; i++)
	{
		tv.erase(i);
		tv.erase(299 - i);
	}

	if (tv.size() != 200)
		return false;

	for (size_t i = 0; i < tv.size(); i++)
		if (tv[i] != i + 50)
			return false;
	return true;
}

bool testEraseAllEvenNumbers()
{
	TieredVector<int> tv;

	for (size_t i = 0; i < 300; i++)
		tv.insert(i);

	for (size_t i = 0; i < 300; i += 2)
		tv.erase(i);

	if (tv.size() != 150)
		return false;

	for (size_t i = 0; i < tv.size(); i++)
		if (tv[i] % 2 != 1)
			return false;
	return true;
}

bool testEraseRandom()
{
	TieredVector<int> tv;

	for (size_t i = 0; i < 300; i++)
		tv.insert(i);

	for (size_t i = 0; i < 50; i++)
	{
		tv.erase(i);
		tv.erase(100 + i);
		tv.erase(299 - i);
	}

	if (tv.size() != 150)
		return false;

	for (size_t i = 0; i < 50; i++)
		if (tv[i] != i + 50)
			return false;
	for (size_t i = 0; i < 50; i++)
		if (tv[i + 50] != i + 150)
			return false;
	for (size_t i = 0; i < 50; i++)
		if (tv[i + 100] != i + 200)
			return false;
	return true;
}

bool testMakeEmptyAndThenRefill()
{
	TieredVector<int> tv;
	for (size_t i = 1; i <= 200; i++)
		tv.insert(i);
	if (tv.size() != 200)
		return false;

	for (size_t i = 200; i != 0; i--)
		tv.erase(i);
	if (tv.size() != 0)
		return false;

	for (size_t i = 200; i != 0; i--)
		tv.insert(i);
	if (tv.size() != 200)
		return false;

	return true;
}

bool testMakeEmptyAndThenRefill2()
{
	TieredVector<int> tv;
	for (size_t i = 1; i <= 200; i++)
		tv.insert(i);
	if (tv.size() != 200)
		return false;

	for (size_t i = 1; i <= 200; i++)
		tv.erase(i);
	if (tv.size() != 0)
		return false;

	for (size_t i = 200; i != 0; i--)
		tv.insert(i);
	if (tv.size() != 200)
		return false;

	return true;
}

bool testCopy()
{
	TieredVector<int> tv1;
	for (size_t i = 10; i < 20; i++)
		tv1.insert(i);
	for (int i = 9; i >= 0; i--)
		tv1.insert(i);

	TieredVector<int> tv2(tv1);

	TieredVector<int> tv3;
	tv3.insert(1);
	tv3 = tv2;

	tv2.erase(5);

	if (tv1.size() != 20)
		return false;

	for (size_t i = 0; i < 20; i++)
		if (tv1[i] != i)
			return false;

	if (tv2.size() != 19)
		return false;

	for (size_t i = 0; i < 19; i++)
	{
		if (i < 5 && tv2[i] != i)
			return false;
		if (i >= 5 && tv2[i] - 1 != i)
			return false;
	}

	tv3.insert(20);
	if (tv3.size() != 21)
		return false;

	for (size_t i = 0; i < 21; i++)
		if (tv3[i] != i)
			return false;

	if (tv1.size() != 20)
		return false;

	for (size_t i = 0; i < 20; i++)
		if (tv1[i] != i)
			return false;

	return true;
}

void runTests()
{
	std::cout << "Test 1:  " << testInitialize() << std::endl;
	std::cout << "Test 2:  " << testInsertBack() << std::endl;
	std::cout << "Test 3:  " << testInsertFront() << std::endl;
	std::cout << "Test 4:  " << testInsertBackAndFront() << std::endl;
	std::cout << "Test 5:  " << testEraseBackAndFront() << std::endl;
	std::cout << "Test 6:  " << testEraseAllEvenNumbers() << std::endl;
	std::cout << "Test 7:  " << testEraseRandom() << std::endl;
	std::cout << "Test 8:  " << testMakeEmptyAndThenRefill() << std::endl;
	std::cout << "Test 9:  " << testMakeEmptyAndThenRefill2() << std::endl;
	std::cout << "Test 10: " << testCopy() << std::endl;
}