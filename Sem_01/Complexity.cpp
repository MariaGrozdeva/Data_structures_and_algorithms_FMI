#include <iostream>
#include <stddef.h>

// O(n)
int sum(const int* arr, size_t len)
{
	int sum = 0;
	for (size_t i = 0; i < len; i++)
	{
		sum += arr[i];
	}
	return sum;
}

// O(n)
bool contains(const int* arr, size_t len, int el)
{
	for (size_t i = 0; i < len; i++)
	{
		if (arr[i] == el)
		{
			return true;
		}
	}
	return false;
}

// O(n)
size_t f1(unsigned n) // sum = 1 + 2 + ... + n = n(n+1)/2
{
	size_t sum = 0;
	for (size_t i = 1; i <= n; i++)
	{
		sum += i;
	}
	return sum;
}
// O(1)
size_t f1Better(unsigned n)
{
	return n * (n + 1) / 2;
}

// O(log(b))
unsigned power(unsigned a, unsigned b)
{
	unsigned pow = 1;
	while (b)
	{
		if (b & 1)
		{
			pow = pow * a;
			--b;
		}
		a = a * a;
		b = b / 2;
	}
	return pow;
}

// O(log(1) + log(2) + ... + log(n)) = O(log(n!)) = O(nlog(n)) 
unsigned f2(unsigned n) // res = 2^0 + 2^1 + ... + 2^n = 2^(n+1) - 1
{
	unsigned res = 0;
	unsigned iter = 2;
	for (size_t i = 0; i <= n; i++)
	{
		res += power(iter, i);
	}
	return res;
}
// O(1)
unsigned f2Better(unsigned n)
{
	return (1 << (n + 1)) - 1;
}

// O(log(n))
bool f3(unsigned n) // checks whether n is a power of two
{
	while (n > 1)
	{
		if (n % 2 == 1)
		{
			return false;
		}
		n /= 2;
	}
	return true;
}
// O(1)
bool f3Better(unsigned n)
{
	if (n != 0)
	{
		return !(n & (n - 1));
	}
	return false;
}

// O(n)
void f4(unsigned n)
{
	for (size_t i = 1; i <= n; i *= 2)
	{
		for (size_t j = 1; j <= i; j++)
		{
			// O(1)
		}
	}	
}

// O(nlog(n))
void f5(unsigned n)
{
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= n; j += i)
		{
			// O(1)
		}
	}	
}

int main()
{

}
