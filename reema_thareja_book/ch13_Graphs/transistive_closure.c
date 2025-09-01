#include <stdio.h>

#define MAX 20

void print_matrix(int n, int matrix[MAX][MAX])
{
	int i;
	int j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", matrix[i][j]);
		}

		printf("\n");
	}
}

void transistive_closure(int n, int A[MAX][MAX], int T[MAX][MAX])
{
	int i;
	int j;
	int k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			T[i][j] = A[i][j];
		}
	}

	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (T[i][j] || (T[i][k] && T[k][j]))
				{
					T[i][j] = 1;
				}

				else
				{
					T[i][j] = 0;
				}
			}
		}
	}
}


int main(void)
{
	int i;
	int j;

	int n;

	int A[MAX][MAX];

	int T[MAX][MAX];

	printf("Enter number of vertices (<= %d): ", MAX);

	if (scanf ("%d", &n) != 1)
	{
		printf("Error: could not read number.\n");
		return 1;
	}

	if (n < 1 || n > MAX)
	{
		printf("Error: n must be between 1 and 5d.\n", MAX);
		return 1;
	}

	printf("\nEnter the %d * %d adjacency matrix (0 or 1 values):\n", n, n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (scanf("%d", &A[i][j]) != 1)
			{
				printf("Error: bad matrix input.\n");
				return 1;
			}

			A[i][j] = (A[i][j] != 0) ? 1 : 0;
		}
	}

	transistive_closure(n, A, T);

	printf("\nOriginal adjacency matrix (A):\n");

	print_matrix(n, A);

	printf("\nTransistive closure matrix (T):\n");

	print_matrix(n, T);

	return 0;
}


