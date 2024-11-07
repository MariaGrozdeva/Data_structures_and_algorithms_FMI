#include <iostream>

template <class T>
struct Node
{
	T data;
	Node<T>* next = nullptr;
	
	Node(const T& data, Node<T>* next = nullptr) : data(data), next(next) {}
};

template <class T>
void printList(Node<T>* iter)
{
	while (iter)
	{
		std::cout << iter->data;
		if (iter->next)
		{
			std::cout << " -> ";
		}
		iter = iter->next;
	}
}

template <class T>
void freeList(Node<T>* iter)
{
	while (iter)
	{
		Node<T>* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}

template <class T>
void push_back(Node<T>*& begin, Node<T>*& end, Node<T>* toAdd)
{
	if (begin == nullptr)
	{
		begin = end = toAdd;
	}
	else
	{
		end->next = toAdd;
		end = toAdd;
	}
}

template <class T>
Node<T>* mergeLists(Node<T>* first, Node<T>* second)
{
	Node<T>* resultBegin = nullptr, *resultEnd = nullptr;
	while (first && second)
	{
		if (first->data < second->data)
		{
			push_back(resultBegin, resultEnd, first);
			first = first->next;
		}
		else
		{
			push_back(resultBegin, resultEnd, second);
			second = second->next;
		}
	}
	if (!first)
	{
		push_back(resultBegin, resultEnd, second);
	}
	else
	{
		push_back(resultBegin, resultEnd, first);
	}
	return resultBegin;
}

template <class T>
Node<T>* getMid(Node<T>* iter)
{
    	Node<T>* slow = iter;
    	Node<T>* fast = iter->next;
    
    	while (fast && fast->next)
    	{
        	slow = slow->next;
        	fast = fast->next->next;
    	}
    	return slow;
}

template <class T>
Node<T>* mergeSort(Node<T>* list)
{
    	if (!list || !list->next) 
    	{
        	return list;
    	}
    
    	Node<T>* mid = getMid(list);
    	Node<T>* left = list;
    	Node<T>* right = mid->next;
    	mid->next = nullptr;
    
    	left = mergeSort(left);
    	right = mergeSort(right);
    
    	return mergeLists(left, right);
}

int main()
{
	Node<int>* list = new Node<int>{ 23, new Node<int>{5, new Node<int>{22, new Node<int>{5}}} };
	
	list = mergeSort(list);
	printList(list);
	freeList(list);
	list = nullptr;
}
