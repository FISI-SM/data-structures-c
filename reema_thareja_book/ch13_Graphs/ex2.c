#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void breadth_first_search(int adj[][MAX], int visited[], int n, int start);

int main(void)
{
	int visited[MAX] = {0};

	int adj[MAX][MAX];

	int i, j;

	int n;

	int start;

	printf("Enter number of vertices (max %d): ", MAX);

	if (scanf("%d", &n) != 1)
	{
		fprintf(stderr, "Input error: expected an integer.\n");
		return 1;
	}

	if (n < 0 || n > MAX)
	{
		fprintf(stderr, "Error: number of vertices must be between 0 and %d.\n", MAX);
		return 1;
	}

	printf("Enter the number %d * %d adjacency matrix (0/1 values):\n", n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (scanf("%d", &adj[i][j]) != 1)
			{
				fprintf(stderr, "Input error: expected an intger.\n");
				return 1;
			}
		}
	}

	printf("Enter start vertex (0 to %d): ", n - 1);

	if (scanf("%d", &start) != 1)
	{
		fprintf(stderr, "Input error: expected as integer.\n");
		return 1;
	}

	if (start < 0 || start >= n)
	{
		fprintf(stderr, "Error: start vertex must be between 0 and %d.\n", n - 1);
		return 1;
	}

	printf("\nBFS visit order:\n");

	breadth_first_search(adj, visited, n, start);

	printf("\n");

	return 0;
}


void breadth_first_search(int adj[][MAX], int visited[], int n, int start)
{
	int queue[MAX];

	int front = 0;

	int rear = 0;

	int i;

	int v;

	queue[rear++] = start;

	visited[start] = 1;

	while (front < rear)
	{
		v = queue[front++];

		if (v >= 0 && v < 26)
		{
			printf("%c ", 'A' + v);
		}
		else
		{
			printf("%d ", v);
		}


		for (i = 0; i < n; i++)
		{
			if (adj[v][i] == 1 && visited[i] == 0)
			{
				queue[rear++] = i;

				visited[i] = 1;
			}
		}
	}
}

	
	
 		

