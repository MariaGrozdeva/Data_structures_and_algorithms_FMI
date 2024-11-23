#include <iostream>
#include <vector>

struct Node
{
	int data;

	Node* left;
	Node* right;

	Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

void free(Node* root)
{
        if (!root)
        {
                return;
        }
        free(root->left);
        free(root->right);
        delete root;
}

unsigned getElementsCount(Node* root)
{
	if (!root)
	{
		return 0;
	}
	return 1 + (getElementsCount(root->left) + getElementsCount(root->right));
}

bool checkIfAllNumbersAreInTree(Node* root, std::vector<bool>& numbers)
{
	if (!root)
	{
		return true;
	}
	if ((root->data < 1 || root->data > numbers.size()) || numbers[root->data - 1])
	{
		return false;
	}
	numbers[root->data - 1] = true;
	return checkIfAllNumbersAreInTree(root->left, numbers) && checkIfAllNumbersAreInTree(root->right, numbers);
}

bool isPermutation(Node* root)
{
	unsigned size = getElementsCount(root);
	std::vector<bool> numbers(size, 0);
	return checkIfAllNumbersAreInTree(root, numbers);
}

int main()
{
	Node* root = new Node(2);
	Node* n1 = new Node(7);
	Node* n2 = new Node(5);
	Node* n3 = new Node(1);
	Node* n4 = new Node(6);
	Node* n5 = new Node(9);
	Node* n6 = new Node(3);
	Node* n7 = new Node(8);
	Node* n8 = new Node(4);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;
	n5->left = n8;

	std::cout << isPermutation(root);
	free(root);
}
