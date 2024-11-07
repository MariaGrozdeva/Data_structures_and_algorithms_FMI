#include <iostream>
#include <utility>

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

template <class T, class PredicateType>
std::pair<Node<T>*, Node<T>*> partition(Node<T>* current, const PredicateType& pred)
{
	Node<T>* trueListBegin = nullptr;
	Node<T>* trueListEnd = nullptr;

	Node<T>* falseListBegin = nullptr;
	Node<T>* falseListEnd = nullptr;

	while (current != nullptr)
	{
		if (pred(current->data))
		{
			push_back(trueListBegin, trueListEnd, current);
		}
		else
		{
			push_back(falseListBegin, falseListEnd, current);
		}
		current = current->next;
	}
	if (trueListEnd)
	{
		trueListEnd->next = nullptr;
	}
	if (falseListEnd)
	{
		falseListEnd->next = nullptr;
	}

	return std::make_pair(trueListBegin, falseListBegin);
}

template <class T>
std::pair<Node<T>*, Node<T>*> concatLists(Node<T>* leftBegin, Node<T>* leftEnd, Node<T>* rightBegin, Node<T>* rightEnd) 
{
	if (leftBegin == nullptr)
	{
	    	return std::make_pair(rightBegin, rightEnd); 
	}
	if (rightBegin == nullptr)
	{
	    	return std::make_pair(leftBegin, leftEnd);
	}

	leftEnd->next = rightBegin;
	return std::make_pair(leftBegin, rightEnd);
}

template <class T>
std::pair<Node<T>*, Node<T>*> quickSort(Node<T>* list)
{
	if (!list || !list->next)
	{
		return std::make_pair(list, list);
	}

	T pivot = list->data;
	std::pair<Node<T>*, Node<T>*> partitionResults = partition(list, [pivot](int el) {return el < pivot; });

	Node<T>* pivotPtr = partitionResults.second;

	std::pair<Node<T>*, Node<T>*> leftToConcat = quickSort(partitionResults.first);
	std::pair<Node<T>*, Node<T>*> rightToConcat = quickSort(partitionResults.second->next); // skip the pivot

	pivotPtr->next = rightToConcat.first; // attach the pivot to the beginning of right
	rightToConcat.first = pivotPtr;
	if (!rightToConcat.second) // the right was empty list, we should concat only the pivot
	{
		rightToConcat.second = pivotPtr;
	}

	return concatLists(leftToConcat.first, leftToConcat.second, rightToConcat.first, rightToConcat.second);
}

int main()
{
	Node<int>* list = new Node<int>{ 23, new Node<int>{5, new Node<int>{22, new Node<int>{5}}} };
	
	std::pair<Node<int>*, Node<int>*> res = quickSort(list);
	list = res.first;
	printList(list);
	freeList(list);
	list = nullptr;
}
