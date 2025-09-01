/* Include standard input/output function declarations. */
#include <stdio.h>

/* Include standard library for exit() if we need to abort on invalid input. */
#include <stdlib.h>

/* Define the maximum number of nodes supported (matrix is MAX x MAX). */
#define MAX 5

/* Forward declaration: read an n x n adjacency matrix from user (0/1). */
void read_matrix(int mat[MAX][MAX], int n);

/* Forward declaration: display an n x n matrix with A,B,C... row/col labels. */
void display_matrix(int mat[MAX][MAX], int n);

/* Forward declaration: compute transitive closure using Warshall’s algorithm. */
void warshall(int adj[MAX][MAX], int n, int path[MAX][MAX]);

/* Program execution starts here. */
int main(void)
{
    /* Declare adjacency matrix entered by user. */
    int adj[MAX][MAX];
    /* Declare path matrix (transitive closure) to be computed. */
    int P[MAX][MAX];
    /* Store number of nodes actually used. */
    int n;

    /* Ask user how many nodes are in the graph. */
    printf("\nEnter the number of nodes in the graph (max %d): ", MAX);
    /* Read node count; if bad input, quit. */
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    /* Validate node count is in range. */
    if (n <= 0 || n > MAX) {
        fprintf(stderr, "Invalid size.\n");
        return 1;
    }

    /* Prompt to enter adjacency matrix values. */
    printf("\nEnter the %d x %d adjacency matrix (0/1):\n", n, n);
    /* Read the matrix from user. */
    read_matrix(adj, n);

    /* Echo adjacency matrix back to user with labels. */
    printf("\nThe adjacency matrix is:\n");
    display_matrix(adj, n);

    /* Compute path (reachability) matrix using Warshall’s algorithm. */
    warshall(adj, n, P);

    /* Show final path matrix with labels. */
    printf("\nThe Path (Transitive Closure) Matrix is:\n");
    display_matrix(P, n);

    /* Return 0 to signal normal completion. */
    return 0;
}

/* Read an n x n matrix of 0/1 edges; label prompts with A,B,C... */
void read_matrix(int mat[MAX][MAX], int n)
{
    /* Row index. */
    int i;
    /* Column index. */
    int j;

    /* Loop over each row. */
    for (i = 0; i < n; i++) {
        /* Loop over each column in the row. */
        for (j = 0; j < n; j++) {
            /* Prompt for edge from row node to column node. */
            printf("Enter edge from %c to %c (0 or 1): ", 'A' + i, 'A' + j);
            /* Read value into matrix. */
            scanf("%d", &mat[i][j]);
        }
    }
}

/* Display an n x n matrix with letter labels on rows and columns. */
void display_matrix(int mat[MAX][MAX], int n)
{
    /* Row index. */
    int i;
    /* Column index. */
    int j;

    /* Print leading tab to align column headers. */
    printf("\t");
    /* Print column headers A,B,C... */
    for (j = 0; j < n; j++) {
        printf("%c\t", 'A' + j);
    }
    /* End header line. */
    printf("\n");

    /* Print each row preceded by its letter label. */
    for (i = 0; i < n; i++) {
        /* Row label. */
        printf("%c\t", 'A' + i);
        /* Row contents. */
        for (j = 0; j < n; j++) {
            printf("%d\t", mat[i][j]);
        }
        /* End of this row. */
        printf("\n");
    }
}

/* Compute transitive closure matrix path[][] from adjacency matrix adj[][]. */
void warshall(int adj[MAX][MAX], int n, int path[MAX][MAX])
{
    /* Row index. */
    int i;
    /* Column index. */
    int j;
    /* Intermediate node index k. */
    int k;

    /* Initialize path[][] from adjacency: nonzero becomes 1, zero becomes 0. */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            path[i][j] = (adj[i][j] != 0) ? 1 : 0;
        }
        /* Make each node reachable from itself (comment out if not desired). */
        path[i][i] = 1;
    }

    /* Core Warshall triple loop: try all intermediate nodes k. */
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                /* Reachable if already reachable OR via k (i->k AND k->j). */
                path[i][j] = path[i][j] || (path[i][k] && path[k][j]);
            }
        }
    }
}

