#include<iostream>
#include<vector>
#include<stack>
#include<list>

void equalize(std::list<std::stack<int>>& arg) {
	const int numberOfStacks = arg.size();
	int numberOfElements = 0;

	for (const std::stack<int>& x : arg) {
		numberOfElements += x.size();
	}

	int median = numberOfElements / numberOfStacks;
	bool eq = numberOfElements % numberOfStacks;

	std::vector<std::stack<int>> overMedian;
	std::vector<std::stack<int>> underMedian;

	for (const std::stack<int>& x : arg) {
		if (x.size() < median) {
			underMedian.push_back(x);
		}
		else if (x.size() >= median) {
			overMedian.push_back(x);
		}
	}

	int it = 0;
	int its = 0;

	for (std::stack<int>& x : underMedian) {
		while (x.size() <= median - !(eq)) {
			while (overMedian[it].size() == median) {
				if (overMedian.size() == it + 1) {
					overMedian.push_back(underMedian[its++]);
				}
				++it;
			}
			x.push(overMedian[it].top());
			overMedian[it].pop();
		}
	}
	for (int i = 0; i < its; i++) {
		overMedian.pop_back();
	}

	arg.clear();

	it = 0;
	its = 0;

	for (int i = 0; i < overMedian.size(); i++) {
		arg.push_back(overMedian[i]);
	}
	for (int i = 0; i < underMedian.size(); i++) {
		arg.push_back(underMedian[i]);
	}
}

int main() {
	//worst test cases ever
	std::list<std::stack<int>> l;
	std::stack<int> a;
	for (int i = 0; i < 27; i++)
		a.push(i);
	std::stack<int> b;
	for (int i = 0; i < 123; i++)
		b.push(i);
	std::stack<int> c;
	for (int i = 0; i < 999; i++)
		c.push(i);
	std::stack<int> d;
	std::stack<int> e;
	for (int i = 0; i < 1; i++)
		d.push(i);
	for (int i = 0; i < 10; i++)
		e.push(i);
	
	l.push_back(a);
	l.push_back(b);
	l.push_back(c);
	l.push_back(d);
	l.push_back(e);
	equalize(l);

	for (std::stack<int> a : l) {
		std::cout << a.size() << ": ";
		while (!a.empty()) {
			std::cout << a.top() << " ";
			a.pop();
		}
		std::cout << std::endl;
	}
}
