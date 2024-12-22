#include "AVL.hpp"

bool testInitialize()
{
	AVL<int> avl = { 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10 };
	if (avl.size() != 11)
		return false;

	for (size_t i = 0; i < avl.size(); i++)
		if (avl[i] != i)
			return false;
	return true;
}

bool testInsertWithOnlyLeftRotations()
{
	AVL<int> avl;

	for (size_t i = 0; i <= 200; i++)
		avl.insert(i);
	if (avl.size() != 201)
		return false;
	
	for (size_t i = 0; i < avl.size(); i++)
		if (avl[i] != i)
			return false;
	return true;
}

bool testInsertWithOnlyRightRotations()
{
	AVL<int> avl;

	for (size_t i = 200; i != 0; i--)
		avl.insert(i);
	if (avl.size() != 200)
		return false;

	for (size_t i = 0; i < avl.size(); i++)
		if (avl[i] != i + 1)
			return false;
	return true;
}

bool testInsertWithLeftRightRotationsAndRightLeftRotations()
{
	AVL<int> avl;

	for (size_t i = 0; i != 300; i += 3)
	{
		avl.insert(i);
		avl.insert(i + 2);
		avl.insert(i + 1);
	}
	for (size_t i = 300; i != 600; i += 3)
	{
		avl.insert(i + 2);
		avl.insert(i);
		avl.insert(i + 1);
	}
	if (avl.size() != 600)
		return false;

	for (size_t i = 0; i < avl.size(); i++)
		if (avl[i] != i)
			return false;
	return true;
}

bool testEraseOnlyLeavesAndNodesWithOneChild()
{
	AVL<int> avl;

	for (size_t i = 0; i < 300; i++)
		avl.insert(i);

	for (size_t i = 0; i < 50; i++)
	{
		avl.erase(i);
		avl.erase(299 - i);
	}

	if (avl.size() != 200)
		return false;

	for (size_t i = 0; i < avl.size(); i++)
		if (avl[i] != i + 50)
			return false;
	return true;
}

bool testEraseNodesWithTwoChildren()
{
	AVL<int> avl;

	for (size_t i = 0; i < 300; i++)
		avl.insert(i);

	for (size_t i = 0; i < 100; i++)
		avl.erase(i + 100);

	if (avl.size() != 200)
		return false;

	for (size_t i = 0; i < 100; i++)
		if (avl[i] != i)
			return false;
	for (size_t i = 100; i < 200; i++)
		if (avl[i] != i + 100)
			return false;
	return true;
}

bool testEraseRandom()
{
	AVL<int> avl;

	for (size_t i = 0; i < 300; i++)
		avl.insert(i);

	for (size_t i = 0; i < 50; i++)
	{
		avl.erase(i);
		avl.erase(100 + i);
		avl.erase(299 - i);
	}

	if (avl.size() != 150)
		return false;

	for (size_t i = 0; i < 50; i++)
		if (avl[i] != i + 50)
			return false;
	for (size_t i = 0; i < 50; i++)
		if (avl[i + 50] != i + 150)
			return false;
	for (size_t i = 0; i < 50; i++)
		if (avl[i + 100] != i + 200)
			return false;
	return true;
}

bool testCopy()
{
	AVL<int> avl;
	for (size_t i = 0; i <= 200; i++)
		avl.insert(i);
	if (avl.size() != 201)
		return false;

	AVL<int> avl2(avl);
	if (avl.size() != avl2.size())
		return false;
	for (size_t i = 0; i < avl2.size(); i++)
		if (avl[i] != avl2[i])
			return false;

	AVL<int> avl3 = { 1, 2, 3 };
	avl3 = avl2;
	if (avl2.size() != avl3.size())
		return false;
	for (size_t i = 0; i < avl3.size(); i++)
		if (avl2[i] != avl3[i])
			return false;

	return true;
}

bool testRank()
{
        AVL<int> avl = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        for (size_t i = 0; i < avl.size(); i++)
                if (avl.rank(i) != i)
                        return false;
        if (avl.rank(15) != -1)
                return false;

        return true;
}

void runTests()
{
	std::cout << "Test 1: " << testInitialize() << std::endl;
	std::cout << "Test 2: " << testInsertWithOnlyLeftRotations() << std::endl;
	std::cout << "Test 3: " << testInsertWithOnlyRightRotations() << std::endl;
	std::cout << "Test 4: " << testInsertWithLeftRightRotationsAndRightLeftRotations() << std::endl;
	std::cout << "Test 5: " << testEraseOnlyLeavesAndNodesWithOneChild() << std::endl;
	std::cout << "Test 6: " << testEraseNodesWithTwoChildren() << std::endl;
	std::cout << "Test 7: " << testEraseRandom() << std::endl;
	std::cout << "Test 8: " << testCopy() << std::endl;
	std::cout << "Test 9: " << testRank() << std::endl;
}
