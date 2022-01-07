#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class PriorityQueue
{
private:
	struct Node
	{
		T data;
		size_t timeStamp;

		Node(const T& data, size_t timeStamp) : data(data), timeStamp(timeStamp)
		{}

		bool operator>(const Node& other) const
		{
			// simulate operator> with operator< (so that the user defines only operator<)
			if (!(data < other.data) && !(data < other.data && other.data < data))
				return true;

			if (data == other.data)
				return timeStamp < other.timeStamp;

			return false;
		}
	};

	vector<Node*> heap;
	size_t lastSetTimeStamp;

public:
	PriorityQueue(const vector<T>& v);

	PriorityQueue();
	PriorityQueue(const PriorityQueue<T>& other);
	PriorityQueue<T>& operator=(const PriorityQueue<T>& other);
	~PriorityQueue();

private:
	void copyFrom(const PriorityQueue<T>& other);
	void free();

	size_t parent(size_t i) const;
	size_t leftChild(size_t i) const;
	size_t rightChild(size_t i) const;

	void heapify(size_t i);
	void buildHeap(const vector<T>& v);

	void printRec(size_t elIndex, size_t space) const;

public:
	const T& top() const;
	void pop();
	void insert(const T& el);
	bool empty() const;

	void print() const;
};

template <typename T>
const T& PriorityQueue<T>::top() const
{
	if (empty())
		throw length_error("Empty queue!");

	return heap[0]->data;
}
template <typename T>
void PriorityQueue<T>::pop()
{
	if (empty())
		throw length_error("Empty queue!");

	delete heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.pop_back();

	if (!empty())
		heapify(0);
}
template <typename T>
void PriorityQueue<T>::insert(const T& el)
{
	Node* newNode = new Node(el, lastSetTimeStamp++);
	heap.push_back(newNode);

	size_t currInd = heap.size() - 1;
	size_t parentInd = parent(currInd);
	while (currInd > 0 && *heap[currInd] > *heap[parentInd])
	{
		swap(heap[currInd], heap[parentInd]);
		currInd = parentInd;
		parentInd = parent(currInd);
	}
}
template <typename T>
bool PriorityQueue<T>::empty() const
{
	return heap.size() == 0;
}

template <typename T>
void PriorityQueue<T>::heapify(size_t i)
{
	while (true)
	{
		size_t leftChildInd = leftChild(i);
		size_t rightChildInd = rightChild(i);

		bool shouldGoLeft = leftChildInd < heap.size() && *heap[leftChildInd] > *heap[i];
		bool shouldGoRight = rightChildInd < heap.size() && *heap[rightChildInd] > *heap[i];

		if (shouldGoLeft && shouldGoRight)
		{
			if (*heap[leftChildInd] > *heap[rightChildInd])
			{
				swap(heap[i], heap[leftChildInd]);
				i = leftChildInd;
			}
			else
			{
				swap(heap[i], heap[rightChildInd]);
				i = rightChildInd;
			}
		}
		else if (shouldGoLeft)
		{
			swap(heap[i], heap[leftChildInd]);
			i = leftChildInd;
		}
		else if (shouldGoLeft)
		{
			swap(heap[i], heap[rightChildInd]);
			i = rightChildInd;
		}
		else 
			break;
	}
}
template <typename T>
void PriorityQueue<T>::buildHeap(const vector<T>& v)
{
	for (size_t i = 0; i < v.size(); i++)
		heap.push_back(new Node(v[i], lastSetTimeStamp++));

	for (int i = heap.size() / 2 - 1; i >= 0; i--)
		heapify(i);
}

template <typename T>
size_t PriorityQueue<T>::parent(size_t i) const
{
	return (i - 1) / 2;
}
template <typename T>
size_t PriorityQueue<T>::leftChild(size_t i) const
{
	return 2 * i + 1;
}
template <typename T>
size_t PriorityQueue<T>::rightChild(size_t i) const
{
	return 2 * i + 2;
}

template <typename T>
void PriorityQueue<T>::print() const
{
	printRec(0, 0);
}
template <typename T>
void PriorityQueue<T>::printRec(size_t elIndex, size_t space) const
{
	const int SPACES_COUNT = 10;
	if (elIndex >= heap.size())
		return;

	space += SPACES_COUNT;

	printRec(rightChild(elIndex), space);
	cout << endl;

	for (size_t i = SPACES_COUNT; i < space; i++)
		cout << ' ';
	cout << heap[elIndex]->data << endl;

	printRec(leftChild(elIndex), space);
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const vector<T>& v)
{
	buildHeap(v);
}

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	lastSetTimeStamp = 0;
}
template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other)
{
	copyFrom(other);
}
template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	free();
}

template <typename T>
void PriorityQueue<T>::copyFrom(const PriorityQueue<T>& other)
{
	lastSetTimeStamp = other.lastSetTimeStamp;

	for (size_t i = 0; i < other.heap.size(); i++)
		heap.push_back(new Node<T>(other.heap[i]));
}
template <typename T>
void PriorityQueue<T>::free()
{
	for (size_t i = 0; i < heap.size(); i++)
		delete heap[i];
	lastSetTimeStamp = 0;
}
