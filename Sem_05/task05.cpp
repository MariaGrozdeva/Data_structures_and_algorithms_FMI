#include<iostream>
#include<vector>
#include<stack>
#include<list>

template<class T>
struct Node
{
	T data;
	Node<T>* next;
};

template<class T>
void shuffle(Node<T>* start)
{
	int size = 0; //might pass size as argument too
	Node<T>* iteratorFirst = start;

	while (iteratorFirst)
	{
		++size;
		iteratorFirst = iteratorFirst->next;
	}

	int middle = size / 2 + (size % 2);

	Node<T>* iteratorSecond = start;
	iteratorFirst = start;

	for (int i = 0; i < middle - 1; i++)
	{
		iteratorSecond = iteratorSecond->next;
		iteratorFirst = iteratorFirst->next;
	}
	iteratorSecond = iteratorSecond->next;

	for (int i = middle; i < size; i++)
	{
		Node<T>* nextElement = iteratorSecond->next;
		iteratorSecond->next = start;
		start = iteratorSecond;
		iteratorSecond = nextElement;
	}

	iteratorFirst->next = nullptr;
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

	Node<int>* one = new Node<int>;
	one->next = two;
	two->data = 2;
	one->data = 1;
	shuffle(one);


	while (five)
	{
		std::cout << five->data << " ";
		five = five->next;
	}
	
	delete one;
	delete two;
	delete three;
	delete four;
	delete five;
}
