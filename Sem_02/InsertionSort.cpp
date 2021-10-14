#include <iostream>
using namespace std;

template<typename T>
void Swap(T* arr, int x, int y)
{
	T temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

template<typename T>
void InsertionSortNaive(T* arr, int len)
{
	for (size_t i = 1; i < len; i++)
	{
		int index = i - 1;

		while (index >= 0 && arr[index] > arr[index + 1])
		{
			Swap(arr, index, index + 1);
			index--;
		}
	}
}

template<typename T>
void InsertionSort(T* arr, int len)
{
	for (size_t i = 1; i < len; i++)
	{
		T element = arr[i];
		int index = i - 1;

		while (index >= 0 && arr[index] > element)
		{
			arr[index + 1] = arr[index];
			index--;
		}

		arr[index + 1] = element;
	}
}

int main()
{
	int arr[8] = { 8,7,6,5,4,3,2,1};
	InsertionSort(arr, 8);

	for (int i = 0; i < 8; i++)
		cout << arr[i] << " ";
}