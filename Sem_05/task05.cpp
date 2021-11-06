#include<iostream>
#include<stack>
#include<list>

template<class T>
struct Node
{
	T data;
	Node<T>* next;
};

template <typename T>
int getNumOfNodes(Node<T>* list)
{
	Node<T>* iter = list;
	int countOfNodes = 0;

	while (iter != nullptr)
	{
		countOfNodes++;
		iter = iter->next;
	}

	return countOfNodes;
}

template <typename T>
Node<T>* getMiddle(Node<T>* list)
{
	Node<T>* slowIter = list;
	Node<T>* fastIter = list;

	while (fastIter != nullptr && fastIter->next != nullptr)
	{
		slowIter = slowIter->next;
		fastIter = fastIter->next->next;
	}

	if (getNumOfNodes<T>(list) % 2 == 0)
		return slowIter;
	else
		return slowIter->next;
}

template<class T>
void shuffle(Node<T>* start)
{
	Node<T>* middleNode = getMiddle(start);
	Node<T>* beginningOfFirstHalf = start;
	Node<T>* endOfFirstHalf = start;

	Node<T>* iter = start->next;

	std::stack<Node<T>*> nodesToReverse;

	while (iter != middleNode) 
	{
		endOfFirstHalf->next = iter;
		endOfFirstHalf = endOfFirstHalf->next;

		iter = iter->next;
	}

	while (iter != nullptr)
	{
		nodesToReverse.push(iter);
		iter = iter->next;
	}

	Node<T>* firstOfListToReturn = nodesToReverse.top();
	Node<T>* listToReturn = nodesToReverse.top();

	nodesToReverse.pop();

	while (!nodesToReverse.empty())
	{
		listToReturn->next = nodesToReverse.top();
		listToReturn = listToReturn->next;
		nodesToReverse.pop();
	}

	listToReturn->next = beginningOfFirstHalf;

	endOfFirstHalf->next = nullptr;
}

int main()
{
	Node<int>* five = new Node<int>;
	five->data = 5;
	five->next = nullptr;
  
	Node<int>* four = new Node<int>;
	four->data = 4;
	four->next = five;
  
	Node<int>* three = new Node<int>;
	three->data = 3;
	three->next = four;
  
	Node<int>* two = new Node<int>;
	two->next = three;
  two->data = 2;
  
	Node<int>* one = new Node<int>;
	one->next = two;
	one->data = 1;
  
	shuffle(one);


	while (five)
	{
		std::cout << five->data << " ";
		five = five->next;
	}
  
  delete one, two, three, four, five; 
}
