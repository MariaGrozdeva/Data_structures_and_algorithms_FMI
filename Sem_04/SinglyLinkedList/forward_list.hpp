#pragma once
#include <iostream>
#include <initializer_list>

template <class T>
class forward_list
{
	struct Node
	{
		Node(const T& data) : data(data), next(nullptr) {}
		Node(T&& data) : data(std::move(data)), next(nullptr) {}

		T data;
		Node* next;
	};

public:
	forward_list() = default;
	forward_list(const std::initializer_list<T>& values);

	forward_list(const forward_list<T>& other);
	forward_list<T>& operator=(const forward_list<T>& other);

	forward_list(forward_list<T>&& other) noexcept;
	forward_list<T>& operator=(forward_list<T>&& other) noexcept;

	~forward_list() noexcept;

	void push_front(const T& el);
	void push_front(T&& el);

	void push_back(const T& el);
	void push_back(T&& el);

	void pop_front();

	const T& front() const;
	const T& back() const;
	
	T& front(); 
	T& back();
	
	size_t getSize() const;
	bool empty() const;
	
	void append(forward_list<T> other);

	void reverse();

 	template<class Func>
	void map(const Func& func);

    	template<class Func>
	void filter(const Func& predicate);
	
	class SllIterator
	{
	public:
		typedef std::forward_iterator_tag iterator_category;

		SllIterator(Node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		T& operator*()
		{
			return currentElementPtr->data;
		}

		T* operator->()
		{
			return &currentElementPtr->data;
		}

		SllIterator& operator++()
		{
			if (currentElementPtr)
			{
				currentElementPtr = currentElementPtr->next;
			}
			return *this;
		}

		SllIterator operator++(int)
		{
			SllIterator copy(*this);
			++(*this);
			return copy;
		}

		bool operator==(const SllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const SllIterator& rhs) const { return !(rhs == *this); }

	private:
		Node* currentElementPtr;
		friend class forward_list;
	};
	
	class ConstSllIterator
	{
	public:
		typedef std::forward_iterator_tag iterator_category;
		
		ConstSllIterator(const SllIterator& nonConstIter) : currentElementPtr(nonConstIter.currentElementPtr) {}
		ConstSllIterator(Node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		const T& operator*() const
		{
			return currentElementPtr->data;
		}

		const T* operator->() const
		{
			return &currentElementPtr->data;
		}

		ConstSllIterator& operator++()
		{
			if (currentElementPtr)
			{
				currentElementPtr = currentElementPtr->next;
			}
			return *this;
		}

		ConstSllIterator operator++(int)
		{
			ConstSllIterator copy(*this);
			++(*this);
			return copy;
		}

		bool operator==(const ConstSllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const ConstSllIterator& rhs) const { return !(rhs == *this); }

	private:
		Node* currentElementPtr;
		friend class forward_list;
	};
	
	SllIterator begin()
	{
		return SllIterator(head);
	}
	SllIterator end()
	{
		return SllIterator(nullptr);
	}
	
	ConstSllIterator cbegin() const
	{
		return ConstSllIterator(head);
	}
	ConstSllIterator cend() const
	{
		return ConstSllIterator(nullptr);
	}
	
	SllIterator insert_after(const T& element, const ConstSllIterator& it);
	SllIterator insert_after(T&& element, const ConstSllIterator& it);

