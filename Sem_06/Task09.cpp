#include <iostream>
#include <vector>
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

void fillStrings(Node* root, std::vector<std::string>& words, std::string currentWord)
{
	if (!root)
	{
		return;
	}

	currentWord.push_back(root->data);
	if (!root->left && !root->right)
	{
		words.push_back(currentWord);
		return;
	}
	fillStrings(root->left, words, currentWord);
	fillStrings(root->right, words, currentWord);
}

std::vector<std::string> getWords(Node* root)
{
	std::vector<std::string> words;
	std::string currentWord = "";
	fillStrings(root, words, currentWord);
	return words;
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

        std::vector<std::string> words = getWords(root);
	for (size_t i = 0; i < words.size(); i++)
	{
		std::cout << words[i] << std::endl;
	}
	free(root);
}
