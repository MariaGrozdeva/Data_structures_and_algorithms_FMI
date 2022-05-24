#include <list>
#include <optional>
#include "BinomialTree.hpp"

template <typename T>
class BinomialHeap
{
private:
	std::list<BinomialTree<T>> data;
    size_t size = 0; // number of currently contained values
    mutable std::optional<T> min;

    void push_back(const BinomialTree<T>& el);
    void pop_front();

    size_t countr_zero(size_t n) const;
    size_t getRank() const; // get the rank of the first tree in the list

    void mergeWithCarry(BinomialTree<T>& carry, size_t carryRank, BinomialHeap<T>& result, BinomialHeap<T>& lhs, BinomialHeap<T>& rhs);

public:
    BinomialHeap() = default;
    BinomialHeap(const T& value);
    BinomialHeap(T&& value);

    void mergeHeaps(BinomialHeap<T>& result, BinomialHeap<T>& lhs, BinomialHeap<T>& rhs); // O(lgn) where n = max(lhs.size, rhs.size)

    // O(1) amortized
    void insert(const T& value);
    void insert(T&& value);

    const T& getMin() const; // O(1)
    // const T& extractMin(); // tbi
};

template <typename T>
void BinomialHeap<T>::mergeWithCarry(BinomialTree<T>& carry, size_t carryRank, BinomialHeap<T>& result, BinomialHeap<T>& lhs, BinomialHeap<T>& rhs)
{
    while (!lhs.data.empty() && !rhs.data.empty())
    {
        size_t lhsRank = lhs.getRank();
        size_t rhsRank = rhs.getRank();

        if (carryRank == lhsRank && carryRank == rhsRank)
        {
            result.push_back(carry);

            BinomialTree<T> newCarry = mergeTrees(lhs.data.front(), rhs.data.front());
            lhs.pop_front();
            rhs.pop_front();

            mergeWithCarry(newCarry, carryRank + 1, result, lhs, rhs);
        }
        else if (carryRank == lhsRank)
        {
            carry = mergeTrees(carry, lhs.data.front());
            lhs.pop_front();
            ++carryRank;
        }
        else if (carryRank == rhsRank)
        {
            carry = mergeTrees(carry, rhs.data.front());
            rhs.pop_front();
            ++carryRank;
        }
        else
        {
            result.push_back(carry);
            mergeHeaps(result, lhs, rhs);
        }
    }

    BinomialHeap<T> rest = !lhs.data.empty() ? lhs : rhs;
    while (!rest.data.empty() && carryRank == rest.getRank())
    {
        carry = mergeTrees(carry, rest.data.front());
        rest.pop_front();
        ++carryRank;
    }

    assert(rest.data.size() == 0 || carryRank < rest.getRank());

    result.push_back(carry);
    result.data.splice(result.data.end(), rest.data);
    result.size += rest.size;
}
template <typename T>
void BinomialHeap<T>::mergeHeaps(BinomialHeap<T>& result, BinomialHeap<T>& lhs, BinomialHeap<T>& rhs)
{
    if (lhs.data.empty() || rhs.data.empty())
    {
        if (!lhs.data.empty())
        {
            result.data.splice(result.data.end(), lhs.data);
            result.size += lhs.size;
        }
        else
        {
            result.data.splice(result.data.end(), rhs.data);
            result.size += rhs.size;
        }
        return;
    }

    size_t lhsRank = lhs.getRank();
    size_t rhsRank = rhs.getRank();

    if (lhsRank != rhsRank)
    {
        if (lhsRank < rhsRank)
        {
            result.push_back(lhs.data.front());
            lhs.pop_front();
        }
        else
        {
            result.push_back(rhs.data.front());
            rhs.pop_front();
        }

        mergeHeaps(result, lhs, rhs);
    }
    else
    {
        BinomialTree<T> carry = mergeTrees(lhs.data.front(), rhs.data.front());
        lhs.pop_front();
        rhs.pop_front();

        mergeWithCarry(carry, lhsRank + 1, result, lhs, rhs);
    }
}

template <typename T>
void BinomialHeap<T>::insert(const T& value)
{
    BinomialHeap<T> binHeap(value);

    BinomialHeap<T> result;
    mergeHeaps(result, *this, binHeap);
    *this = std::move(result);
}
template <typename T>
void  BinomialHeap<T>::insert(T&& value)
{
    BinomialHeap<T> binHeap(std::move(value));

    BinomialHeap<T> result;
    mergeHeaps(result, *this, binHeap);
    *this = std::move(result);
}

template <typename T>
const T& BinomialHeap<T>::getMin() const
{
    if (!min.has_value())
    {
        std::optional<T> tempMin;
        for (auto it = data.begin(); it != data.end(); ++it)
            if (!tempMin.has_value() || (tempMin > (*it).getMin()))
                tempMin = (*it).getMin();
        min = tempMin;
    }

    return min.value();
}

template <typename T>
BinomialHeap<T>::BinomialHeap(const T& value)
{
    data.push_back(std::move(BinomialTree<T>(value)));
    ++size;
}
template <typename T>
BinomialHeap<T>::BinomialHeap(T&& value)
{
    data.push_back(std::move(BinomialTree<T>(std::move(value))));
    ++size;
}

template <typename T>
size_t BinomialHeap<T>::countr_zero(size_t n) const
{
    if (n == 0)
        return 0;

    size_t zerosCount = 0;
    while (!(n & 1))
    {
        ++zerosCount;
        n = n >> 1;
    }
    return zerosCount;
}
template <typename T>
size_t BinomialHeap<T>::getRank() const
{
    return countr_zero(size);
}

template <typename T>
void BinomialHeap<T>::push_back(const BinomialTree<T>& el)
{
    size += el.getSize();
    data.push_back(el);
}
template <typename T>
void BinomialHeap<T>::pop_front()
{
    size -= data.front().getSize();
    data.pop_front();
}