#include <iostream>
#include <vector>
#include <stack>

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
template <typename T>
void free(Node<T>* root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

class GraphChar
{
private:
	vector<vector<char>> adjList;

public:
	GraphChar(int n) : adjList(n) 
	{}

	void addEdge(char start, char end)
	{
		adjList[start].push_back(end);
	}
	vector<char> getSuccessors(char vertex) const
	{
		return adjList[vertex];
	}
	int getVerticesCount() const
	{
		return adjList.size();
	}
};

// NOT the optimal solution!!
int toNum(char ch)
{
	return ch - 'a';
}

void getWordsDFS(Node<char>* root, vector<string>& words, string tempWord = "")
{
	if (!root)
		return;

	if (!root->left && !root->right)
	{
		tempWord += root->data;
		words.push_back(tempWord);
		return;
	}

	tempWord += root->data;

	getWordsDFS(root->left, words, tempWord);
	getWordsDFS(root->right, words, tempWord);
}

bool DFS_containsPath(const GraphChar& g, char start, char end, const string& word)
{
	vector<char> visited(g.getVerticesCount(), false);
	stack<char> s;

	s.push(start);
	int currentIndex = 0;

	while (!s.empty())
	{
		char currentVertex = s.top();
		s.pop();

		if (currentVertex == end && currentIndex == word.size() - 1)
			return true;

		if (visited[currentVertex] || currentVertex != toNum(word[currentIndex]))
			continue;

		currentIndex++;
		visited[currentVertex] = true;

		vector<char> successors = g.getSuccessors(currentVertex);
		for (size_t i = 0; i < successors.size(); i++)
			s.push(successors[i]);
	}

	return false;
}
bool checkIfPathExist(const GraphChar& g, const string& word)
{
	char start = toNum(word[0]);
	char end = toNum(word[word.size() - 1]);

	return DFS_containsPath(g, start, end, word);
}

bool checkIfGraphContainsPathFromTree(Node<char>* root, const GraphChar& g)
{
	vector<string> paths;
	getWordsDFS(root, paths);

	for (size_t i = 0; i < paths.size(); i++)
	{
		if (checkIfPathExist(g, paths[i]))
			return true;
	}

	free(root);
	return false;
}

int main()
{
	Node<char>* root = new Node<char>('a');
	Node<char>* n1 = new Node<char>('e');
	Node<char>* n2 = new Node<char>('f');
	Node<char>* n3 = new Node<char>('d');
	Node<char>* n4 = new Node<char>('g');
	Node<char>* n5 = new Node<char>('c');
	Node<char>* n6 = new Node<char>('b');
	Node<char>* n7 = new Node<char>('h');
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n3->left = n6;
	n5->left = n7;

	GraphChar g(8);
	g.addEdge(toNum('a'), toNum('f'));
	g.addEdge(toNum('a'), toNum('d'));
	g.addEdge(toNum('b'), toNum('h'));
	g.addEdge(toNum('c'), toNum('h'));
	g.addEdge(toNum('d'), toNum('e'));
	g.addEdge(toNum('e'), toNum('h'));
	g.addEdge(toNum('f'), toNum('h'));
	g.addEdge(toNum('f'), toNum('c'));
	g.addEdge(toNum('g'), toNum('b'));
	g.addEdge(toNum('g'), toNum('e'));

	cout << checkIfGraphContainsPathFromTree(root, g);
}