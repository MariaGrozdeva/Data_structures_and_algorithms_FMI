#include "PriorityQueue/priority_queue.hpp"
#include <iostream>
#include <vector>

template <typename T>
void heapSort(std::vector<T>& v) // O(nlog(n))
{
	priority_queue<T> pq(v); // O(n)
	for (int i = v.size() - 1; i >= 0; i--) // O(n)
	{
		v[i] = pq.top(); // O(log(n))
		pq.pop();
	}
}

int main()
{
        std::vector<int> v{ 10, 3, 0, 88, 101, 20 };
        heapSort(v);
        for (size_t i = 0; i < v.size(); i++)
        {
                std::cout << v[i] << " ";
        }
}
