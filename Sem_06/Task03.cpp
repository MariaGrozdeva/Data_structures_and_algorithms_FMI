#include <iostream>
#include <algorithm>
#include <stdexcept>

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

template <typename T, typename Func>
const T& getMaxElement(Node<T>* root, const Func& comp)
{
	if (!root)
	{
	        throw std::invalid_argument("Empty tree");
	}
	if (!root->left && !root->right)
	{
	        return root->data;
	}
	if (!root->left)
	{
	        return std::max(root->data, getMaxElement(root->right, comp), comp);
	}
	if (!root->right)
	{
	        return std::max(root->data, getMaxElement(root->left, comp), comp);
	}
	return std::max(root->data, std::max(getMaxElement(root->left, comp), getMaxElement(root->right, comp), comp), comp);
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

	std::cout << getMaxElement(root, [](int a, int b) { return a < b; });
	free(root);
}
