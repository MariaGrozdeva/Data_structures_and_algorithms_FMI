#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Interval
{
	int start;
	int end;

	Interval(int start, int end) : start(start), end(end) 
	{}

	int getAverage() const
	{
		return (start + end) / 2;
	}
};

struct NodeInterval
{
	Interval interval;

	NodeInterval* left;
	NodeInterval* right;

	NodeInterval(const Interval& interval) : interval(interval), left(nullptr), right(nullptr) 
	{}
};
template <typename T>
void free(NodeInterval* root)
{
	if (!root)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

bool intersection(const Interval& int1, const Interval& int2)
{
	return !(int1.end < int2.start || int1.start > int2.end);
}
bool noEmptyIntersection(NodeInterval* root, const Interval& interval)
{
	if (!root)
		return true;

	if (!intersection(root->interval, interval))
		return false;

	return noEmptyIntersection(root->left, interval) && noEmptyIntersection(root->right, interval);
}

void getMaxIntervalHelper(NodeInterval* currRoot, NodeInterval*& currMax, NodeInterval* root)
{
	if (!currRoot || currMax)
		return;

	getMaxIntervalHelper(currRoot->right, currMax, root);

	if (!currMax && noEmptyIntersection(root, currRoot->interval))
	{
		currMax = currRoot;
		return;
	}

	getMaxIntervalHelper(currRoot->left, currMax, root);
}
Interval getMaxInterval(NodeInterval* root)
{
	NodeInterval* currMax = nullptr;
	getMaxIntervalHelper(root, currMax, root);

	if (!currMax)
		return move(Interval(0, 0));

	return currMax->interval;
}

int main()
{
	NodeInterval* root = new NodeInterval({ 8,12 });
	NodeInterval* n1 = new NodeInterval({ 6,10 }); // Replace with {6,8} and getMaxInterval(root) will return {8,12}
	NodeInterval* n2 = new NodeInterval({ 10,20 });
	NodeInterval* n3 = new NodeInterval({ 7,12 });
	NodeInterval* n4 = new NodeInterval({ 11,18 });
	NodeInterval* n5 = new NodeInterval({ 10,30 });
	root->left = n1;
	root->right = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;

	cout << '[' << getMaxInterval(root).start << ' ' << getMaxInterval(root).end << ']';
	free(root);
}