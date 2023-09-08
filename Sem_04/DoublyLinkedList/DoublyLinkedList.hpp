#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node* prev;

		Node(const T& data)
		{
			this->data = data;
			next = nullptr;
			prev = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
	~DoublyLinkedList();

private:
	void copyFrom(const DoublyLinkedList<T>& other);
	void free();

public:
	void push_front(const T& el);
	void push_back(const T& el);

	void pop_front();
	void pop_back();

	const T& front() const;
	const T& back() const;

	bool empty() const;

	template <typename U>
	friend DoublyLinkedList<U> concat(DoublyLinkedList<U>& lhs, DoublyLinkedList<U>& rhs);

	void print() const;
};

template <typename T>
void DoublyLinkedList<T>::push_front(const T& el)
{
	Node* newNode = new Node(el);

	if (!head)
	{
		head = tail = newNode;
		return;
	}

	newNode->next = head;
	head->prev = newNode;
	head = newNode;
}
template <typename T>
void DoublyLinkedList<T>::push_back(const T& el)
{
	Node* newNode = new Node(el);

	if (!tail)
	{
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;
}

template <typename T>
void DoublyLinkedList<T>::pop_front()
{
	if (!head)
		throw length_error("Empty list!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		return;
	}

	head->next->prev = nullptr;

	Node* toDelete = head;
	head = head->next;
	delete toDelete;
}
template <typename T>
void DoublyLinkedList<T>::pop_back()
{
	if (!head)
		throw length_error("Empty list!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		return;
	}

	tail->prev->next = nullptr;

	Node* toDelete = tail;
	tail = tail->prev;
	delete toDelete;
}

template <typename T>
const T& DoublyLinkedList<T>::front() const
{
	if (!head)
		throw length_error("Empty list!");

	return head->data;
}
template <typename T>
const T& DoublyLinkedList<T>::back() const
{
	if (!tail)
		throw length_error("Empty list!");

	return tail->data;
}

template <typename T>
bool DoublyLinkedList<T>::empty() const
{
	return head == nullptr;
}

template <typename T>
DoublyLinkedList<T> concat(DoublyLinkedList<T>& lhs, DoublyLinkedList<T>& rhs)
{
	DoublyLinkedList<T> result;
	
	if (!lhs.head && !rhs.head)
	{
		return result;
	}
	if (!lhs.head)
	{
		result.head = rhs.head;
		result.tail = rhs.tail;
	}
	else if (!rhs.head)
	{
		result.head = lhs.head;
		result.tail = lhs.tail;
	}
	else
	{
		lhs.tail->next = rhs.head;
		rhs.head->prev = lhs.tail;
		result.head = lhs.head;
		result.tail = rhs.tail;
	}

	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

	return result;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	head = tail = nullptr;
}
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
	copyFrom(other);
}
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	free();
}

template <typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other)
{
	Node* iter = other.head;

	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}
template <typename T>
void DoublyLinkedList<T>::free()
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

template <typename T>
void DoublyLinkedList<T>::print() const
{
	Node* iter = head;

	while (iter)
	{
		cout << iter->data << ' ';
		if (iter->next)
			cout << "<->" << ' ';
		iter = iter->next;
	}
}
