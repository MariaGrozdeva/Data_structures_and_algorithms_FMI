#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct NodeFull
{
	int data;
	vector<NodeFull*> children;

	NodeFull(int data) : data(data) 
	{}
};
template <typename T>
void free(NodeFull* root)
{
	for (size_t i = 0; i < root->children.size(); i++)
		free(root->children[i]);

	delete root;
}

bool isTreeSeenTheSameFromBothSides(NodeFull* root, vector<int>& view)
{
	vector<NodeFull*> current;
	current.push_back(root);

	while (!current.empty())
	{
		vector<NodeFull*> next;

		if (current[0]->data != current[current.size() - 1]->data)
		{
			view.clear();
			return false;
		}

		view.push_back(current[0]->data);

		for (size_t i = 0; i < current.size(); i++)
			next.insert(next.end(), current[i]->children.begin(), current[i]->children.end());

		current = next;
	}

	free(root);
	return true;
}

int main()
{
	NodeFull* root = new NodeFull(5);

	(root->children).push_back(new NodeFull(22));
	(root->children).push_back(new NodeFull(23));
	(root->children).push_back(new NodeFull(22));
	(root->children[0]->children).push_back(new NodeFull(24));
	(root->children[1]->children).push_back(new NodeFull(66));
	(root->children[1]->children[0]->children).push_back(new NodeFull(7));
	(root->children[2]->children).push_back(new NodeFull(8));
	(root->children[2]->children).push_back(new NodeFull(24));

	vector<int> view;
	cout << isTreeSeenTheSameFromBothSides(root, view) << endl;

	for (size_t i = 0; i < view.size(); i++)
		cout << view[i] << ' ';
}