#include<iostream>
#include<vector>
#include<stack>
#include<list>

template<class T>
struct Node 
{
	T data;
	Node<T>* next;
};

template<class T>
T reduce(Node<T>* ptr, T(*F)(const T&, const T&)) 
{
	int size = 0;

	if (ptr == nullptr)
		throw std::exception("Empty list");
	else if (ptr->next == nullptr)
		return ptr->data;

	return F(reduce(ptr->next, F), ptr->data);
}

int divs(const int& x, const int& y) 
{
	return x / y;
}

int main() 
{
	Node<int>* end = new Node<int>;
	end->data = 1024;
	end->next = nullptr;

	Node<int>* eigth = new Node<int>;
	eigth->data = 16;
	eigth->next = end;


	Node<int>* four = new Node<int>;
	four->data = 4;
	four->next = eigth;

	Node<int>* two = new Node<int>;
	two->data = 2;
	two->next = four;

	std::cout << reduce(two, divs);
	
	delete end;
	delete eigth;
	delete four;
	delete two;
}
