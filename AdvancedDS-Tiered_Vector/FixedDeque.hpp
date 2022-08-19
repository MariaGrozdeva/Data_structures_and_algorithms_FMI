#pragma once
#include <iostream>

template <typename T>
struct FixedDeque
{
private:
	T* data;

	size_t head; // index of the first element
	size_t tail; // index of the last element + 1

	void moveFrom(FixedDeque<T>&&);

	void movePosition(size_t&, bool, size_t) const;

	size_t getMidIndex(size_t, size_t, size_t) const;
	const T& getMidElement(size_t) const;

public:
	FixedDeque();
	FixedDeque(size_t);
	FixedDeque(FixedDeque<T>&&);
	FixedDeque<T>& operator=(FixedDeque<T>&&);
	~FixedDeque();
	FixedDeque(const FixedDeque<T>&) = delete;
	FixedDeque<T>& operator=(const FixedDeque<T>&) = delete;

	void free();
	void copyFrom(const FixedDeque<T>&, size_t);

	void insert(const T& el, size_t capacity);
	bool erase(const T& el, size_t capacity);
	int contains(const T& el, size_t capacity);

	void push_back(const T&, size_t);
	void push_back(T&&, size_t);
	void push_front(const T&, size_t);
	void push_front(T&&, size_t);

	void pop_back(size_t);
	void pop_front(size_t);

	const T& back(size_t) const;
	const T& front() const;
	T& back(size_t);
	T& front();

	const T& getElementByIndex(size_t, size_t) const;
	T& getElementByIndex(size_t, size_t);

	bool empty() const;
};

template <typename T>
void FixedDeque<T>::insert(const T& el, size_t capacity)
{
	if (empty())
	{
		push_back(el, capacity);
		return;
	}

	if (el < getMidElement(capacity))
	{
		size_t current = head;
		size_t prev = head; movePosition(prev, false, capacity);
		while (data[current] < el)
		{
			data[prev] = data[current];
			prev = current;
			movePosition(current, true, capacity);
		}
		data[prev] = el;
		movePosition(head, false, capacity);
	}
	else
	{
		size_t current = tail;
		size_t prev = tail; movePosition(prev, false, capacity);
		while (data[prev] > el)
		{
			data[current] = data[prev];
			current = prev;
			movePosition(prev, false, capacity);
		}
		data[current] = el;
		movePosition(tail, true, capacity);
	}
}
template <typename T>
bool FixedDeque<T>::erase(const T& el, size_t capacity)
{
	int index = contains(el, capacity);
	if (index == -1)
		return false;

	size_t tailDecremented = tail; movePosition(tailDecremented, false, capacity);
	size_t mid = getMidIndex(head, tailDecremented, capacity);

	if (el > data[mid])
	{
		size_t current = index;
		size_t next = current; movePosition(next, true, capacity);

		while (next != tail)
		{
			data[current] = data[next];
			current = next;
			movePosition(next, true, capacity);
		}
		movePosition(tail, false, capacity);
	}
	else
	{
		size_t current = index;
		size_t prev = current; movePosition(prev, false, capacity);

		while (current != head)
		{
			data[current] = data[prev];
			current = prev;
			movePosition(prev, false, capacity);
		}
		movePosition(head, true, capacity);
	}
	return true;
}
template <typename T>
int FixedDeque<T>::contains(const T& el, size_t capacity)
{
	size_t low = head;
	size_t high = tail; movePosition(high, false, capacity);

	bool stop = false;
	while (!stop)
	{
		if (low == high)
			stop = true;

		size_t mid = getMidIndex(low, high, capacity);

		if (data[mid] < el)
		{
			low = mid; movePosition(low, true, capacity);
		}
		else if (data[mid] > el)
		{
			high = mid; movePosition(high, false, capacity);
		}
		else
		{
			return mid;
		}

		if (stop)
			break;
	}
	return -1;
}

