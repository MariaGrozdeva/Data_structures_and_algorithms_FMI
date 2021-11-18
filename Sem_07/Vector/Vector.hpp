#include <iostream>
#include <vector>
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
	bool empty() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	class VectorIterator
	{
	private:
		T* currentElementPtr;

	public:
		VectorIterator(T* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr)
		{}

		T& operator*()
		{
			return *currentElementPtr;
		}

		T* operator->()
		{
			return currentElementPtr;
		}

		T& operator[](size_t index)
		{
			return *(currentElementPtr + index);
		}

		VectorIterator& operator++()
		{
			currentElementPtr++;
			return *this;
		}
		VectorIterator operator++(int)
		{
			VectorIterator copy(*this);
			++(*this);
			return copy;
		}

		VectorIterator& operator--()
		{
			currentElementPtr--;
			return *this;
		}
		VectorIterator operator--(int)
		{
			VectorIterator copy(*this);
			--(*this);
			return copy;
		}

		VectorIterator& operator+=(int s)
		{
			currentElementPtr += s;
			return *this;
		}
		VectorIterator& operator-=(int s)
		{
			return *this += (-s);
		}

		VectorIterator operator+(int i) const
		{
			VectorIterator res(*this);
			return res += i;
		}
		VectorIterator operator-(int i) const
		{
			VectorIterator res(*this);
			return res -= i;
		}

		int operator-(const VectorIterator& rhs) const
		{
			return *currentElementPtr - *rhs.currentElementPtr;
		}

		bool operator==(const VectorIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const VectorIterator& rhs) const { return !(*this == rhs); }
		bool operator<(const VectorIterator& rhs) const { return currentElementPtr < rhs.currentElementPtr; }
		bool operator>(const VectorIterator& rhs) const { return (*this < rhs); }
		bool operator<=(const VectorIterator& rhs) const { return !(*this > rhs); }
		bool operator>=(const VectorIterator& rhs) const { return !(*this < rhs); }
	};

	VectorIterator begin()
	{
		return VectorIterator(arr);
	}
	VectorIterator end()
	{
		return VectorIterator(arr + size);
	}
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
bool Vector<T>::empty() const
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