#include <iostream>

template <typename T>
void merge(T* arr1, size_t len1, T* arr2, size_t len2, T* result)
{
    unsigned arr1Iter = 0;
    unsigned arr2Iter = 0;
    unsigned resultIter = 0;

    while (arr1Iter < len1 && arr2Iter < len2)
    {
        if (arr1[arr1Iter] <= arr2[arr2Iter])
        {
            result[resultIter++] = arr1[arr1Iter++];
        }
        else
        {
            result[resultIter++] = arr2[arr2Iter++];
        }
    }

    while (arr1Iter < len1)
    {
        result[resultIter++] = arr1[arr1Iter++];
    }

    while (arr2Iter < len2)
    {
        result[resultIter++] = arr2[arr2Iter++];
    }
}

template <typename T>
void mergeSortStep(T* arr, size_t len, T* bufferArray)
{
    if (len <= 1)
    {
        return;
    }

    unsigned midIndex = len / 2;

    mergeSortStep<T>(arr, midIndex, bufferArray);
    mergeSortStep<T>(arr + midIndex, len - midIndex, bufferArray);

    merge<T>(arr, midIndex, arr + midIndex, len - midIndex, bufferArray);

    for (size_t i = 0; i < len; i++)
    {
        arr[i] = bufferArray[i];
    }
}

template <typename T>
void mergeSort(T* arr, size_t len)
{
    if (!arr || len == 0)
    {
        return;
    }

    T* bufferArray = new T[len];
    mergeSortStep<T>(arr, len, bufferArray);
    delete[] bufferArray;
}

int main()
{
    int arr[8] = {170, 45, 75, 90, 802, 24, 2, 66};
    mergeSort<int>(arr, 8);

    for (int i = 0; i < 8; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}
