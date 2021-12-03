#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
	char data;

	Node* left;
	Node* middle;
	Node* right;

	Node(char data) : data(data), left(nullptr), middle(nullptr), right(nullptr) 
    {}
};

string getTreeFromFile()
{
    string tree;
    ifstream myFile("TripleTree.txt");

    if (myFile.is_open())
    {
        while (!myFile.eof())
            getline(myFile, tree);

        myFile.close();
    }

    return tree;
}

int getEndIndexOfChild(string tree, bool endIndexOfSecChildNeeded = false)
{
    bool foundFirstBr = false;
    int countOfBrackets = 0;
    int size = tree.size();

    if (!endIndexOfSecChildNeeded)
    {
        if (tree[3] == '*')
            return 3;
    }
    int i = 1;
    if (endIndexOfSecChildNeeded)
    {
        i = getEndIndexOfChild(tree) + 2;

        if (tree[i] == '*')
            return i;
    }

    for (i; i < size; i++)
    {
        if (tree[i] == '(')
        {
            countOfBrackets++;
            foundFirstBr = true;
        }
        if (tree[i] == ')')
            countOfBrackets--;

        if (foundFirstBr && countOfBrackets == 0)
            return i;
    }
}

Node* createTreeFromString(string tree)
{
    bool indOfSecChildNeeded = false;

    Node* root = new Node(tree[1]);

    if (tree[0] == '*')
        return nullptr;

    root->left = createTreeFromString(tree.substr(3, getEndIndexOfChild(tree)));
    root->middle = createTreeFromString(tree.substr(getEndIndexOfChild(tree) + 2, getEndIndexOfChild(tree, true)));
    root->right = createTreeFromString(tree.substr(getEndIndexOfChild(tree, true) + 2, tree.size() - 1));

    return root;
}

int height(Node* root)
{
    if (!root)
        return -1;

    return 1 + max(height(root->left), max(height(root->middle), height(root->right)));
}
vector<string> getWordsOnLevel(Node* tree)
{
    int heightOfTree = height(tree);
    vector<Node*> nodesOnLevel;
    vector<string> words;

    nodesOnLevel.push_back(tree);

    for (int j = 0; j <= heightOfTree; j++)
    {
        vector<Node*> nodesOnNextLevel;
        for (int i = 0; i < nodesOnLevel.size(); i++)
        {
            if (nodesOnLevel[i]->left)
                nodesOnNextLevel.push_back(nodesOnLevel[i]->left);
            if (nodesOnLevel[i]->middle)
                nodesOnNextLevel.push_back(nodesOnLevel[i]->middle);
            if (nodesOnLevel[i]->right)
                nodesOnNextLevel.push_back(nodesOnLevel[i]->right);
        }

        string tempWord = "";
        for (int i = 0; i < nodesOnLevel.size(); i++)
            tempWord = tempWord + nodesOnLevel[i]->data;
        words.push_back(tempWord);
        
        nodesOnLevel = nodesOnNextLevel;
    }

    return words;
}

void free(Node* root)
{
    if (!root)
        return;

    free(root->left);
    free(root->middle);
    free(root->right);

    delete root;
}

int main()
{
    string tree = getTreeFromFile();
    Node* root = createTreeFromString(tree);

    vector<string> words = getWordsOnLevel(root);
    int size = words.size();

    for (int i = 0; i < size; i++)
        cout << words[i] << endl;

    free(root);
}