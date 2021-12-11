#include "BST.hpp"

int main()
{
	BST<int> bst;

	bst.insert(2);
	bst.insert(1);
	bst.insert(4);
	bst.insert(3);
	bst.insert(5);

	cout << "Initial BST:" << endl;
	bst.print();
	cout << "------------------------------" << endl;

	bst.remove(2);
	cout << "After removing 2:" << endl;
	bst.print();
	cout << "------------------------------" << endl;

	bst.remove(4);
	cout << "After removing 4:" << endl;
	bst.print();
	cout << "------------------------------" << endl;

	BST<int> bst2 = bst;
	cout << "After copy:" << endl;
	bst.print();
	cout << "------------------------------" << endl;
}