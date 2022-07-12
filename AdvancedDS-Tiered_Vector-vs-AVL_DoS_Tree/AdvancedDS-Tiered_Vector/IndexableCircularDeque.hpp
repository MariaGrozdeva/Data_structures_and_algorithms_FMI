#pragma once
#include <iostream>
#include <cassert>

template <typename T>
class Deque
{
private:
	T* data;

	size_t size;
	size_t capacity;

	size_t head; // index of the first element
	size_t tail; // index of the last element + 1

	void free();
	void copyFrom(const Deque<T>& other);
	void moveFrom(Deque<T>&& other);

	void resize(size_t newCapacity);

public:
	Deque();
	Deque(const Deque<T>& other);
	Deque(Deque<T>&& other);
	Deque<T>& operator=(const Deque<T>& other);
	Deque<T>& operator=(Deque<T>&& other);
	~Deque();


private:
	void movePosition(size_t& currPosition, bool moveForward) const;

	void shiftElementsForInsertion(size_t index);
	void shiftElementsForErasion(size_t index);

public:
	void insertAt(size_t index, const T& el);
	void insertAt(size_t index, T&& el);
	void eraseAt(size_t index);

	void push_back(const T& el);
	void push_back(T&& el);
	void push_back_default();

	void push_front(const T& el);
	void push_front(T&& el);
	void push_front_default();

	void pop_back();
	void pop_front();

	const T& back() const;
	const T& front() const;
	T& back();
	T& front();

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	bool empty() const;
	size_t getSize() const;
};

template <typename T>
void Deque<T>::shiftElementsForInsertion(size_t index)
{
	size_t i = (head + index) % capacity;

	if (index <= size / 2)
	{
		movePosition(head, false);
		size_t currPos = head;
		size_t nextPos = head; movePosition(nextPos, true);
		while (nextPos != i)
		{
			data[currPos] = data[nextPos];
			currPos = nextPos;
			movePosition(nextPos, true);
		}
	}
	else
	{
		size_t currPos = tail, prevPos = tail;
		while (currPos != i)
		{
			movePosition(prevPos, false);
			data[currPos] = data[prevPos];
			currPos = prevPos;
		}
		movePosition(tail, true);
	}
}
template <typename T>
void Deque<T>::insertAt(size_t index, const T& el)
{
	if (index == 0)
	{
		push_front(el);
		return;
	}
	if (index == size)
	{
		push_back(el);
		return;
	}

	if (index >= size)
		throw std::out_of_range("Invalid index!");

	if (size == capacity)
		resize(capacity * 2);

	shiftElementsForInsertion(index);
	data[(head + index) % capacity] = el;
	size++;
}
template <typename T>
void Deque<T>::insertAt(size_t index, T&& el)
{
	if (index == 0)
	{
		push_front(std::move(el));
		return;
	}
	if (index == size)
	{
		push_back(std::move(el));
		return;
	}

	if (index >= size)
		throw std::out_of_range("Invalid index!");

	if (size == capacity)
		resize(capacity * 2);

	shiftElementsForInsertion(index);
	data[(head + index) % capacity] = std::move(el);
	size++;
}

template <typename T>
void Deque<T>::shiftElementsForErasion(size_t index)
{
	size_t i = (head + index) % capacity;

	if (index < size / 2)
	{
		while (i != head)
		{
			size_t prevPos = i; movePosition(prevPos, false);
			data[i] = data[prevPos];
			i = prevPos;
		}
		movePosition(head, true);
	}
	else
	{
		movePosition(tail, false);
		while (i != tail)
		{
			size_t nextPos = i; movePosition(nextPos, true);
			data[i] = data[nextPos];
			i = nextPos;
		}
	}
}
template <typename T>
void Deque<T>::eraseAt(size_t index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size)
	{
		pop_back();
		return;
	}

	if (index >= size)
		throw std::out_of_range("Invalid index!");

	shiftElementsForErasion(index);
	size--;
	if (size * 8 == capacity)
		resize(capacity / 2);
}

template <typename T>
void Deque<T>::push_back(const T& el)
{
	if (size == capacity)
		resize(capacity * 2);

	data[tail] = el;
	movePosition(tail, true);
	size++;
}
template <typename T>
void Deque<T>::push_back(T&& el)
{
	if (size == capacity)
		resize(capacity * 2);

	data[tail] = std::move(el);
	movePosition(tail, true);
	size++;
}
template <typename T>
void Deque<T>::push_back_default()
{
	if (size == capacity)
		resize(capacity * 2);

	movePosition(tail, true);
	size++;
}

template <typename T>
void Deque<T>::push_front(const T& el)
{
	if (size == capacity)
		resize(capacity * 2);

	movePosition(head, false);
	data[head] = el;
	size++;
}
template <typename T>
void Deque<T>::push_front(T&& el)
{
	if (size == capacity)
		resize(capacity * 2);

	movePosition(head, false);
	data[head] = std::move(el);
	size++;
}
template <typename T>
void Deque<T>::push_front_default()
{
	if (size == capacity)
		resize(capacity * 2);
	if (empty())
	{
		size++;
		movePosition(tail, true);
		return;
	}

	movePosition(head, false);
	size++;
}

template <typename T>
void Deque<T>::pop_back()
{
	if (empty())
		throw std::length_error("Empty deque!");

	movePosition(tail, false);
	size--;

	if (size * 8 == capacity)
		resize(capacity / 2);
}
template <typename T>
void Deque<T>::pop_front()
{
	if (empty())
		throw std::length_error("Empty deque!");

	movePosition(head, true);
	size--;

	if (size * 8 == capacity)
		resize(capacity / 2);
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
	assert(index < size);
	return data[(head + index) % capacity];
}
template <typename T>
T& Deque<T>::operator[](size_t index)
{
	assert(index < size);
	return data[(head + index) % capacity];
}

template <typename T>
bool Deque<T>::empty() const
{
	return size == 0;
}
template <typename T>
size_t Deque<T>::getSize() const
{
	return size;
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
Deque<T>::Deque()
{
	size = 0;
	capacity = 8;
	data = new T[capacity];

	head = tail = 0;
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
}
template <typename T>
void Deque<T>::copyFrom(const Deque<T>& other)
{
	size = other.size;
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
	size = other.size;
	capacity = other.capacity;

	head = other.head;
	tail = other.tail;

	other.size = other.capacity = other.head = other.tail = 0;

	data = other.data;
	other.data = nullptr;
}

template <typename T>
void Deque<T>::resize(size_t newCapacity)
{
	T* resized = new T[newCapacity];
	for (size_t i = 0; i < size; i++)
	{
		resized[i] = data[head];
		movePosition(head, true);
	}
	delete[] data;
	data = resized;

	capacity = newCapacity;
	head = 0;
	tail = size;
}