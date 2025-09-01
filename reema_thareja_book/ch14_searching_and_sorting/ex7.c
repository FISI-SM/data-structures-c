/*****************  INSERTION SORT ALGORITHM ****************/

#include <stdio.h>

#define size 5

void insertion_sort(int arr[], int n)
{
	int i, j, temp;

	for (i = 1; i < n; i++)
	{
		temp = arr[i];
		 j = i - 1;

		 while ((temp < arr[j]) && (j >= 0))
		 {
			 arr[j + 1] = arr[j];
			 j--;
		 }

		 arr[j + 1] = temp;
	}
}

int main()
{
	int arr[size];

	int i, n;

	printf("\n Enter the number of elements in the array: ");
	scanf("%d", &n);

	printf("\n Enter the elements of the array: ");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	insertion_sort(arr, n);

	printf("\n The sorted array is: \n");
	for (i = 0; i < n; i++)
	{
		printf(" %d\t", arr[i]);
	}

	return 0;
}
