#include "priority_queue.hpp"
#include <iostream>

int main()
{
	priority_queue<int> pq({ 3, 5, 22, 23, 24, 1, 1, 100 });
	
	std::cout << pq.top() << std::endl; // 100
	pq.pop();
	
	pq.push(-420);
	pq.push(-42);
	pq.push(55);
	
	std::cout << pq.top() << std::endl; // 55
	pq.pop();
	std::cout << pq.top() << std::endl; // 24
        pq.pop();
        std::cout << pq.top() << std::endl; // 23
        pq.pop();
	std::cout << pq.top() << std::endl; // 22
}
