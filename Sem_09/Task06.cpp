#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	Node(const T& data) : data(data), left(nullptr), right(nullptr)
	{}
};

int sumOfNodesOnOddLevelsHelper(Node<int>* root, int level)
{
	if (!root)
		return 0;

	if (level % 2)
	{
		if (root->right && !root->left)
			return root->data;
	}

	return sumOfNodesOnOddLevelsHelper(root->left, level + 1) + sumOfNodesOnOddLevelsHelper(root->right, level + 1);
}
int sumOfNodesOnOddLevels(Node<int>* root)
{
	return sumOfNodesOnOddLevelsHelper(root, 0);
}

int main()
{
	// Same tree as in the previous tasks but without the left child (12) of the node with value 25
	Node<int>* root = new Node<int>(50); 
	Node<int>* n1 = new Node<int>(25);
	Node<int>* n2 = new Node<int>(75);
	Node<int>* n3 = new Node<int>(30);
	Node<int>* n4 = new Node<int>(60);
	Node<int>* n5 = new Node<int>(85);
	Node<int>* n6 = new Node<int>(52);
	Node<int>* n7 = new Node<int>(70);

	root->left = n1;
	root->right = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;

	cout << sumOfNodesOnOddLevels(root);
}