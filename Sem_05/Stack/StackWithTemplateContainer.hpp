#pragma once
#include "deque.hpp"

template <class T, class Container = deque<T>>
class stack
{
public:
	void push(const T& el)
	{
		c.push_back(el);
	}
	void pop()
	{
		c.pop_back();
	}
	
	T& top()
	{
		return c.back();
	}
	const T& top() const
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
