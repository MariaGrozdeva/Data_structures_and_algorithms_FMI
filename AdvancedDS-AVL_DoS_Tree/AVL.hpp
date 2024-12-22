#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdint> // for uintptr_t

template <typename T>
class AVL
{
private:
	struct Node
	{
		T data;
		size_t size;

		// The size of the Node is a multiple of 4. Therefore instances of this structure will be stored in memory addresses such as
		// 0x1000, 0x1004, 0x1008.., but never will be stored in 0x1001, 0x1002, 0x1003 or any other address
		// that cannot be divisible by 4.
		// All binary numbers that are multiples of 4 end with 00.
		// In fact, this means that all pointers of type Node* always have their last two bits set to 0.
		// Therefore balance factors will be hidden in these "free" bits with the following meanings:
		// 0 - both subtrees are of same heights
		// 1 - the tree is left-heavy
		// 2 - the tree is right-heavy
		Node* left;
		Node* right;

		Node(const T& data) : data(data), size(1), left(nullptr), right(nullptr)
		{}
		Node(T&& data) : data(std::move(data)), size(1), left(nullptr), right(nullptr)
		{}
	};

	void copyFromRec(Node*&, const Node*);
	void freeRec(Node*);

	void copyFrom(const AVL<T>&);
	void moveFrom(AVL<T>&&);
	void free();

public:
	AVL(std::initializer_list<T>);

	AVL();
	AVL(const AVL<T>&);
	AVL(AVL<T>&&);
	AVL<T>& operator=(const AVL<T>&);
	AVL<T>& operator=(AVL<T>&&);
	~AVL();

private:
	void rotateLeft(Node*&);
	void rotateRight(Node*&);

	void leftLeftCase(Node*&);
	void rightRightCase(Node*&);
	void leftRightCase(Node*&);
	void rightLeftCase(Node*&);

	void updateBfsAndMakeRotations(Node*&, bool);
	void updateBalanceFactors(Node*&, bool&, bool, bool = true);

	bool insertRec(Node*&, const T&, bool&);
	bool insertRec(Node*&, T&&, bool&);

	Node*& findMax(Node*&, bool&);
	bool deletionAndUpdate(Node*&, bool&);
	bool eraseRec(Node*&, const T&, bool&, bool);

	bool containsRec(const Node*, const T&) const;

	T& dos(Node*, size_t);
	const T& dos(const Node*, size_t) const;
	
	int rankRec(const Node*, const T&) const;

public:
	Node* root = nullptr;

	bool insert(const T&);
	bool insert(T&&);

	bool erase(const T&);

	bool contains(const T&) const;
	bool empty() const;
	size_t size() const;

	T& operator[](size_t);
	const T& operator[](size_t) const;
	
	int rank(const T&) const;
};

template <typename T>
bool AVL<T>::insertRec(Node*& root, const T& el, bool& existBfZero)
{
	bool toLeft = false;
	if (!root)
	{
		root = new Node(el);
		return true;
	}

	if (root->data > el)
	{
		short int oldBf = getBf(root->left);
		cleansePointer(root->left);

		bool res = insertRec(root->left, el, existBfZero);

		putBf(root->left, oldBf);

		if (res)
		{
			toLeft = true;
			root->size++;
			updateBalanceFactors(root, existBfZero, toLeft);
		}
		return res;
	}
	else if (root->data < el)
	{
		bool res = insertRec(root->right, el, existBfZero);

		if (res)
		{
			toLeft = false;
			root->size++;
			updateBalanceFactors(root, existBfZero, toLeft);
		}
		return res;
	}
	else
	{
		return false;
	}
}
template <typename T>
bool AVL<T>::insert(const T& el)
{
	bool existBfZero = false;
	return insertRec(root, el, existBfZero);
}
template <typename T>
bool AVL<T>::insertRec(Node*& root, T&& el, bool& existBfZero)
{
	bool toLeft = false;
	if (!root)
	{
		root = new Node(std::move(el));
		return true;
	}

	if (root->data > el)
	{
		short int oldBf = getBf(root->left);
		cleansePointer(root->left);

		bool res = insertRec(root->left, std::move(el), existBfZero);

		putBf(root->left, oldBf);

		if (res)
		{
			toLeft = true;
			root->size++;
			updateBalanceFactors(root, existBfZero, toLeft);
		}
		return res;
	}
	else if (root->data < el)
	{
		bool res = insertRec(root->right, std::move(el), existBfZero);

		if (res)
		{
			toLeft = false;
			root->size++;
			updateBalanceFactors(root, existBfZero, toLeft);
		}
		return res;
	}
	else
	{
		return false;
	}
}
template <typename T>
bool AVL<T>::insert(T&& el)
{
	bool existBfZero = false;
	return insertRec(root, std::move(el), existBfZero);
}

