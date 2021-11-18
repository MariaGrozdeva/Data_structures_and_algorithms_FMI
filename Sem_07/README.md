# Итератори (Iterator design pattern)

Итераторите могат да бъдат разглеждани като “указатели” към елементите на дадена структура от данни.  
Те дават възможност за ***последователен достъп*** до елементите на обект, без да е нужна вътрешна информация за него.  
Всяка структура, ***в която има дефинирана наредба на елементите***, може да бъде обхождана чрез итератор.  
За всички итератори е дефиниран *операторът ++*, който премества итератора към следващия елемент от контейнера. Итераторите на някои контейнери поддържат и операцията *\-\-* (например, двусвързан списък).  

Концепцията за итератори ни дава възможност да пишем ***обобщени алгоритми***, които включват последователно обхождане на структура, без да се интересуваме каква точно е тя.  

```c++
namespace CustomAlgorithms
{
	template <typename Iter, typename ElementType>
	bool containsElement(Iter it1, Iter it2, const ElementType& searched)
	{
		while (it1 != it2)
		{
			if (*it1 == searched)
				return true;

			++it1;
		}
		return false;
	}

	template <typename Iter>
	bool isSorted(Iter it1, Iter it2)
	{
		while (it1 != it2)
		{
			Iter next = it1;
			next++;

			if (next == it2)
				break;

			if (*it1 > *next)
				return false;

			++it1;
		}
		return true;
	}
}
```

```c++
#include "Vector.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"
#include "Algorithms.hpp"

int main()
{
	{ // vector
		Vector<int> v;

		v.push_back(5);
		v.push_back(10);
		v.push_back(15);

		cout << "Vector contains element: " << boolalpha << CustomAlgorithms::containsElement(v.begin(), v.end(), 10) << endl;
		cout << "Vector is sorted: " << boolalpha << CustomAlgorithms::isSorted(v.begin(), v.end()) << endl << endl;
	}

	{ // singly linked list
		SinglyLinkedList<int> sll;

		sll.push_back(1);
		sll.push_back(2);
		sll.push_back(3);
		sll.push_back(4);

		cout << "SLL contains element: " << boolalpha << CustomAlgorithms::containsElement(sll.begin(), sll.end(), 3) << endl;
		cout << "SLL is sorted: " << boolalpha << CustomAlgorithms::isSorted(sll.begin(), sll.end()) << endl << endl;
	}

	{ // doubly linked list
		DoublyLinkedList<int> dll;

		dll.push_back(5);
		dll.push_back(23);
		dll.push_back(22);
		dll.push_back(24);

		cout << "DLL contains element: " << boolalpha << CustomAlgorithms::containsElement(dll.begin(), dll.end(), 3) << endl;
		cout << "DLL contains element: " << boolalpha << CustomAlgorithms::isSorted(dll.begin(), dll.end()) << endl;
	}
}
```
