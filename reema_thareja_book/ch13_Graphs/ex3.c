#include <stdio.h>

#define MAX 5

void depth_first_search(int adj[][MAX], int visited[], int start);

int main(void)
{
	int adj[MAX][MAX];

	int visited[MAX] = {0};

	int i, j;

	printf("\nEnter the %d * %d adjacency matrix (0/1 values):\n", MAX, MAX);

	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			scanf("%d", &adj[i][j]);
		}
	}

	printf("DFS Traversal: ");

	depth_first_search(adj, visited, 0);

	printf("\n");

	return 0;
}


void depth_first_search(int adj[][MAX], int visited[], int start)
{
	int stack[MAX];

	int top = -1;

	int i;

	int v;

	printf("%c- ", start + 'A');

	visited[start] = 1;

	stack[++top] = start;

	while (top != -1)
	{
		v = stack[top];

		for (i = 0; i < MAX; i++)
		{
			if (adj[v][i] == 1 && visited[i] == 0)
			{
				stack[++top] = i;

				printf("%c-", i + 'A');

				visited[i] = 1;

				break;
			}
		}

		if (i == MAX)
		{
			top--;
		}
	}
}



