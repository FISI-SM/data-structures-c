#include <stdio.h>
#include <string.h>

int stk[10];

int top = -1;

int pop();
void push(int val);
int get_type(char c);

int main()
{
	char prefix[10];
	int len, val, i, opr1, opr2, res;

	printf("\n Enter the prefix expression: ");
	fgets(prefix, sizeof(prefix), stdin);
	prefix[strcspn(prefix, "\n")] = '\0';

	len = strlen(prefix);

	for (i = len - 1; i >= 0; i--)
	{
		switch (get_type(prefix[i]))
		{
			case 0:
				val = prefix[i] - '0';
				push(val);
				break;

			case 1:
				opr1 = pop();
				opr2 = pop();

				switch (prefix[i])
				{
					case '+':
						res = opr1 + opr2;
						break;

					case '-':
						res = opr1 - opr2;
						break;

					case '*':
						res = opr1 * opr2;
						break;

					case '/':
						res = opr1 / opr2;
						break;

					default:
						printf("\n Invalid operator: %c", prefix[i]);
						return 1;
				}

				push(res);
				break;
		}
	}

	printf("\n RESULT = %d\n", stk[0]);

	return 0;
}

void push(int val)
{
	stk[++top] = val;
}

int pop()
{
	return stk[top--];
}

int get_type(char c)
{
	if (c =='+' || c == '-' || c == '*' || c == '/')
		return 1;

	else
		return 0;
}
