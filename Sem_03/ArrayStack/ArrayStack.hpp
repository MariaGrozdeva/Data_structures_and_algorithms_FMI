#include <iostream>
using namespace std;

template <typename T>
class Stack
{
private:
	T* arr;

	size_t size;
	size_t capacity;

public:
	Stack();
	Stack(const Stack<T>& other);
	Stack<T>& operator=(const Stack<T>& other);
	~Stack();

private:
	void copyFrom(const Stack<T>& other);
	void free();

	void resize(size_t capacity);

public:
	void push(const T& element);
	void pop();
	const T& top();
	bool empty();
};

template <typename T>
void Stack<T>::push(const T& element)
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = element;
}
template <typename T>
void Stack<T>::pop()
{
	if (empty())
		throw length_error("Empty stack!");

	if (--size * 2 <= capacity && capacity > 1)
		resize(capacity / 2);
}
template <typename T>
const T& Stack<T>::top()
{
	if (empty())
		throw length_error("Empty stack!");

	return arr[size - 1];
}
template <typename T>
bool Stack<T>::empty()
{
	return size == 0;
}

template <typename T>
Stack<T>::Stack()
{
	size = 0;
	capacity = 4;

	arr = new T[capacity];
}
template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
	copyFrom(other);
}
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
Stack<T>::~Stack()
{
	free();
}

template<typename T>
void Stack<T>::copyFrom(const Stack<T>& other)
{
	arr = new T[other.capacity];

	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
		arr[i] = other.arr[i];
}
template<typename T>
void Stack<T>::free()
{
	delete[] arr;
}

template <typename T>
void Stack<T>::resize(size_t capacity)
{
	this->capacity = capacity;
	T* temp = new T[capacity];

	for (size_t i = 0; i < size; i++)
		temp[i] = arr[i];

	delete[] arr;
	arr = temp;
}
