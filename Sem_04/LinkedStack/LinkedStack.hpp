#include <iostream>
using namespace std;

template <typename T>
class LinkedStack
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data)
		{
			this->data = data;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	LinkedStack();
	LinkedStack(const LinkedStack<T>& other);
	LinkedStack<T>& operator=(const LinkedStack<T>& other);
	~LinkedStack();

private:
	void copyFrom(const LinkedStack<T>& other);
	void free();

public:
	void push(const T& el);
	void pop();
	const T& top();
	bool empty() const;
};

template <typename T>
void LinkedStack<T>::push(const T& el)
{
	Node* newNode = new Node(el);

	if (!head)
	{
		head = tail = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
}
template <typename T>
void LinkedStack<T>::pop()
{
	if (!head)
		throw length_error("Empty stack!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		return;
	}

	Node* toDelete = head;
	head = head->next;
	delete toDelete;
}
template <typename T>
const T& LinkedStack<T>::top()
{
	if (!head)
		throw length_error("Empty stack!");

	return head->data;
}
template <typename T>
bool LinkedStack<T>::empty() const
{
	return head == nullptr;
}

template <typename T>
LinkedStack<T>::LinkedStack()
{
	head = tail = nullptr;
}
template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other)
{
	copyFrom(other);
}
template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
LinkedStack<T>::~LinkedStack()
{
	free();
}

template <typename T>
void LinkedStack<T>::copyFrom(const LinkedStack<T>& other)
{
	if (other.empty())
		return;

	Node* otherIter = other.head;
	head = new Node(otherIter->data);
	Node* thisIter = head;

	do
	{
		otherIter = otherIter->next;

		if (otherIter)
		{
			thisIter->next = new Node(otherIter->data);
			thisIter = thisIter->next;
		}
	} while (otherIter);
}
template <typename T>
void LinkedStack<T>::free()
{
	Node* iter = head;

	while (iter)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}