	SllIterator erase_after(const ConstSllIterator& it);

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void copyFrom(const forward_list<T>& other);
	void moveFrom(forward_list<T>&& other);
	void free();
};

template <class T>
void forward_list<T>::push_front(const T& el)
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
void forward_list<T>::push_front(T&& el)
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
void forward_list<T>::push_back(const T& el)
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
void forward_list<T>::push_back(T&& el)
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
void forward_list<T>::pop_front()
{
	if (!head)
	{
		throw std::logic_error("Empty list\n");
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
const T& forward_list<T>::front() const
{
	if (!head)
	{
		throw std::logic_error("Empty list\n");
	}
	return head->data;
}

template <class T>
const T& forward_list<T>::back() const 
{
	if (!tail)
	{
		throw std::logic_error("Empty list\n");
	}
	return tail->data;
}

template <class T>
T& forward_list<T>::front() 
{
	if (!head)
	{
		throw std::logic_error("Empty list\n");
	}
	return head->data;
}

template <class T>
T& forward_list<T>::back() 
{
	if (!tail)
	{
		throw std::logic_error("Empty list\n");
	}
	return tail->data;
}

template <class T>
size_t forward_list<T>::getSize() const
{
    	return size;
}

template <class T>
bool forward_list<T>::empty() const
{
    	return size == 0;
}

template <class T>
void forward_list<T>::append(forward_list<T> other)
{
	if (tail)
	{
        	tail->next = other.head;
    	}
    	else
	{
        	head = other.head;
	}
	
    	tail = other.tail;
    	size += other.size;
    	other.head = other.tail = nullptr;
}

template <class T>
void forward_list<T>::reverse()
{
    	if (size < 2)
	{
        	return;
    	}

    	Node* current = head;
    	Node* prev = nullptr;
    	Node* next = nullptr;
    	tail = head;

    	while (current != nullptr)
	{
        	next = current->next;
        	current->next = prev;
        	prev = current;
        	current = next;
    	}
	head = prev;
}

template <class T>
template <class Func>
void forward_list<T>::map(const Func& func)
{
	for (forward_list<T>::SllIterator it = begin(); it != end(); it++)
	{
		func(*it);
	}
}

template <class T>
template <class Func>
void forward_list<T>::filter(const Func& predicate)
{
	Node* trueListHead = nullptr;
	Node* trueListCurrent = nullptr;
	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr)
	{
		if (predicate(current->data))
		{
			if (!trueListHead)
			{
				trueListHead = trueListCurrent = current;
			}
			else
			{
				trueListCurrent->next = current;
				trueListCurrent = trueListCurrent->next;
			}
			previous = current;
			current = current->next;
		}
		else
		{
			Node* toDelete = current;
			if (previous)
			{
				previous->next = current->next;
			}
			else
			{
				head = current->next;
			}
			current = current->next;
			delete toDelete;
			--size;
		}
	}
	if (trueListCurrent)
	{
		trueListCurrent->next = nullptr;
		tail = trueListCurrent;
	}
	else
	{
		head = tail = nullptr;
	}
}

template <class T>
class forward_list<T>::SllIterator forward_list<T>::insert_after(const T& element, const typename forward_list<T>::ConstSllIterator& it)
{
	if (it == end())
	{
        	return end();
	}
	
	Node* newNode = new Node(element);
	Node* itNode = it.currentElementPtr;

	newNode->next = itNode->next;
	itNode->next = newNode;
    	size++;
	return forward_list<T>::SllIterator(newNode);
}

template <class T>
class forward_list<T>::SllIterator forward_list<T>::insert_after(T&& element, const typename forward_list<T>::ConstSllIterator& it)
{
	if (it == end())
	{
        	return end();
	}
	
	Node* newNode = new Node(std::move(element));
	Node* itNode = it.currentElementPtr;

	newNode->next = itNode->next;
	itNode->next = newNode;
    	size++;
	return forward_list<T>::SllIterator(newNode);
}

template <class T>
class forward_list<T>::SllIterator forward_list<T>::erase_after(const typename forward_list<T>::ConstSllIterator& it)
{
    	if (it == end() || size == 1)
	{
        	return end();
	}
        
	typename forward_list<T>::ConstSllIterator itCopy = it;
	Node* toDelete = (++itCopy).currentElementPtr;
	Node* newNext = toDelete->next;
	it.currentElementPtr->next = newNext;
	if (toDelete == tail)
	{
	    	tail = it.currentElementPtr;
	}
	delete toDelete;
	size--;
	return forward_list<T>::SllIterator(newNext);
}

template<class T>
forward_list<T>::forward_list(const std::initializer_list<T>& values) : forward_list()
{
    	for (const T& val : values)
    	{
        	push_back(val);
    	}
}

template <class T>
forward_list<T>::forward_list(const forward_list<T>& other) 
{
	copyFrom(other);
}

template <class T>
forward_list<T>& forward_list<T>::operator=(const forward_list<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
forward_list<T>::forward_list(forward_list<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T>
forward_list<T>& forward_list<T>::operator=(forward_list<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T>
forward_list<T>::~forward_list() noexcept
{
	free();
}

template <class T>
void forward_list<T>::copyFrom(const forward_list<T>& other)
{
	Node* iter = other.head;
	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template <class T>
void forward_list<T>::moveFrom(forward_list<T>&& other)
{
	head = other.head;
    	tail = other.tail;
    	size = other.size;
    	other.head = other.tail = nullptr;
    	other.size = 0;
}

template <class T>
void forward_list<T>::free()
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
