#include <iostream>

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

int sum(Node* root)
{
	if (!root)
	{
		return 0;
	}
	return root->data + sum(root->left) + sum(root->right);
}

int main()
{
	Node* root = new Node(2);
	Node* n1 = new Node(7);
	Node* n2 = new Node(5);
	Node* n3 = new Node(2);
	Node* n4 = new Node(6);
	Node* n5 = new Node(9);
	Node* n6 = new Node(5);
	Node* n7 = new Node(11);
	Node* n8 = new Node(4);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;
	n5->left = n8;

	std::cout << sum(root);
	free(root);
}
