#pragma once

#include <iostream>
using namespace std;

class HashingFunction
{
public:
	virtual ~HashingFunction() = default;

	// Calculates the hash of an integer
	virtual size_t calculateHashCode(int key) = 0;
};

class ModAndMultHashingFunction : public HashingFunction
{
private:
	size_t mod;
	size_t multiplier;

public:
	ModAndMultHashingFunction(size_t mod, size_t multiplier) : mod(mod), multiplier(multiplier)
	{}

	size_t calculateHashCode(int key) override
	{
		return (key % mod) * multiplier;
	}
};

template <typename ValueType>
class Hash
{
protected:
	HashingFunction* hashFunc;

public:
	Hash(HashingFunction* hashFunc = nullptr) : hashFunc(hashFunc)
	{}
	virtual ~Hash() = default;

	virtual void insert(int key, const ValueType& value) = 0;
	virtual const ValueType& find(int key) const = 0;
	virtual bool remove(int key) = 0;
};
