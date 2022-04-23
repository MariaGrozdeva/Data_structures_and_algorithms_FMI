#include "AVL.hpp"

int main()
{
	AVL<int> avl;

	avl.insert(5);
	avl.insert(8);
	avl.insert(10);
	avl.insert(22);
	avl.insert(23);
	avl.insert(24);
	avl.insert(9);

	avl.erase(23);
}