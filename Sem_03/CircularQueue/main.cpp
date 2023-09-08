#include "CircularQueue.hpp"

#include <cassert>

int main()
{
	CircularQueue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);

	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();

	assert(q.empty());

	q.enqueue(55);

	CircularQueue<int> qCopy(q);
	qCopy.dequeue();

	assert(qCopy.empty());
}