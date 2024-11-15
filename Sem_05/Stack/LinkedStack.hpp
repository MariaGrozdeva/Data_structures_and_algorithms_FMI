#pragma once
#include <iostream>

template <class T>
class stack
{
	struct Node
	{
		Node(const T& data) : data(data), next(nullptr) {}
		Node(T&& data) : data(std::move(data)), next(nullptr) {}

		T data;
		Node* next;
	};

public:
	stack() = default;

	stack(const stack<T>& other);
	stack<T>& operator=(const stack<T>& other);

	stack(stack<T>&& other) noexcept;
	stack<T>& operator=(stack<T>&& other) noexcept;

	~stack() noexcept;

	void push(const T& el);
	void push(T&& el);
	
	template <class... Args>
	T emplace(Args&&... args);

	void pop();

	const T& top() const;
	T& top(); 
	
	size_t getSize() const;
	bool empty() const;
    
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void copyFrom(const stack<T>& other);
	void moveFrom(stack<T>&& other);
	void free();
};

template <class T>
void stack<T>::push(const T& el)
{
	Node* newNode = new Node(el);
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	 	newNode->next = head;
	 	head = newNode;   
	}
	size++;
}

template <class T>
void stack<T>::push(T&& el)
{
	Node* newNode = new Node(std::move(el));
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	 	newNode->next = head;
	 	head = newNode;   
	}
	size++;
}

template <class T>
template <class... Args>
T stack<T>::emplace(Args&&... args)
{
        T newObj(std::forward<Args>(args)...);
        Node* newNode = new Node(newObj);
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	 	newNode->next = head;
	 	head = newNode;   
	}
	size++;
	return newObj;
}

template <class T>
void stack<T>::pop()
{
	if (!head)
	{
		throw std::logic_error("Empty stack\n");
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
const T& stack<T>::top() const
{
	if (!head)
	{
		throw std::logic_error("Empty stack\n");
	}
	return head->data;
}

template <class T>
T& stack<T>::top() 
{
	if (!head)
	{
		throw std::logic_error("Empty stack\n");
	}
	return head->data;
}

template <class T>
size_t stack<T>::getSize() const
{
    	return size;
}

template <class T>
bool stack<T>::empty() const
{
    	return size == 0;
}

template <class T>
stack<T>::stack(const stack<T>& other) 
{
	copyFrom(other);
}

template <class T>
stack<T>& stack<T>::operator=(const stack<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
stack<T>::stack(stack<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T>
stack<T>& stack<T>::operator=(stack<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T>
stack<T>::~stack() noexcept
{
	free();
}

template <class T>
void stack<T>::copyFrom(const stack<T>& other)
{
	Node* iter = other.head;
	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template <class T>
void stack<T>::moveFrom(stack<T>&& other)
{
	head = other.head;
    	tail = other.tail;
    	size = other.size;
    	other.head = other.tail = nullptr;
    	other.size = 0;
}

template <class T>
void stack<T>::free()
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
