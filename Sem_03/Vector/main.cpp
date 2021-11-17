#include "Vector.hpp"

int main()
{
	Vector<int> v1;
	v1.push_back(22);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(33);

	v1.pop_back();
	v1.pop_back();
	v1.pop_back();

	Vector<int> v2(v1);
	v2.push_back(23);
	v2.push_back(24);
	v2.push_back(25);

	v1.pop_back();
	cout << "v1 is empty: " << boolalpha << (v1.empty()) << endl;
}