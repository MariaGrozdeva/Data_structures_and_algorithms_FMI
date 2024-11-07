#pragma once
#include <iostream>
#include <initializer_list>

template <class T>
class list
{
	struct Node
	{
		Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
		Node(T&& data) : data(std::move(data)), next(nullptr), prev(nullptr) {}

		T data;
		Node* next;
		Node* prev;
	};

public:
	list() = default;
	list(const std::initializer_list<T>& values);

	list(const list<T>& other);
	list<T>& operator=(const list<T>& other);

	list(list<T>&& other) noexcept;
	list<T>& operator=(list<T>&& other) noexcept;

	~list() noexcept;

	void push_front(const T& el);
	void push_front(T&& el);

	void push_back(const T& el);
	void push_back(T&& el);

	void pop_front();
	void pop_back();

	const T& front() const;
	const T& back() const;
	
	T& front(); 
	T& back();
	
	size_t getSize() const;
	bool empty() const;

	void clear();
	
	class DllIterator
	{
	public:
		typedef std::bidirectional_iterator_tag iterator_category;

		DllIterator(list& l, Node* currentElementPtr = nullptr) : l(l), currentElementPtr(currentElementPtr) {}

		T& operator*()
		{
			return currentElementPtr->data;
		}

		T* operator->()
		{
			return &currentElementPtr->data;
		}

		DllIterator& operator++()
		{
			if (currentElementPtr)
			{
				currentElementPtr = currentElementPtr->next;
			}
			return *this;
		}

		DllIterator operator++(int)
		{
			DllIterator copy(*this);
			++(*this);
			return copy;
		}

		DllIterator& operator--()
		{
			if (currentElementPtr)
			{
				currentElementPtr = currentElementPtr->prev;
			}
			else
			{
				currentElementPtr = l.tail;
			}
			return *this;
		}

		DllIterator operator--(int)
		{
			DllIterator copy(*this);
			--(*this);
			return copy;
		}

		bool operator==(const DllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const DllIterator& rhs) const { return !(rhs == *this); }

	private:
		Node* currentElementPtr = nullptr;
		list& l;

		friend class list;
	};
	
	class ConstDllIterator
	{
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		
		ConstDllIterator(const DllIterator& nonConstIter) : l(nonConstIter.l), currentElementPtr(nonConstIter.currentElementPtr) {}
		ConstDllIterator(const list& l, Node* currentElementPtr = nullptr) : l(l), currentElementPtr(currentElementPtr) {}

		const T& operator*() const
		{
			return currentElementPtr->data;
		}

		const T* operator->() const
		{
			return &currentElementPtr->data;
		}

		ConstDllIterator& operator++()
		{
			if (currentElementPtr)
			{
				currentElementPtr = currentElementPtr->next;
			}
			return *this;
		}

		ConstDllIterator operator++(int)
		{
			ConstDllIterator copy(*this);
			++(*this);
			return copy;
		}

		ConstDllIterator& operator--()
		{
			if (currentElementPtr)
			{
				currentElementPtr = currentElementPtr->prev;
			}
			else
			{
				currentElementPtr = l.tail;
			}
			return *this;
		}

		ConstDllIterator operator--(int)
		{
			DllIterator copy(*this);
			--(*this);
			return copy;
		}

		bool operator==(const ConstDllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const ConstDllIterator& rhs) const { return !(rhs == *this); }

	private:
		Node* currentElementPtr = nullptr;
		const list& l;

		friend class list;
	};
	
	DllIterator begin()
	{
		return DllIterator(*this, head);
	}
	DllIterator end()
	{
		return DllIterator(*this, nullptr);
	}
	
	ConstDllIterator cbegin() const
	{
		return ConstDllIterator(*this, head);
	}
	ConstDllIterator cend() const
	{
		return ConstDllIterator(*this, nullptr);
	}
	
	DllIterator insert(const T& element, const ConstDllIterator& it);
	DllIterator insert(T&& element, const ConstDllIterator& it);

	DllIterator erase(const ConstDllIterator& it);

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void copyFrom(const list<T>& other);
	void moveFrom(list<T>&& other);
	void free();
};

template <class T>
void list<T>::push_front(const T& el)
{
	Node* newNode = new Node(el);
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	 	newNode->next = head;
		head->prev = newNode;
	 	head = newNode;   
	}
	size++;
}

template <class T>
void list<T>::push_front(T&& el)
{
	Node* newNode = new Node(std::move(el));
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	 	newNode->next = head;
		head->prev = newNode;
	 	head = newNode;   
	}
	size++;
}

