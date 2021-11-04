#include <iostream>
#include <queue>

using namespace std;

bool areSignsTheSame(int n, int k)
{
	return (n > 0 && k > 0) || (n < 0 && k < 0);
}

bool areEqualSubsequences(int* arr, int len)
{
	queue<int> subsequence;

	for (size_t i = 0; i < len; i++)
	{
		if (arr[i] == 0)
			continue;

		if (subsequence.empty())
		{
			subsequence.push(arr[i]);
			continue;
		}

		int currentInArray = arr[i];
		int currentInQueue = subsequence.front();

		if (areSignsTheSame(currentInArray, currentInQueue))
			subsequence.push(currentInArray);
		else
		{
			if (-currentInArray != currentInQueue)
				return false;
			else
				subsequence.pop();
		}
	}
	return subsequence.empty();
}

int main()
{
	int arr[] = { 1, 5, -1, 4, -5, 9, 8, -4, -9, 18, -8, -18, -7, 7 };
	cout << areEqualSubsequences(arr, sizeof(arr) / sizeof(int));
}