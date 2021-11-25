#include <iostream>
#include <string>

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

// First way
void fillString(Node<char>* root, string& word, int k)
{
	if (!root)
		return;

	if (k == 1)
	{
		word.push_back(root->data);
		return;
	}

	fillString(root->left, word, k - 1);
	fillString(root->right, word, k - 1);
}
string getWordOnLevel(Node<char>* root, int k)
{
	string word;
	fillString(root, word, k);

	return word;
}

// Second way
string buildString(Node<char>* root, int k)
{
	if (!root)
		return "";

	if (k == 1)
		return string(1, root->data);

	return buildString(root->left, k - 1) + buildString(root->right, k - 1);
}
string getWordOnLevel2(Node<char>* root, int k)
{
	string word;
	return buildString(root, k);
}

int main()
{
	Node<char>* root = new Node<char>('a');
	Node<char>* n1 = new Node<char>('b');
	Node<char>* n2 = new Node<char>('c');
	Node<char>* n3 = new Node<char>('d');
	Node<char>* n4 = new Node<char>('e');
	Node<char>* n5 = new Node<char>('f');
	Node<char>* n6 = new Node<char>('g');
	Node<char>* n7 = new Node<char>('h');
	Node<char>* n8 = new Node<char>('i');

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;
	n5->left = n8;

	cout << getWordOnLevel(root, 3);
}