template <typename T>
typename AVL<T>::Node*& AVL<T>::findMax(Node*& root, bool& existBfZero)
{
	if (!root->right)
	{
		if (root->left)
		{
			root->size--;
			updateBalanceFactors(root, existBfZero, true, false);
		}
		return root;
	}

	Node*& maxNode = findMax(root->right, existBfZero);
	root->size--;
	updateBalanceFactors(root, existBfZero, false, false);
	return maxNode;
}
template <typename T>
bool AVL<T>::deletionAndUpdate(Node*& root, bool& existBfZero)
{
	Node* rootLeftCleaned = getCleanedPointer(root->left);
	root->size--;

	// remove leaf
	if (!rootLeftCleaned && !root->right)
	{
		delete root;
		root = nullptr;
	}
	// remove node with only left or right child
	else if ((rootLeftCleaned && !root->right) || (!rootLeftCleaned && root->right))
	{
		Node* toDelete = rootLeftCleaned ? rootLeftCleaned : root->right;
		swapPointers(root, toDelete);
		delete toDelete;
	}
	// remove node with left and right children
	else
	{
		short int oldBf = getBf(root->left);
		cleansePointer(root->left);

		Node*& maxNode = findMax(root->left, existBfZero);

		Node* oldRootLeft = root->left;
		Node* oldRootRight = root->right;
		Node* oldMaxNodeLeft = maxNode->left;

		if (maxNode == root->left) // the case in which root and maxNode are adjacent
		{
			maxNode->right = root->right;
           		Node* toDelete = root;
            		root = maxNode;
            		delete toDelete;
		}
		else
		{
			swapPointers(root, maxNode);
			std::swap(root->size, maxNode->size);

			root->left = oldRootLeft;
			root->right = oldRootRight;
			maxNode->left = oldMaxNodeLeft;
			maxNode->right = nullptr;

			deletionAndUpdate(maxNode, existBfZero);
		}
		putBf(root->left, oldBf);
		updateBalanceFactors(root, existBfZero, true, false);
	}
	return true;
}
template <typename T>
bool AVL<T>::eraseRec(Node*& root, const T& el, bool& existBfZero, bool toLeft)
{
	if (!root)
		return false;

	if (root->data > el)
	{
		short int oldBf = getBf(root->left);
		cleansePointer(root->left);

		toLeft = true;
		bool res = eraseRec(root->left, el, existBfZero, toLeft);

		putBf(root->left, oldBf);

		if (res)
		{
			root->size--;
			updateBalanceFactors(root, existBfZero, toLeft, false);
		}
		return res;
	}
	else if (root->data < el)
	{
		toLeft = false;
		bool res = eraseRec(root->right, el, existBfZero, toLeft);

		if (res)
		{
			root->size--;
			updateBalanceFactors(root, existBfZero, toLeft, false);
		}
		return res;
	}
	else
	{
		return deletionAndUpdate(root, existBfZero);
	}
}
template <typename T>
bool AVL<T>::erase(const T& el)
{
	bool existBfZero = true;
	bool toLeft = false;
	return eraseRec(root, el, existBfZero, toLeft);
}

