#include "SinglyLinkedList.hpp"

int main()
{
	SinglyLinkedList<int> l1 = { 1, 2, 3, 4, 5 };
	SinglyLinkedList<int> l2;

	l2 = std::move(l1); // move operator= called
	SinglyLinkedList<int> l3(std::move(l2)); // move copy constr called
	SinglyLinkedList<int> l4(l3); // copy constr called

	l3.push_back(10);
	l3.push_back(11);
	l3.push_back(12);
	l3.push_back(13);
	l3.push_back(14);
	cout << l3 << endl;

	l3.push_front(0);
	l3.push_front(-1);
	l3.push_front(-2);
	cout << l3 << endl;

	l3.pop_front();
	l3.pop_front();
	l3.pop_front();
	cout << l3 << endl;

	cout << l3.front() << endl;
	cout << l3.back() << endl;

	SinglyLinkedList<int> res = concat(l3, l4);
	std::cout << res;
}
