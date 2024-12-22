#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> getNextLevel(const std::vector<int>& currLevel, const std::vector<int>& parentArray)
{
	std::vector<int> nextLevel;
	for (size_t i = 0; i < parentArray.size(); i++)
	{
		int currVertexParent = parentArray[i];
		auto it = std::find(currLevel.cbegin(), currLevel.cend(), currVertexParent);
		if (it != currLevel.cend())
		{
			nextLevel.push_back(i);
		}
	}
	return nextLevel;
}

int getHeight(const std::vector<int>& parentArray)
{
	std::vector<int> currentLevel = { -1 };
	int level = -1;
	while (!currentLevel.empty())
	{
		level++;
		currentLevel = getNextLevel(currentLevel, parentArray);
	}
	return level - 1;
}

int main()
{
	std::vector<int> v = { -1, 0, 1, 2 };
	std::cout << getHeight(v);
}
