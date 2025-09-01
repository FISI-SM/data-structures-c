#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void create_graph(int adj[][MAX], int *n_ptr);

void display_graph(int adj[][MAX], int n);

void topological_sort(int adj[][MAX], int n);

int main(void)
{
	int adj[MAX][MAX] = {0};

	int n = 0;

	create_graph(adj, &n);

	printf("\n");

	display_graph(adj, n);

	printf("\nTopological sort order:\n");

	topological_sort(adj, n);

	printf("\n");

	return 0;

}


void create_graph(int adj[][MAX], int *n_ptr)
{
	int n;
	
	int u, v;

	int i, j;

	printf("Enter number of vertices (max %d): ", MAX);

	if (scanf("%d", &n) != 1)
	{
		fprintf(stderr, "Input error: expected an integer.\n");
		exit(1);
	}

	if (n < 0 || n > MAX)
	{
		fprintf(stderr, "Error: number of vertices must be between 0 and %d.\n");
		exit(1);
	}

	*n_ptr = n;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			adj[i][j] = 0;
		}
	}

	printf("Enter directed edges as: from_vertex to_vertex (0 based. e.g 0 2)\n");
	printf("Enter -1 -1 to stop.\n");

	while (1)
	{
		printf("Edge: ");

		if (scanf("%d %d", &u, &v) != 2)
		{
			fprintf(stderr, "Input error: expected two integers.\n");
			exit(1);
		}

		if (u == -1 && v == -1)
		{
			break;
		}

		if (u < 0 || u >= n || v < 0 || v >= n)
		{
			printf(" Invalid edge (%d -> %d): vertices must be in 0..%d.\n", u, v, n - 1);

			continue;
		}

		adj[u][v] = 1;
	}
}


void display_graph(int adj[][MAX], int n)
{
	int i;
	int j;

	printf("Adjacency matrix (%d * %d):\n     ", n, n);

	for (j = 0; j < n; j++)
	{
		printf("%3d", j);
	}

	printf("\n");

	printf("   ");
	
	for (j = 0; j < n; j++)
	{
		printf("- - -");
	}

	printf("\n");

	for (i = 0; i < n; i++)
	{
		printf("%3d|", i);

		for (j = 0; j < n; j++)
		{
			printf("%3d", adj[i][j]);
		}

		printf("\n");
	}
}


void topological_sort(int adj[][MAX], int n)
{
	int indeg[MAX];

	int queue[MAX];

	int front = 0;

	int rear = 0;

	int order[MAX];

	int out_count = 0;

	int i, j;

	int v;


	for (j = 0; j < n; j++)
	{
		indeg[j] = 0;

		for (i = 0; i < n; i++)
		{
			if (adj[i][j] == 1)
			{
				indeg[j]++;
			}
		}
	}

	for (i = 0; i < n; i++)
	{
		if (indeg[i] == 0)
		{
			queue[rear++] = i;
		}
	}

	while (front < rear)
	{
		v =  queue[front++];

		order[out_count++] = v;

		for (j = 0; j < n; j++)
		{
			if (adj[v][j] == 1)
			{
				indeg[j]--;

				if (indeg[j] == 0)
				{
					queue[rear++] = j;
				}
			}
		}
	}

	if (out_count < n)
	{
		printf("Graph has a cycle| Topological sort not possible.\n");

		return;
	}


	for (i = 0; i < out_count; i++)
	{
		if (order[i] >= 0 && order[i] < 26)
		{
			printf("%c", 'A' + order[i]);
		}

		printf(" ");
	}
}

