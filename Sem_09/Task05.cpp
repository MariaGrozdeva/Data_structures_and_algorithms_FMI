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

int nodesCountInAnInterval(Node<int>* root, int start, int end)
{
	if (!root)
		return 0;

	if (root->data >= start && root->data <= end)
		return 1 + nodesCountInAnInterval(root->left, start, end) + nodesCountInAnInterval(root->right, start, end);

	else if (root->data <= start)
		return nodesCountInAnInterval(root->right, start, end);

	else if (root->data >= end)
		return nodesCountInAnInterval(root->left, start, end);
}
int sumOfNodesWithOddNumberOfChildren(Node<int>* root, int start, int end)
{
	if (!root)
		return 0;

	int numOfChildren = nodesCountInAnInterval(root->left, start, end) + nodesCountInAnInterval(root->right, start, end);

	if (numOfChildren % 2)
		return root->data +
		sumOfNodesWithOddNumberOfChildren(root->left, start, end) + sumOfNodesWithOddNumberOfChildren(root->right, start, end);

	return sumOfNodesWithOddNumberOfChildren(root->left, start, end) + sumOfNodesWithOddNumberOfChildren(root->right, start, end);
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

	cout << sumOfNodesWithOddNumberOfChildren(root, 30, 75);
}