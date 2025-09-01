#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10

struct Node 
{
	int vertex;
	struct Node *next;
};


void createGraph(struct Node *Adj[], int no_of_nodes);
void displayGraph(struct Node *Adj[], int no_of_nodes);
void deleteGraph(struct Node *Adj[], int no_of_nodes);


int main(void)
{
	struct Node *Adj[MAX_NODES];

	int i, no_of_nodes;

	printf("\nEnter the number of nodes in G (max %d): ", MAX_NODES);

	if (scanf("%d", &no_of_nodes) != 1)
	{
		fprintf(stderr, "Input error: expected an integer.\n");
		return 1;
	}

	if (no_of_nodes < 0 || no_of_nodes > MAX_NODES)
	{
		fprintf(stderr, "Error: number of nodes must be between 0 and %d.\n", MAX_NODES);
		return 1;
	}

	for (i = 0; i < no_of_nodes; i++)
	{
		Adj[i] = NULL;
	}

	createGraph(Adj, no_of_nodes);

	printf("\n");

	displayGraph(Adj, no_of_nodes);

	deleteGraph(Adj, no_of_nodes);

	return 0;
}


void createGraph(struct Node *Adj[], int no_of_nodes)
{
	struct Node *new_node;

	struct Node *last;

	int i, j;

	int n;

	int val;

	for (i = 0; i < no_of_nodes; i++)
	{
		last = NULL;

		printf("\nEnter the number of neighbours of %d: ", i);

		if (scanf("%d", &n) != 1)
		{
			fprintf(stderr, "Input error: expected an integer.\n");

			continue;
		}

		for (j = 1; j <= n; j++)
		{
			printf(" Enter neighbour %d: ", j, i);

			if (scanf("%d", &val) != 1)
			{
				fprintf(stderr, "Input error: expected an integer.\n");
				break;
			}

			if (val < 0 || val >= no_of_nodes)
			{
				fprintf(stderr, " Warning: %d is not a valid vertex. Skipping.\n");
				continue;
			}

			new_node = (struct Node *)malloc(sizeof(struct Node));
			if (new_node == NULL)
			{
				fprintf(stderr, " Error: out of memory while adding neighbour.\n");
				break;
			}

			new_node->vertex = val;
			new_node->next = NULL;

			if (Adj[i] == NULL)
			{
				Adj[i] = new_node;
			}
			else
			{
				last->next = new_node;
			}

			last = new_node;
		}
	}
}



void displayGraph(struct Node *Adj[], int no_of_nodes)
{
	struct Node *ptr;
	int i;

	for (i = 0; i < no_of_nodes; i++)
	{
		ptr = Adj[i];

		printf("Neighbours of node %d;", i);

		while (ptr != NULL)
		{
			printf(" %d", ptr->vertex);

			ptr = ptr->next;
		}

		printf("\n");
	}
}


void deleteGraph(struct Node *Adj[], int no_of_nodes)
{
	int i;
	
	struct Node *ptr;

	struct Node *temp;

	for (i = 0; i < no_of_nodes; i++)
	{
		ptr = Adj[i];

		while (ptr != NULL)
		{
			temp = ptr;

			ptr = ptr->next;

			free(temp);
		}

		Adj[i] = NULL;
	}
}
