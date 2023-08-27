#include <iostream>
#include <functional>
using namespace std;

template <typename T>
class SinglyLinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data)
		{
			this->data = data;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	SinglyLinkedList();
	SinglyLinkedList(std::initializer_list<T> iList);

	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept;

	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other) noexcept;

	~SinglyLinkedList();

private:
	void copyFrom(const SinglyLinkedList<T>& other);
	void moveFrom(SinglyLinkedList<T>&& other);

	void free();

	Node* getMid(Node* head) const;
	Node* mergeLists(Node* firstIter, Node* secondIter, std::function<bool(const T&, const T&)> cmp);
	Node* mergeSort(Node* head, std::function<bool(const T&, const T&)> cmp);

public:
	void push_front(const T& el);
	void push_back(const T& el);

	void pop_front();

	const T& front() const;
	const T& back() const;

	bool empty() const;

	void sort(std::function<bool(const T&, const T&)> cmp);

	template <typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<U>& l);
};

template <typename T>
void SinglyLinkedList<T>::push_front(const T& el)
{
	Node* newNode = new Node(el);

	if (!head)
	{
		head = tail = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
}
template <typename T>
void SinglyLinkedList<T>::push_back(const T& el)
{
	Node* newNode = new Node(el);

	if (!tail)
	{
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
}

template <typename T>
void SinglyLinkedList<T>::pop_front()
{
	if (!head)
		throw length_error("Empty list!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		return;
	}

	Node* toDelete = head;
	head = head->next;
	delete toDelete;
}

template <typename T>
const T& SinglyLinkedList<T>::front() const
{
	if (!head)
		throw length_error("Empty list!");

	return head->data;
}
template <typename T>
const T& SinglyLinkedList<T>::back() const
{
	if (!tail)
		throw length_error("Empty list!");

	return tail->data;
}

template <typename T>
bool SinglyLinkedList<T>::empty() const
{
	return head == nullptr;
}

template <typename T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getMid(Node* head) const
{
	Node* slow = head;
	Node* fast = head->next;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
template <typename T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::mergeLists(Node* firstIter, Node* secondIter, std::function<bool(const T&, const T&)> comp)
{
	if (!firstIter)
		return secondIter;
	if (!secondIter)
		return firstIter;

	Node* resultHead = nullptr;
	Node* resultIter = nullptr;

	if (comp(firstIter->data, secondIter->data))
	{
		resultHead = firstIter;
		resultIter = firstIter;
		firstIter = firstIter->next;
	}
	else
	{
		resultHead = secondIter;
		resultIter = secondIter;
		secondIter = secondIter->next;
	}

	while (firstIter && secondIter)
	{
		if (comp(firstIter->data, secondIter->data))
		{
			resultIter->next = firstIter;
			firstIter = firstIter->next;
		}
		else
		{
			resultIter->next = secondIter;
			secondIter = secondIter->next;
		}
		resultIter = resultIter->next;
	}

	resultIter->next = firstIter ? firstIter : secondIter;
	return resultHead;
}
template <typename T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::mergeSort(Node* head, std::function<bool(const T&, const T&)> comp)
{
	if (!head || !head->next)
		return head;

	Node* mid = getMid(head);

	Node* left = head;
	Node* right = mid->next;
	mid->next = nullptr;

	left = mergeSort(left, comp);
	right = mergeSort(right, comp);

	return mergeLists(left, right, comp);
}

template <typename T>
void SinglyLinkedList<T>::sort(std::function<bool(const T&, const T&)> comp)
{
	head = mergeSort(head, comp);
}

template <typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs) // suppose lhs and rhs are different
{
	SinglyLinkedList<T> result;
	
	if (!lhs.head && !rhs.head)
	{
		return result;
	}
	if (!lhs.head)
	{
		result.head = rhs.head;
		result.tail = rhs.tail;
	}
	else if (!rhs.head)
	{
		result.head = lhs.head;
		result.tail = lhs.tail;
	}
	else
	{
		lhs.tail->next = rhs.head;
		result.head = lhs.head;
		result.tail = rhs.tail;
	}

	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

	return result;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	head = tail = nullptr;
}
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> iList)
{
	for (const T& el : iList)
		push_back(el);
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
	copyFrom(other);
}
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	free();
}

template <typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other)
{
	Node* iter = other.head;

	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}
template <typename T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList<T>&& other)
{
	this->head = other.head;
	this->tail = other.tail;
	other.head = other.tail = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::free()
{
	Node* iter = head;

	while (iter)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}

	head = tail = nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& l)
{
	typename SinglyLinkedList<T>::Node* iter = l.head;

	while (iter)
	{
		os << iter->data << ' ';
		if (iter->next)
			os << "->" << ' ';
		iter = iter->next;
	}

	return os;
}
