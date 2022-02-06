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

template <typename T>
void free(Node<T>* root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

bool checkIfSubtree(Node<int>* rootA, Node<int>* rootB)
{
	if (!rootB)
		return true;

	if (rootA->data == rootB->data)
		return checkIfSubtree(rootA->left, rootB->left) && checkIfSubtree(rootA->right, rootB->right);

	return false;
}
bool isSubtree(Node<int>* rootA, Node<int>* rootB)
{
	if (!rootA)
		return false;

	if (rootA->data == rootB->data)
	{
		if (checkIfSubtree(rootA->left, rootB->left) && checkIfSubtree(rootA->right, rootB->right))
			return true;
	}

	return isSubtree(rootA->left, rootB) || isSubtree(rootA->right, rootB);
}

int main()
{
	Node<int>* root1 = new Node<int>(50);
	Node<int>* n1 = new Node<int>(25);
	Node<int>* n2 = new Node<int>(75);
	Node<int>* n3 = new Node<int>(12);
	Node<int>* n4 = new Node<int>(30);
	Node<int>* n5 = new Node<int>(60);
	Node<int>* n6 = new Node<int>(85);
	Node<int>* n7 = new Node<int>(52);
	Node<int>* n8 = new Node<int>(70);
	root1->left = n1;
	root1->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
	n5->left = n7;
	n5->right = n8;

	Node<int>* root2 = new Node<int>(60);
	Node<int>* nn1 = new Node<int>(52);
	Node<int>* nn2 = new Node<int>(70);
	root2->left = nn1;
	root2->right = nn2;

	cout << isSubtree(root1, root2);
	free(root1);
	free(root2);
}