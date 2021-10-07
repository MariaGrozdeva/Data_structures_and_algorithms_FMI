#include <iostream>
using namespace std;

template<typename T>
void Swap(T* arr, int x, int y)
{
	T temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

// BC = AC = WC -> O(n^2)
// NOT stable - does NOT maintain the relative order of records with equal keys
template<typename T>
void SelectionSort(T* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		int minIndex = i;
		for (int j = minIndex + 1; j < len; j++)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}

		if (minIndex != i)
			Swap(arr, i, minIndex);
	}
}

int main()
{
	int arr[8] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	SelectionSort(arr, 8);

	for (int i = 0; i < 8; i++)
		cout << arr[i] << " ";
}