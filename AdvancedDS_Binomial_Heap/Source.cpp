#include "BinomialHeap.hpp"

int main()
{
	BinomialHeap<int> b;
	b.insert(2);
	b.insert(7);
	b.insert(4);
	b.insert(8);
	b.insert(12);
	b.insert(10);
	b.insert(5);
	b.insert(21);
	b.insert(1);
	b.insert(9);
	b.insert(11);

	std::cout << b.getMin();
}