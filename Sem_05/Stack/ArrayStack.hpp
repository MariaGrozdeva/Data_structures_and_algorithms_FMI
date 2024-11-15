#pragma once
#include <memory>

namespace Constants
{
constexpr unsigned GROWTH_FACTOR = 2;
}

template <class T, class Allocator = std::allocator<T>>
class stack
{
  public:
	stack() = default;

	stack(const stack& other);
	stack& operator=(const stack& other);

	stack(stack&& other) noexcept;
	stack& operator=(stack&& other) noexcept;
	
	~stack() noexcept;

	void push(const T& element);
	void push(T&& element);
	
	template <class... Args>
	T emplace(Args&&... args);
	
	void pop();

	size_t getSize() const;
	bool empty() const;

	const T& top() const;
	T& top();

  private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
	
	Allocator myAlloc;
	
	void copyFrom(const stack& other);
	void free();
	void moveFrom(stack&& other);
	void reserve(size_t n);
	size_t calculateCapacity() const;
};

template <class T, class Allocator>
void stack<T, Allocator>::push(const T& element)
{
	if (size == capacity)
	{
		reserve(calculateCapacity());
	}
	std::construct_at(data[size++], element);
}

template <class T, class Allocator>
void stack<T, Allocator>::push(T&& element)
{
	if (size == capacity)
	{
		reserve(calculateCapacity());
	}
	std::construct_at(&data[size++], std::move(element));
}

template <class T, class Allocator>
template <class... Args>
T stack<T, Allocator>::emplace(Args&&... args)
{
        T newObj(std::forward<Args>(args)...);
	if (size == capacity)
	{
		reserve(calculateCapacity());
        }
	std::construct_at(&data[size++], std::forward<Args>(args)...);
	return newObj;
}

template <class T, class Allocator>
void stack<T, Allocator>::pop()
{
	if (empty())
	{
		throw std::logic_error("Empty stack\n");
	}
	std::destroy_at(&data[--size]);
}

template <class T, class Allocator>
const T& stack<T, Allocator>::top() const
{
	return data[size - 1];
}

template <class T, class Allocator>
T& stack<T, Allocator>::top()
{
	return data[size - 1];
}

template <class T, class Allocator>
size_t stack<T, Allocator>::getSize() const
{
	return size;
}

template <class T, class Allocator>
bool stack<T, Allocator>::empty() const
{
	return size == 0;
}

template <class T, class Allocator>
stack<T, Allocator>::stack(const stack& other)
{
	copyFrom(other);
}

template <class T, class Allocator>
stack<T, Allocator>& stack<T, Allocator>::operator=(const stack& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T, class Allocator>
stack<T, Allocator>::stack(stack&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T, class Allocator>
stack<T, Allocator>& stack<T, Allocator>::operator=(stack&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T, class Allocator>
stack<T, Allocator>::~stack() noexcept
{
	free();
}

template <class T, class Allocator>
void stack<T, Allocator>::copyFrom(const stack<T, Allocator>& other)
{
	data = myAlloc.allocate(other.capacity);
	for (size_t i = 0; i < other.size; i++)
	{
		std::construct_at(&data[i], other[i]);
        }
	size = other.getSize();
	capacity = other.capacity();
}

template <class T, class Allocator>
void stack<T, Allocator>::moveFrom(stack<T, Allocator>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template <class T, class Allocator>
void stack<T, Allocator>::free()
{
	for (size_t i = 0; i < size; i++)
	{
		std::destroy_at(&data[i]);
	}
	myAlloc.deallocate(data, capacity);
}

template <class T, class Allocator>
void stack<T, Allocator>::reserve(size_t n)
{
	if (n <= capacity)
	{
		return;
        }
	T* newdata = myAlloc.allocate(n);
	for (size_t i = 0; i < size; i++)
	{
		std::construct_at(&newdata[i], std::move(data[i]));
        }
	myAlloc.deallocate(data, capacity);

	data = newdata;
	capacity = n;
}

template <class T, class Allocator>
size_t stack<T, Allocator>::calculateCapacity() const
{
	if (capacity == 0)
	{
		return 1;
	}
	return capacity * Constants::GROWTH_FACTOR;
}
