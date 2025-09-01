/* Include standard input/output functions like printf() and scanf(). */
#include <stdio.h>

/* Define the number of vertices we will handle in this example (A..E = 5). */
#define MAX 5

/* Declare the DFS function so main() knows about it before we define it. */
void depth_first_search(int adj[][MAX], int visited[], int start);

/* The program begins executing here. */
int main(void)
{
    /* This 2D array stores the adjacency matrix (1 = edge, 0 = no edge). */
    int adj[MAX][MAX];
    /* This array marks whether each vertex has been visited (0 = no, 1 = yes). */
    int visited[MAX] = {0};
    /* Loop counters for reading the matrix from the user. */
    int i, j;

    /* Ask the user to type in the adjacency matrix values. */
    printf("\nEnter the %d x %d adjacency matrix (0/1 values):\n", MAX, MAX);

    /* Loop over each row in the matrix. */
    for (i = 0; i < MAX; i++)
    {
        /* Loop over each column in the current row. */
        for (j = 0; j < MAX; j++)
        {
            /* Read a 0 or 1 into adj[i][j] from the keyboard. */
            scanf("%d", &adj[i][j]);
        }
    }

    /* Print a heading before running DFS so output is labeled clearly. */
    printf("DFS Traversal: ");

    /* Call our DFS function starting from vertex 0 (which we print as 'A'). */
    depth_first_search(adj, visited, 0);

    /* Print a newline after traversal so the shell prompt appears cleanly. */
    printf("\n");

    /* Return 0 to show the program ended normally. */
    return 0;
}

/* This function does an ITERATIVE Depth‑First Search using an explicit stack. */
void depth_first_search(int adj[][MAX], int visited[], int start)
{
    /* Declare an array that we will use as a stack to hold vertices to explore. */
    int stack[MAX];
    /* 'top' will hold the index of the current top of the stack (-1 means empty). */
    int top = -1;
    /* Loop counter used to scan across neighbors in the adjacency matrix row. */
    int i;
    /* Variable to hold the vertex currently at the top of the stack (peek). */
    int v;

    /* Print the starting vertex as a letter (0->A, 1->B, etc.) followed by a dash. */
    printf("%c-", start + 'A');

    /* Mark the starting vertex as visited so we don't push it again. */
    visited[start] = 1;

    /* Push the starting vertex onto the stack by advancing top and storing start. */
    stack[++top] = start;

    /* Keep going as long as the stack is NOT empty (top >= 0 means not empty). */
    while (top != -1)
    {
        /* Look at the vertex on top of the stack WITHOUT popping it yet. */
        v = stack[top];

        /* Scan all possible neighbors of vertex v by walking across row v. */
        for (i = 0; i < MAX; i++)
        {
            /* Check if there is an edge from v to i AND i has NOT been visited. */
            if (adj[v][i] == 1 && visited[i] == 0)
            {
                /* Push this newly discovered neighbor i onto the stack. */
                stack[++top] = i;

                /* Print the neighbor vertex name as a letter followed by a dash. */
                printf("%c-", i + 'A');

                /* Mark the neighbor as visited so we don't process it again. */
                visited[i] = 1;

                /* Break out of the for‑loop so we go "deeper" (DFS behavior). */
                break;
            }
        }

        /* If we scanned ALL columns (i == MAX) and found NO unvisited neighbor... */
        if (i == MAX)
        {
            /* Pop the stack by moving 'top' down one (discard current vertex). */
            top--;
        }
    }
}

