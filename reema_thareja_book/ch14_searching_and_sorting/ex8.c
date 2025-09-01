/****************** SELECTION SORT **********************/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int smallest(int arr[], int k, int n)
{
	int pos = k;
	int small = arr[k];

	for (int i = k + 1; i < n; i++)
	{
		if (arr[i] < small)
		{
			small = arr[i];
			pos = i;
		}
	}

	return pos;
}

void selection_sort(int arr[], int n)
{
	int k, pos, temp;

	for (k = 0; k < n; k++)
	{
		pos = smallest(arr, k, n);

		temp = arr[k];
		arr[k] = arr[pos];
		arr[pos] = temp;
	}
}

int main()
{
	int arr[SIZE];
	int n, i;

	printf("\nEnter the number of elements in the array: ");
	scanf("%d", &n);

	printf("Enter the elements of the array:\n");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	selection_sort(arr, n);

	printf("\nThe sorted array is:\n");
	for (i = 0; i < n; i++)
	{
		printf("%d\t", arr[i]);
	}

	printf("\n");

	return 0;
}
