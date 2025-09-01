#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

char st[MAX];

int top = -1;

void reverse(char str[], char temp[]);
void push(char st[], char val);
char pop(char sr[]);
void InfixtoPostfix(char source[], char target[]);
int getPriority(char op);

char infix[100], postfix[100];

int main()
{
	char temp[100];

	printf("\n Enter any infix expression: ");
	fgets(infix, sizeof(infix), stdin);
	infix[strcspn(infix, "\n")] = '\0';

	reverse(infix, temp);

	strcpy(postfix, "");

	InfixtoPostfix(temp, postfix);

	printf("\n The corresponding postfix expression is: ");
	puts(postfix);

	strcpy(temp, "");

	reverse(postfix, temp);

	printf("\n The prefix expression is: ");
	puts(temp);

	return 0;
}

void reverse(char str[], char temp[])
{
	int len, i = 0, j;

	len = strlen(str);

	j = len - 1;

	while (j >= 0) {
		if (str[j] == '(')
			temp[i] = ')';

		else if (str[j] == ')')
			temp[i] = '(';

		else 
			temp[i] = str[j];

		i++;
		j--;
	}

	temp[i] = '\0';
}


void InfixtoPostfix(char source[], char target[])
{
	int i = 0, j = 0;
	char tempChar;

	while (source[i] != '\0') {
		
		if (source[i] == '(') {
			push(st, source[i]);
			i++;
		}

		else if (source[i] == ')') {

			while ((top != -1) && (st[top] != '(')) {
				target[j] = pop(st);
				j++;
			}

			if (top == -1) {
				printf("\n INCORRECT EXPRESSION");
				exit(1);
			}

			tempChar = pop(st);
			i++;
		}

		else if (isdigit(source[i]) || isalpha(source[i])) {
			target[j] = source[i];
			j++;
			i++;
		}

		else if (source[i] == '+' || source[i] == '-' || source[i] == '*' || source[i] == '/' || source[i] == '%')
		{
			while ((top != -1) && (st[top] != '(') && (getPriority(st[top]) > getPriority(source[i])))
			{
				target[j] = pop(st);
				j++;
			}

			push(st, source[i]);
			i++;
		}

		else 
		{
			printf("\n INCORRECT ELEMENT IN EXPRESSION");
			exit(1);
		}
	}

	while ((top != -1) && (st[top] != '('))
	{
		target[j] = pop(st);
		j++;
	}

	target[j] = '\0';
}

int getPriority(char op)
{
	if (op == '/' || op == '*' || op == '%')
		return 1;

	else if (op == '+' || op == '-')
		return 0;

	else
		return -1;
}

void push(char st[], char val)
{
	if (top == MAX - 1)
		printf("\n STACK OVERFLOW");

	else
	{
		top++;
		st[top] = val;
	}
}

char pop(char st[])
{
	char val = ' ';

	if (top == -1)
		printf("\n STACK UNDEFLOW");

	else
	{
		val = st[top];
		top--;
	}

	return val;
}

