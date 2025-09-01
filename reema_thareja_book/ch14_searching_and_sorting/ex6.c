/********  BUBBLE SORT ALGORITHM   ***********/


#include <stdio.h>

#define MAX 10

int main()
{
	int i, j, temp, n, arr[MAX];

	printf("Enter the number of elements in the array: ");
	scanf("%d", &n);

	printf("Enter the elements:\n");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);

	}

	for (i = 0; i < n - 1; i++)    //controls number of passes
	{
		for (j = 0; j < n - i - 1; j++)   //compares each adjacent pair of numbers
		{
			if (arr[j] > arr[j + 1])  //if number greater than it's neighbor
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	printf("The array sorted in ascending order is:\n");
	for (i = 0; i < n; i++)
	{
		printf("%d\t", arr[i]);
	}

	printf("\n");

	return 0;
}
