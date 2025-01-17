#pragma once

#include "iterator.hpp"
#include <utility>
#include <algorithm>

namespace Constants
{
constexpr unsigned GROWTH_FACTOR = 2;
}

template <class T>
class vector
{
  public:
	using iterator = vector_iterator<T>;
	using const_iterator = const_vector_iterator<T>;
	using reverse_iterator = reverse_vector_iterator<T>;

	vector() = default;
	explicit vector(size_t count);
	vector(size_t count, const T& initial);

	vector(const vector<T>& other);
	vector& operator=(const vector<T>& other);

	vector(vector&& oher) noexcept;
	vector& operator=(vector<T>&& other) noexcept;

	~vector() noexcept;

	void push_back(const T& element);
	void push_back(T&& element);
	void pop_back();

	void erase(const_iterator position);
	void erase(const_iterator first, const_iterator last);

	void clear();

	template <class... Args>
	void emplace_back(Args&&... args);

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;

	T* data();

	void resize(size_t n);
	void reserve(size_t n);
	void shrink_to_fit();

	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	iterator begin()
	{
		return iterator(_data);
	}
	iterator end()
	{
		return iterator(_data + _size);
	}

	const_iterator c_begin() const
	{
		return const_iterator(_data);
	}
	const_iterator c_end() const
	{
		return const_iterator(_data + _size);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(_data + _size - 1);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_data - 1);
	}

	const T& back() const
	{
		return _data[_size - 1];
	}
	T& back()
	{
		return _data[_size - 1];
	}

	const T& front() const
	{
		return _data[0];
	}
	T& front()
	{
		return _data[0];
	}

  private:
	void free();
	void move(vector<T>&& other);
	size_t calculate_capacity() const;

	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};

template <class T>
vector<T>::vector(size_t count)
	: _data(static_cast<T*>(operator new(count * sizeof(T))))
	, _size(count)
	, _capacity(count)
{
	// default construct all elements
	for (size_t i = 0; i < _size; i++)
	{
		new (&_data[i]) T();
	}
}

template <class T>
vector<T>::vector(size_t count, const T& initial)
	: _data(static_cast<T*>(operator new(count * sizeof(T))))
	, _size(count)
	, _capacity(count)
{
	// construct all elements copying initial
	for (size_t i = 0; i < _size; i++)
	{
		new (&_data[i]) T(initial);
	}
}

template <class T>
vector<T>::vector(const vector<T>& other) : _data(nullptr), _capacity(other._capacity)
{
	_capacity = _capacity ? _capacity : 1;
    	_data = static_cast<T*>(operator new(_capacity * sizeof(T)));
    	try
	{
        	for (_size = 0; _size < other._size; _size++)
		{
            		_data[_size] = other[_size];
		}
    	}
    	catch (...)
	{
        	// Ensure no memory will leak if data assignment throws
        	free();
        	throw;
	}
}

template <class T>
vector<T>& vector<T>::operator=(const vector<T>& other)
{
	if (this != &other)
	{
        	if (_capacity < other._size)
		{
            		free();
            		_data = static_cast<T*>(operator new(other._capacity * sizeof(T)));
		}
		else
		{
		        for (size_t i = other._size; i < _size; i++)
		        {
		            _data[i].~T();
		        }
		}
        	for (_size = 0; _size < other._size; ++_size)
		{
            		// If exception is thrown we do not handle it, but no memory leak can happen (basic exception guarantee)
            		_data[_size] = other[_size];
        	}
    	}
	return *this;
}

template <class T>
vector<T>::vector(vector<T>&& other) noexcept
{
	move(std::move(other));
}

