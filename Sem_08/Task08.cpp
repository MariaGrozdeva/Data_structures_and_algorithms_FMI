#include <iostream>
#include <vector>
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

void fillStrings(Node<char>* root, vector<string>& words, string currentWord)
{
	if (!root)
		return;

	currentWord.push_back(root->data);

	if (!root->left && !root->right)
	{
		words.push_back(currentWord);
		return;
	}

	fillStrings(root->left, words, currentWord);
	fillStrings(root->right, words, currentWord);
}
vector<string> getWords(Node<char>* root)
{
	vector<string> words;
	string currentWord = "";
	fillStrings(root, words, currentWord);

	return words;
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

	vector<string> words = getWords(root);
	for (size_t i = 0; i < words.size(); i++)
		cout << words[i] << endl;
}