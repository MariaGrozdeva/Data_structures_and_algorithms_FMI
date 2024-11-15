#pragma once
#include "deque.hpp"

template <class T, class Container = deque<T>>
class queue
{
public:
	void push(const T& el)
	{
		c.push_back(el);
	}
	void pop()
	{
		c.pop_front();
	}
	
	T& front()
	{
		return c.front();
	}
	const T& front() const
	{
		return c.front();
	}

	T& back()
	{
		return c.back();
	}
	const T& back() const
	{
		return c.back();
	}

	bool empty() const
	{
		return c.empty();
	}
	size_t size() const
	{
		return c.size();
	}
	
private:
	Container c;
};