template <class T>
vector<T>& vector<T>::operator=(vector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

template <class T>
vector<T>::~vector() noexcept
{
	free();
}

template <class T>
void vector<T>::free()
{
	// call destructor on constructed elements
	for (size_t i = 0; i < _size; i++)
	{
		_data[i].~T();
	}
	// deallocate memory
	operator delete(_data, _capacity * sizeof(T));
}

template <class T>
void vector<T>::move(vector<T>&& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;

	other._data = nullptr;
	other._size = other._capacity = 0;
}

template <class T>
size_t vector<T>::calculate_capacity() const
{
	if (_capacity == 0)
	{
		return 1;
	}
	return _capacity * Constants::GROWTH_FACTOR;
}

// Resizes the container to contain `n` elements, does nothing if `n` == _size.
// If the current size is greater than `n`, the container is reduced to its first `n` elements.
// If the current size is less than `n`, then additional default-inserted elements are appended.
template <class T>
void vector<T>::resize(size_t n)
{
	if (n < _size)
	{
		// call destructor on constructed elements
		for (size_t i = n; i < _size; i++)
		{
			(_data + i)->~T();
		}
		_size = n;
	}
	else if (n > _size)
	{
		if (n <= _capacity)
		{
			// default construct elements in range [_size, n)
			for (size_t i = _size; i < n; i++)
			{
				new (&_data[i]) T();
			}
			_size = n;
		}
		else
		{
			T* newData = static_cast<T*>(operator new(n * sizeof(T)));
			for (size_t i = 0; i < _size; i++)
			{
				new (&newData[i]) T(std::move(_data[i]));
			}
			for (size_t i = _size; i < n; i++)
			{
				new (&newData[i]) T();
			}
			operator delete(_data, _capacity * sizeof(T));

			_data = newData;
			_capacity = n;
			_size = n;
		}
	}
}

// Increase the _capacity of the vector to a value that's greater than or equal to `n`.
// If `n` is greater than the current capacity, new storage is allocated, otherwise the function does nothing.
template <class T>
void vector<T>::reserve(size_t n)
{
	if (n <= _capacity)
	{
		return;
	}

	T* newData = static_cast<T*>(operator new(n * sizeof(T)));
	for (size_t i = 0; i < _size; i++)
        {
		new (&newData[i]) T(std::move(_data[i]));
	}
	operator delete(_data, _capacity * sizeof(T));

	_data = newData;
	_capacity = n;
}

// Requests the container to reduce its _capacity to fit its _size.
// This may cause a reallocation, but has no effect on the vector _size and cannot alter its elements.
template <class T>
void vector<T>::shrink_to_fit()
{
	if (_size == _capacity)
	{
		return;
	}

	T* newData = static_cast<T*>(operator new(_size * sizeof(T)));
	for (size_t i = 0; i < _size; i++)
	{
		new (&newData[i]) T(std::move(_data[i]));
	}
	operator delete(_data, _capacity * sizeof(T));

	_capacity = _size;
	_data = newData;
}

template <class T>
void vector<T>::push_back(const T& element)
{
	if (_size == _capacity)
	{
		reserve(calculate_capacity());
	}
	new (&_data[_size++]) T(element);
}

template <class T>
void vector<T>::push_back(T&& element)
{
	if (_size == _capacity)
	{
		reserve(calculate_capacity());
	}
	new (&_data[_size++]) T(std::move(element));
}

template <class T>
void vector<T>::pop_back()
{
	if (empty())
	{
		return;
	}
	erase(--end());
}

template <class T>
void vector<T>::erase(const_iterator position)
{
	erase(position, position + 1);
}

template <class T>
void vector<T>::erase(const_iterator first, const_iterator last)
{
	int deleted_count = last - first;

	if (deleted_count <= 0)
	{
		return;
	}

	int begin_offset = first - begin();
	int end_offset = last - begin();

	if (last != c_end())
	{
		for (size_t i = end_offset; i < _size; i++)
		{
			new (&_data[begin_offset++]) T(std::move(_data[i]));
		}
	}

	for (size_t i = end_offset; i < _size; i++)
	{
		(_data + i)->~T();
	}

	_size -= deleted_count;
}

// Appends a new element to the end of the container.
// The element is constructed through placement-new in-place.
template <class T>
template <class... Args>
void vector<T>::emplace_back(Args&&... args)
{
	if (_size == _capacity)
	{
		reserve(calculate_capacity());
	}
	new (&_data[_size++]) T(std::forward<Args>(args)...);
}

template <class T>
T& vector<T>::operator[](size_t idx)
{
	return _data[idx];
}

template <class T>
const T& vector<T>::operator[](size_t idx) const
{
	return _data[idx];
}

template <class T>
T* vector<T>::data()
{
	return _data;
}

template <class T>
void vector<T>::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		(_data + i)->~T();
	}
	_size = 0;
}

template <class T>
size_t vector<T>::size() const
{
	return _size;
}

template <class T>
size_t vector<T>::capacity() const
{
	return _capacity;
}

template <class T>
bool vector<T>::empty() const
{
	return _size == 0;
}
