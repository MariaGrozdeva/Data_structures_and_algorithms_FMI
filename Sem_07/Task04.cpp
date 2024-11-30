#include <iostream>
#include <string>

template <typename T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;

	Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
void free(Node<T>* root)
{
	if (!root)
	{
		return;
	}
	free(root->left);
	free(root->right);
	delete root;
}

void getEncodedString(const Node<char>* root, const std::string& coding, std::string& toGet, int& index)
{
	if (!root->left && !root->right)
	{
		toGet.push_back(root->data);
		return;
	}
	if (coding[index] == '0')
	{
		getEncodedString(root->left, coding, toGet, ++index);
	}
	else
	{
		getEncodedString(root->right, coding, toGet, ++index);
	}
}

std::string readHuffmanEncoding(const Node<char>* root, const std::string& coding)
{
	std::string toGet = "";
	int index = 0;
	while (coding[index] != '\0')
	{
		getEncodedString(root, coding, toGet, index);
	}
	return toGet;
}

int main()
{
	Node<char>* root = new Node<char>('*');
	Node<char>* n1 = new Node<char>('*');
	Node<char>* n2 = new Node<char>('A');
	Node<char>* n3 = new Node<char>('B');
	Node<char>* n4 = new Node<char>('C');

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;

	std::string coding = "1001011";
	std::cout << readHuffmanEncoding(root, coding);
	free(root);
}
