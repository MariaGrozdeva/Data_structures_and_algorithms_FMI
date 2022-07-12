#include "AVL.hpp"

int main()
{
	AVL<int> avl = { 5, 8, 10, 22, 23, 24, 9 };

	avl.erase(23);

	std::cout << avl[5];
}