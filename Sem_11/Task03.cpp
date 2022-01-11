#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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
bool comp(Node<int>* lhs, Node<int>* rhs) 
{
	return lhs->data < rhs->data;
}

template <typename T>
void free(Node<T>* root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

template <typename T>
int height(Node<T>* root)
{
	if (!root)
		return -1;

	return 1 + max(height(root->left), height(root->right));
}

bool areVectorsSame(vector<Node<int>*> nodes1, vector<Node<int>*> nodes2)
{
	sort(nodes1.begin(), nodes1.end(), comp);
	sort(nodes2.begin(), nodes2.end(), comp);

	for (size_t i = 0; i < nodes1.size(); i++)
	{
		if (nodes1[i]->data != nodes2[i]->data)
			return false;
	}

	return true;
}
bool createNextVectors(vector<Node<int>*>& nodes1, vector<Node<int>*>& nodes2)
{
	vector<Node<int>*> nodes1Next;
	vector<Node<int>*> nodes2Next;

	for (size_t i = 0; i < nodes1.size(); i++)
	{
		if (nodes1[i]->left)
			nodes1Next.push_back(nodes1[i]->left);
		if (nodes1[i]->right)
			nodes1Next.push_back(nodes1[i]->right);

		if (nodes2[i]->left)
			nodes2Next.push_back(nodes2[i]->left);
		if (nodes2[i]->right)
			nodes2Next.push_back(nodes2[i]->right);
	}

	nodes1 = nodes1Next;
	nodes2 = nodes2Next;

	return nodes1.size() == nodes2.size();
}

bool sameOnLevel(Node<int>* root1, Node<int>* root2)
{
	int height1 = height(root1);
	int height2 = height(root2);
	if (height1 != height2)
		return false;

	vector<Node<int>*> nodes1;
	vector<Node<int>*> nodes2;

	nodes1.push_back(root1);
	nodes2.push_back(root2);

	for (size_t i = 0; i <= height1; i++)
	{
		if (!areVectorsSame(nodes1, nodes2) || !createNextVectors(nodes1, nodes2))
			return false;
	}

	free(root1);
	free(root2);
	return true;
}

int main()
{
	Node<int>* root1 = new Node<int>(1);
	Node<int>* n1 = new Node<int>(2);
	Node<int>* n2 = new Node<int>(3);
	Node<int>* n3 = new Node<int>(4);
	Node<int>* n4 = new Node<int>(5);
	root1->left = n1;
	root1->right = n2;
	n2->left = n3;
	n2->right = n4;

	Node<int>* root2 = new Node<int>(1);
	Node<int>* n11 = new Node<int>(3);
	Node<int>* n22 = new Node<int>(2);
	Node<int>* n33 = new Node<int>(5);
	Node<int>* n44 = new Node<int>(4);
	root2->left = n11;
	root2->right = n22;
	n22->left = n33;
	n22->right = n44;

	cout << sameOnLevel(root1, root2);
}