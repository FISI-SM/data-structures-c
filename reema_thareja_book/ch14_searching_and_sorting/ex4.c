/********* JUMP SEARCH ALGORITHM ************/

#include <stdio.h>
#include <math.h>

#define MAX 20

int jump_search(int a[], int low, int high, int val, int n)
{
	int step = sqrt(n);

	int prev = 0;

	while (a[(int)fmin(step, n) - 1] < val)
	{
		prev = step;
	        step += sqrt(n);

		if (prev >= n)
			return -1;
	}

	while (prev < fmin(step, n))
	{
		if (a[prev] == val)
			return prev;

		prev++;
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
		scanf("%d", &arr[i]);

	printf("\nEnter the value to be searched: ");
	scanf("%d", &val);

	pos = jump_search(arr, 0, n - 1, val, n);

	if (pos == -1)
		printf("\n%d is not found in the array.\n", val);
	else
		printf("\n%d is found at postion %d.\n", val, pos + 1);

	return 0;
}