template <typename T>
void FixedDeque<T>::push_back(const T& el, size_t capacity)
{
	data[tail] = el; // el should be bigger than all elements in data
	movePosition(tail, true, capacity);
}
template <typename T>
void FixedDeque<T>::push_back(T&& el, size_t capacity)
{
	data[tail] = std::move(el);
	movePosition(tail, true, capacity);
}
template <typename T>
void FixedDeque<T>::push_front(const T& el, size_t capacity)
{
	movePosition(head, false, capacity);
	data[head] = el; // el should be smaller than all elements in data	
}
template <typename T>
void FixedDeque<T>::push_front(T&& el, size_t capacity)
{
	movePosition(head, false, capacity);
	data[head] = std::move(el);
}

template <typename T>
void FixedDeque<T>::pop_back(size_t capacity)
{
	movePosition(tail, false, capacity);
}
template <typename T>
void FixedDeque<T>::pop_front(size_t capacity)
{
	movePosition(head, true, capacity);
}

template <typename T>
const T& FixedDeque<T>::back(size_t capacity) const
{
	size_t lastElement = tail; movePosition(lastElement, false, capacity);
	return data[lastElement];
}
template <typename T>
const T& FixedDeque<T>::front() const
{
	return data[head];
}
template <typename T>
T& FixedDeque<T>::back(size_t capacity)
{
	size_t lastElement = tail; movePosition(lastElement, false, capacity);
	return data[lastElement];
}
template <typename T>
T& FixedDeque<T>::front()
{
	return data[head];
}

template <typename T>
const T& FixedDeque<T>::getElementByIndex(size_t index, size_t capacity) const
{
	return data[(head + index) % capacity];
}
template <typename T>
T& FixedDeque<T>::getElementByIndex(size_t index, size_t capacity)
{
	return data[(head + index) % capacity];
}

template <typename T>
bool FixedDeque<T>::empty() const
{
	return head == tail;
}

template <typename T>
size_t FixedDeque<T>::getMidIndex(size_t low, size_t high, size_t capacity) const
{
	if (low == high)
		return low;

	size_t mid;
	if (low < high)
	{
		mid = (low + high) / 2;
	}
	else
	{
		mid = (low + high + capacity) / 2;
		mid %= capacity;
	}
	return mid;
}
template <typename T>
const T& FixedDeque<T>::getMidElement(size_t capacity) const
{
	size_t tailDecremented = tail; movePosition(tailDecremented, false, capacity);

	size_t midIndex = getMidIndex(head, tailDecremented, capacity);
	return data[midIndex];
}

template <typename T>
void FixedDeque<T>::movePosition(size_t& currPosition, bool moveForward, size_t capacity) const
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
FixedDeque<T>::FixedDeque() : FixedDeque(0)
{}
template <typename T>
FixedDeque<T>::FixedDeque(size_t capacity)
{
	if (capacity == 0)
	{
		data = nullptr;
		head = tail = 0;
	}
	else
	{
		data = new T[capacity];
		head = tail = 0;
	}
}
template <typename T>
FixedDeque<T>::FixedDeque(FixedDeque<T>&& other)
{
	moveFrom(std::move(other));
}
template <typename T>
FixedDeque<T>& FixedDeque<T>::operator=(FixedDeque<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
template <typename T>
FixedDeque<T>::~FixedDeque()
{
	free();
}

template <typename T>
void FixedDeque<T>::free()
{
	delete[] data;
	data = nullptr;
}
template <typename T>
void FixedDeque<T>::copyFrom(const FixedDeque<T>& other, size_t capacity)
{
	head = other.head;
	tail = other.tail;

	data = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
		data[i] = other.data[i];
}
template <typename T>
void FixedDeque<T>::moveFrom(FixedDeque<T>&& other)
{
	head = other.head;
	tail = other.tail;

	other.head = other.tail = 0;

	data = other.data;
	other.data = nullptr;
}