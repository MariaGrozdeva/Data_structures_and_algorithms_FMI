#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <vector>

template <typename T>
class AVL
{
private:
	struct Node
	{
	public:
		T* data;
		size_t height;
		size_t size;

		Node* left;
		Node* right;
		Node* parent;

		Node(const T& data) : data(new T(data)), height(1), size(1), left(nullptr), right(nullptr), parent(nullptr)
		{}
		Node(T&& data) : data(new T(std::move(data))), height(1), size(1), left(nullptr), right(nullptr), parent(nullptr)
		{}

		Node(const Node& other)
		{
			copyFrom(other);
		}
		Node(Node&& other)
		{
			moveFrom(std::move(other));
		}
		Node& operator=(const Node& other)
		{
			if (this != &other)
			{
				free();
				copyFrom(other);
			}

			return *this;
		}
		Node& operator=(Node&& other)
		{
			if (this != &other)
			{
				free();
				moveFrom(std::move(other));
			}

			return *this;
		}
		~Node()
		{
			free();
		}

	private:
		void copyFrom(const Node& other)
		{
			data = new T(*other.data);
			height = other.height;
			size = other.size;
		}
		void moveFrom(Node&& other)
		{
			data = other.data;
			other.data = nullptr;
			height = other.height;
			other.height = 0;
			size = other.size;
			other.size = 0;
		}
		void free()
		{
			delete data;
		}


	public:
		void swap(Node& other) // Swapping ONLY pointers.
		{
			std::swap(data, other.data);
		}

		size_t getHeight() const // The height of an empty node is 0.
		{
			if (!this)
				return 0;

			return height;
		}
		size_t getSize() const // The size of an empty node is 0.
		{
			if (!this)
				return 0;

			return size;
		}

		int getBalanceFactor() const // height(right) - height(left). If we want the tree to be AVL, then the balance factor should be in {-1,0,1}.
		{
			return right->getHeight() - left->getHeight();
		}

		void rotateLeft()
		{
			if (!this || !this->right)
				return;

			Node* originalRight = right;

			swap(*right); // Swapping the data pointers of this and this->right.
			right = originalRight->right;
			originalRight->right = originalRight->left;
			originalRight->left = left;
			left = originalRight;

			// Updating the heights of the affected (because of the rotation) nodes.
			left->height = std::max(left->left->getHeight(), left->right->getHeight()) + 1;
			height = std::max(left->getHeight(), right->getHeight()) + 1;

			// Updating the sizes of the affected (because of the rotation) nodes.
			left->size = left->left->getSize() + left->right->getSize() + 1;

			// Updating the parents of the affected (because of the rotation) nodes.
			updateParents();
		}
		void rotateRight()
		{
			if (!this || !this->left)
				return;

			Node* originalLeft = left;

			swap(*left); // Swapping the data pointers of this and this->left.
			left = originalLeft->left;
			originalLeft->left = originalLeft->right;
			originalLeft->right = right;
			right = originalLeft;

			// Updating the heights of the affected (because of the rotation) nodes.
			right->height = std::max(right->left->getHeight(), right->right->getHeight()) + 1;
			height = std::max(left->getHeight(), right->getHeight()) + 1;

			// Updating the sizes of the affected (because of the rotation) nodes.
			right->size = right->left->getSize() + right->right->getSize() + 1;

			// Updating the parents of the affected (because of the rotation) nodes.
			updateParents();
		}

	private:
		void updateParents()
		{
			if (left)
			{
				left->parent = this;
				if (left->left)
					left->left->parent = left;
				if (left->right)
					left->right->parent = left;
			}
			if (right)
			{
				right->parent = this;
				if (right->left)
					right->left->parent = right;
				if (right->right)
					right->right->parent = right;
			}
		}
	};

	void copyFromRec(Node*& root, const Node* otherRoot);
	void freeRec(Node* root);

	void copyFrom(const AVL<T>& other);
	void moveFrom(AVL<T>&& other);
	void free();

public:
	AVL(std::initializer_list<T> iList);

