#include "AVL_DoS.hpp"

bool testInitialize()
{
	AVL<int> avl = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	for (size_t i = 0; i <= 10; i++)
		if (avl[i] != i)
			return false;
	return true;
}

bool testInsertFrontAndBack()
{
	AVL<int> t;

	for (int i = 100; i >= 0; i--)
		t.insertAt(0, i);
	for (size_t i = 101; i <= 200; i++)
		t.insertAt(t.size(), i);
	
	for (int i = 0; i <= 200; i++)
		if (t[i] != i)
			return false;
	return true;
}

bool testInsertAtRandom()
{
	AVL<int> t;

	for (int i = 50; i >= 0; i -= 2)
		t.insertAt(0, i);
	for (int i = 49; i >= 0; i -= 2)
		t.insertAt(i / 2 + 1, i);

	for (int i = 0; i < 50; i++)
		if (t[i] != i)
			return false;
	return true;
}

bool testRemoveFirstAndLast()
{
	AVL<int> t;

	for (int i = 100; i >= 0; i--)
		t.insertAt(0, i);

	for (size_t i = 0; i < 5; i++)
	{
		t.eraseAt(0);
		t.eraseAt(t.size() - 1);
	}

	for (size_t i = 5; i < 95; i++)
		if (t[i - 5] != i)
			return false;
	return true;
}

bool testRemoveAtRandom()
{
	AVL<int> t;

	for (size_t i = 0; i <= 100; i++)
		t.insertAt(t.size(), i);

	for (int i = 100; i >= 0; i-=2)
		t.eraseAt(i);

	for (size_t i = 1; i < 100; i += 2)
		if (t[i / 2] != i)
			return false;
	return true;
}

bool insertAndEraseMixedTest()
{
	AVL<int> t;

	for (int i = 100; i >= 0; i--)
		t.insertAt(0, i);

	for (int i = 100; i >= 0; i -= 2)
		t.eraseAt(i);

	for (size_t i = 0; i < 100; i += 2)
		t.insertAt(i, i);

	for (size_t i = 0; i < t.size(); i++)
		if (t[i] != i)
			return false;
	return true;
}

bool testBackAndFront()
{
	AVL<int> t;

	for (size_t i = 0; i <= 100; i++)
		t.insertAt(t.size(), i);

	for (size_t i = 0; i < 5; i++)
	{
		int back = t.back();
		if (back != 100 - i)
			return false;
		t.eraseAt(t.size() - 1);

		int front = t.front();
		if (front != i)
			return false;
		t.eraseAt(0);
	}

	return true;
}

bool testPushBackAndPushFront()
{
	AVL<int> t;

	for (size_t i = 1; i <= 50; i++)
	{
		t.push_back(i);
		t.push_front(i);
	}

	for (int i = 50; i >= 1; i--)
		if (t[50 - i] != i)
			return false;
	for (size_t i = 1; i <= 50; i++)
		if (t[i + 49] != i)
			return false;

	return true;
}

bool testPopBackAndPopFront()
{
	AVL<int> t;

	for (size_t i = 1; i <= 50; i++)
		t.push_back(i);

	for (size_t i = 0; i < 10; i++)
	{
		t.pop_back();
		t.pop_front();
	}

	for (size_t i = 11; i <= 40; i++)
		if (t[i - 11] != i)
			return false;
	return true;
}

bool mixedTest()
{
	AVL<int> t;

	for (size_t i = 0; i < 100; i++)
		t.insertAt(i, i);

	for (int i = 50; i >= 0; i--)
		t.insertAt(50, 100*i);

	for (int i = 50; i >= 0; i--)
		t.eraseAt(50);

	for (size_t i = 0; i < t.size(); i++)
		if (t[i] != i)
			return false;
	
	t.eraseAt(10);

	for (size_t i = 0; i < 10; i++)
		if (t[i] != i)
			return false;
	for (size_t i = 10; i < t.size(); i++)
		if (t[i] != i + 1)
			return false;

	return true;
}

bool makeEmptyAndRefill()
{
	AVL<int> t;

	for (size_t i = 0; i < 100; i++)
		t.insertAt(i, i);
	t.insertAt(0, 100);

	for (size_t i = 0; i <= 100; i++)
		t.eraseAt(0);

	if (!t.empty())
		return false;

	for (size_t i = 0; i <= 1000; i++)
		t.insertAt(0, i);

	for (size_t i = 0; i <= 1000; i++)
		if (t[i] != 1000 - i)
			return false;
	return true;
}

void runTests()
{
	std::cout << "Test 1:  " << testInitialize() << std::endl;
	std::cout << "Test 2:  " << testInsertFrontAndBack() << std::endl;
	std::cout << "Test 3:  " << testInsertAtRandom() << std::endl;
	std::cout << "Test 4:  " << testRemoveFirstAndLast() << std::endl;
	std::cout << "Test 5:  " << testRemoveAtRandom() << std::endl;
	std::cout << "Test 6:  " << insertAndEraseMixedTest() << std::endl;
	std::cout << "Test 7:  " << testBackAndFront() << std::endl;
	std::cout << "Test 8:  " << testPushBackAndPushFront() << std::endl;
	std::cout << "Test 9:  " << testPopBackAndPopFront() << std::endl;
	std::cout << "Test 10: " << mixedTest() << std::endl;
	std::cout << "Test 11: " << makeEmptyAndRefill() << std::endl;
}