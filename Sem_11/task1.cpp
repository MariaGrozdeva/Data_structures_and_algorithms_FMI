#include<iostream>
#include<vector>

using Graph = std::vector<std::vector<char>>;
using Vertex = std::vector<char>;

struct Node {
	char data;
	Node* left;
	Node* right;

	Node(char d, Node* l = nullptr, Node* r = nullptr) : data(d), left(l), right(r) {}
};

Vertex emptyVertex() {
	Vertex emptyVert;
	emptyVert.push_back('\0');
	return emptyVert;
}

void addVertex(int start, int end, Graph& g) {
	g[start].push_back(end);
}

int fromLiteral(char c) {
	return c - 'a';
}

Vertex getVertex(char vert, Graph& g) {
	if (fromLiteral(vert) >= g.size())
		return emptyVertex();
	return g[fromLiteral(vert)];
}

Vertex next(const Vertex& curr, char to, Graph& g) {
	int length = curr.size();
	for (int i = 0; i < length; i++)
		if (to == curr[i])
			return g[fromLiteral(curr[i])];
	return emptyVertex();
}

void solution(const Node* root, Graph g, Vertex cVert, std::string currentWord) {
	if (!root)
		return;

	//start case
	Vertex nextVert;
	if (cVert == emptyVertex())
		nextVert = getVertex(root->data, g);
	else
		nextVert = next(cVert, root->data, g);
	if (nextVert != emptyVertex()) {
		if (!root->left && !root->right) {
			std::cout << currentWord + root->data << std::endl;
			return;
		}

		currentWord += root->data;
		solution(root->left, g, nextVert, currentWord);
		solution(root->right, g, nextVert, currentWord);
	}
}

int main() {
	Node* root = new Node('a');
	Node* n1 = new Node('e');
	Node* n2 = new Node('f');
	Node* n3 = new Node('d');
	Node* n4 = new Node('g');
	Node* n5 = new Node('c');
	Node* n6 = new Node('b');
	Node* n7 = new Node('h');
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n3->left = n6;
	n5->left = n7;

	Graph g;
	g.resize(10);
	addVertex(fromLiteral('a'), 'd', g);
	addVertex(fromLiteral('d'), 'e', g);
	addVertex(fromLiteral('e'), 'h', g);
	addVertex(fromLiteral('a'), 'f', g);
	addVertex(fromLiteral('f'), 'c', g);
	addVertex(fromLiteral('f'), 'h', g);
	addVertex(fromLiteral('c'), 'h', g);
	addVertex(fromLiteral('g'), 'b', g);
	addVertex(fromLiteral('g'), 'e', g);
	addVertex(fromLiteral('b'), 'h', g);

	solution(root, g, emptyVertex(), "");
}
