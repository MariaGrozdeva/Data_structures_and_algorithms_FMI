#include <iostream>
#include <stack>

using namespace std;

int RPN(string expr)
{
	stack<int> numbers;
	int len = expr.length();

	for (int i = 0; i < len; i++)
	{
		if (expr[i] == ' ')
			continue;

		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*')
		{
			int rhs = numbers.top();
			numbers.pop();
			int lhs = numbers.top();
			numbers.pop();

			switch (expr[i])
			{
			case '+': numbers.push(lhs + rhs); break;
			case '-': numbers.push(lhs - rhs); break;
			case '*': numbers.push(lhs * rhs); break;
			}
		}
		else
		{
			int n = 0;
			while (expr[i] >= '0' && expr[i] <= '9')
				n *= 10 + (expr[i++] - '0');

			numbers.push(n);
			i--;
		}

	}
	return numbers.top();
}

int main()
{
	string expr = "9 3 4 * - 2 5 * -";
	cout << RPN(expr);
}
