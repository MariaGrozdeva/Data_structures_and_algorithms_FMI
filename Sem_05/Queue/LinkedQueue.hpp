#pragma once
#include <iostream>

template <class T>
class queue
{
	struct Node
	{
		Node(const T& data) : data(data), next(nullptr) {}
		Node(T&& data) : data(std::move(data)), next(nullptr) {}

		T data;
		Node* next;
	};

public:
	queue() = default;

	queue(const queue<T>& other);
	queue<T>& operator=(const queue<T>& other);

	queue(queue<T>&& other) noexcept;
	queue<T>& operator=(queue<T>&& other) noexcept;

	~queue() noexcept;

	void push(const T& el);
	void push(T&& el);
	
	template <class... Args>
	T emplace(Args&&... args);

	void pop();

        T& front(); 
	const T& front() const;
	
	T& back(); 
	const T& back() const;
	
	size_t getSize() const;
	bool empty() const;
    
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void copyFrom(const queue<T>& other);
	void moveFrom(queue<T>&& other);
	void free();
};

template <class T>
void queue<T>::push(const T& el)
{
	Node* newNode = new Node(el);
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	    	tail->next = newNode;
	    	tail = newNode;
	}
	size++;
}

template <class T>
void queue<T>::push(T&& el)
{
	Node* newNode = new Node(std::move(el));
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	    	tail->next = newNode;
	    	tail = newNode;
	}
	size++;
}

template <class T>
template <class... Args>
T queue<T>::emplace(Args&&... args)
{
        T newObj(std::forward<Args>(args)...);
        Node* newNode = new Node(newObj);
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	    	tail->next = newNode;
	    	tail = newNode;
	}
	size++;
	return newObj;
}

template <class T>
void queue<T>::pop()
{
	if (!head)
	{
		throw std::logic_error("Empty queue\n");
	}

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
	    	Node* toDelete = head;
        	head = head->next;
	    	delete toDelete;
	}
    	size--;
}

template <class T>
T& queue<T>::front() 
{
	if (!head)
	{
		throw std::logic_error("Empty queue\n");
	}
	return head->data;
}

template <class T>
const T& queue<T>::front() const
{
	if (!head)
	{
		throw std::logic_error("Empty queue\n");
	}
	return head->data;
}

template <class T>
T& queue<T>::back() 
{
	if (!head)
	{
		throw std::logic_error("Empty queue\n");
	}
	return tail->data;
}

template <class T>
const T& queue<T>::back() const
{
	if (!head)
	{
		throw std::logic_error("Empty queue\n");
	}
	return tail->data;
}

template <class T>
size_t queue<T>::getSize() const
{
    	return size;
}

template <class T>
bool queue<T>::empty() const
{
    	return size == 0;
}

template <class T>
queue<T>::queue(const queue<T>& other) 
{
	copyFrom(other);
}

template <class T>
queue<T>& queue<T>::operator=(const queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
queue<T>::queue(queue<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T>
queue<T>& queue<T>::operator=(queue<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T>
queue<T>::~queue() noexcept
{
	free();
}

template <class T>
void queue<T>::copyFrom(const queue<T>& other)
{
	Node* iter = other.head;
	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template <class T>
void queue<T>::moveFrom(queue<T>&& other)
{
	head = other.head;
    	tail = other.tail;
    	size = other.size;
    	other.head = other.tail = nullptr;
    	other.size = 0;
}

template <class T>
void queue<T>::free()
{
	Node* iter = head;
	while (iter)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
	head = tail = nullptr;
	size = 0;
}
