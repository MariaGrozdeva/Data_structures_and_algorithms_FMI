#include "BinomialHeap.hpp"

int main()
{
	BinomialHeap<int> binHeap;
	binHeap.insert(2);
	binHeap.insert(7);
	binHeap.insert(4);
	binHeap.insert(8);
	binHeap.insert(12);
	binHeap.insert(10);
	binHeap.insert(5);
	binHeap.insert(21);
	binHeap.insert(1);
	binHeap.insert(9);
	binHeap.insert(11);

	std::cout << binHeap.getMin();
}
