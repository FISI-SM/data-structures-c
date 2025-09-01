/* Include standard input/output functions like printf() and scanf(). */
#include <stdio.h>

/* Include standard library for general utilities (not strictly required here, but good practice). */
#include <stdlib.h>

/* Define the maximum number of vertices allowed in this program. */
#define MAX 10

/* Forward declaration: function that creates a directed graph using user-entered edge pairs. */
void create_graph(int adj[][MAX], int *n_ptr);

/* Forward declaration: function that prints the adjacency matrix. */
void display_graph(int adj[][MAX], int n);

/* Forward declaration: function that performs topological sort (Kahn's Algorithm). */
void topological_sort(int adj[][MAX], int n);

/* Program execution starts here. */
int main(void)
{
    /* Declare the adjacency matrix (all zeros at start). */
    int adj[MAX][MAX] = {0};
    /* Variable to hold the number of vertices actually used in the graph. */
    int n = 0;

    /* Build the graph by asking the user for number of vertices and edge list. */
    create_graph(adj, &n);

    /* Print a blank line to separate input from output. */
    printf("\n");

    /* Display the adjacency matrix the user built (for confirmation). */
    display_graph(adj, n);

    /* Print a heading before showing the topological order. */
    printf("\nTopological sort order:\n");

    /* Run Kahn's Algorithm to produce and print a topological ordering. */
    topological_sort(adj, n);

    /* Print a newline so the shell prompt appears cleanly after program output. */
    printf("\n");

    /* Return 0 to indicate successful program completion. */
    return 0;
}
/* End of main(). */


/* This function asks the user for the number of vertices and then edge pairs (u v). */
void create_graph(int adj[][MAX], int *n_ptr)
{
    /* Local variable to hold the number of vertices entered by the user. */
    int n;
    /* Variables to hold each edge's origin (u) and destination (v). */
    int u, v;
    /* Loop counter used when clearing the matrix (optional safety). */
    int i, j;

    /* Ask the user for how many vertices will be in the graph. */
    printf("Enter number of vertices (max %d): ", MAX);
    /* Read the vertex count from the keyboard. */
    if (scanf("%d", &n) != 1) {
        /* Print an error if input fails. */
        fprintf(stderr, "Input error: expected an integer.\n");
        /* Exit the program since we cannot continue. */
        exit(1);
    }

    /* Check that n is within valid range. */
    if (n < 0 || n > MAX) {
        /* Warn the user and exit if invalid. */
        fprintf(stderr, "Error: number of vertices must be between 0 and %d.\n", MAX);
        exit(1);
    }

    /* Save the valid vertex count back through the pointer given by the caller. */
    *n_ptr = n;

    /* Clear the adjacency matrix rows actually in use (safety even though we zeroed at declaration). */
    for (i = 0; i < n; i++) {
        /* Loop across all columns for row i. */
        for (j = 0; j < n; j++) {
            /* Set no edge initially. */
            adj[i][j] = 0;
        }
    }

    /* Explain to the user how to enter edges. */
    printf("Enter directed edges as: from_vertex to_vertex  (0-based, e.g., 0 2)\n");
    /* Tell user how to finish entering edges. */
    printf("Enter -1 -1 to stop.\n");

    /* Keep reading edges until the user types the stop signal. */
    while (1) {
        /* Prompt for the next edge. */
        printf("Edge: ");
        /* Read two integers: u (from) and v (to). */
        if (scanf("%d %d", &u, &v) != 2) {
            /* If read fails, show error and exit. */
            fprintf(stderr, "Input error: expected two integers.\n");
            exit(1);
        }

        /* If the user entered -1 -1, stop reading edges. */
        if (u == -1 && v == -1) {
            /* Break out of the infinite while loop. */
            break;
        }

        /* Check that the edge is within the valid vertex range. */
        if (u < 0 || u >= n || v < 0 || v >= n) {
            /* Warn about invalid edge and ignore it. */
            printf("  Invalid edge (%d -> %d): vertices must be in 0..%d. Ignored.\n", u, v, n - 1);
            /* Continue to next input attempt without recording this edge. */
            continue;
        }

        /* Record a directed edge u -> v by setting adjacency matrix cell to 1. */
        adj[u][v] = 1;
    }
}
/* End of create_graph(). */


