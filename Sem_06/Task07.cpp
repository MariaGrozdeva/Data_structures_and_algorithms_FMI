#include <iostream>
#include <string>
#include <stdexcept>

struct Node
{
	char data;

	Node* left;
	Node* right;

	Node(char data) : data(data), left(nullptr), right(nullptr) {}
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

// First way
void createWord(Node* root, std::string& word, int k)
{
	if (!root)
	{
		return;
	}
	if (k == 1)
	{
		word.push_back(root->data);
		return;
	}
	createWord(root->left, word, k - 1);
	createWord(root->right, word, k - 1);
}

std::string getWordOnLevel(Node* root, int k)
{
        if (!root || k == 0)
	{
		throw std::invalid_argument("Invalid parameter");
        }
        
	std::string word;
	createWord(root, word, k);
	return word;
}

// Second way
std::string getWordOnLevel2(Node* root, unsigned k)
{
	if (!root || k == 0)
	{
		throw std::invalid_argument("Invalid parameter");
        }
	if (k == 1)
	{
		return std::string(1, root->data);
	}
	return getWordOnLevel2(root->left, k - 1) + getWordOnLevel2(root->right, k - 1);
}

int main()
{
	Node* root = new Node('a');
	Node* n1 = new Node('b');
	Node* n2 = new Node('c');
	Node* n3 = new Node('d');
	Node* n4 = new Node('e');
	Node* n5 = new Node('f');
	Node* n6 = new Node('g');
	Node* n7 = new Node('h');
	Node* n8 = new Node('i');

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;
	n5->left = n8;

	std::cout << getWordOnLevel(root, 3);
	free(root);
}
