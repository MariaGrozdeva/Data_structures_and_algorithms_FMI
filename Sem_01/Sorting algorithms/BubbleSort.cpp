#include <iostream>
#include <utility>

template <typename T>
void bubbleSort(T* arr, const unsigned len)
{
    unsigned end = len - 1;
    for (size_t i = 0; i < len; i++)
    {
        unsigned lastSwappedIndex = 0;

        for (size_t j = 0; j < end; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                lastSwappedIndex = j;
            }
        }

        end = lastSwappedIndex;
        if (lastSwappedIndex == 0)
        {
            return;
        }
    }
}

int main()
{
    int arr[] = { 7, 6, 5, 4, 3, 2, 1 };

    bubbleSort<int>(arr, 7);

    for (size_t i = 0; i < 7; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}