template <typename T>
bool AVL<T>::containsRec(const Node* root, const T& el) const
{
	if (!root)
		return false;
	if (root->data == el)
		return true;

	if (root->data > el)
		return containsRec(getCleanedPointer(root->left), el);
	else
		return containsRec(root->right, el);
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
template <typename T>
size_t AVL<T>::size() const
{
	return root ? root->size : 0;
}

// Allowing index for logarithmic time.
template <typename T>
T& AVL<T>::dos(Node* root, size_t index)
{
	size_t leftSize = getCleanedPointer(root->left) ? getCleanedPointer(root->left)->size : 0;
	if (leftSize == index)
		return root->data;
	else if (leftSize > index)
		return dos(getCleanedPointer(root->left), index);
	else
		return dos(root->right, index - leftSize - 1);
}
template <typename T>
T& AVL<T>::operator[](size_t index)
{
	assert(root && index < root->size);
	return dos(root, index);
}

template <typename T>
const T& AVL<T>::dos(const Node* root, size_t index) const
{
	size_t leftSize = getCleanedPointer(root->left) ? getCleanedPointer(root->left)->size : 0;
	if (leftSize == index)
		return root->data;
	else if (leftSize > index)
		return dos(getCleanedPointer(root->left), index);
	else
		return dos(root->right, index - leftSize - 1);
}
template <typename T>
const T& AVL<T>::operator[](size_t index) const
{
	assert(root && index < root->size);
	return dos(root, index);
}

template <typename T>
int AVL<T>::rankRec(const Node* root, const T& el) const
{
        if (!root)
                return -1;
        
        int leftSize = getCleanedPointer(root->left) ? getCleanedPointer(root->left)->size : 0;
    
        if (root->data == el)
                return leftSize;
        if (root->data > el)
                return rankRec(getCleanedPointer(root->left), el);
        else
        {
                int rightRank = rankRec(root->right, el);
                if (rightRank == -1) 
                        return -1; // If element is not found in the right subtree, propagate -1
                return leftSize + 1 + rightRank;
        }
}
template <typename T>
int AVL<T>::rank(const T& el) const
{
        return rankRec(root, el);
}

template <typename T>
void AVL<T>::rotateLeft(Node*& root)
{
	if (!root || !root->right)
		return;

	short int rootBf = getBf(root->left) == 3 ? 2 : getBf(root->left); // in the left rotation the invalid balance factor 3 means 2
	short int rootRightBf = getBf(root->right->left) == 3 ? 2 : getBf(root->right->left);

	cleansePointer(root->right->left);

	size_t rightSize = root->right->size;
	Node* originalRoot = root;
	Node* originalRootRightLeft = root->right->left;

	root = root->right;
	root->left = originalRoot;
	originalRoot->right = originalRootRightLeft;

	// Updating the sizes and balance factors of the affected (because of the rotation) nodes.
	root->size = originalRoot->size;
	root->left->size = originalRootRightLeft ? root->size - rightSize + originalRootRightLeft->size : root->size - rightSize;
	
	putBf(root->left->left, rootBf - 1 - std::max<short int>(rootRightBf, 0));
	putBf(root->left, rootRightBf - 1 + std::min<short int>(getBf(root->left->left), 0));
}
template <typename T>
void AVL<T>::rotateRight(Node*& root)
{
	if (!root || !getCleanedPointer(root->left))
		return;

	short int rootBf = getBf(root->left) == 3 ? -2 : getBf(root->left); // in the right rotation the invalid balance factor 3 means -2
	short int rootLeftBf = getBf(getCleanedPointer(root->left)->left) == 3 ? -2 : getBf(getCleanedPointer(root->left)->left);

	cleansePointer(root->left);
	cleansePointer(root->left->right);

	size_t leftSize = root->left->size;
	Node* originalRoot = root;
	Node* originalRootLeftRight = root->left->right;

	root = root->left;
	root->right = originalRoot;
	originalRoot->left = originalRootLeftRight;

	// Updating the sizes and balance factors of the affected (because of the rotation) nodes.
	root->size = originalRoot->size;
	root->right->size = originalRootLeftRight ? root->size - leftSize + originalRootLeftRight->size : root->size - leftSize;

	putBf(root->right->left, rootBf + 1 - std::min<short int>(rootLeftBf, 0));
	putBf(root->left, rootLeftBf + 1 + std::max<short int>(getBf(root->right->left), 0));
}

template <typename T>
void AVL<T>::leftLeftCase(Node*& root)
{
	cleansePointer(root); // root may be the left child of other node
	rotateRight(root);
}
template <typename T>
void AVL<T>::rightRightCase(Node*& root)
{
	cleansePointer(root); // root may be the left child of other node
	rotateLeft(root);
}
template <typename T>
void AVL<T>::leftRightCase(Node*& root)
{
	cleansePointer(root); // root may be the left child of other node
	short int oldBf = getBf(root->left);
	cleansePointer(root->left);

	rotateLeft(root->left);
	putBf(root->left, oldBf);
	rotateRight(root);
}
template <typename T>
void AVL<T>::rightLeftCase(Node*& root)
{
	cleansePointer(root); // root may be the left child of other node

	rotateRight(root->right);
	rotateLeft(root);
}

template <typename T>
void AVL<T>::updateBfsAndMakeRotations(Node*& root, bool shouldDecreaseBf)
{
	Node* cleanedRoot = getCleanedPointer(root); // root may be the left child of other node
	short int currentBf = getBf(cleanedRoot->left);

	if (shouldDecreaseBf)
		currentBf--;
	else
		currentBf++;

	if (currentBf != -2 && currentBf != 2) // Balance factor is valid.
	{
		putBf(root->left, currentBf);
	}
	else // Balance factor is -2 or 2 (invalid!). A rotation must be done.
	{
		if (shouldDecreaseBf) // bf is -2
		{
			putBf(root->left, -2);
			if (getBf(getCleanedPointer(cleanedRoot->left)->left) <= 0)
				leftLeftCase(root);
			else if (getBf(getCleanedPointer(cleanedRoot->left)->left) >= 0)
				leftRightCase(root);
		}
		else // bf is 2
		{
			putBf(root->left, 2);
			if (getBf(cleanedRoot->right->left) >= 0)
				rightRightCase(root);
			else if (getBf(cleanedRoot->right->left) <= 0)
				rightLeftCase(root);
		}
	}
}
template <typename T>
void AVL<T>::updateBalanceFactors(Node*& root, bool& existBfZero, bool toLeft, bool calledFromInsert)
{
	// We use existBfZero in order to check if the height has changed (it has changed if there is NOT bf = 0).
	if ((existBfZero && calledFromInsert) || (!existBfZero && !calledFromInsert))
		return;

	if ((toLeft && calledFromInsert) || (!toLeft && !calledFromInsert))
		updateBfsAndMakeRotations(root, true);
	else if ((!toLeft && calledFromInsert) || (toLeft && !calledFromInsert))
		updateBfsAndMakeRotations(root, false);

	existBfZero = (getBf(root->left) == 0);
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

	root = new Node(otherRoot->data);
	root->size = otherRoot->size;

	copyFromRec(root->left, getCleanedPointer(otherRoot->left));
	copyFromRec(root->right, otherRoot->right);

	putBf(root->left, getBf(otherRoot->left));
}
template <typename T>
void AVL<T>::freeRec(Node* root)
{
	if (!root)
		return;

	freeRec(getCleanedPointer(root->left));
	freeRec(root->right);

	delete root;
}

// --------------------------------------------
// Hides the bf in the pointer ptr.
// If bf is 0, it is hidden in the pointer as 0. If bf is -1, it is hidden as 1. If bf is 1, it is hidden as 2.
// If bf is -2 or 2 (invalid balance factors which should be temporarily put to show that a rotation must be done), it is hidden as 3.
template <typename P>
void putBf(P*& ptr, short int bf)
{
	cleansePointer(ptr);

	if (bf == 0)
		return;
	else if (bf == -1)
		bf = 1;
	else if (bf == 1)
		bf = 2;
	else if (bf == -2 || bf == 2)
		bf = 3;

	assert(bf < 4);
	uintptr_t ptrWithHiddenBf = (uintptr_t)ptr | bf;
	ptr = (P*)ptrWithHiddenBf;
}

// Extracts the hidden bf from the pointer ptr.
// Returns -1 if the tree is left-heavy, 0 if both subtrees are of same heights, 1 if the tree is right-heavy.
template <typename P>
short int getBf(P* ptr)
{
	unsigned short int bf = (unsigned short int)((uintptr_t)ptr & 3);
	assert(bf < 4);

	if (bf == 0)
		return 0;
	else if (bf == 1)
		return -1;
	else if (bf == 2)
		return 1;
	else
		return bf;
}

// Removes the hidden bf from the pointer ptr.
template <typename P>
void cleansePointer(P*& ptr)
{
	uintptr_t cleaned = (uintptr_t)ptr & ~3;
	ptr = (P*)cleaned;
}
// Returns the original pointer ptr (without the hidden bf).
template <typename P>
P* getCleanedPointer(P* ptr)
{
	return (P*)((uintptr_t)ptr & ~3);
}

template <typename P>
void swapPointers(P*& left, P*& right)
{
	// swap balance factors (to KEEP THE ORIGINAL ONES!)
	short int tempBf = getBf(left);
	putBf(left, getBf(right));
	putBf(right, tempBf);

	// swap pointers
	P* tempPtr = left;
	left = right;
	right = tempPtr;
}
// --------------------------------------------
