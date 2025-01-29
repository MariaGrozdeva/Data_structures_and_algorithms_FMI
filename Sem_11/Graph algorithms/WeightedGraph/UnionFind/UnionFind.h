#include <iostream>
#include <vector>

class UnionFind
{
public:
	UnionFind(unsigned n); // set of n elements (0..n-1)

	bool Union(unsigned n, unsigned k); // O(log(n))
	size_t Find(unsigned n); // O(log(n))
	
private:
	std::vector<unsigned> parents;
	std::vector<unsigned> sizes;
};
