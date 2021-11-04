#include <iostream>
#include <list>

using namespace std;

int getNumberFromList(const list<int>& l)
{
	int number = 0;

	for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
		(number *= 10) += (*it);

	return number;
}
int getReversedNumberFromList(const list<int>& l)
{
	int number = 0;

	for (list<int>::const_reverse_iterator it = l.rbegin(); it != l.rend(); ++it)
		(number *= 10) += (*it);

	return number;
}

int sum(const list<list<int>>& l)
{
	int sum = 0;
	for (auto it = l.begin(); it != l.end(); ++it)
		sum += (getNumberFromList(*it) + getReversedNumberFromList(*it));

	return sum;
}

int main()
{
	list<list<int>> l;
	
	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	list<int> l2;
	l2.push_back(4);
	l2.push_back(5);
	l2.push_back(6);
	list<int> l3;
	list<int> l4;
	l4.push_back(7);
	l4.push_back(8);
	l4.push_back(9);
	list<int> l5;
	l5.push_back(10);

	l.push_back(l1);
	l.push_back(l2);
	l.push_back(l3);
	l.push_back(l4);
	l.push_back(l5);

	cout << sum(l);
}