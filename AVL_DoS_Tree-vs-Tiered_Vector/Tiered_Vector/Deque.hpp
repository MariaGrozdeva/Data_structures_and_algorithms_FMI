#pragma once
#include <iostream>
#include <cassert>

template <typename T>
class Deque
{
private:
	T* data;

	size_t elementsCount;
	size_t capacity;

	size_t head; // index of the first element
	size_t tail; // index of the last element + 1

	void copyFrom(const Deque<T>&);
	void moveFrom(Deque<T>&&);

	void movePosition(size_t&, bool) const;

public:
	Deque() = default;
	Deque(const Deque<T>&);
	Deque(Deque<T>&&);
	Deque<T>& operator=(const Deque<T>&);
	Deque<T>& operator=(Deque<T>&&);
	~Deque();

	void free();

	void push_back(const T&);
	void push_back(T&&);
	void push_front(const T&);
	void push_front(T&&);

	void pop_back();
	void pop_front();

	const T& back() const;
	const T& front() const;
	T& back();
	T& front();

	const T& operator[](size_t) const;
	T& operator[](size_t);

	bool empty() const;
	size_t size() const;

	void setCapacity(size_t);
	size_t getCapacity() const;
};

template <typename T>
void Deque<T>::push_back(const T& el)
{
	data[tail] = el;
	movePosition(tail, true);
	elementsCount++;
}
template <typename T>
void Deque<T>::push_back(T&& el)
{
	data[tail] = std::move(el);
	movePosition(tail, true);
	elementsCount++;
}
template <typename T>
void Deque<T>::push_front(const T& el)
{
	movePosition(head, false);
	data[head] = el;
	elementsCount++;
}
template <typename T>
void Deque<T>::push_front(T&& el)
{
	movePosition(head, false);
	data[head] = std::move(el);
	elementsCount++;
}

template <typename T>
void Deque<T>::pop_back()
{
	if (empty())
		throw std::length_error("Empty deque!");

	movePosition(tail, false);
	elementsCount--;
}
template <typename T>
void Deque<T>::pop_front()
{
	if (empty())
		throw std::length_error("Empty deque!");

	movePosition(head, true);
	elementsCount--;
}

template <typename T>
const T& Deque<T>::back() const
{
	if (empty())
		throw std::length_error("Empty deque!");

	size_t lastElement = tail; movePosition(lastElement, false);
	return data[lastElement];
}
template <typename T>
const T& Deque<T>::front() const
{
	if (empty())
		throw std::length_error("Empty deque!");

	return data[head];
}
template <typename T>
T& Deque<T>::back()
{
	if (empty())
		throw std::length_error("Empty deque!");

	size_t lastElement = tail; movePosition(lastElement, false);
	return data[lastElement];
}
template <typename T>
T& Deque<T>::front()
{
	if (empty())
		throw std::length_error("Empty deque!");

	return data[head];
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const
{
	assert(index < elementsCount);
	return data[(head + index) % capacity];
}
template <typename T>
T& Deque<T>::operator[](size_t index)
{
	assert(index < elementsCount);
	return data[(head + index) % capacity];
}

template <typename T>
bool Deque<T>::empty() const
{
	return elementsCount == 0;
}
template <typename T>
size_t Deque<T>::size() const
{
	return elementsCount;
}

template <typename T>
void Deque<T>::setCapacity(size_t capacity)
{
	delete[] data;

	elementsCount = 0;
	this->capacity = capacity;
	data = new T[capacity];

	head = tail = 0;
}
template <typename T>
size_t Deque<T>::getCapacity() const
{
	return capacity;
}

template <typename T>
void Deque<T>::movePosition(size_t& currPosition, bool moveForward) const
{
	if (moveForward)
	{
		(++currPosition) %= capacity;
	}
	else
	{
		if (currPosition == 0)
			currPosition = capacity - 1;
		else
			currPosition--;
	}
}

template <typename T>
Deque<T>::Deque(const Deque<T>& other)
{
	copyFrom(other);
}
template <typename T>
Deque<T>::Deque(Deque<T>&& other)
{
	moveFrom(std::move(other));
}
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template <typename T>
Deque<T>& Deque<T>::operator=(Deque<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
template <typename T>
Deque<T>::~Deque()
{
	free();
}

template <typename T>
void Deque<T>::free()
{
	delete[] data;
	data = nullptr;
}
template <typename T>
void Deque<T>::copyFrom(const Deque<T>& other)
{
	elementsCount = other.elementsCount;
	capacity = other.capacity;

	head = other.head;
	tail = other.tail;

	data = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
		data[i] = other.data[i];
}
template <typename T>
void Deque<T>::moveFrom(Deque<T>&& other)
{
	elementsCount = other.elementsCount;
	capacity = other.capacity;

	head = other.head;
	tail = other.tail;

	other.elementsCount = other.capacity = other.head = other.tail = 0;

	data = other.data;
	other.data = nullptr;
}
