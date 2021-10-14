#include <iostream>
using namespace std;

template<typename T>
void Swap(T* arr, int x, int y)
{
	T temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

//7.0. Partition function - puts the pivot on the right position and returns its index
template <typename T>
int Partition(T* arr, int len)
{
	T pivot = arr[len / 2];

	int i = 0;
	int j = len - 1;

	while (true)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;

		if (arr[i] == arr[j])
			i++;
		if (i < j)
			Swap(arr, i, j);
		else
			return j;
	}
}

template <typename T>
void QuickSort(T* arr, int len)
{
	if (len <= 1)
		return;

	int pivotIndex = Partition<T>(arr, len);

	QuickSort(arr, pivotIndex);
	QuickSort(arr + pivotIndex + 1, len - pivotIndex - 1);
}

int main()
{
	int arr[6] = { 6, 70, 7, 3, 4, 12 };
	QuickSort(arr, 6);

	for (int i = 0; i < 6; i++)
		cout << arr[i] << " ";
}