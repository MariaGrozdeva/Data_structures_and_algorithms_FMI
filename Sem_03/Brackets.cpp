#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isOpeningBracket(char ch)
{
	return ch == '(' || ch == '[' || ch == '{';
}
bool isClosingBracket(char ch)
{
	return ch == ')' || ch == ']' || ch == '}';
}
bool matchBrackets(char opening, char closing)
{
	return (opening == '(' && closing == ')') || (opening == '[' && closing == ']') || (opening == '{' && closing == '}');
}
bool isValid(const string& expr)
{
	size_t len = expr.length();
	stack<char> brackets;

	for (int i = 0; i < len; i++)
	{
		if (expr[i] == ' ')
			continue;

		if (isOpeningBracket(expr[i]))
			brackets.push(expr[i]);

		else if (isClosingBracket(expr[i]))
		{
			if (brackets.empty() || !matchBrackets(brackets.top(), expr[i]))
				return false;
			else
				brackets.pop();
		}
	}

	return brackets.empty();
}

int main()
{
	cout << isValid("( ( ( [ ] ) ) )");
}