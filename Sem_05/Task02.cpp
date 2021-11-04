#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void sortSpecificArray(vector<int>& v)
{
	vector<int> even;
	vector<int> odd;

	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i] % 2)
			odd.push_back(v[i]);
		else
			even.push_back(v[i]);
	}

	reverse(odd.begin(), odd.end());
	merge(even.begin(), even.end(), odd.begin(), odd.end(), v.begin());
}

int main()
{
	vector<int> v = { 2, 5, 8, 3, 12, 14, 20, 1 };
	sortSpecificArray(v);

	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << ' ';
}