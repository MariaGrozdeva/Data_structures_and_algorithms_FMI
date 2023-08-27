#include "BST.hpp"

int main()
{
	BST<int> bst;

	bst.insert(2);
	bst.insert(1);
	bst.insert(4);
	bst.insert(3);
	bst.insert(5);

	std::cout << "Initial BST:" << std::endl;
	bst.print();
	std::cout << "------------------------------" << std::endl;

	bst.remove(2);
	std::cout << "After removing 2:" << std::endl;
	bst.print();
	std::cout << "------------------------------" << std::endl;

	bst.remove(4);
	std::cout << "After removing 4:" << std::endl;
	bst.print();
	std::cout << "------------------------------" << std::endl;

	BST<int> bst2 = bst;
	std::cout << "After copy:" << std::endl;
	bst.print();
	std::cout << "------------------------------" << std::endl;
}