	AVL();
	AVL(const AVL<T>& other);
	AVL(AVL<T>&& other);
	AVL<T>& operator=(const AVL<T>& other);
	AVL<T>& operator=(AVL<T>&& other);
	~AVL();


private:
	void leftLeftCase(Node* current);
	void rightRightCase(Node* current);
	void leftRightCase(Node* current);
	void rightLeftCase(Node* current);

	void update(Node* current);

	void findMax(Node* root, Node*& maxNode) const;
	void eraseRec(Node*& root, const T& el);

	bool containsRec(Node* root, const T& el, Node*& parent) const;

	T& dos(size_t index, const Node* root);
	const T& dos(size_t index, const Node* root) const;

public:
	Node* root = nullptr;

	void insert(const T& el);
	void insert(T&& el);
	void erase(const T& el);

	bool contains(const T& el) const;
	bool empty() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;
};

template <typename T>
void AVL<T>::leftLeftCase(Node* current)
{
	current->rotateRight();
}
template <typename T>
void AVL<T>::rightRightCase(Node* current)
{
	current->rotateLeft();
}
template <typename T>
void AVL<T>::leftRightCase(Node* current)
{
	current->left->rotateLeft();
	current->rotateRight();
}
template <typename T>
void AVL<T>::rightLeftCase(Node* current)
{
	current->right->rotateRight();
	current->rotateLeft();
}

template <typename T>
void AVL<T>::update(Node* current)
{
	if (!current)
		return;

	current->height = 1 + std::max(current->left->getHeight(), current->right->getHeight());
	current->size = 1 + current->left->getSize() + current->right->getSize();

	int balanceFactor = current->getBalanceFactor();

	// If the current node becomes unbalanced, then there are 4 cases:
	if (balanceFactor == -2 && current->left->getBalanceFactor() <= 0)
		leftLeftCase(current);

	else if (balanceFactor == 2 && current->right->getBalanceFactor() >= 0)
		rightRightCase(current);

	else if (balanceFactor == -2 && current->left->getBalanceFactor() >= 0)
		leftRightCase(current);

	else if (balanceFactor == 2 && current->right->getBalanceFactor() <= 0)
		rightLeftCase(current);

	update(current->parent); // Keep going up the tree and updating heights and balance factors.
}

template <typename T>
void AVL<T>::insert(const T& el)
{
	if (!root)
	{
		root = new Node(el);
		return;
	}

	Node* parent = nullptr;
	bool found = containsRec(root, el, parent);
	if (found)
		return;

	Node* newNode = new Node(el);
	if (*(parent->data) > el)
		parent->left = newNode;
	else
		parent->right = newNode;

	newNode->parent = parent;

	update(parent); // Maintain the tree to be AVL. In this update we make <= 2 rotations.
}
template <typename T>
void AVL<T>::insert(T&& el)
{
	if (!root)
	{
		root = new Node(std::move(el));
		return;
	}

	Node* parent = nullptr;
	bool found = containsRec(root, el, parent);
	if (found)
		return;

	Node* newNode = new Node(std::move(el));
	if (*(parent->data) > el)
		parent->left = newNode;
	else
		parent->right = newNode;

	newNode->parent = parent;

	update(parent);
}

