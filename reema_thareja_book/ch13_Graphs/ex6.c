/****** Warshall's Algotihm *************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

void read_matrix(int mat[MAX][MAX], int n);
void display_matrix(int mat[MAX][MAX], int n);
void warshall(int adj[MAX][MAX], int n, int path[MAX][MAX]);

int main(void)
{
	int adj[MAX][MAX];

	int P[MAX][MAX];

	int n;

	printf("\nEnter the number of nodes in the graph (max %d): ", MAX);

	if (scanf("%d", &n) != 1)
	{
		fprintf(stderr, "Input error.\n");
		return 1;
	}

	if (n <= 0 || n > MAX)
	{
		fprintf(stderr, "Invalid graph size.\n");
		return 1;
	}

	printf("\nEnter the %d * %d adjacency matrix (0/1):\n", n, n);

	read_matrix(adj, n);

	printf("\nThe adjacency matrix is:\n");
	display_matrix(adj, n);

	warshall(adj, n, P);

	printf("\nThe path (Transistive Closure) Matrix is:\n");
	display_matrix(P, n);

	return 0;
}

void read_matrix(int mat[MAX][MAX], int n)
{
	int i;

	int j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("Enter edge from %c to %c (0 or 1): ", 'A' + i, 'A' + j);
			scanf("%d", &mat[i][j]);
		}
	}
}


void display_matrix(int mat[MAX][MAX], int n)
{
	int i;

	int j;

	printf("\t");

	for (j = 0; j < n; j++)
	{
		printf("%c\t", 'A' + j);
	}

	printf("\n");

	for (i = 0; i < n; i++)
	{
		printf("%c\t", 'A' + i);

		for (j = 0; j < n; j++)
		{
			printf("%d\t", mat[i][j]);
		}

		printf("\n");
	}
}


void warshall(int adj[MAX][MAX], int n, int path[MAX][MAX])
{
	int i, j, k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (adj[i][j] != 0)
				path[i][j] = 1;

			else
				path[i][j] = 0;
		}

		path[i][i] = 1;
	}

	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				path[i][j] = path[i][j] || (path[i][k] && path[k][j]);
			}
		}
	}
}



