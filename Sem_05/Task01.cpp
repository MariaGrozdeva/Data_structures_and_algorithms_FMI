#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Partition(vector<int>& v)
{
	int pivot = 0;

	int i = 0;
	int j = v.size() - 1;

	while (true)
	{
		while (v[i] < pivot)
			i++;
		while (v[j] > pivot)
			j--;

		if (v[i] == v[j])
			i++;
		if (i < j)
			swap(v[i], v[j]);
		else
			return j;
	}
}

int main()
{
	vector<int> v = { 3,6, 5, -5,-1,5,-5 };
	Partition(v);

	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << ' ';
}