template <class T>
void list<T>::push_back(const T& el)
{
	Node* newNode = new Node(el);
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	    	tail->next = newNode;
		newNode->prev = tail;
	    	tail = newNode;
	}
	size++;
}

template <class T>
void list<T>::push_back(T&& el)
{
	Node* newNode = new Node(std::move(el));
	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
	    	tail->next = newNode;
		newNode->prev = tail;
	    	tail = newNode;
	}
	size++;
}

template <class T>
void list<T>::pop_front()
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
		head->prev = nullptr;
	    	delete toDelete;
	}
    	size--;
}

template <class T>
void list<T>::pop_back()
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
	    	Node* toDelete = tail;
        	tail = tail->prev;
		tail->next = nullptr;
	    	delete toDelete;
	}
    	size--;
}

template <class T>
const T& list<T>::front() const
{
	if (!head)
	{
		throw std::logic_error("Empty list\n");
	}
	return head->data;
}

template <class T>
const T& list<T>::back() const 
{
	if (!tail)
	{
		throw std::logic_error("Empty list\n");
	}
	return tail->data;
}

template <class T>
T& list<T>::front() 
{
	if (!head)
	{
		throw std::logic_error("Empty list\n");
	}
	return head->data;
}

template <class T>
T& list<T>::back() 
{
	if (!tail)
	{
		throw std::logic_error("Empty list\n");
	}
	return tail->data;
}

template <class T>
size_t list<T>::getSize() const
{
    	return size;
}

template <class T>
bool list<T>::empty() const
{
    	return size == 0;
}

template <class T>
void list<T>::clear()
{
	free();
}

template <class T>
class list<T>::DllIterator list<T>::insert(const T& element, const typename list<T>::ConstDllIterator& it)
{
	if (it == cbegin())
    	{
        	push_front(element);
        	return begin();
    	}
    	else if (it == cend())
    	{
        	push_back(element);
        	return DllIterator(*this, tail);
    	}
	
	Node* newNode = new Node(element);
	Node* itNode = it.currentElementPtr;

	newNode->next = itNode;
	newNode->prev = itNode->prev;
	itNode->prev->next = newNode;
	itNode->prev = newNode;
    	size++;
	return DllIterator(*this, newNode);
}

template <class T>
class list<T>::DllIterator list<T>::insert(T&& element, const typename list<T>::ConstDllIterator& it)
{
	if (it == cbegin())
    	{
        	push_front(std::move(element));
        	return begin();
    	}
    	else if (it == cend())
    	{
        	push_back(std::move(element));
        	return DllIterator(*this, tail);
    	}
	
	Node* newNode = new Node(std::move(element));
	Node* itNode = it.currentElementPtr;

	newNode->next = itNode;
	newNode->prev = itNode->prev;
	itNode->prev->next = newNode;
	itNode->prev = newNode;
    	size++;
	return DllIterator(*this, newNode);
}

template <class T>
class list<T>::DllIterator list<T>::erase(const typename list<T>::ConstDllIterator& it)
{
	typename list<T>::ConstDllIterator tempIt = cend();
	if (it == cbegin())
    	{
        	pop_front();
        	return begin();
    	}
    	else if (it == --tempIt)
    	{
        	pop_back();
        	return DllIterator(*this, tail);
    	}
        
	Node* toDelete = it.currentElementPtr;
	if (!toDelete)
	{
		throw std::invalid_argument("Bad iterator\n");
	}

	toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
	
        Node* nextNode = toDelete->next;

        delete toDelete;
        size--;
        return DllIterator(*this, nextNode);
}

template<class T>
list<T>::list(const std::initializer_list<T>& values) : list()
{
    	for (const T& val : values)
    	{
        	push_back(val);
    	}
}

template <class T>
list<T>::list(const list<T>& other) 
{
	copyFrom(other);
}

template <class T>
list<T>& list<T>::operator=(const list<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
list<T>::list(list<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T>
list<T>& list<T>::operator=(list<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T>
list<T>::~list() noexcept
{
	free();
}

template <class T>
void list<T>::copyFrom(const list<T>& other)
{
	Node* iter = other.head;
	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template <class T>
void list<T>::moveFrom(list<T>&& other)
{
	head = other.head;
    	tail = other.tail;
    	size = other.size;
    	other.head = other.tail = nullptr;
    	other.size = 0;
}

template <class T>
void list<T>::free()
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
