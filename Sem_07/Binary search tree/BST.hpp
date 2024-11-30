#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

template <typename T, typename Compare = std::less<T>>
class BST
{
	struct Node
	{
		T data;

		Node* left = nullptr;
		Node* right = nullptr;

		Node(const T& data) : data(data) {}
	};

public:
	BST();
	explicit BST(const Compare& comp);
	explicit BST(const std::vector<T>& v);

	BST(const BST<T, Compare>& other);
	BST<T, Compare>& operator=(const BST<T, Compare>& other);

	BST(BST<T, Compare>&& other) noexcept;
	BST<T, Compare>& operator=(BST<T, Compare>&& other) noexcept;

	~BST() noexcept;

	bool contains(const T& el) const;
	void insert(const T& el);
	void remove(const T& el);

	size_t getSize() const;
	bool empty() const;

	void print() const;

    	class ForwardIterator
    	{
    	public:
		ForwardIterator(Node* root = nullptr) 
        	{
            		pushLeft(root);
        	}

        	T& operator*() const 
        	{
            		return nodeStack.top()->data;
        	}

        	ForwardIterator& operator++() 
        	{
            		Node* node = nodeStack.top();
            		nodeStack.pop();
            		if (node->right)
			{
                		pushLeft(node->right);
            		}
            		return *this;
        	}

        	ForwardIterator operator++(int)
        	{
            		ForwardIterator old = *this;
            		++(*this);
            		return old;
        	}

        	bool operator!=(const ForwardIterator& other) const 
        	{
            		return nodeStack != other.nodeStack;
        	}

        	bool operator==(const ForwardIterator& other) const 
        	{
            		return nodeStack == other.nodeStack;
        	}

    	private:
        	std::stack<Node*> nodeStack;

        	void pushLeft(Node* node) 
        	{
            		while (node) 
            		{
                		nodeStack.push(node);
                		node = node->left;
            		}
        	}
    	};

    	ForwardIterator begin() const 
    	{
        	return ForwardIterator(root);
    	}

    	ForwardIterator end() const 
    	{
        	return ForwardIterator(nullptr);
    	}

private:
	bool containsRec(const T& el, Node* root, Node*& prev) const;

	void findToRemove(const T& el, Node*& root);
	void removeRec(Node*& root);

	Node*& findMax(Node*& root) const;

	void createBSTRec(Node*& root, const std::vector<T>& v, int start, int end);

	void copyFrom(const BST<T, Compare>& other);
	void copyFromRec(Node*& root, const Node* otherRoot);

	void moveFrom(BST<T, Compare>&& other);

	void free();
	void freeRec(Node* root);

	void printRec(Node* root, unsigned space) const;

	Node* root;
	size_t size;
	Compare comp;
};

template <typename T, typename Compare>
bool BST<T, Compare>::contains(const T& el) const
{
	Node* prev = nullptr;
	return containsRec(el, root, prev);
}

template <typename T, typename Compare>
bool BST<T, Compare>::containsRec(const T& el, Node* root, Node*& prev) const
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
	if (comp(el, root->data))
	{
		return containsRec(el, root->left, prev);
	}
	else
	{
		return containsRec(el, root->right, prev);
	}
}

template <typename T, typename Compare>
void BST<T, Compare>::insert(const T& el)
{
	if (!root)
	{
		root = new Node(el);
		size++;
		return;
	}

	Node* prev = nullptr;
	if (containsRec(el, root, prev))
	{
		return;
	}

	Node* newNode = new Node(el);
	if (comp(el, prev->data))
	{
		prev->left = newNode;
	}
	else
	{
		prev->right = newNode;
	}
}

template <typename T, typename Compare>
void BST<T, Compare>::remove(const T& el)
{
	findToRemove(el, root);
}

template <typename T, typename Compare>
void BST<T, Compare>::findToRemove(const T& el, Node*& root)
{
	if (!root)
	{
		return;
	}

	if (root->data == el)
	{
		removeRec(root);
		size--;
	}
	else if (comp(el, root->data))
	{
		findToRemove(el, root->left);
	}
	else
	{
		findToRemove(el, root->right);
	}
}

template <typename T, typename Compare>
void BST<T, Compare>::removeRec(Node*& root)
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
			maxNode->right = root->right;
           		Node* toDelete = root;
            		root = maxNode;
            		delete toDelete;
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

template <typename T, typename Compare>
class BST<T, Compare>::Node*& BST<T, Compare>::findMax(Node*& root) const
{
	if (!root->right)
	{
		return root;
	}
	return findMax(root->right);
}

template <typename T, typename Compare>
size_t BST<T, Compare>::getSize() const
{
	return size;
}

template <typename T, typename Compare>
bool BST<T, Compare>::empty() const
{
	return size == 0;
}

template <typename T, typename Compare>
BST<T, Compare>::BST()
{
	root = nullptr;
	size = 0;
}

template <typename T, typename Compare>
BST<T, Compare>::BST(const Compare& comp) : BST()
{
	this->comp = comp;
}

template <typename T, typename Compare>
BST<T, Compare>::BST(const std::vector<T>& v)
{
	if (!is_sorted(v.begin(), v.end()))
	{
		throw "Array should be sorted!";
	}
	createBSTRec(root, v, 0, v.size() - 1);
	size = v.size();
}

template <typename T, typename Compare>
BST<T, Compare>::BST(const BST<T, Compare>& other)
{
	copyFrom(other);
}

template <typename T, typename Compare>
BST<T, Compare>& BST<T, Compare>::operator=(const BST<T, Compare>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T, typename Compare>
BST<T, Compare>::BST(BST<T, Compare>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T, typename Compare>
BST<T, Compare>& BST<T, Compare>::operator=(BST<T, Compare>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T, typename Compare>
BST<T, Compare>::~BST() noexcept
{
	free();
}

template <typename T, typename Compare>
void BST<T, Compare>::createBSTRec(Node*& root, const std::vector<T>& v, int start, int end)
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

template <typename T, typename Compare>
void BST<T, Compare>::copyFrom(const BST<T, Compare>& other)
{
	copyFromRec(root, other.root);
	size = other.size;
	comp = other.comp;
}

template <typename T, typename Compare>
void BST<T, Compare>::copyFromRec(Node*& root, const Node* otherRoot)
{
	if (!otherRoot)
	{
		return;
	}

	root = new Node(otherRoot->data);
	copyFromRec(root->left, otherRoot->left);
	copyFromRec(root->right, otherRoot->right);
}

template <typename T, typename Compare>
void BST<T, Compare>::moveFrom(BST<T, Compare>&& other)
{
	root = other.root;
	other.root = nullptr;
	size = other.size;
	other.size = 0;
	comp = other.comp;
}

template <typename T, typename Compare>
void BST<T, Compare>::free()
{
	freeRec(root);
}

template <typename T, typename Compare>
void BST<T, Compare>::freeRec(Node* root)
{
	if (!root)
	{
		return;
	}

	freeRec(root->left);
	freeRec(root->right);
	delete root;
}

template <typename T, typename Compare>
void BST<T, Compare>::print() const
{
	printRec(root, 0);
}

template <typename T, typename Compare>
void BST<T, Compare>::printRec(Node* root, unsigned space) const
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

template <class P>
void swapPointers(P*& left, P*& right)
{
	P* tempPtr = left;
	left = right;
	right = tempPtr;
}
