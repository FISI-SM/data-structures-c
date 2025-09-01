/************ FIBONACCI SEARCH ALGORITHM ***********/

#include <stdio.h>

int fibonacciSearch(int arr[], int n, int x)
{
	int fib2 = 0;
	int fib1 = 1;
	int fibM = fib2 + fib1;

	while (fibM < n)
	{
		fib2 = fib1;
		fib1 = fibM;
		fibM = fib1 + fib2;
	}

	int offset = -1;

	while (fibM > 1)
	{
		int i = (offset + fib2 < n - 1) ? offset + fib2 : n - 1;

		if (arr[i] < x)
		{
			fibM = fib1;
			fib1 = fib2;
			fib2 = fibM - fib1;
			offset = i;
		}

		else if (arr[i] > x)
		{
			fibM = fib2;
			fib1 = fib1 - fib2;
			fib2 = fibM - fib1;
		}

		else
		{
			return i;
		}
	}

	if (fib1 && arr[offset + 1] == x)
	{
		return offset + 1;
	}

	return -1;
}


int main()
{
	int arr[100], n, i, val, pos;

	printf("Enter number of  elements (sorted): ");
	scanf("%d", &n);

	printf("Enter %d sorted elements:\n", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("Enter value to search: ");
	scanf("%d", &val);

	pos = fibonacciSearch(arr, n, val);

	if (pos >= 0)
		printf("%d found at index %d\n", val, pos);
	else
		printf("%d not found in the array\n", val);

	return 0;
}

