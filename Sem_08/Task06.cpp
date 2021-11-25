#include <iostream>
#include <vector>

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
size_t getElementsCount(Node<T>* root)
{
	if (!root)
		return 0;

	if (!root->left && !root->right)
		return 1;

	return 1 + (getElementsCount(root->left) + getElementsCount(root->right));
}

bool checkIfAllNumbersAreInTree(Node<int>* root, vector<bool>& numbers)
{
	if (!root)
		return true;

	if ((root->data < 1 || root->data > numbers.size()) || numbers[root->data - 1])
		return false;

	numbers[root->data - 1] = true;

	return checkIfAllNumbersAreInTree(root->left, numbers) && checkIfAllNumbersAreInTree(root->right, numbers);
}
bool isPermutation(Node<int>* root)
{
	size_t size = getElementsCount(root);
	vector<bool> numbers(size, 0);

	return checkIfAllNumbersAreInTree(root, numbers);
}

int main()
{
	Node<int>* root = new Node<int>(2);
	Node<int>* n1 = new Node<int>(7);
	Node<int>* n2 = new Node<int>(5);
	Node<int>* n3 = new Node<int>(2);
	Node<int>* n4 = new Node<int>(6);
	Node<int>* n5 = new Node<int>(9);
	Node<int>* n6 = new Node<int>(5);
	Node<int>* n7 = new Node<int>(11);
	Node<int>* n8 = new Node<int>(4);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;
	n5->left = n8;

	cout << isPermutation(root);
}