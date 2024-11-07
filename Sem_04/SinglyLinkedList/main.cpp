#include "list.hpp"
#include <cassert>

bool testPushFront()
{
    forward_list<int> list;
    list.push_front(10);
    list.push_front(20);
    return list.front() == 20 && list.back() == 10 && list.getSize() == 2;
}

bool testPushBack()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    return list.front() == 10 && list.back() == 20 && list.getSize() == 2;
}

bool testPopFront()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_front();
    return list.front() == 20 && list.getSize() == 1;
}

bool testFrontBack()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    return list.front() == 10 && list.back() == 20;
}

bool testConstFrontBack()
{
    const forward_list<int> list = []()
    {
        forward_list<int> temp;
        temp.push_back(10);
        temp.push_back(20);
        return temp;
    }();
    return list.front() == 10 && list.back() == 20;
}

bool testGetSizeIsEmpty()
{
    forward_list<int> list;
    bool emptyBefore = list.empty();
    list.push_back(10);
    bool notEmptyAfter = !list.empty();
    bool correctSize = list.getSize() == 1;
    return emptyBefore && notEmptyAfter && correctSize;
}

bool testConcat()
{
    forward_list<int> list1, list2;
    list1.push_back(1);
    list1.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    list1.append(list2);
    return list1.front() == 1 && list1.back() == 4 && list1.getSize() == 4;
}

bool testIterator()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        sum += *it;
    }
    return sum == 60;
}

bool testConstIterator()
{
    const forward_list<int> list = []()
    {
        forward_list<int> temp;
        temp.push_back(10);
        temp.push_back(20);
        temp.push_back(30);
        return temp;
    }();

    int sum = 0;
    for (auto it = list.cbegin(); it != list.cend(); ++it)
    {
        sum += *it;
    }
    return sum == 60;
}

bool testInsertAfter()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    auto it = list.begin();
    list.insert_after(15, it);
    ++it;
    return *it == 15 && list.getSize() == 3;
}

bool testRemoveAfter()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.begin();
    list.erase_after(it);
    return *it == 10 && *(++it) == 30 && list.getSize() == 2;
}

bool testPushFrontMultipleElements()
{
    forward_list<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    return list.front() == 30 && list.back() == 10 && list.getSize() == 3;
}

bool testPushBackMultipleElements()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    return list.front() == 10 && list.back() == 30 && list.getSize() == 3;
}

bool testPopFrontUntilEmpty()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_front();
    list.pop_front();
    list.pop_front();
    return list.empty() && list.getSize() == 0;
}

bool testMixedPushFrontAndBack()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_front(20);
    list.push_back(30);
    list.push_front(40);

    bool testPass = list.front() == 40 && list.back() == 30 && list.getSize() == 4;

    list.pop_front();
    list.pop_front();
    testPass = testPass && (list.front() == 10 && list.back() == 30);

    return testPass;
}

bool testRemoveAfterVariousPositions()
{
    forward_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    auto it = list.begin();
    it = list.erase_after(it);
    
    auto itCopy(it);
    bool testPass = list.getSize() == 3 && list.front() == 10 && *(it) == 30 && *(++itCopy) == 40;
    it = list.erase_after(it);
    testPass &= list.back() == 30 && list.getSize() == 2 && it == list.end();

    return testPass;
}

bool testConcatLargeLists()
{
    forward_list<int> list1, list2;
    for (int i = 1; i <= 100; ++i)
    {
        list1.push_back(i);
    }
    for (int i = 101; i <= 200; ++i)
    {
        list2.push_back(i);
    }

    list1.append(list2);

    bool testPass = list1.getSize() == 200 && list1.front() == 1 && list1.back() == 200;

    auto it = list1.begin();
    for (int i = 1; i <= 200; ++i, ++it)
    {
        testPass = testPass && (*it == i);
    }
    return testPass;
}

bool testIteratorOnEmptyList()
{
    forward_list<int> list;
    bool testPass = true;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        testPass = false;
    }
    return testPass && list.empty();
}

