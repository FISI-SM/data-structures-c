#include <stdio.h>

int exp_rec(int x, int y);

int main()
{
	int num1, num2, res;

	printf("\n Enter the two numbers (base and exponent): ");
	scanf("%d %d", &num1, &num2);

	res = exp_rec(num1, num2);

	printf("\n RESULT = %d\n", res);

	return 0;
}

int exp_rec(int x, int y)
{
	if (y == 0)
		return 1;
	else
		return (x * exp_rec(x, y - 1));
}
