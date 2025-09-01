#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10

#define INF 1000000000

int adj[MAX][MAX];

int tree[MAX][2];

int n = 0;

void readmatrix(void)
{
	int i, j;

	int w;

	printf("\nEnter the number of nodes in the Graph (max %d): ", MAX);

	if (scanf("%d", &n) != 1)
	{
		fprintf(stderr, "Input error.\n");
		exit(1);
	}

	if (n <= 0 || n > MAX)
	{
		fprintf(stderr, "Invalid number of nodes.\n");
		exit(1);
	}

	printf("\nEnter the %d * %d adjacency (weight) matrix:\n", n, n);
	printf("Use 0 for N0 EDGE between DIFFERENT vertices. Diagonal may be 0.)\n");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (scanf("%d", &w) != 1)
			{
				fprintf(stderr, "Input error wile readin matrix.\n");
				exit(1);
			}

			if (i != j && w == 0)
			{
				adj[i][j] = INF;
			}

			if (i != j && w == 0)
			{
				adj[i][j] = INF;
			}

			else
			{
				adj[i][j] = w;
			}
		}
	}
}



int spanningtree(int src)
{
	int visited[MAX];

	int d[MAX];

	int parent[MAX];

	int i, j;

	int u = -1;

	int v;

	int min;

	int cost = 0;

	int k = 0;

	for (i = 0; i < n; i++)
	{
		d[i] = adj[src][i];

		visited[i] = 0;

		parent[i] = src;
	}

	visited[src] = 1;

	parent[src] = -1;

	d[src] = 0;

	for (i = 1; i < n; i++)
	{
		min = INF;

		u = -1;

		for (j = 0; j < n; j++)
		{
			if (!visited[j] && d[j] < min)
			{
				min = d[j];

				u = j;
			}
		}

		if (u == -1 || min == INF)
		{
			printf("\nWarning: Graph is disconnected; MST incomplete.\n");
			break;
		}

		visited[u] = 1;

		cost += d[u];

		tree[k][0] = parent[u];
		tree[k][1] = u;
		k++;

		for (v = 0; v < n; v++)
		{
			if (!visited[v] && adj[u][v] < d[v])
			{
				d[v] = adj[u][v];

				parent[v] = u;
			}
		}
	}

	return cost;
}


void display(int cost)
{
	int i;

	printf("\nThe Edges of the minimum spanning Tree are:\n");

	for (i = 0; i < n - 1; i++)
	{
		if (tree[i][0] == -1)
		{
			continue;
		}

		printf("%d %d\n", tree[i][0], tree[i][1]);
	}

	printf("\nThe total cost of the Minimum Spanning Tree is: %d\n", cost);
}


int main(void)
{
	int source;

	int treecost;

	readmatrix();

	printf("\nEnter the source (0 to %d): ", n - 1);

	if (scanf("%d", &source) != 1)
	{
		fprintf(stderr, "Input error.\n");
		return 1;
	}

	if (source < 0 || source >= n)
	{
		fprintf(stderr, "Invalid source vertex.\n");
		return 1;
	}

	treecost = spanningtree(source);

	display(treecost);

	return 0;
}
