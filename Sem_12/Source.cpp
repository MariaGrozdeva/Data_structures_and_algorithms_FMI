#include "HeapSort.hpp"

int main()
{
	PriorityQueue<int> pq({ 3, 5, 22, 23, 24, 1, 1, 100 });
	pq.print();
	cout << "----------------------------------------------" << endl << endl;

	pq.insert(-420);
	pq.insert(-42);
	pq.insert(55);
	cout << "After inserting -420, -42, 55:" << endl;
	pq.print();
	cout << "----------------------------------------------" << endl << endl;

	pq.pop();
	cout << "After removing the biggest element" << endl;
	pq.print();
	cout << "----------------------------------------------" << endl << endl;

	cout << "Heap Sort:" << endl;
	vector<int> v = { 100, 1, 1, 23, 22, 77, 50 };

	heapSort(v);
	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << ' ';
	cout << endl;
}