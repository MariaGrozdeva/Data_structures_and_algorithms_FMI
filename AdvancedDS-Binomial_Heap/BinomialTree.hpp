#include <iostream>
#include <assert.h>

template <typename T>
class BinomialTree;
template <typename T>
BinomialTree<T> mergeTrees(const BinomialTree<T>& lhs, const BinomialTree<T>& rhs);

template <typename T>
class BinomialTree
{
private:
    struct Node
    {
        T data;
        Node* next; // right sibling
        Node* firstChild; // left child

        Node(const T& data) : data(data), next(nullptr), firstChild(nullptr)
        {}
    };

    Node* root;
    size_t rank;
    size_t size = 0;

    void copyFromRec(Node*& root, Node* otherRoot);
    void freeRec(Node* root);

    void copyFrom(const BinomialTree<T>& other);
    void moveFrom(BinomialTree<T>&& other);
    void free();

public:
    BinomialTree() = default;
    BinomialTree(const T& value);
    BinomialTree(T&& value);

    BinomialTree(const BinomialTree<T>& other);
    BinomialTree(BinomialTree<T>&& other);
    BinomialTree<T>& operator=(const BinomialTree<T>& other);
    BinomialTree<T>& operator=(BinomialTree<T>&& other);
    ~BinomialTree();

    size_t getRank() const;
    size_t getSize() const;
    const T& getMin() const;

    friend BinomialTree<T> mergeTrees<T>(const BinomialTree<T>& lhs, const BinomialTree<T>& rhs);
};

template <typename T>
size_t BinomialTree<T>::getRank() const
{
    return rank;
}
template <typename T>
size_t BinomialTree<T>::getSize() const
{
    return size;
}
template <typename T>
const T& BinomialTree<T>::getMin() const
{
    assert(root);
    return root->data;
}

template <typename T>
BinomialTree<T> mergeTrees<T>(const BinomialTree<T>& lhs, const BinomialTree<T>& rhs)
{
    assert(lhs.rank == rhs.rank);

    BinomialTree<T> lhsCopy(lhs);
    BinomialTree<T> rhsCopy(rhs);

    if (lhsCopy.root->data > rhsCopy.root->data)
    {
        auto prevFirstChild = rhsCopy.root->firstChild;
        rhsCopy.root->firstChild = lhsCopy.root;
        lhsCopy.root->next = prevFirstChild;

        lhsCopy.root = nullptr;
        ++rhsCopy.rank;
        rhsCopy.size += lhsCopy.size;

        return std::move(rhsCopy);
    }

    auto prevFirstChild = lhsCopy.root->firstChild;
    lhsCopy.root->firstChild = rhsCopy.root;
    rhsCopy.root->next = prevFirstChild;

    rhsCopy.root = nullptr;
    ++lhsCopy.rank;
    lhsCopy.size += rhsCopy.size;

    return std::move(lhsCopy);
}

template <typename T>
BinomialTree<T>::BinomialTree(const T& value)
{
    root = new Node(value);
    rank = 0;
    ++size;
}
template <typename T>
BinomialTree<T>::BinomialTree(T&& value)
{
    root = new Node(std::move(value));
    rank = 0;
    ++size;
}

template <typename T>
BinomialTree<T>::BinomialTree(const BinomialTree<T>& other)
{
    copyFrom(other);
}
template <typename T>
BinomialTree<T>::BinomialTree(BinomialTree<T>&& other)
{
    moveFrom(std::move(other));
}
template <typename T>
BinomialTree<T>& BinomialTree<T>::operator=(const BinomialTree<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}
template <typename T>
BinomialTree<T>& BinomialTree<T>::operator=(BinomialTree<T>&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}
template <typename T>
BinomialTree<T>::~BinomialTree()
{
    free();
}

template <typename T>
void BinomialTree<T>::copyFrom(const BinomialTree<T>& other)
{
    rank = other.rank;
    size = other.size;
    copyFromRec(root, other.root);
}
template <typename T>
void BinomialTree<T>::moveFrom(BinomialTree<T>&& other)
{
    root = other.root;
    other.root = nullptr;
    rank = other.rank;
    other.rank = 0;
    size = other.size;
    other.size = 0;
}
template <typename T>
void BinomialTree<T>::free()
{
    freeRec(root);
}

template <typename T>
void BinomialTree<T>::copyFromRec(Node*& root, Node* otherRoot)
{
    if (!otherRoot)
    {
        root = nullptr;
        return;
    }

    root = new Node(*otherRoot);

    copyFromRec(root->next, otherRoot->next);
    copyFromRec(root->firstChild, otherRoot->firstChild);
}
template <typename T>
void BinomialTree<T>::freeRec(Node* root)
{
    if (!root)
        return;

    freeRec(root->next);
    freeRec(root->firstChild);

    delete root;
}