/******************* MERGE SORT ALGORITHM ********************/

#include <stdio.h>

#define size 100

void merge(int a[], int beg, int mid, int end);
void merge_sort(int a[], int beg, int end);

int main()
{
	int arr[size], i, n;

	printf("\n Enter the number of elements in the array: ");
	scanf("%d", &n);

	printf("\n Enter the elements of the array: ");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	merge_sort(arr, 0, n - 1);

	printf("\n The sorted array is: \n");
	for (i = 0; i < n; i++)
	{
		printf(" %d\t", arr[i]);
	}

	return 0;
}

void merge(int arr[], int beg, int mid, int end)
{
	int i = beg, j =  mid + 1, index = beg, temp[size], k;

	while (i <= mid && j <= end)
	{
		if (arr[i] < arr[j])
		{
			temp[index] = arr[i];
			i++;
		}

		else
		{
			temp[index] = arr[j];
			j++;
		}

		index++;
	}

	if (i <= mid)
	{
		while (i <= mid)
		{
			temp[index] = arr[i];
			i++;
			index++;
		}
	}

	else
	{
		while (j <= end)
		{
			temp[index] = arr[j];
			j++;
			index++;
		}
	}

	for (k = beg; k < index; k++)
	{
		arr[k] = temp[k];
	}
}


void merge_sort(int arr[], int beg, int end)
{
	int mid;

	if (beg < end)
	{
		mid = (beg + end) / 2;

		merge_sort(arr, beg, mid);

		merge_sort(arr, mid + 1, end);

		merge(arr, beg, mid, end);
	}
}
