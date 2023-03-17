SinglyLinkedList<int> l1 = { 1, 2, 3, 4, 5 };
	SinglyLinkedList<int> l2;

	l2 = std::move(l1); // move operator= called
	SinglyLinkedList<int> l3(std::move(l2)); // move copy constr called
	std::cout << "Initial list:" << std::endl << l3 << std::endl << std::endl;
	SinglyLinkedList<int> l4(l3); // copy constr called

	l3.push_back(10);
	l3.push_back(11);
	l3.push_back(12);
	l3.push_back(13);
	l3.push_back(14);
	std::cout << "List after calling push_back with 10, 11, 12, 13 and 14:" << std::endl << l3 << std::endl << std::endl;

	l3.push_front(0);
	l3.push_front(-1);
	l3.push_front(-2);
	std::cout << "List after calling push_front with 0, -1 and -2:" << std::endl << l3 << std::endl << std::endl;

	l3.pop_front();
	l3.pop_front();
	l3.pop_front();
	std::cout << "List after calling pop_front three times:" << std::endl << l3 << std::endl << std::endl;

	std::cout << "Calling front returns: " << l3.front() << std::endl << std::endl;
	std::cout << "Calling back returns: " << l3.back() << std::endl << std::endl;

	SinglyLinkedList<int> res = concat(l3, l4);
	std::cout << "New list after concatenating the old one with \"1 -> 2 -> 3 -> 4 -> 5\":" << std::endl << res << std::endl << std::endl;

	res.sort([](int a, int b) { return a <= b; });
	std::cout << "List after sorting in increasing order:" << std::endl << res << std::endl << std::endl;
}