bool testIteratorIncrementAndComparison()
{
    forward_list<int> list;
    for (int i = 1; i <= 5; ++i)
    {
        list.push_back(i);
    }

    auto it = list.begin();
    it++;
    it++;
    bool testPass = *it == 3;

    it++;
    auto it2 = ++it;;
    testPass = testPass && (*it2 == 5);

    return testPass;
}

bool testConstIteratorUsage()
{
    const forward_list<int> list = []()
    {
        forward_list<int> temp;
        for (int i = 1; i <= 5; ++i)
        {
            temp.push_back(i);
        }
        return temp;
    }();

    bool testPass = true;
    int expectedValue = 1;
    for (auto it = list.cbegin(); it != list.cend(); ++it)
    {
        testPass = testPass && (*it == expectedValue++);
    }
    return testPass && expectedValue == 6;
}

bool testMap()
{
    forward_list<int> list;
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++)
    {
        list.push_back((int)i);
    }

    list.map([](int& x){x *= 2;});

    size_t i = 0;
    for (auto it = list.begin(); it != list.end(); it++, i++)
    {
        assert(*it == (int)(2 * i));
    }
    assert(list.back() == 198);

    list.push_front(0);
    list.push_back(200);
    assert(list.front() == 0);
    assert(list.back() == 200);
    
    return true;
}

bool testFilter()
{
    forward_list<int> list;
    
    list.push_back(3);
    list.filter([](int x){return x % 3 == 0;});
    assert(list.getSize() == 1);
    list.pop_front();
    
    list.push_back(2);
    list.filter([](int x){return x % 3 == 0;});
    assert(list.getSize() == 0);
    
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++)
    {
        list.push_front((int)i);
    }

    list.filter([](int x){return x % 3;});

    assert(list.getSize() == 66);
    for (auto it = list.begin(); it != list.end(); it++)
    {
        assert(*it % 3);
    }
    assert(list.back() == 1);

    list.push_front(0);
    list.push_back(200);
    assert(list.front() == 0);
    assert(list.back() == 200);
    
    return true;
}

int main()
{
    std::cout << "Test Push Front: " << testPushFront() << std::endl;
    std::cout << "Test Push Back: " << testPushBack() << std::endl;
    std::cout << "Test Pop Front: " << testPopFront() << std::endl;
    std::cout << "Test Front and Back: " << testFrontBack() << std::endl;
    std::cout << "Test Const Front and Back: " << testConstFrontBack() << std::endl;
    std::cout << "Test Get Size and Is Empty: " << testGetSizeIsEmpty() << std::endl;
    std::cout << "Test Concat: " << testConcat() << std::endl;
    std::cout << "Test Iterator: " << testIterator() << std::endl;
    std::cout << "Test Const Iterator: " << testConstIterator() << std::endl;
    std::cout << "Test Insert After: " << testInsertAfter() << std::endl;
    std::cout << "Test Remove After: " << testRemoveAfter() << std::endl;
    std::cout << "Test Push Front Multiple Elements: " << testPushFrontMultipleElements() << std::endl;
    std::cout << "Test Push Back Multiple Elements: " << testPushBackMultipleElements() << std::endl;
    std::cout << "Test Pop Front Until Empty: " << testPopFrontUntilEmpty() << std::endl;
    std::cout << "Test Mixed Push Front and Back: " << testMixedPushFrontAndBack() << std::endl;
    std::cout << "Test Remove After Various Positions: " << testRemoveAfterVariousPositions() << std::endl;
    std::cout << "Test Concat Large Lists: " << testConcatLargeLists() << std::endl;
    std::cout << "Test Iterator on Empty List: " << testIteratorOnEmptyList() << std::endl;
    std::cout << "Test Iterator Increment and Comparison: " << testIteratorIncrementAndComparison() << std::endl;
    std::cout << "Test Const Iterator Usage: " << testConstIteratorUsage() << std::endl;
    std::cout << "Test Map: " << testMap() << std::endl;
    std::cout << "Test Filter: " << testFilter() << std::endl;

    return 0;
}
