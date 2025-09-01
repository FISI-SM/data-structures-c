/************* RADIX SORT ALGORITHM *****************/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int largest(int arr[], int n);
void radix_sort(int arr[], int n);

int main()
{
	int arr[SIZE];
	int i, n;

	printf("\nEnter the number of elements in the array: ");
	scanf("%d", &n);

	printf("\nEnter the elements of the array: ");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	radix_sort(arr, n);

	printf("\nThe sorted array is:\n");
	for (i = 0; i < n; i++)
	{
		printf("%d\t", arr[i]);
	}

	printf("\n");

	return 0;
}

int largest(int arr[], int n)
{
	int large = arr[0];
	int i;

	for (i = 1; i < n; i++)
	{
		if (arr[i] > large)
			large = arr[i];
	}

	return large;
}


void radix_sort(int arr[], int n)
{
	int bucket[SIZE][SIZE];
	int bucket_count[SIZE];

	int i, j, k;
	int remainder;
	int NOP = 0;
	int divisor = 1;
	int large;
	int pass;

	large = largest(arr, n);

	while (large > 0)
	{
		NOP++;
		large /= SIZE;
	}

	for (pass = 0; pass < NOP; pass++)
	{
		for (i = 0; i < SIZE; i++)
		{
			bucket_count[i] = 0;
		}

		for (i = 0; i < n; i++)
		{
			remainder = (arr[i] / divisor) % SIZE;
			bucket[remainder][bucket_count[remainder]] = arr[i];
			bucket_count[remainder]++;
		}

		i = 0;

		for (k = 0; k < SIZE; k++)
		{
			for (j = 0; j < bucket_count[k]; j++)
			{
				arr[i] = bucket[k][j];
				i++;
			}
		}

		divisor *= SIZE;
	}
}

