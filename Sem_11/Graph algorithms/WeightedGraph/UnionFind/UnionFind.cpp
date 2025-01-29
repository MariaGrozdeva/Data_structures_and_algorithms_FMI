#include "UnionFind.h"

UnionFind::UnionFind(unsigned n) : parents(n), sizes(n)
{
	for (size_t i = 0; i < n; i++)
	{
		parents[i] = i; // At the beginning each set consists of only one element which is also a parent to itself (and the leader of the set)
		sizes[i] = 1; // All sets are with one element
	}
}

bool UnionFind::Union(unsigned n, unsigned k) // Union by rank
{
	unsigned firstLeader = Find(n);
	unsigned secondLeader = Find(k);

	if (firstLeader == secondLeader) // n and k are already in one set
	{
		return false;
	}
	if (sizes[firstLeader] < sizes[secondLeader])
	{
		std::swap(firstLeader, secondLeader);
	}

	// The set with leader "firstLeader" certainly has more elements than the other one
	parents[secondLeader] = firstLeader;
	sizes[firstLeader] += sizes[secondLeader];

	return true;
}

unsigned UnionFind::Find(unsigned n) // Returns the leader of the set where n belongs to
{
	if (parents[n] == n)
	{
		return n;
	}
	return Find(parents[n]);
}
