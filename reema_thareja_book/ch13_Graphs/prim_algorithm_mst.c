#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

#define INF 100000000

void prim_mst(int cost[MAX][MAX], int n);

int main(void)
{
	int cost[MAX][MAX];

	int n;

	int i, j;

	int w;

	printf("Enter number of vertices (max %d): ", MAX);

	if (scanf("%d", &n) != 1)
	{
		fprintf(stderr, "Input error: expected an integer.\n");

		return 1;
	}

	if (n <= 0 || n >  MAX)
	{
		fprintf(stderr, "Error: number of vertices must be between 1 and %d.\n", MAX);

		return 1;
	}

	printf("Enter the %d * %d weight matrix.\n", n, n);

	printf("Use 0 for NO EDGE between DIFFERENT vertices.)\n");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (scanf("%d", &w) != 1)
			{
				fprintf(stderr, "Input error: expected an integer weight.\n");

				return 1;
			}

			if (i != j && w == 0)
			{
				cost[i][j] = INF;
			}

			else
			{
				cost[i][j] = w;
			}
		}
	}

	printf("\n");

	prim_mst(cost, n);

	return 0;
}

void prim_mst(int cost[MAX][MAX], int n)
{
	int key[MAX];

	int parent[MAX];

	int in_mst[MAX];

	int i, j;

	int u;

	int total_weight = 0;

	for (i = 0; i < n; i++)
	{
		key[i] = INF;

		parent[i] = -1;

		in_mst[i] = 0;
	}

	key[0] = 0;

	for (i = 0; i < n; i++)
	{
		u = -1;

		for (j = 0; j < n; j++)
		{
			if (!in_mst[j])
			{
				if (u == -1 || key[j] < key[u])
				{
					u = j;
				}

			}
		}
	

	
		in_mst[u] = 1;

	
		if (parent[u] != -1)
		{
		
			total_weight += cost[parent[u]][u];
		}

	
		for (j = 0; j < n; j++)
		{
			if (!in_mst[j] && cost[u][j] < key[j])
			{
			
				key[j] = cost[u][j];

				parent[j] = u;
			}
		}
	}
	
	printf("Edges in the Minimum spanning Tree:\n");

	for (i = 1; i < n; i++)
	{
		if (parent[i] >= 0 && parent[i] < 26 && i < 26)
		{
			printf("%c  - %c : %d\n", 'A' + parent[i], 'A' + i, cost[parent[i]][i]);
		}

		else
		{
			printf("%d - %d : %d\n", parent[i], i, cost[parent[i]][i]);
		}

	}

	printf("Total MST weight = %d\n", total_weight);
}
	
		
	
	
	
		
	
	


	



