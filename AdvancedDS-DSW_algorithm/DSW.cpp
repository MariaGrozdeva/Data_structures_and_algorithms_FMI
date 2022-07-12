#include <iostream>
#include <algorithm>

template <typename T>
struct Node
{
	T* data;
	Node<T>* left;
	Node<T>* right;

	Node(const T& data) : data(new T(data)), left(nullptr), right(nullptr)
	{}
};

template <typename T>
void free(Node<T>* root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root->data;
	delete root;
}

size_t closestLowerPowerOfTwo(size_t n)
{
	size_t result = 0;
	for (size_t i = n; i >= 1; i--)
	{
		if ((i & (i - 1)) == 0)
		{
			result = i;
			break;
		}
	}
	return result;
}

template <typename T>
size_t height(const Node<T>* root)
{
	if (!root)
		return 0;

	return 1 + std::max(height(root->left), height(root->right));
}

template <typename T>
void rotateLeft(Node<T>*& root)
{
	if (!root || !root->right)
		return;

	std::swap(root->data, root->right->data);
	Node<T>* originalRight = root->right;
	root->right = originalRight->right;
	originalRight->right = originalRight->left;
	originalRight->left = root->left;
	root->left = originalRight;
}
template <typename T>
void rotateRight(Node<T>*& root)
{
	if (!root || !root->left)
		return;

	std::swap(root->data, root->left->data);
	Node<T>* originalLeft = root->left;
	root->left = originalLeft->left;
	originalLeft->left = originalLeft->right;
	originalLeft->right = root->right;
	root->right = originalLeft;
}

// Balance the tree using the Day-Stout-Warren algorithm.

template <typename T>
bool DSW(Node<T>*& root)
{
	// 1. Make the tree completely unbalanced (straight) to the right by doing right rotations on all left children.

	Node<T>* currentNode = root; // Start at the root.
	size_t nodesCount = 0; // Keep track of the number of nodes in this tree.

	while (currentNode) // Go from the root to the bottom right node.
	{
		while (currentNode->left) // While we still see a left child.
			rotateRight(currentNode); // Get rid of the left child.
		if (nodesCount == 0)
			root = currentNode; // After we've done all rotations on the root, update the original one. 
		currentNode = currentNode->right; // Update our current node to it's right child.
		nodesCount++;
	}

	// If the tree height isn't equal to the number of nodes in the tree, this step failed.
	if (nodesCount != height(root))
		return false;

	// 2. Do left rotations and balance the tree (currently - backbone(vine)).

	size_t leavesOnBottomLevel = nodesCount - closestLowerPowerOfTwo(nodesCount) + 1; // The number of nodes on the bottom level.
	currentNode = root;

	for (size_t i = 0; i < leavesOnBottomLevel; i++) // For the nodes on the bottom level:
	{
		if (i == 0) // Rotate the root.
		{
			rotateLeft(currentNode);
			root = currentNode;
		}
		else // If not the root, rotate the right of the current node.
			rotateLeft(currentNode->right);
	}

	size_t rotationsCount = nodesCount;
	while (rotationsCount > 1) // The number of rotations are reduced twice each time because as we go up the tree, the number of nodes on a certain level are 50% of all nodes (on this level + the upper ones).
	{
		rotationsCount /= 2;
		currentNode = root;

		for (size_t i = 0; i < rotationsCount - 1; i++) // For the length of the vine:
		{
			if (i == 0) // Rotate the root.
			{
				rotateLeft(currentNode);
				root = currentNode;
			}
			else
			{
				currentNode = currentNode->right; // Update the current node.
				rotateLeft(currentNode); // Rotate the current node.
			}
		}
	}

	// The tree should be balanced. The height of it (measured in number of edges) is expected to be log(# nodes).
	return !(ceil(log(nodesCount)) != height(root) - 1);
}

int main()
{
	Node<int>* root = new Node<int>(10);
	Node<int>* n1 = new Node<int>(5);
	Node<int>* n2 = new Node<int>(20);
	Node<int>* n3 = new Node<int>(7);
	Node<int>* n4 = new Node<int>(15);
	Node<int>* n5 = new Node<int>(30);
	Node<int>* n6 = new Node<int>(25);
	Node<int>* n7 = new Node<int>(40);
	Node<int>* n8 = new Node<int>(23);
	root->left = n1;
	root->right = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n5->left = n6;
	n5->right = n7;
	n6->left = n8;

	std::cout << DSW(root);
	free(root);
}
