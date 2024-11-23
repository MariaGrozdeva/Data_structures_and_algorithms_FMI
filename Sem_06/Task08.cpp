#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

struct Node
{
	char data;

	std::vector<Node*> children;

	Node(char data) : data(data) {}
};

void free(Node* root)
{
        if (!root)
        {
                return;
        }
        for (Node* child : root->children)
        {
                free(child);
        }
        delete root;
}

void printByLevels(Node* root)
{
        std::vector<const Node*> currLevel{ root };

        while (!currLevel.empty())
        {
                std::vector<const Node*> nextLevel;
                for (const Node* curr : currLevel)
                {
                        std::cout << curr->data;
                        for (const Node* child : curr->children)
                        {
                                nextLevel.push_back(child);
                        }
                }
                std::cout << std::endl;
                currLevel = nextLevel;
        }
}

int main()
{
        Node* root = new Node{ 'a' };
        root->children.push_back(new Node{'b'});
        root->children.push_back(new Node{ 'c' });
        root->children.push_back(new Node{ 'd' });
        root->children.at(0)->children.push_back(new Node{ 'x' });
        root->children.at(0)->children.push_back(new Node{ 'y' });

        printByLevels(root);
        free(root);
}
