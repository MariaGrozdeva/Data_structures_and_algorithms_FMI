#include <iostream>
using namespace std;

template<typename T>
void Swap(T* arr, int x, int y)
{
	T temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

// BC -> O(n), AC = WC -> O(n^2)
template<typename T>
void BubbleSort(T* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		bool isSwapped = false;
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(arr, j, j + 1);
				isSwapped = true;
			}
		}

		if (!isSwapped)
			return;
	}
}

int main()
{
	int arr[8] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	BubbleSort(arr, 8);

	for (int i = 0; i < 8; i++)
		cout << arr[i] << " ";
}