template <typename T>
void AVL<T>::findMax(Node* root, Node*& maxNode) const
{
	Node* iter = root;
	while (iter)
	{
		maxNode = iter;
		iter = iter->right;
	}
}
template <typename T>
void AVL<T>::eraseRec(Node*& root, const T& el)
{
	if (!root)
		return;

	Node* parent = nullptr;
	if (!containsRec(root, el, parent))
		return;

	Node*& toErase = parent == nullptr ? root :
		el < *parent->data ? parent->left : parent->right;

	// remove leaf
	if (!toErase->left && !toErase->right)
	{
		Node* toEraseParent = toErase->parent;
		delete toErase;
		toErase = nullptr;

		update(toEraseParent); // Maintain the tree to be AVL. In this update we can make up to O(h) rotations. Therefore deletion of an element in AVL
		                       // is slower than insertion. If we have a lot of deletions (and insertions), Red–black trees are preferred over AVL trees.
	}

	// remove node with only left child (this child is certainly a leaf because the tree is AVL (otherwise, the tree wouldn't be balanced).
	else if (toErase->left && !toErase->right)
	{
		toErase->swap(*toErase->left);
		eraseRec(toErase->left, el);
	}
	// remove node with only right child (this child is certainly a leaf because the tree is AVL (otherwise, the tree wouldn't be balanced).
	else if (!toErase->left && toErase->right)
	{
		toErase->swap(*toErase->right);
		eraseRec(toErase->right, el);
	}

	// remove node with left and right children
	else
	{
		Node* maxNode;
		findMax(toErase->left, maxNode);
		toErase->swap(*maxNode);
		eraseRec(toErase->left, el);
	}
}
template <typename T>
void AVL<T>::erase(const T& el)
{
	eraseRec(root, el);
}

template <typename T>
bool AVL<T>::containsRec(Node* root, const T& el, Node*& parent) const
{
	if (!root)
		return false;
	if (*(root->data) == el)
		return true;

	parent = root;
	if (*(root->data) > el)
		return containsRec(root->left, el, parent);
	containsRec(root->right, el, parent);
}
template <typename T>
bool AVL<T>::contains(const T& el) const
{
	return containsRec(root, el);
}

template <typename T>
bool AVL<T>::empty() const
{
	return root == nullptr;
}

// Allowing index for logarithmic time.
template <typename T>
T& AVL<T>::dos(size_t index, const Node* root)
{
	if (root->left->getSize() == index)
		return *(root->data);
	if (root->left->getSize() > index)
		return dos(index, root->left);
	else
		return dos(index - root->left->getSize() - 1, root->right);
}
template <typename T>
T& AVL<T>::operator[](size_t index)
{
	assert(root && index < root->size);
	return dos(index, root);
}

template <typename T>
const T& AVL<T>::dos(size_t index, const Node* root) const
{
	if (root->left->getSize() == index)
		return *(root->data);
	if (root->left->getSize() > index)
		return dos(index, root->left);
	else
		return dos(index - root->left->getSize() - 1, root->right);
}
template <typename T>
const T& AVL<T>::operator[](size_t index) const
{
	assert(root && index < root->size);
	return dos(index, root);
}

template <typename T>
AVL<T>::AVL(std::initializer_list<T> iList)
{
	for (const T& el : iList)
		insert(el);
}

template <typename T>
AVL<T>::AVL() : root(nullptr)
{}
template <typename T>
AVL<T>::AVL(const AVL<T>& other)
{
	copyFrom(other);
}
template <typename T>
AVL<T>::AVL(AVL<T>&& other)
{
	moveFrom(std::move(other));
}
template <typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
AVL<T>& AVL<T>::operator=(AVL<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}
template <typename T>
AVL<T>::~AVL()
{
	free();
}

template <typename T>
void AVL<T>::copyFrom(const AVL<T>& other)
{
	copyFromRec(root, other.root);
}
template <typename T>
void AVL<T>::moveFrom(AVL<T>&& other)
{
	if (!other.root)
	{
		root = nullptr;
		return;
	}

	root = other.root;
	other.root = nullptr;
}
template <typename T>
void AVL<T>::free()
{
	freeRec(root);
}

template <typename T>
void AVL<T>::copyFromRec(Node*& root, const Node* otherRoot)
{
	if (!otherRoot)
	{
		root = nullptr;
		return;
	}

	root = new Node(*otherRoot);
	root->parent = nullptr;

	copyFromRec(root->left, otherRoot->left);
	copyFromRec(root->right, otherRoot->right);

	if (root->left)
		root->left->parent = root;
	if (root->right)
		root->right->parent = root;
}
template <typename T>
void AVL<T>::freeRec(Node* root)
{
	if (!root)
		return;

	freeRec(root->left);
	freeRec(root->right);

	delete root;
}