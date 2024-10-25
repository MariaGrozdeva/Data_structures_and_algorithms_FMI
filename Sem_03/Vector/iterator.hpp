#pragma once
#include <stddef.h>

template <class T>
class const_vector_iterator
{
public:
    const_vector_iterator(T* passedVal) : memPointer{passedVal} {}
    const_vector_iterator(T* passedVal, size_t push) : memPointer{passedVal + push} {}

    const_vector_iterator<T> operator+(int offset) const
    {
        return memPointer + offset;
    }

    const_vector_iterator<T> operator-(int offset) const
    {
        return memPointer - offset;
    }
    
    int operator-(const_vector_iterator<T> other) const
    {
        return memPointer - other.memPointer;
    }

    const T* operator->() const noexcept
    {
        return memPointer;
    }

    const T& operator*() const noexcept
    {
        return *memPointer;
    }
    
    const T& operator[](int index) const
    {
        return *(memPointer + index);
    }

    template <class P>
    bool operator==(const const_vector_iterator<P>& other) const
    {
        return memPointer == other.memPointer;
    }

    template <class P>
    bool operator!=(const const_vector_iterator<P>& other) const
    {
        return !(memPointer == other.memPointer);
    }

private:
    T* memPointer;
};

template <class T>
class vector_iterator
{
public:
    vector_iterator(T* passedVal) : memPointer{passedVal} {};
    vector_iterator(T* passedVal, size_t push) : memPointer{passedVal + push} {};

    vector_iterator<T>& operator++()
    {
        memPointer++;
        return *this;
    }

    vector_iterator<T> operator++(int)
    {
        vector_iterator<T> it = *this;
        ++(*this);
        return it;
    }

    vector_iterator<T>& operator--()
    {
        memPointer--;
        return *this;
    }

    vector_iterator<T> operator--(int)
    {
        vector_iterator<T> it = *this;
        --(*this);
        return it;
    }
    
    vector_iterator<T>& operator+=(int offset)
    {
        memPointer += offset;
        return *this;
    }
    
    vector_iterator<T>& operator-=(int offset)
    {
        memPointer -= offset;
        return *this;
    }

    vector_iterator<T> operator+(int offset) const
    {
        return memPointer + offset;
    }

    vector_iterator<T> operator-(int offset) const
    {
        return memPointer - offset;
    }

    T* operator->()
    {
        return memPointer;
    }

    const T* operator->() const
    {
        return memPointer;
    }

    T& operator*()
    {
        return *memPointer;
    }
    
    const T& operator*() const
    {
        return *memPointer;
    }
    
    operator const_vector_iterator<T>() const
    {
        return const_vector_iterator<T>(memPointer);
    }
    
    T& operator[](int index)
    {
        return *(memPointer + index);
    }
    
    const T& operator[](int index) const
    {
        return *(memPointer + index);
    }

    template <class P>
    bool operator==(const vector_iterator<P>& other) const
    {
        return memPointer == other.memPointer;
    }

    template <class P>
    bool operator!=(const vector_iterator<P>& other) const
    {
        return !(memPointer == other.memPointer);
    }

private:
    T* memPointer;
};

template <class T>
class reverse_vector_iterator
{
public:
    reverse_vector_iterator(T* passedVal) : memPointer{passedVal} {};
    reverse_vector_iterator(T* passedVal, size_t push) : memPointer{passedVal + push} {};

    reverse_vector_iterator<T>& operator++()
    {
        memPointer--;
        return *this;
    }

    reverse_vector_iterator<T> operator++(int)
    {
        reverse_vector_iterator it = *this;
        --(*this);
        return it;
    }

    reverse_vector_iterator<T>& operator--()
    {
        memPointer++;
        return *this;
    }

    reverse_vector_iterator<T> operator--(int)
    {
        reverse_vector_iterator it = *this;
        ++(*this);
        return it;
    }
    
    reverse_vector_iterator<T>& operator+=(int offset)
    {
        memPointer -= offset;
        return *this;
    }
    
    reverse_vector_iterator<T>& operator-=(int offset)
    {
        memPointer += offset;
        return *this;
    }

    reverse_vector_iterator<T> operator+(int offset) const
    {
        return memPointer - offset;
    }

    reverse_vector_iterator<T> operator-(int offset) const
    {
        return memPointer + offset;
    }

    T* operator->()
    {
        return memPointer;
    }

    const T* operator->() const
    {
        return memPointer;
    }

    T& operator*()
    {
        return *memPointer;
    }
    
    const T& operator*() const
    {
        return *memPointer;
    }
    
    T& operator[](int index)
    {
        return *(memPointer - index);
    }
    
    const T& operator[](int index) const
    {
        return *(memPointer - index);
    }

    template <class P>
    bool operator==(const reverse_vector_iterator<P>& other) const
    {
        return memPointer == other.memPointer;
    }

    template <class P>
    bool operator!=(const reverse_vector_iterator<P>& other) const
    {
        return !(memPointer == other.memPointer);
    }

private:
    T* memPointer;
};
