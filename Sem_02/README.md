# Анализ на рекурсивни алгоритми

Анализът на сложността на **рекурсивни алгоритми** се извършва чрез решаване на рекурентни уравнения.  
При изследването на алгоритмите не се интересуваме от точен израз за сложността. Интересува ни асимптотиката. Съответно, няма да се опитваме да решаваме рекурентните уравнения точно, а **ще търсим асимптотиката на решението**.

*Пример - Числа на Фибоначи:*  
$T(n) = T(n - 1) + T(n - 2)$  
Начални условия:  
$T(0) = 1 \\ \\ \\ T(1) = 1$  
Да решим рекурентното уравнение означава да намерим затворена формула, т.е. такава, в която няма рекурсивно извикване отдясно:  
$\displaystyle T(n) = A \cdot \left( \frac{1 + \sqrt{5}}{2} \right)^n + B \cdot \left( \frac{1 - \sqrt{5}}{2} \right)^n$  
Константите $A$ и $B$ не ни интересуват, тъй като търсим само асимптотиката на $T(n)$.

---

## Как решаваме рекурентни уравнения?
- Налучкване и доказване
- Развиване
- Master theorem
- Други

---

## Сложност на рекурсивни алгоритми
Връзката между рекурентните уравнения и рекурсивните алгоритми е трикова. От една страна, всяко рекурентно уравнение е рекурсивен алгоритъм, който за всеки достатъчно голям вход-число връща изход число след пресмятане, което включва рекурсия. От друга страна, сложността на рекурсивните алгоритми по правило се описва от рекурентни уравнения. При изследването на сложността на рекурсивни алгоритми чрез рекурентни уравнения е важно да се прави разлика между алгоритъма, чиято сложност изследваме, и рекурентното уравнение, което описва тази сложност. На свой ред то също е рекурсивен алгоритъм, но е съвършено различен обект от първоначалния алгоритъм. Като пример да разгледаме следното рекурентното уравнение:  
$\displaystyle T(n) = 1, \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ \\ n = 0$  
$\displaystyle T(n) = n \cdot T(n-1) + 1, \\ n \ne 0$  

То описва сложността на алгоритъм от вида:
```c++
unsigned long long f(unsigned n)
{
    	if (n == 0)
    	{
        	return 1;
    	} 
    
    	unsigned long long s = n;
    	for (size_t i = 1; i <= n; i++)
    	{
		s += f(n - 1);
    	}
    	return s;
}
```

Ако пресметнем рекурентното уравнение, ще получим $\displaystyle T(n) = \Theta(n!)$, т.е. това е алгоритъм, който няма да приключи никога дори за малки стойности на $n$. От друга страна, ако самото рекурентно уравнение бъде пренаписано като рекурсивен алгоритъм, то той ще има линейна сложност.

---

### Задача 1 - Анализ на линейно търсене
$\displaystyle T(n) = T(n-1) + \Theta(1) = T(n-2) + 2\cdot \Theta(1) = T(n-3) + 3\cdot \Theta(1) = ... = n\cdot \Theta(1) = \Theta(n)$

---

### Задача 2
Каква е сложността на следния алгоритъм:
```c++
int f(int n) 
{
	if (n == 0)
	{
        	return 7;
	}
    	return 3 * f(n - 1) + 2 * f(n - 1) + f(n - 1);
}
```

$\displaystyle T(n) = 3\cdot T(n-1) + \Theta(1)$

![alt_text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/images/Task02.png)

---

### Задача 3 - Анализ на Фибоначи
```c++
unsigned long long fibb(unsigned n) 
{
    	if (n == 0 || n == 1)
	{
        	return 1;
	}
    	return fibb(n - 1) + fibb(n - 2);
}
```

$\displaystyle T(n) = T(n-1) + T(n-2)$  

За да намерим $n$-тото число на Фибоначи, алгоритъмът ще извърши точно толкова стъпки, колкото е самото число. Това е така, защото алгоритъмът акумулира резултата само чрез "събиране с 1-ца".

![alt_text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/images/Task03.png)

---

### Задача 4 - "Разделяй и владей"
- Разделяме задачата на подзадачи
- Решаваме по-малките задачи
- Акумулираме решенията

*Пример - Линейно търсене по схемата "Разделяй и владей" (в несортиран масив!):*  
```c++
bool linearSearchDivideAndConquer(const int* arr, int len, int x)
{
	if (len == 0)
    	{
        	return false;
    	}
    	if (len == 1)
    	{
        	return arr[0] == x;
    	}
    	return linearSearchDivideAndConquer(arr, len / 2, x) || linearSearchDivideAndConquer(arr + len / 2, len - len / 2, x);
}
```

$\displaystyle T(n) = 2 \cdot T\left(\frac{n}{2}\right) + \Theta(1) = \Theta(n)$

