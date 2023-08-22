#include <iostream>
using namespace std;

// 6.0. Merge function - merges 2 sorted arrays
template <typename T>
void Merge(T* arr1, size_t len1, T* arr2, size_t len2, T* result)
{
    	unsigned arr1Iter = 0;
    	unsigned arr2Iter = 0;
    	unsigned resultIter = 0;
    
    	while (arr1Iter < len1 && arr2Iter < len2)
    	{
        	if (arr1[arr1Iter] <= arr2[arr2Iter])
            		result[resultIter++] = arr1[arr1Iter++];
        	else
            		result[resultIter++] = arr2[arr2Iter++];    
    	}
    
    	while (arr1Iter < len1)
        	result[resultIter++] = arr1[arr1Iter++];
    
    	while (arr2Iter < len2)
        	result[resultIter++] = arr2[arr2Iter++];   
}

template <typename T>
void MergeSortStep(T* arr, size_t len, T* bufferArray)
{
    	if (len <= 1)
        	return;
    
    	unsigned midIndex = len / 2;
    
    	MergeSortStep<T>(arr, midIndex, bufferArray);
    	MergeSortStep<T>(arr + midIndex, len - midIndex, bufferArray);
    
    	Merge<T>(arr, midIndex, arr + midIndex, len - midIndex, bufferArray);
    
    	for (size_t i = 0; i < len; i++)
        	arr[i] = bufferArray[i];
}

// 6.1. Merge sort (Complexity - 0(nlog(n)))
template <typename T>
void MergeSort(T* arr, size_t len)
{
    	if (!arr || len == 0)
		return;
		
    	T* bufferArray = new T[len];
    
    	MergeSortStep<T>(arr, len, bufferArray);
    
    	delete[] bufferArray;
}

int main()
{
    	int arr[8] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	MergeSort(arr, 8);

	for (int i = 0; i < 8; i++)
		cout << arr[i] << " ";
}
