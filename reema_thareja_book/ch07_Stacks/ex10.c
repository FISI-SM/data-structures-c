#include <stdio.h>

int Fact(int n);

int main()
{
	int num, val;

	printf("\n Enter the number: ");
	scanf("%d", &num);
	
	val = Fact(num);

	printf("\n Factorial of %d = %d\n", num, val);

	return 0;
}

int Fact(int n)
{
	if (n == 1)
		return 1;

	else
		return (n * Fact(n - 1));
}
