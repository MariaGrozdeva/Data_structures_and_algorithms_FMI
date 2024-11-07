#include <iostream>
#include "list.hpp"

bool testInitialization()
{
    list<int> list;
    if (list.empty() && list.getSize() == 0)
    {
        std::cout << "testInitialization passed\n";
        return true;
    }
    else
    {
        std::cout << "testInitialization failed\n";
        return false;
    }
}

bool testPushBackAndBack()
{
    list<int> list;
    list.push_back(10);
    if (!list.empty() && list.getSize() == 1 && list.back() == 10)
    {
        list.push_back(20);
        if (list.getSize() == 2 && list.back() == 20)
        {
            std::cout << "testPushBackAndBack passed\n";
            return true;
        }
    }
    std::cout << "testPushBackAndBack failed\n";
    return false;
}

bool testPushFrontAndFront()
{
    list<int> list;
    list.push_front(10);
    if (!list.empty() && list.getSize() == 1 && list.front() == 10)
    {
        list.push_front(20);
        if (list.getSize() == 2 && list.front() == 20)
        {
            std::cout << "testPushFrontAndFront passed\n";
            return true;
        }
    }
    std::cout << "testPushFrontAndFront failed\n";
    return false;
}

bool testPopBack()
{
    list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    if (list.getSize() == 1 && list.back() == 10)
    {
        list.pop_back();
        if (list.empty())
        {
            std::cout << "testPopBack passed\n";
            return true;
        }
    }
    std::cout << "testPopBack failed\n";
    return false;
}

bool testPopFront()
{
    list<int> list;
    list.push_front(10);
    list.push_front(20);
    list.pop_front();
    if (list.getSize() == 1 && list.front() == 10)
    {
        list.pop_front();
        if (list.empty())
        {
            std::cout << "testPopFront passed\n";
            return true;
        }
    }
    std::cout << "testPopFront failed\n";
    return false;
}

bool testInsertAndRemove()
{
    list<int> list;
    list.push_back(10);
    list.push_back(30);
    auto it = list.begin();
    ++it;

    list.insert(20, it);
    
    std::cout << list.getSize() << " " << *list.begin() << " " << *++list.begin() << " " << *++(++list.begin()) << std::endl;
    if (list.getSize() == 3 && *++list.begin() == 20)
    {
        list.erase(list.begin());
        if (list.getSize() == 2 && list.front() == 20)
        {
            std::cout << "testInsertAndRemove passed\n";
            return true;
        }
    }
    std::cout << "testInsertAndRemove failed\n";
    return false;
}

bool testIteratorTraversal()
{
    list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.begin();
    if (*it == 10 && *(++it) == 20 && *(++it) == 30)
    {
        std::cout << "testIteratorTraversal passed\n";
        return true;
    }
    std::cout << "testIteratorTraversal failed\n";
    return false;
}

bool testFrontOnEmptyList()
{
    list<int> list;
    try
    {
        list.front();
        std::cout << "testFrontOnEmptyList failed\n";
        return false;
    }
    catch (...)
    {
        std::cout << "testFrontOnEmptyList passed\n";
        return true;
    }
}

bool testBackOnEmptyList()
{
    list<int> list;
    try
    {
        list.back();
        std::cout << "testBackOnEmptyList failed\n";
        return false;
    }
    catch (...)
    {
        std::cout << "testBackOnEmptyList passed\n";
        return true;
    }
}

bool testPushBackMultipleElements()
{
    list<int> list;
    for (int i = 1; i <= 10; ++i)
    {
        list.push_back(i);
    }
    bool passed = list.getSize() == 10 && list.back() == 10;
    std::cout << (passed ? "testPushBackMultipleElements passed\n" : "testPushBackMultipleElements failed\n");
    return passed;
}

bool testPushFrontMultipleElements()
{
    list<int> list;
    for (int i = 1; i <= 10; ++i)
    {
        list.push_front(i);
    }
    bool passed = list.getSize() == 10 && list.front() == 10;
    std::cout << (passed ? "testPushFrontMultipleElements passed\n" : "testPushFrontMultipleElements failed\n");
    return passed;
}

bool testClearList()
{
    list<int> list;
    for (int i = 0; i < 5; ++i)
    {
        list.push_back(i);
    }
    list.clear();
    bool passed = list.empty() && list.getSize() == 0;
    std::cout << (passed ? "testClearList passed\n" : "testClearList failed\n");
    return passed;
}

bool testCopyConstructor()
{
    list<int> l;
    l.push_back(10);
    l.push_back(20);
    list<int> copyList(l);
    bool passed = (copyList.getSize() == 2) && (copyList.front() == 10) && (copyList.back() == 20);
    std::cout << (passed ? "testCopyConstructor passed\n" : "testCopyConstructor failed\n");
    return passed;
}

bool testAssignmentOperator()
{
    list<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list<int> list2;
    list2.push_back(30);
    list2 = list1;

    bool passed = (list2.getSize() == 2) && (list2.front() == 10) && (list2.back() == 20);
    std::cout << (passed ? "testAssignmentOperator passed\n" : "testAssignmentOperator failed\n");
    return passed;
}

bool testIteratorIncrement()
{
    list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.begin();
    if (*it == 10 && *(++it) == 20 && *(++it) == 30)
    {
        std::cout << "testIteratorIncrement passed\n";
        return true;
    }
    std::cout << "testIteratorIncrement failed\n";
    return false;
}

bool testIteratorDecrement()
{
    list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    auto it = list.end();
    --it;
    if (*it == 30 && *(--it) == 20 && *(--it) == 10)
    {
        std::cout << "testIteratorDecrement passed\n";
        return true;
    }
    std::cout << "testIteratorDecrement failed\n";
    return false;
}

int main()
{
    int passedTests = 0;
    passedTests += testInitialization();
    passedTests += testPushBackAndBack();
    passedTests += testPushFrontAndFront();
    passedTests += testPopBack();
    passedTests += testPopFront();
    passedTests += testInsertAndRemove();
    passedTests += testIteratorTraversal();
    passedTests += testFrontOnEmptyList();
    passedTests += testBackOnEmptyList();
    passedTests += testPushBackMultipleElements();
    passedTests += testPushFrontMultipleElements();
    passedTests += testClearList();
    passedTests += testCopyConstructor();
    passedTests += testAssignmentOperator();
    passedTests += testIteratorIncrement();
    passedTests += testIteratorDecrement();

    std::cout << passedTests << " out of 16 tests passed\n";
    return 0;
}
