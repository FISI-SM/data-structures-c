/********** INTERPOLATION OR EXTRAPOLATION SEARCH ALGORITHM *********/


#include <stdio.h>

#define MAX 20

int interpolation_search(int a[], int low, int high, int val)
{
	int mid;

	while (low <= high && val >= a[low] && val <= a[high])
	{
		mid = low + ((val - a[low]) * (high - low)) / (a[high] - a[low]);

		if (val == a[mid])
			return mid;

		if (val < a[mid])
			high = mid - 1;

		else
			low = mid + 1;
	}

	return -1;
}


int main()
{
	int arr[MAX], i, n, val, pos;

	printf("\nEnter the number of elements in the array: ");
	scanf("%d", &n);

	printf("\nEnter the elements in sorted order: ");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}	

	printf("\nEnter the value to be seached: ");
	scanf("%d", &val);

	pos = interpolation_search(arr, 0, n - 1, val);

	if (pos == -1)
		printf("\n%d is not found in the array.\n", val);
	else
		printf("\n%d is found at position %d.\n", val, pos + 1);

	return 0;
}
