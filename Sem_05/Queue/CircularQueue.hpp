#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T, typename Allocator = std::allocator<T>>
class queue 
{
public:
    queue() : data(myAlloc.allocate(capacity)), size(0), capacity(8), putIter(0), getIter(0) {}

    queue(const queue<T, Allocator>& other);
    queue<T, Allocator>& operator=(const queue<T, Allocator>& other);

    queue(queue<T, Allocator>&& other) noexcept;
    queue<T, Allocator>& operator=(queue<T, Allocator>&& other) noexcept;

    ~queue() noexcept;

    void push(const T& el);
    void push(T&& el);

    template <class... Args>
    T emplace(Args&&... args);

    void pop();

    T& front(); 
    const T& front() const;

    T& back(); 
    const T& back() const;

    size_t getSize() const;
    bool empty() const;

private:
    T* data;
    size_t size;
    size_t capacity;

    size_t putIter;
    size_t getIter;

    Allocator myAlloc;

    void copyFrom(const queue<T, Allocator>& other);
    void moveFrom(queue<T, Allocator>&& other);
    void free();
    void resize();
};

template<typename T, typename Allocator>
void queue<T, Allocator>::push(const T& el)
{
    if (size == capacity)
    {
        resize();
    }
    std::construct_at(&data[putIter], el);
    putIter = (putIter + 1) % capacity;
    ++size;
}

template<typename T, typename Allocator>
void queue<T, Allocator>::push(T&& el)
{
    if (size == capacity)
    {
        resize();
    }
    std::construct_at(&data[putIter], std::move(el));
    putIter = (putIter + 1) % capacity;
    ++size;
}

template<typename T, typename Allocator>
template <class... Args>
T queue<T, Allocator>::emplace(Args&&... args)
{
    if (size == capacity)
    {
        resize();
    }
    T newObj(std::forward<Args>(args)...);
    std::construct_at(&data[putIter], std::forward<Args>(args)...);
    putIter = (putIter + 1) % capacity;
    ++size;
    return newObj;
}

template<typename T, typename Allocator>
void queue<T, Allocator>::pop()
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty!");
    }
    std::destroy_at(&data[getIter]);
    getIter = (getIter + 1) % capacity;
    --size;
}

template<typename T, typename Allocator>
T& queue<T, Allocator>::front()
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty!");
    }
    return data[getIter];
}

template<typename T, typename Allocator>
const T& queue<T, Allocator>::front() const
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty!");
    }
    return data[getIter];
}

template<typename T, typename Allocator>
T& queue<T, Allocator>::back()
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty!");
    }
    size_t backIter = (putIter + capacity - 1) % capacity;
    return data[backIter];
}

template<typename T, typename Allocator>
const T& queue<T, Allocator>::back() const
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty!");
    }
    size_t backIter = (putIter + capacity - 1) % capacity;
    return data[backIter];
}

template<typename T, typename Allocator>
size_t queue<T, Allocator>::getSize() const
{
    return size;
}

template<typename T, typename Allocator>
bool queue<T, Allocator>::empty() const
{
    return size == 0;
}

template<typename T, typename Allocator>
queue<T, Allocator>::queue(const queue<T, Allocator>& other)
{
    copyFrom(other);
}

template<typename T, typename Allocator>
queue<T, Allocator>& queue<T, Allocator>::operator=(const queue<T, Allocator>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T, typename Allocator>
queue<T, Allocator>::queue(queue<T, Allocator>&& other) noexcept
{
    moveFrom(std::move(other));
}

template<typename T, typename Allocator>
queue<T, Allocator>& queue<T, Allocator>::operator=(queue<T, Allocator>&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T, typename Allocator>
queue<T, Allocator>::~queue() noexcept
{
    free();
}

template<typename T, typename Allocator>
void queue<T, Allocator>::copyFrom(const queue<T, Allocator>& other)
{
    data = myAlloc.allocate(other.capacity);

    for (size_t i = 0; i < other.size; ++i)
    {
        size_t index = (other.getIter + i) % other.capacity;
        std::construct_at(&data[i], other.data[index]);
    }

    size = other.size;
    capacity = other.capacity;
    putIter = other.putIter;
    getIter = other.getIter;
}

template<typename T, typename Allocator>
void queue<T, Allocator>::moveFrom(queue<T, Allocator>&& other)
{
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    putIter = other.putIter;
    getIter = other.getIter;

    other.data = nullptr;
    other.size = other.capacity = 0;
    other.putIter = other.getIter = 0;
}

template<typename T, typename Allocator>
void queue<T, Allocator>::free()
{
    for (size_t i = 0; i < size; ++i)
    {
        size_t index = (getIter + i) % capacity;
        std::destroy_at(&data[index]);
    }

    myAlloc.deallocate(data, capacity);
    data = nullptr;
    size = capacity = 0;
}

template<typename T, typename Allocator>
void queue<T, Allocator>::resize()
{
    size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
    T* newData = myAlloc.allocate(newCapacity);

    for (size_t i = 0; i < size; ++i)
    {
        size_t index = (getIter + i) % capacity;
        std::construct_at(&newData[i], std::move(data[index]));
        std::destroy_at(&data[index]);
    }

    myAlloc.deallocate(data, capacity);
    data = newData;
    capacity = newCapacity;
    getIter = 0;
    putIter = size;
}
