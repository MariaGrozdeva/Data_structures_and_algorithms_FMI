#include <vector>
#include "Hash.h"

template <typename ValueType>
class LinearProbingHash : public Hash<ValueType>
{
private:
	struct Pair
	{
		int key;
		ValueType value;

		bool empty;
		bool hasBeenDeleted;

		Pair() : empty(true), hasBeenDeleted(false)
		{}
		Pair(int key, const ValueType& value, bool empty = true, bool hasBeenDeleted = false) : key(key), value(value), empty(empty), hasBeenDeleted(hasBeenDeleted)
		{}
	};

	size_t step;
	size_t size;
	size_t maxFillLevel;

	vector<Pair> linearProb;

	void setMaxFillLevel(size_t capacity);
	void resize();

public:
	LinearProbingHash(HashingFunction* hashFunc, size_t step);

	void insert(int key, const ValueType& value) override;
	const ValueType& find(int key) const override;
	bool remove(int key) override;
};

template <typename ValueType>
LinearProbingHash<ValueType>::LinearProbingHash(HashingFunction* hashFunc, size_t capacity) : Hash<ValueType>(hashFunc)
{
	linearProb.resize(capacity);
	setMaxFillLevel(capacity);

	step = 1;
	size = 0;
}

template <typename ValueType>
void LinearProbingHash<ValueType>::insert(int key, const ValueType& value)
{
	size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(key) % linearProb.capacity();

	while (!linearProb[hashCode].empty)
		(++hashCode) % linearProb.capacity();
	linearProb[hashCode] = Pair(key, value, false, false);
	size++;

	if (size >= maxFillLevel)
		resize();
}
template <typename ValueType>
const ValueType& LinearProbingHash<ValueType>::find(int key) const
{
	size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(key) % linearProb.capacity();

	while (!linearProb[hashCode].empty || linearProb[hashCode].hasBeenDeleted)
	{
		if (linearProb[hashCode].key == key && !linearProb[hashCode].hasBeenDeleted)
			return linearProb[hashCode].value;
		(++hashCode) % linearProb.capacity();
	}

	throw "No such element!";
}
template <typename ValueType>
bool LinearProbingHash<ValueType>::remove(int key)
{
	size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(key) % linearProb.capacity();

	while (!linearProb[hashCode].empty || linearProb[hashCode].hasBeenDeleted)
	{
		if (linearProb[hashCode].key == key && !linearProb[hashCode].hasBeenDeleted)
		{
			linearProb[hashCode].empty = true;
			linearProb[hashCode].hasBeenDeleted = true;
			size--;
			return true;
		}
		(++hashCode) % linearProb.capacity();
	}
	return false;
}

template <typename ValueType>
void LinearProbingHash<ValueType>::resize()
{
	vector<Pair> resized(linearProb.capacity() * 2);
	vector<Pair> temp = linearProb;
	linearProb = resized;

	setMaxFillLevel(linearProb.capacity());

	for (size_t i = 0; i < temp.capacity(); i++)
	{
		if (linearProb[i].empty)
			continue;

		size_t hashCode = Hash<ValueType>::hashFunc->calculateHashCode(temp[i].key) % linearProb.capacity();
		linearProb[hashCode] = Pair(temp[i].key, temp[i].value, false);
	}
}
template <typename ValueType>
void LinearProbingHash<ValueType>::setMaxFillLevel(size_t capacity)
{
	maxFillLevel = (7 * capacity) / 10;
}
