#include <stdio.h>

#define MAX 10

void restoreHeapUp(int *heap, int index);
void restoreHeapDown(int *heap, int index, int n);

int main()
{
	int heap[MAX];
	int n, i, j;

	printf("\nEnter the number of elements: ");
	scanf("%d", &n);

	printf("Enter the elements:\n");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &heap[i]);
		restoreHeapUp(heap, i);
	}

	j = n;

	for (i = j - 1; i >= 1; i--)
	{
		int temp;

		temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;

		restoreHeapDown(heap, 0, i - 1);
	}

	printf("\nThe sorted elements are:\n");
	for (i = 0; i < j; i++)
	{
		printf("%4d", heap[i]);
	}

	printf("\n");

	return 0;
}

void restoreHeapUp(int *heap, int index)
{
	int val = heap[index];
	int parent = (index - 1) / 2;

	while (index > 0 && heap[parent] < val)
	{
		heap[index] = heap[parent];
		index = parent;
		parent = (index - 1) / 2;
	}

	heap[index] = val;
}


void restoreHeapDown(int *heap, int index, int n)
{
	int val = heap[index];
	int child = 2 * index + 1;

	while (child <= n)
	{
		if (child + 1 <= n && heap[child] < heap[child + 1])
		{
			child = child + 1;
		}

		if (val >= heap[child])
		{
			break;
		}

		heap[index] = heap[child];

		index = child;
		child = 2 * index + 1;
	}

	heap[index] = val;
}
