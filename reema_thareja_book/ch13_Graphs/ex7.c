#include <stdio.h>
#include <stdlib.h>

#define MAX 5

#define INFINITY 9999

void read_matrix(int mat[MAX][MAX], int n);
void display_matrix(int mat[MAX][MAX], int n);
void floyd_warshall(int adj[MAX][MAX], int n, int Q[MAX][MAX]);

int main(void)
{
	int adj[MAX][MAX];
	int Q[MAX][MAX];
	int n;

	printf("\nEnter the number of nodes in the graph (max %d): ", MAX);

	if (scanf("%d", &n) != 1)
	{
		fprintf(stderr, "Input error.\n");
		return 1;
	}

	if (n<= 0 || n > MAX)
	{
		fprintf(stderr, "Invalid graph size.\n");
		return 1;
	}

	printf("\nEnter the %d * %d weighted adjacency matrix.\n", n, n);
	printf("(Use %d for NO EDGE. Diagonal entries will be forced to 0.)\n", INFINITY);

	read_matrix(adj, n);

	printf("\nThe adjacency matrix is:\n");
	display_matrix(adj, n);

	floyd_warshall(adj, n, Q);

	printf("\nFinal shortest-path distance matrix:\n");
	display_matrix(Q, n);

	return 0;
}

void read_matrix(int mat[MAX][MAX], int n)
{
	int i;
	int j;
	int w;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("Weight from %c to %c (0 ok, %d=no edge): ", 'A' + i, 'A' + j, INFINITY);

			if (scanf("%d", &w) != 1)
			{
				fprintf(stderr, "Input error while reading matrix.\n");
				exit(1);
			}

			if (i == j)
			{
				mat[i][j] = 0;
			}

			else if (w == INFINITY)
			{
				mat[i][j] = INFINITY;
			}

			else if (w == 0)
			{
				mat[i][j] = INFINITY;
			}

			else
			{
				mat[i][j] = w;
			}
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
			if (mat[i][j] >= INFINITY)
			{
				printf("INF\t");
			}

			else
			{
				printf("%d\t", mat[i][j]);
			}
		}

		printf("\n");
	}
}



void floyd_warshall(int adj[MAX][MAX], int n, int Q[MAX][MAX])
{
	int i;
	int j;
	int k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Q[i][j] = adj[i][j];
		}
	}

	printf("\nInitial distance matrix (k = none):\n");
	display_matrix(Q, n);

	
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (Q[i][k] < INFINITY && Q[k][j] < INFINITY)
				{
					if (Q[i][k] + Q[k][j] < Q[i][j])
					{
						Q[i][j] = Q[i][k] + Q[i][j];
					}
				}
			}
		}

		printf("\nDistance matrix after considering %c as intermediate (k = %d):\n", 'A' + k, k);
		display_matrix(Q, n);
	}
}
