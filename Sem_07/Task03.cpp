#include <iostream>

template <typename T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;

	Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
void free(Node<T>* root)
{
	if (!root)
	{
		return;
	}
	free(root->left);
	free(root->right);
	delete root;
}

template <typename T>
Node<T>* lca(Node<T>* root, const T& x, const T& y)
{
	if ((x < root->data && y > root->data) || (y < root->data && x > root->data))
	{
		return root;
	}
	if (x < root->data && y < root->data)
	{
		return lca(root->left, x, y);
	}
	return lca(root->right, x, y);
}

int main()
{
	Node<int>* root = new Node<int>(50);
	Node<int>* n1 = new Node<int>(25);
	Node<int>* n2 = new Node<int>(75);
	Node<int>* n3 = new Node<int>(12);
	Node<int>* n4 = new Node<int>(30);
	Node<int>* n5 = new Node<int>(60);
	Node<int>* n6 = new Node<int>(85);
	Node<int>* n7 = new Node<int>(52);
	Node<int>* n8 = new Node<int>(70);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
	n5->left = n7;
	n5->right = n8;

	Node<int>* result = lca(root, 52, 85);
	std::cout << result->data;
	free(root);
}