/* This function prints the adjacency matrix for confirmation/debugging. */
void display_graph(int adj[][MAX], int n)
{
    /* Loop counter for rows. */
    int i;
    /* Loop counter for columns. */
    int j;

    /* Print a heading line showing column labels as numbers. */
    printf("Adjacency matrix (%d x %d):\n    ", n, n);

    /* Print column indices across the top. */
    for (j = 0; j < n; j++) {
        /* Each column index printed in 3 spaces for alignment. */
        printf("%3d", j);
    }
    /* End the heading row with a newline. */
    printf("\n");

    /* Print a separator line to make the matrix easier to read. */
    printf("    ");
    for (j = 0; j < n; j++) {
        printf("---");
    }
    printf("\n");

    /* Loop over each row of the matrix. */
    for (i = 0; i < n; i++) {
        /* Print the row label (the row index number). */
        printf("%3d|", i);
        /* Loop across all columns in row i. */
        for (j = 0; j < n; j++) {
            /* Print the matrix entry (0 or 1). */
            printf("%3d", adj[i][j]);
        }
        /* End the row with a newline. */
        printf("\n");
    }
}
/* End of display_graph(). */


/* This function computes and prints a topological ordering using Kahn's Algorithm. */
void topological_sort(int adj[][MAX], int n)
{
    /* Array to hold the in-degree (incoming edge count) for each vertex. */
    int indeg[MAX];
    /* Queue to hold vertices whose in-degree is currently zero. */
    int queue[MAX];
    /* Front index for queue removal. */
    int front = 0;
    /* Rear index for queue insertion. */
    int rear = 0;
    /* Array to store the final topological order as we produce it. */
    int order[MAX];
    /* Count of how many vertices we have output so far. */
    int out_count = 0;
    /* Loop counters. */
    int i, j;
    /* Variable to hold the vertex removed from the queue. */
    int v;

    /* First, compute in-degree of every vertex by scanning columns. */
    for (j = 0; j < n; j++) {
        /* Start each in-degree at 0. */
        indeg[j] = 0;
        /* Scan each row i to see if there is an edge i -> j. */
        for (i = 0; i < n; i++) {
            /* If an edge exists from i to j, increment in-degree of j. */
            if (adj[i][j] == 1) {
                indeg[j]++;
            }
        }
    }

    /* Add all vertices with in-degree 0 into the queue to start the process. */
    for (i = 0; i < n; i++) {
        /* Check if this vertex has no incoming edges. */
        if (indeg[i] == 0) {
            /* Enqueue it by placing it at queue[rear] then advancing rear. */
            queue[rear++] = i;
        }
    }

    /* Process the queue until it is empty (front == rear means empty). */
    while (front < rear) {
        /* Remove (dequeue) the next zero in-degree vertex. */
        v = queue[front++];

        /* Record this vertex in the topological order array. */
        order[out_count++] = v;

        /* For each neighbor j such that v -> j is an edge... */
        for (j = 0; j < n; j++) {
            /* Check if there is an edge from v to j. */
            if (adj[v][j] == 1) {
                /* "Remove" the edge by decrementing j's in-degree. */
                indeg[j]--;
                /* OPTIONAL: we could also clear adj[v][j] = 0, but in-degree is what matters. */
                /* If j now has in-degree 0, enqueue it. */
                if (indeg[j] == 0) {
                    queue[rear++] = j;
                }
            }
        }
    }

    /* After processing, if out_count < n, the graph has a cycle (no topological order). */
    if (out_count < n) {
        /* Warn the user that a cycle stopped completion. */
        printf("Graph has a cycle! Topological sort not possible.\n");
        /* Return early because we cannot print a full order. */
        return;
    }

    /* If we get here, we have a valid topological order stored in 'order'. */
    for (i = 0; i < out_count; i++) {
        /* Print each vertex as a letter if small enough, else as a number. */
        if (order[i] >= 0 && order[i] < 26) {
            /* Print letter name for readability. */
            printf("%c", 'A' + order[i]);
        } else {
            /* Fallback to numeric print for larger indices. */
            printf("%d", order[i]);
        }
        /* Print a space after each except maybe last (space is fine). */
        printf(" ");
    }
}
/* End of topological_sort(). */

