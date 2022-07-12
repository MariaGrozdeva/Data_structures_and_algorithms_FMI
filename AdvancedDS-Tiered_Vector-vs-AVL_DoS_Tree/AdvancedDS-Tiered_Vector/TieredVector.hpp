#pragma once
#include "IndexableCircularDeque.hpp"

template <typename T>
class TieredVector
{
private:
	Deque<Deque<T>> data;

	size_t elementsCount;
	size_t capacity;

	size_t getDequeIndex(size_t index) const;

	void resize(size_t newCapacity);
	
	void pushFrontDequeIfNeeded();
	void pushBackDequeIfNeeded();

	void popPushForInsertion(size_t dequeInd);
	void popPushForErasion(size_t dequeInd);

public:
	TieredVector();
	TieredVector(std::initializer_list<T> iList);

	void insertAt(size_t index, const T& el);
	void insertAt(size_t index, T&& el);
	void eraseAt(size_t index);

	void push_back(const T& el);
	void push_back(T&& el);
	void push_front(const T& el);
	void push_front(T&& el);

	void pop_back();
	void pop_front();

	const T& back() const;
	const T& front() const;
	T& back();
	T& front();

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	bool empty() const;
	size_t getSize() const;

	// only for TESTING PURPOSES
	void print() const
	{
		std::cout << "-------Tiered vector-------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		for (size_t i = 0; i < data.getSize(); i++)
		{
			std::cout << "ElementsCount: " << data[i].getSize() << ", elements: ";
			for (size_t j = 0; j < data[i].getSize(); j++)
			{
				std::cout << data[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << "---------------------------" << std::endl;
	}
};

template <typename T>
void TieredVector<T>::popPushForInsertion(size_t dequeInd)
{
	if (dequeInd < data.getSize() / 2)
	{
		for (size_t i = 0; i != dequeInd; i++)
		{
			data[i].push_back(data[i + 1].front());
			data[i + 1].pop_front();
		}
		if (data.front().getSize() > capacity)
		{
			data.push_front_default();
			data.front().push_back(data[1].front());
			data[1].pop_front();
		}
	}
	else
	{
		for (size_t i = data.getSize() - 1; i != dequeInd; i--)
		{
			data[i].push_front(data[i - 1].back());
			data[i - 1].pop_back();
		}
		if (data.back().getSize() > capacity)
		{
			data.push_back_default();
			data.back().push_front(data[data.getSize() - 2].back());
			data[data.getSize() - 2].pop_back();
		}
	}
}
template <typename T>
void TieredVector<T>::insertAt(size_t index, const T& el)
{
	if (index == elementsCount)
	{
		push_back(el);
		return;
	}

	if (index >= elementsCount)
		throw std::out_of_range("Invalid index!");

	size_t dequeIndex = getDequeIndex(index);
	size_t elementIndex = dequeIndex == 0 ? index : (index - data.front().getSize()) % capacity;

	// Shift phase - O(sqrt(n))
	data[dequeIndex].insertAt(elementIndex, el);
	elementsCount++;

	// Pop-Push phase - O(sqrt(n))
	popPushForInsertion(dequeIndex);

	if (data.getSize() > capacity)
		resize(capacity * 2);
}
template <typename T>
void TieredVector<T>::insertAt(size_t index, T&& el)
{
	if (index == elementsCount)
	{
		push_back(el);
		return;
	}

	if (index >= elementsCount)
		throw std::out_of_range("Invalid index!");

	size_t dequeIndex = getDequeIndex(index);
	size_t elementIndex = dequeIndex == 0 ? index : (index - data.front().getSize()) % capacity;

	// Shift phase - O(sqrt(n))
	data[dequeIndex].insertAt(elementIndex, std::move(el));
	elementsCount++;

	// Pop-Push phase - O(sqrt(n))
	popPushForInsertion(dequeIndex);

	if (data.getSize() > capacity)
		resize(capacity * 2);
}

template <typename T>
void TieredVector<T>::popPushForErasion(size_t dequeInd)
{
	if (dequeInd <= data.getSize() / 2)
	{
		for (size_t i = dequeInd; i != 0; i--)
		{
			data[i].push_front(data[i - 1].back());
			data[i - 1].pop_back();
		}
		if (data.front().empty() && data.getSize() > 1) 
			data.pop_front();
	}
	else
	{
		for (size_t i = dequeInd; i != data.getSize() - 1; i++)
		{
			data[i].push_back(data[i + 1].front());
			data[i + 1].pop_front();
		}
		if (data.back().empty() && data.getSize() > 1)
			data.pop_back();
	}
}
template <typename T>
void TieredVector<T>::eraseAt(size_t index)
{
	if (index >= elementsCount)
		throw std::out_of_range("Invalid index!");

	size_t dequeInd = getDequeIndex(index);
	size_t elementIndex = dequeInd == 0 ? index : (index - data.front().getSize()) % capacity;

	// Shift phase - O(sqrt(n))
	data[dequeInd].eraseAt(elementIndex);
	elementsCount--;

	// Pop-Push phase - O(sqrt(n))
	popPushForErasion(dequeInd);

	if (elementsCount * 8 == capacity * capacity)
		resize(capacity / 2);
}

template <typename T>
void TieredVector<T>::push_back(const T& el)
{
	pushBackDequeIfNeeded();

	data.back().push_back(el);
	elementsCount++;

	if (data.getSize() > capacity)
		resize(capacity * 2);
}
template <typename T>
void TieredVector<T>::push_back(T&& el)
{
	pushBackDequeIfNeeded();

	data.back().push_back(std::move(el));
	elementsCount++;

	if (data.getSize() > capacity)
		resize(capacity * 2);
}
template <typename T>
void TieredVector<T>::push_front(const T& el)
{
	pushFrontDequeIfNeeded();

	data.front().push_front(el);
	elementsCount++;

	if (data.getSize() > capacity)
		resize(capacity * 2);
}
template <typename T>
void TieredVector<T>::push_front(T&& el)
{
	pushFrontDequeIfNeeded();

	data.front().push_front(std::move(el));
	elementsCount++;

	if (data.getSize() > capacity)
		resize(capacity * 2);
}

template <typename T>
void TieredVector<T>::pop_back()
{
	data.back().pop_back();
	if (data.back().empty())
		data.pop_back();

	elementsCount--;
	if (elementsCount * 8 == capacity * capacity)
		resize(capacity / 2);
}
template <typename T>
void TieredVector<T>::pop_front()
{
	data.front().pop_front();
	if (data.front().empty())
		data.pop_front();

	elementsCount--;
	if (elementsCount * 8 == capacity * capacity)
		resize(capacity / 2);
}

template <typename T>
const T& TieredVector<T>::back() const
{
	if (empty())
		throw std::length_error("Empty vector!");
	return data.back().back();
}
template <typename T>
const T& TieredVector<T>::front() const
{
	if (empty())
		throw std::length_error("Empty vector!");
	return data.front().front();
}
template <typename T>
T& TieredVector<T>::back()
{
	if (empty())
		throw std::length_error("Empty vector!");
	return data.back().back();
}
template <typename T>
T& TieredVector<T>::front()
{
	if (empty())
		throw std::length_error("Empty vector!");
	return data.front().front();
}

template <typename T>
const T& TieredVector<T>::operator[](size_t index) const
{
	assert(index < elementsCount);

	size_t dequeIndex = getDequeIndex(index);
	size_t elementIndex = dequeIndex == 0 ? index : (index - data.front().getSize()) % capacity;

	return data[dequeIndex][elementIndex];
}
template <typename T>
T& TieredVector<T>::operator[](size_t index)
{
	assert(index < elementsCount);

	size_t dequeIndex = getDequeIndex(index);
	size_t elementIndex = dequeIndex == 0 ? index : (index - data.front().getSize()) % capacity;

	return data[dequeIndex][elementIndex];
}

template <typename T>
bool TieredVector<T>::empty() const
{
	return elementsCount == 0;
}
template <typename T>
size_t TieredVector<T>::getSize() const
{
	return elementsCount;
}

template <typename T>
TieredVector<T>::TieredVector()
{
	elementsCount = 0;
	capacity = 4;
	data.push_back_default();
}
template <typename T>
TieredVector<T>::TieredVector(std::initializer_list<T> iList) : TieredVector()
{
	for (const T& el : iList)
		push_back(el);
}

template <typename T>
void TieredVector<T>::resize(size_t newCapacity)
{
	TieredVector<T> resized;
	resized.capacity = newCapacity;

	size_t unchangedElementsCount = elementsCount;
	for (size_t i = 0; i < unchangedElementsCount; i++)
	{
		resized.push_back(front());
		pop_front();
	}
	*this = std::move(resized);
}

template <typename T>
void TieredVector<T>::pushFrontDequeIfNeeded()
{
	if (data.front().getSize() == capacity)
		data.push_front_default();
}
template <typename T>
void TieredVector<T>::pushBackDequeIfNeeded()
{
	if (data.back().getSize() == capacity)
		data.push_back_default();
}

template <typename T>
size_t TieredVector<T>::getDequeIndex(size_t index) const
{
	if (index < data.front().getSize()) // the first may not be full
		return 0;

	index -= data.front().getSize();
	return index / capacity + 1; // +1 to skip the head
}