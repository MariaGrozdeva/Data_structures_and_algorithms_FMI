#include "BinomialHeap.hpp"

int main()
{
	BinomialHeap<int> binHeap1;
	binHeap1.insert(2);
	binHeap1.insert(7);
	binHeap1.insert(4);
	binHeap1.insert(8);
	binHeap1.insert(12);
	binHeap1.insert(10);
	binHeap1.insert(5);
	binHeap1.insert(21);
	binHeap1.insert(9);
	binHeap1.insert(11);
	binHeap1.insert(1);

	BinomialHeap<int> binHeap2;
	binHeap2.insert(6);
	binHeap2.insert(14);
	binHeap2.insert(3);

	BinomialHeap<int> result;
	mergeHeaps(result, binHeap1, binHeap2);

	std::cout << result.getMin();
}