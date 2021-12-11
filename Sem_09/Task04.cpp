#include <iostream>
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

void getEncodedString(Node<char>* root, const string& coding, string& toGet, int& index)
{
	if (!root->left && !root->right)
	{
		toGet.push_back(root->data);
		return;
	}

	if (coding[index] == '0')
		getEncodedString(root->left, coding, toGet, ++index);
	else
		getEncodedString(root->right, coding, toGet, ++index);
}
string readHuffmanEncoding(Node<char>* root, const string& coding)
{
	string toGet = "";

	int index = 0;
	while (coding[index] != '\0')
		getEncodedString(root, coding, toGet, index);

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

	string coding = "1001011";
	string decoding;
	
	decoding = readHuffmanEncoding(root, coding);
	cout << decoding;
}