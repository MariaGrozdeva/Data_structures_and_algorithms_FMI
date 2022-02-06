#include "PriorityQueue.hpp"

template <typename T>
void heapSort(vector<T>& v) // O(nlog(n))
{
	PriorityQueue<T> pq(v); // O(n)

	for (int i = v.size() - 1; i >= 0; i--) // O(n)
	{
		v[i] = pq.top(); // O(log(n))
		pq.pop();
	}
}