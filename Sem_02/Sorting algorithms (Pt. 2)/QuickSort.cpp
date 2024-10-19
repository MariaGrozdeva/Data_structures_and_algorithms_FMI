#include <iostream>
#include <utility>

template <typename T>
int partition(T* arr, int len)
{
    T pivot = arr[len / 2];

    int i = 0;
    int j = len - 1;

    while (true)
    {
        while (arr[i] < pivot)
        {
            i++;
        }
        while (arr[j] > pivot)
        {
            j--;
        }

        if (arr[i] == arr[j])
        {
            i++;
        }
        if (i < j)
        {
            std::swap(arr[i], arr[j]);
        }
        else
        {
            return j;
        }
    }
}

template <typename T>
void quickSort(T* arr, int len)
{
    if (len <= 1)
    {
        return;
    }

    int pivotIndex = partition<T>(arr, len);

    quickSort<T>(arr, pivotIndex);
    quickSort<T>(arr + pivotIndex + 1, len - pivotIndex - 1);
}

int main()
{
    int arr[6] = { 6, 70, 7, 3, 4, 12 };
    quickSort<int>(arr, 6);

    for (int i = 0; i < 6; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}
