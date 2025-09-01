#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge 
{
	int u;
	int v;
	int w;
};

struct Subset
{
	int parent;
	int rank;
};

int compareEdges(const void *a, const void *b)
{
	const struct Edge *e1 = (const struct Edge *)a;
	const struct Edge *e2 = (const struct Edge *)b;

	return e1->w - e2->w;
}

int find(struct Subset subsets[], int i)
{
	if (subsets[i].parent != i)
	{
		subsets[i].parent = find(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y)
{
	int rootX = find(subsets, x);
	int rootY = find(subsets, y);

	if (rootX == rootY)
	{
		return;
	}

	if (subsets[rootX].rank < subsets[rootY].rank)
	{
		subsets[rootX].parent = rootY;
	}

	else if (subsets[rootX].rank > subsets[rootY].rank)
	{
		subsets[rootY].parent = rootX;
	}

	else
	{
		subsets[rootY].parent = rootX;

		subsets[rootX].rank++;
	}
}






int main(void)
{
	int V, E, i, totalCost = 0, mstCount = 0;
	
	struct Edge *mstEdges = NULL;

	struct Edge *edges = NULL;

	struct Subset *subsets = NULL;

	printf("Enter number of vertices: ");

	if (scanf("%d", &V) != 1)
	{
		fprintf(stderr, "Input error.\n");
		return 1;
	}

	printf("Enter number of edges: ");

	if (scanf("%d", &E) != 1)
	{
		fprintf(stderr, "Input error.\n");
		return 1;
	}

	edges = (struct Edge *)malloc(E * sizeof(struct Edge));
	if (edges == NULL)
	{
		fprintf(stderr, "Out of memory (edges).\n");
		return 1;
	}

	mstEdges = (struct Edge *)malloc((V - 1) * sizeof(struct Edge));
	if (mstEdges == NULL)
	{
		fprintf(stderr, "Out of memory (mstEdges).\n");
		free(edges);
		return 1;
	}

	subsets = (struct Subset *)malloc(V * sizeof(struct Subset));
	if (subsets ==  NULL)
	{
		fprintf(stderr, "Out of memory (subsets).\n");
		free(edges);
		free(mstEdges);
		return 1;
	}

	printf("Enter each edge as: u v w (vertices 0..%d, weight w)\n", V - 1);

	for (i = 0; i < E; i++)
	{
		if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w) != 3)
		{
			fprintf(stderr, "Input error while reading edges.\n");
			free(edges);
			free(mstEdges);
			free(subsets);
			return 1;
		}
	

		if (edges[i].u < 0 || edges[i].u >= V || edges[i].v < 0 || edges[i].v >= V)
		{
			fprintf(stderr, "Invalid edge ignored: %d %d %d\n", edges[i].u, edges[i].v, edges[i].w);
			edges[i].u = edges[i].v = 0;
			edges[i].w = INT_MAX;
		}
	}	


	qsort(edges, E, sizeof(edges[0]), compareEdges);

	for (i = 0; i < V; i++)
	{
		subsets[i].parent = i;

		subsets[i].rank = 0;
	}

	for (i = 0; i < E && mstCount < V - 1; i++)
	{
		int set_u = find(subsets, edges[i].u);

		int set_v = find(subsets, edges[i].v);

		if (set_u != set_v)
		{
			mstEdges[mstCount] = edges[i];

			totalCost += edges[i].w;

			mstCount++;

			Union(subsets, set_u, set_v);
		}
	}

	printf("\nEdges in the Minimum Spanning Tree:\n");

	for (i = 0; i <  mstCount; i++)
	{
		printf("%d -- %d (weight %d)\n", mstEdges[i].u, mstEdges[i].v, mstEdges[i].w);
	}

	printf("Total cost of Minimum Spanning Tree: %d\n", totalCost);

	if (mstCount < V - 1)
	{
		printf("Warning: Graph is disconnected; MST incomplete.\n");
	}

	free(edges);
	free(mstEdges);
	free(subsets);

	return 0;
}
