#pragma once

#include <iostream>

template <typename T>
class CircularQueue
{
private:
	T* data;

	size_t size = 0;
	size_t capacity = 4;

	unsigned getIter = 0;
	unsigned putIter = 0;

	void copyFrom(const CircularQueue<T>& other);
	void free();

	void resize(size_t capacity);

public:
	CircularQueue();
	CircularQueue(const CircularQueue<T>& other);
	CircularQueue<T>& operator=(const CircularQueue<T>& other);
	~CircularQueue();

	void enqueue(const T& el);
	void dequeue();
	const T& peek() const;
	bool empty() const;
};

template <typename T>
void CircularQueue<T>::enqueue(const T& el)
{
	if (size >= capacity)
	{
		resize(capacity * 2);
	}

	data[putIter] = el;
	(++putIter) %= capacity;
	size++;
}
template <typename T>
void CircularQueue<T>::dequeue()
{
	if (empty())
	{
		throw std::logic_error("Empty queue!");
	}

	(++getIter) %= capacity;
	size--;
}
template <typename T>
const T& CircularQueue<T>::peek() const
{
	if (empty())
	{
		throw std::logic_error("Empty queue!");
	}

	return data[getIter];
}
template <typename T>
bool CircularQueue<T>::empty() const
{
	return size == 0;
}

template <typename T>
CircularQueue<T>::CircularQueue()
{
	data = new T[capacity];
}
template <typename T>
CircularQueue<T>::CircularQueue(const CircularQueue<T>& other)
{
	copyFrom(other);
}
template <typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
CircularQueue<T>::~CircularQueue()
{
	free();
}

template <typename T>
void CircularQueue<T>::copyFrom(const CircularQueue<T>& other)
{
	data = new T[capacity];
	
	for (size_t i = 0; i != size; i++)
	{
		data[i] = other.data[(other.getIter + i) % other.capacity];
	}

	size = other.size;
	capacity = other.capacity;

	getIter = other.getIter;
	putIter = other.putIter;
}
template <typename T>
void CircularQueue<T>::free()
{
	delete[] data;
}

template <typename T>
void CircularQueue<T>::resize(size_t capacity)
{
	T* temp = new T[capacity];

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[(getIter + i) % this->capacity];
	}

	delete[] data;
	data = temp;

	this->capacity = capacity;

	getIter = 0;
	putIter = size;
}