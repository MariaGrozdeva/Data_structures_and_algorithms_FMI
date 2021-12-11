#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class BST
{
private:
	struct Node
	{
		T data;

		Node* left;
		Node* right;

		Node(const T& data) : data(data), left(nullptr), right(nullptr)
		{}
	};

	Node* root;

public:
	BST();

	BST(const vector<T>& v);
	BST(const BST<T>& other);
	BST<T>& operator=(const BST<T>& other);
	~BST();

private:
	void copyFromRec(Node*& root, Node* otherRoot);
	void freeRec(Node* root);

	void copyFrom(const BST<T>& other);
	void free();

	void createBSTRec(Node*& root, const vector<T>& v, int start, int end);

	void findMax(Node* root, Node*& maxNode);

	bool containsRec(const T& el, Node* root, Node*& prev);
	void removeRec(const T& el, Node*& root);

	void printRec(Node* root, int space) const;

public:
	bool contains(const T& el) const;
	void insert(const T& el);
	void remove(const T& el);

	void print() const;
};

template <typename T>
bool BST<T>::contains(const T& el) const
{
	containsRec(el, root);
}
template <typename T>
void BST<T>::insert(const T& el)
{
	if (!root)
	{
		root = new Node(el);
		return;
	}

	Node* prev = nullptr;
	if (containsRec(el, root, prev))
		return;

	Node* newNode = new Node(el);

	if (el < prev->data)
		prev->left = newNode;
	else
		prev->right = newNode;
}
template <typename T>
void BST<T>::remove(const T& el)
{
	removeRec(el, root);
}

template <typename T>
BST<T>::BST()
{
	root = nullptr;
}

template <typename T>
BST<T>::BST(const vector<T>& v)
{
	if (!is_sorted(v.begin(), v.end()))
		throw "Array should be sorted!";

	createBSTRec(root, v, 0, v.size() - 1);
}
template <typename T>
BST<T>::BST(const BST<T>& other)
{
	copyFrom(other);
}
template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
BST<T>::~BST()
{
	free();
}

template <typename T>
bool BST<T>::containsRec(const T& el, Node* root, Node*& prev)
{
	if (!root)
		return false;
	if (root->data == el)
		return true;
	
	prev = root;
	if (el < root->data)
		return containsRec(el, root->left, prev);
	else
		return containsRec(el, root->right, prev);
}
template <typename T>
void BST<T>::removeRec(const T& el, Node*& root)
{
	if (!root)
		return;

	Node* prev = nullptr;
	if (!containsRec(el, root, prev))
		return;

	Node*& toDelete = prev == nullptr ? root :
		el < prev->data ? prev->left : prev->right;

	// remove leaf
	if (!toDelete->left && !toDelete->right)
	{
		delete toDelete;
		toDelete = nullptr;
	}

	// remove node only with left child
	else if (toDelete->left && !toDelete->right)
	{
		if (prev->left == toDelete)
			prev->left = toDelete->left;
		else
			prev->right = toDelete->left;

		delete toDelete;
		toDelete = nullptr;
	}
	// remove node only with right child
	else if (!toDelete->left && toDelete->right)
	{
		if (prev->left == toDelete)
			prev->left = toDelete->right;
		else
			prev->right = toDelete->right;

		delete toDelete;
		toDelete = nullptr;
	}

	// remove node with left and right child
	else
	{
		Node* maxNode;
		findMax(toDelete->left, maxNode);
		swap(toDelete->data, maxNode->data);
		removeRec(maxNode->data, toDelete->left);
	}
}

template <typename T>
void BST<T>::findMax(Node* root, Node*& maxNode)
{
	Node* iter = root;
	while (iter)
	{
		maxNode = iter;
		iter = iter->right;
	}
}

template <typename T>
void BST<T>::createBSTRec(Node*& root, const vector<T>& v, int start, int end)
{
	if (start > end)
	{
		root = nullptr;
		return;
	}

	int mid = start + (end - start) / 2;
	root = new Node(v[mid]);

	createBSTRec(root->left, v, start, mid - 1);
	createBSTRec(root->right, v, mid + 1, end);
}

template <typename T>
void BST<T>::copyFrom(const BST<T>& other)
{
	copyFromRec(root, other.root);
}
template <typename T>
void BST<T>::free()
{
	freeRec(root);
}

template <typename T>
void BST<T>::copyFromRec(Node*& root, Node* otherRoot)
{
	if (!otherRoot)
		return;

	root = new Node(otherRoot->data);

	copyFromRec(root->left, otherRoot->left);
	copyFromRec(root->right, otherRoot->right);
}
template <typename T>
void BST<T>::freeRec(Node* root)
{
	if (!root)
		return;

	freeRec(root->left);
	freeRec(root->right);

	delete root;
}

template <typename T>
void BST<T>::printRec(Node* root, int space) const
{
	if (!root)
		return;

	int count = 10;

	space += count;
	printRec(root->right, space);

	cout << endl;
	for (int i = count; i < space; i++)
		cout << ' ';
	cout << root->data << endl;

	printRec(root->left, space);
}
template <typename T>
void BST<T>::print() const
{
	printRec(root, 0);
}