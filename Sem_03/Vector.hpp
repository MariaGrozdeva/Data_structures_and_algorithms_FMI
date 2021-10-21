#include <iostream>
using namespace std;

template <typename T>
class Vector
{
private:
	T* arr;

	size_t size;
	size_t capacity;

public:
	Vector(size_t capacity);

	Vector();
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

private:
	void copyFrom(const Vector<T>& other);
	void free();

	void resize(size_t capacity);

public:
	void push_back(const T& element);
	void pop_back();
	bool empty();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;
};

template <typename T>
void Vector<T>::push_back(const T& element)
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = element;
}
template <typename T>
void Vector<T>::pop_back()
{
	if (empty())
		throw length_error("Empty vector!");

	if (--size * 2 <= capacity && capacity > 1)
		resize(capacity / 2);
}
template <typename T>
bool Vector<T>::empty()
{
	return size == 0;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	if (index > size)
		throw out_of_range("Out of range!");

	return arr[index];
}
template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	if (index > size)
		throw out_of_range("Out of range!");

	return arr[index];
}

template <typename T>
Vector<T>::Vector(size_t capacity) : size(0)
{
	auto closestPowerOfTwo = [](size_t n)
	{
		n--;

		n |= n >> 1;
		n |= n >> 2;
		n |= n >> 4;
		n |= n >> 8;
		n |= n >> 16;
		n |= n >> 32;

		return n + 1;
	};

	this->capacity = closestPowerOfTwo(capacity);
	arr = new T[capacity];
}

template <typename T>
Vector<T>::Vector() : Vector(4)
{}
template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	arr = new T[other.capacity];

	size = other.size;
	capacity = other.capacity;

	for (size_t i = 0; i < size; i++)
		arr[i] = other.arr[i];
}
template<typename T>
void Vector<T>::free()
{
	delete[] arr;
}

template <typename T>
void Vector<T>::resize(size_t capacity)
{
	this->capacity = capacity;
	T* temp = new T[capacity];

	for (size_t i = 0; i < size; i++)
		temp[i] = arr[i];

	delete[] arr;
	arr = temp;
}