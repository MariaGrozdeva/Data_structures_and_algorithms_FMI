#include <iostream>
using namespace std;

template <typename T>
class ArrayStack
{
private:
	T* arr;

	size_t size;
	size_t capacity;

public:
	ArrayStack();
	ArrayStack(const ArrayStack<T>& other);
	ArrayStack<T>& operator=(const ArrayStack<T>& other);
	~ArrayStack();

private:
	void copyFrom(const ArrayStack<T>& other);
	void free();

	void resize(size_t capacity);

public:
	void push(const T& element);
	void pop();
	const T& top();
	bool empty() const;
};

template <typename T>
void ArrayStack<T>::push(const T& element)
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = element;
}
template <typename T>
void ArrayStack<T>::pop()
{
	if (empty())
		throw length_error("Empty ArrayStack!");

	if (--size * 2 <= capacity && capacity > 1)
		resize(capacity / 2);
}
template <typename T>
const T& ArrayStack<T>::top()
{
	if (empty())
		throw length_error("Empty ArrayStack!");

	return arr[size - 1];
}
template <typename T>
bool ArrayStack<T>::empty() const
{
	return size == 0;
}

template <typename T>
ArrayStack<T>::ArrayStack()
{
	size = 0;
	capacity = 4;

	arr = new T[capacity];
}
template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other)
{
	copyFrom(other);
}
template<typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
ArrayStack<T>::~ArrayStack()
{
	free();
}

template<typename T>
void ArrayStack<T>::copyFrom(const ArrayStack<T>& other)
{
	arr = new T[other.capacity];

	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
		arr[i] = other.arr[i];
}
template<typename T>
void ArrayStack<T>::free()
{
	delete[] arr;
}

template <typename T>
void ArrayStack<T>::resize(size_t capacity)
{
	this->capacity = capacity;
	T* temp = new T[capacity];

	for (size_t i = 0; i < size; i++)
		temp[i] = arr[i];

	delete[] arr;
	arr = temp;
}