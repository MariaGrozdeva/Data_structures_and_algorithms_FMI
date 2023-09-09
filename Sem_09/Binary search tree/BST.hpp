#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class BST
{
private:
	struct Node
	{
		T data;

		Node* left = nullptr;
		Node* right = nullptr;

		Node(const T& data) : data(data)
		{}
	};

	Node* root;

public:
	BST();

	BST(const std::vector<T>& v);

	BST(const BST<T>& other);

	BST<T>& operator=(const BST<T>& other);

	~BST();

private:
	void createBSTRec(Node*& root, const std::vector<T>& v, unsigned start, unsigned end);

	void copyFrom(const BST<T>& other);

	void copyFromRec(Node*& root, Node* otherRoot);

	void free();

	void freeRec(Node* root);

	void printRec(Node* root, unsigned space) const;

	bool containsRec(const T& el, Node* root, Node*& prev) const;

	void findToRemove(const T& el, Node*& root);

	void removeRec(Node*& root);

	Node*& findMax(Node*& root) const;

public:
	bool contains(const T& el) const;

	void insert(const T& el);

	void remove(const T& el);

	void print() const;
};

template <typename T>
bool BST<T>::contains(const T& el) const
{
	Node* prev = nullptr;
	return containsRec(el, root, prev);
}

template <typename T>
bool BST<T>::containsRec(const T& el, Node* root, Node*& prev) const
{
	if (!root)
	{
		return false;
	}
	if (root->data == el)
	{
		return true;
	}

	prev = root;
	if (el < root->data)
	{
		return containsRec(el, root->left, prev);
	}
	else
	{
		return containsRec(el, root->right, prev);
	}
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
	{
		return;
	}

	Node* newNode = new Node(el);
	if (el < prev->data)
	{
		prev->left = newNode;
	}
	else
	{
		prev->right = newNode;
	}
}

template <typename T>
void BST<T>::remove(const T& el)
{
	findToRemove(el, root);
}

template <typename T>
void BST<T>::findToRemove(const T& el, Node*& root)
{
	if (!root)
	{
		return;
	}

	if (root->data == el)
	{
		removeRec(root);
	}
	else if (el < root->data)
	{
		findToRemove(el, root->left);
	}
	else
	{
		findToRemove(el, root->right);
	}
}

template <typename T>
void BST<T>::removeRec(Node*& root)
{
	if (!root)
	{
		return;
	}

	// remove leaf
	if (!root->left && !root->right)
	{
		delete root;
		root = nullptr;
	}
	// remove node with only one child
	else if (!root->left || !root->right)
	{
		Node* toDelete = root->left ? root->left : root->right;
		swapPointers(root, toDelete);
		delete toDelete;
		toDelete = nullptr;
	}
	// remove node with both left and right child
	else
	{
		Node*& maxNode = findMax(root->left);

		Node* oldRootLeft = root->left;
		Node* oldRootRight = root->right;
		Node* oldMaxNodeLeft = maxNode->left;

		if (maxNode == root->left) // the case in which root and maxNode are adjacent
		{
			Node* maxNodeNotRef = maxNode;
			swapPointers(root, maxNodeNotRef);

			root->left = maxNodeNotRef;
			root->right = oldRootRight;
			maxNodeNotRef->left = oldMaxNodeLeft;
			maxNodeNotRef->right = nullptr;

			removeRec(root->left);
		}
		else
		{
			swapPointers(root, maxNode);

			root->left = oldRootLeft;
			root->right = oldRootRight;
			maxNode->left = oldMaxNodeLeft;
			maxNode->right = nullptr;

			removeRec(maxNode);
		}
	}
}

template <typename T>
typename BST<T>::Node*& BST<T>::findMax(Node*& root) const
{
	if (!root->right)
	{
		return root;
	}

	Node*& maxNode = findMax(root->right);
	return maxNode;
}

template <typename T>
BST<T>::BST()
{
	root = nullptr;
}

template <typename T>
BST<T>::BST(const std::vector<T>& v)
{
	if (!is_sorted(v.begin(), v.end()))
	{
		throw "Array should be sorted!";
	}
	createBSTRec(root, v, 0, v.size() - 1);
}

template <typename T>
void BST<T>::createBSTRec(Node*& root, const std::vector<T>& v, unsigned start, unsigned end)
{
	if (start > end)
	{
		root = nullptr;
		return;
	}

	unsigned mid = start + (end - start) / 2;
	root = new Node(v[mid]);

	createBSTRec(root->left, v, start, mid - 1);
	createBSTRec(root->right, v, mid + 1, end);
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
void BST<T>::copyFrom(const BST<T>& other)
{
	copyFromRec(root, other.root);
}

template <typename T>
void BST<T>::copyFromRec(Node*& root, Node* otherRoot)
{
	if (!otherRoot)
	{
		return;
	}

	root = new Node(otherRoot->data);
	copyFromRec(root->left, otherRoot->left);
	copyFromRec(root->right, otherRoot->right);
}

template <typename T>
void BST<T>::free()
{
	freeRec(root);
}

template <typename T>
void BST<T>::freeRec(Node* root)
{
	if (!root)
	{
		return;
	}

	freeRec(root->left);
	freeRec(root->right);
	delete root;
}

template <typename T>
void BST<T>::print() const
{
	printRec(root, 0);
}

template <typename T>
void BST<T>::printRec(Node* root, unsigned space) const
{
	if (!root)
	{
		return;
	}

	unsigned count = 10;
	space += count;
	printRec(root->right, space);

	std::cout << std::endl;
	for (size_t i = count; i < space; i++)
	{
		std::cout << ' ';
	}
	std::cout << root->data << std::endl;

	printRec(root->left, space);
}

template <typename P>
void swapPointers(P*& left, P*& right)
{
	P* tempPtr = left;
	left = right;
	right = tempPtr;
}
