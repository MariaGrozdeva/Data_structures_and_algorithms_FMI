#include <iostream>
using namespace std;

// BC = AC = WC -> O(n)
int sum(const int* arr, size_t len)
{
	int sum = 0;

	for (size_t i = 0; i < len; i++)
		sum += arr[i];

	return sum;
}

// BC -> O(1), AC = WC -> O(n)
bool contains(const int* arr, size_t len, int el)
{
	for (size_t i = 0; i < len; i++)
	{
		if (arr[i] == el)
			return true;
	}
	return false;
}

// BC = AC = WC-> O(n)
size_t f1(size_t n) // sum = 1 + 2 + ... + n = n(n+1)/2
{
	size_t sum = 0;

	for (size_t i = 1; i <= n; i++)
		sum += i;

	return sum;
}
// O(1)
size_t f1_better(size_t n)
{
	return n * (n + 1) / 2;
}

// O(log(b))
size_t power(size_t a, size_t b)
{
	size_t pow = 1;

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
// log(1) + log(2) + ... + log(n) = log(n!) = nlog(n) 
size_t f2(size_t n) // res = 2^0 + 2^1 + ... + 2^n = 2^(n+1) - 1
{
	int res = 0;
	size_t iter = 2;

	for (size_t i = 0; i <= n; i++)
		res += power(iter, i);

	return res;
}
// O(1)
size_t f2_better(size_t n)
{
	return (1 << (n + 1)) - 1;
}
// BC -> O(1), AC = WC -> O(log(n))
bool f3(size_t n) // check if n is a power of two
{
	while (n > 1)
	{
		if (n % 2 == 1)
			return false;
		n /= 2;
	}

	return true;
}
// O(1)
bool f3_better(int n)
{
	if (n != 0)
		return !(n & (n - 1));

	return false;
}

int main()
{

}