#include <iostream>
#include <utility> 

template <typename T>
void selectionSort(T* arr, const unsigned len)
{
    for (size_t i = 0; i < len - 1; i++)
    {
        size_t minElementIndex = i;

        for (size_t j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[minElementIndex])
            {
                minElementIndex = j;
            }
        }

        if (i != minElementIndex)
        {
            std::swap(arr[i], arr[minElementIndex]);
        }
    }
}

int main()
{
    int arr[] = { 7, 6, 5, 4, 3, 2, 1 };

    selectionSort<int>(arr, 7);

    for (size_t i = 0; i < 7; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}
