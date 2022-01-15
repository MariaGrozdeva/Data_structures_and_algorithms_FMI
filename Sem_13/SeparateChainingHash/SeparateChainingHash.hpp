#include <vector>
#include <list>
#include "Hash.h"

template <typename ValueType>
class SeparateChainingHash : public Hash<ValueType>
{
private:
	struct Pair
	{
		int key;
		ValueType value;

		Pair(int key, const ValueType& value) : key(key), value(value)
		{}
	};

	size_t size;
	size_t maxFillLevel;

	vector<list<Pair>> sepChaining;

	void setMaxFillLevel(size_t capacity);
	void resize();

public:
	SeparateChainingHash(HashingFunction* hashFunc, size_t capacity);

	void insert(int key, const ValueType& value) override;
	const ValueType& find(int key) const override;
	void remove(int key) override;
};

template <typename ValueType>
SeparateChainingHash<ValueType>::SeparateChainingHash(HashingFunction* hashFunc, size_t capacity) : Hash<ValueType>(hashFunc)
{
	sepChaining.resize(capacity);
	setMaxFillLevel(capacity);
}

template <typename ValueType>
void SeparateChainingHash<ValueType>::insert(int key, const ValueType& value)
{
	size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(key) % sepChaining.capacity();
	sepChaining[hashCode].push_back(Pair(key, value));
	size++;

	if (size >= maxFillLevel)
		resize();
}
template <typename ValueType>
const ValueType& SeparateChainingHash<ValueType>::find(int key) const
{
	size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(key) % sepChaining.capacity();

	for (auto it = sepChaining[hashCode].begin(); it != sepChaining[hashCode].end(); ++it)
	{
		if (it->key == key)
			return it->value;
	}
	
	throw "No such element!";
}
template <typename ValueType>
void SeparateChainingHash<ValueType>::remove(int key)
{
	size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(key) % sepChaining.capacity();

	for (auto it = sepChaining[hashCode].begin(); it != sepChaining[hashCode].end(); ++it)
	{
		if (it->key == key)
		{
			it = sepChaining[hashCode].erase(it);
			size--;
			return;
		}
	}
}

template <typename ValueType>
void SeparateChainingHash<ValueType>::resize()
{
	vector<list<Pair>> resized(sepChaining.capacity() * 2);
	vector<list<Pair>> temp = sepChaining;
	sepChaining = resized;

	setMaxFillLevel(sepChaining.capacity());

	for (size_t i = 0; i < temp.capacity(); i++)
	{
		for (auto it = temp[i].begin(); it != temp[i].end(); ++it)
		{
			size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(it->key) % sepChaining.capacity();
			sepChaining[hashCode].push_back(Pair(it->key, it->value));
		}
	}
}
template <typename ValueType>
void SeparateChainingHash<ValueType>::setMaxFillLevel(size_t capacity)
{
	maxFillLevel = (7 * capacity) / 10;
}