#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue
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
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T>& other);
	LinkedQueue<T>& operator=(const LinkedQueue<T>& other);
	~LinkedQueue();

private:
	void copyFrom(const LinkedQueue<T>& other);
	void free();

public:
	void enqueue(const T& el);
	void dequeue();
	const T& peek();
	bool empty() const;
};

template <typename T>
void LinkedQueue<T>::enqueue(const T& el)
{
	Node* newNode = new Node(el);

	if (!tail)
	{
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
}
template <typename T>
void LinkedQueue<T>::dequeue()
{
	if (!head)
		throw length_error("Empty queue!");

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
const T& LinkedQueue<T>::peek()
{
	if (!head)
		throw length_error("Empty queue!");

	return head->data;
}
template <typename T>
bool LinkedQueue<T>::empty() const
{
	return head == nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	head = tail = nullptr;
}
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
{
	copyFrom(other);
}
template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	free();
}

template <typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue<T>& other)
{
	Node* iter = other.head;

	while (iter)
	{
		enqueue(iter->data);
		iter = iter->next;
	}
}
template <typename T>
void LinkedQueue<T>::free()
{
	Node* iter = head;

	while (iter)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}

	head = tail = nullptr;
}