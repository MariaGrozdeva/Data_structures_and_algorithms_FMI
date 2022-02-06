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
void free(Node<T>* root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

void getAllPaths(Node<int>* root, vector<vector<int>>& paths, vector<int> currentPath)
{
	if (!root)
		return;

	if (root->data % 2)
		return;

	if (!root->left && !root->right)
	{
		paths.push_back(currentPath);
		return;
	}

	currentPath.push_back(root->data);

	getAllPaths(root->left, paths, currentPath);
	getAllPaths(root->right, paths, currentPath);
}
bool existsEvenPathFromLeafToLeaf(Node<int>* root)
{
	vector<vector<int>> paths;
	vector<int> path;

	getAllPaths(root, paths, path);

	return paths.size() > 1 ? true : false;
}

int main()
{
	Node<int>* root = new Node<int>(50);
	Node<int>* n1 = new Node<int>(26);
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

	cout << existsEvenPathFromLeafToLeaf(root);
	free(root);
}