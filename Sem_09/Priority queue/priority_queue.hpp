#pragma once
#include <iostream>
#include <vector>
#include <<utility>>

template <typename T>
class priority_queue
{
public:
    priority_queue() = default;
    priority_queue(const std::vector<T>& v);

    const T& top() const;
    void push(const T& el);
    void pop();
    
    size_t size() const;
    bool empty() const;
    
private:
    static size_t leftChild(size_t i);
    static size_t rightChild(size_t i);
    static int parent(int i);

    void heapify(size_t ind); 
    
    std::vector<T> data;
};

template <typename T>
priority_queue<T>::priority_queue(const std::vector<T>& v)  // O(n)
{
    data = v;
    for (int i = v.size() / 2 - 1; i >= 0; i--)
    {
        heapify(i);
    }
}

template <typename T>
const T& priority_queue<T>::top() const
{
    if (empty())
    {
        throw std::runtime_error("Empty queue!");
    }
    return data[0];
}

template <typename T>
void priority_queue<T>::push(const T& el)
{
    data.push_back(el);
    int ind = data.size() - 1;
    int parentIndex = parent(ind);

    while (ind > 0 && data[ind] > data[parentIndex])
    {
        std::swap(data[ind], data[parentIndex]);
        ind = parentIndex;
        parentIndex = parent(ind);
    }
}

template <typename T>
void priority_queue<T>::pop()
{
    if (empty())
    {
        throw std::runtime_error("Empty queue!");
    }

    data[0] = data[data.size() - 1];
    data.pop_back();
    if (data.size() != 0)
    {
        heapify(0);
    }
}

template <typename T>
size_t priority_queue<T>::size() const
{
    return data.size();
}

template <typename T>
bool priority_queue<T>::empty() const
{
    return data.empty();
}

template <typename T>
size_t priority_queue<T>::leftChild(size_t i)
{
    return 2 * i + 1;
}

template <typename T>
size_t priority_queue<T>::rightChild(size_t i)
{
    return 2 * i + 2;
}

template <typename T>
int priority_queue<T>::parent(int i)
{
    return (i - 1) / 2;
}

template <typename T>
void priority_queue<T>::heapify(size_t ind)
{
    int currentElementIndex = ind;
    while (true)
    {
        int leftChildIndex = leftChild(currentElementIndex);
        int rightChildIndex = rightChild(currentElementIndex);

        bool shouldGoLeft = leftChildIndex < data.size() && data[leftChildIndex] > data[currentElementIndex];
        bool shouldGoRight = rightChildIndex < data.size() && data[rightChildIndex] > data[currentElementIndex];

        if (shouldGoLeft && shouldGoRight)
        {
            if (data[leftChildIndex] > data[rightChildIndex])
            {
                std::swap(data[currentElementIndex], data[leftChildIndex]);
                currentElementIndex = leftChildIndex;
            }
            else
            {
                std::swap(data[currentElementIndex], data[rightChildIndex]);
                currentElementIndex = rightChildIndex;
            }
        }
        else if (shouldGoLeft)
        {
            std::swap(data[currentElementIndex], data[leftChildIndex]);
            currentElementIndex = leftChildIndex;
        }
        else if (shouldGoRight)
        {
            std::swap(data[currentElementIndex], data[rightChildIndex]);
            currentElementIndex = rightChildIndex;
        }
        else
        {
            break;
        }
    }
}
