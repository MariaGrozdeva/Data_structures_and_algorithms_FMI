#include <iostream>
#include <utility>

template <typename T>
void insertionSortNaive(T* arr, const unsigned len) 
{
    for (size_t i = 1; i < len; i++)
    {
        size_t elIndex = i;
        while (elIndex >= 0 && arr[elIndex] < arr[elIndex - 1])
        {
            std::swap(arr[elIndex], arr[elIndex - 1]); 
            elIndex--;
        }
    }
}

template <typename T>
void insertionSort(T* arr, const unsigned len)
{
    for (size_t i = 1; i < len; i++)
    {
        T el = arr[i];
        int index = i - 1;
        while (index >= 0 && el < arr[index])
        {
            arr[index + 1] = arr[index];
            index--;
        }
        arr[index + 1] = el;
    }
}

int main()
{
    int arr[] = { 7, 6, 5, 4, 3, 2, 1 };

    insertionSort<int>(arr, 7);

    for (size_t i = 0; i < 7; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}
