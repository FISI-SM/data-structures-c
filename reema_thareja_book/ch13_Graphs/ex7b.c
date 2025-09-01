/* Include standard input/output library for printf() and scanf(). */
#include <stdio.h>

/* Include standard library for exit() if we want to abort on bad input. */
#include <stdlib.h>

/* Define the maximum number of vertices supported (5 to match your original code). */
#define MAX 5

/* Define a large value to represent "no edge" / infinity. */
#define INFINITY 9999

/* Forward declare: read a weighted adjacency matrix with A,B,C labels. */
void read_matrix(int mat[MAX][MAX], int n);

/* Forward declare: display a matrix with A,B,C labels and show INF nicely. */
void display_matrix(int mat[MAX][MAX], int n);

/* Forward declare: run Floyd–Warshall, print intermediate Q matrices. */
void floyd_warshall(int adj[MAX][MAX], int n, int Q[MAX][MAX]);

/* Program entry point. */
int main(void)
{
    /* Declare adjacency matrix as entered by the user. */
    int adj[MAX][MAX];
    /* Declare matrix Q that will hold current shortest path distances. */
    int Q[MAX][MAX];
    /* Number of nodes actually in the graph. */
    int n;

    /* Ask user for number of nodes in the graph. */
    printf("\nEnter the number of nodes in the graph (max %d): ", MAX);
    /* Read n and check for input error. */
    if (scanf("%d", &n) != 1) {
        /* Report bad input and exit with error. */
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    /* Validate that n is within allowed range. */
    if (n <= 0 || n > MAX) {
        /* Report invalid size and exit. */
        fprintf(stderr, "Invalid graph size.\n");
        return 1;
    }

    /* Prompt user to enter the weighted adjacency matrix. */
    printf("\nEnter the %d x %d weighted adjacency matrix.\n", n, n);
    printf("(Use %d for NO EDGE. Diagonal entries will be forced to 0.)\n", INFINITY);
    /* Read values into adj[][] with labeled prompts. */
    read_matrix(adj, n);

    /* Echo the matrix back so the user can confirm input. */
    printf("\nThe adjacency matrix is:\n");
    display_matrix(adj, n);

    /* Run Floyd–Warshall and capture shortest paths into Q[][]; intermediate prints included. */
    floyd_warshall(adj, n, Q);

    /* Print final all‑pairs shortest path matrix after algorithm completes. */
    printf("\nFinal shortest‑path distance matrix:\n");
    display_matrix(Q, n);

    /* Normal program termination. */
    return 0;
}

/* Read an n x n weighted adjacency matrix with A,B,C labels. */
void read_matrix(int mat[MAX][MAX], int n)
{
    /* Row index. */
    int i;
    /* Column index. */
    int j;
    /* Temporary variable for user input. */
    int w;

    /* Loop over each row. */
    for (i = 0; i < n; i++) {
        /* Loop over each column in the row. */
        for (j = 0; j < n; j++) {
            /* Prompt user for weight from node i to node j. */
            printf("Weight from %c to %c (0 ok, %d=no edge): ", 'A' + i, 'A' + j, INFINITY);
            /* Read integer weight. */
            if (scanf("%d", &w) != 1) {
                /* Bad input: bail out. */
                fprintf(stderr, "Input error while reading matrix.\n");
                exit(1);
            }
            /* If on diagonal, force 0 distance (distance to self). */
            if (i == j) {
                mat[i][j] = 0;
            }
            /* Else if user entered INFINITY, keep as INFINITY (no edge). */
            else if (w == INFINITY) {
                mat[i][j] = INFINITY;
            }
            /* Else if user entered 0 off‑diagonal, treat as NO EDGE → INFINITY. */
            else if (w == 0) {
                mat[i][j] = INFINITY;
            }
            /* Otherwise store actual weight. */
            else {
                mat[i][j] = w;
            }
        }
    }
}

/* Display an n x n matrix with A,B,C column headers and INF for large values. */
void display_matrix(int mat[MAX][MAX], int n)
{
    /* Row index. */
    int i;
    /* Column index. */
    int j;

    /* Print top header spacing. */
    printf("\t");
    /* Print column labels A,B,C,... */
    for (j = 0; j < n; j++) {
        printf("%c\t", 'A' + j);
    }
    /* End header line. */
    printf("\n");

    /* Print each row labeled. */
    for (i = 0; i < n; i++) {
        /* Row label. */
        printf("%c\t", 'A' + i);
        /* Row contents. */
        for (j = 0; j < n; j++) {
            /* If value is INFINITY or greater, print INF token. */
            if (mat[i][j] >= INFINITY) {
                printf("INF\t");
            }
            /* Else print numeric distance. */
            else {
                printf("%d\t", mat[i][j]);
            }
        }
        /* End row. */
        printf("\n");
    }
}

/* Run Floyd–Warshall all‑pairs shortest paths on adj[][]; store results in Q[][]. */
/* Also print the matrix after each intermediate k (like your original code). */
void floyd_warshall(int adj[MAX][MAX], int n, int Q[MAX][MAX])
{
    /* Row index. */
    int i;
    /* Column index. */
    int j;
    /* Intermediate node index. */
    int k;

    /* Initialize Q from adj: copy all weights. */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            Q[i][j] = adj[i][j];
        }
    }

    /* Print initial distance matrix before any updates. */
    printf("\nInitial distance matrix (k = none):\n");
    display_matrix(Q, n);

    /* Outer loop: allow each vertex k as an intermediate in turn. */
    for (k = 0; k < n; k++) {
        /* For every source vertex i… */
        for (i = 0; i < n; i++) {
            /* For every destination vertex j… */
            for (j = 0; j < n; j++) {
                /* Check if going i -> k -> j is shorter than current i -> j. */
                /* Avoid overflow: only add if both legs are not INFINITY. */
                if (Q[i][k] < INFINITY && Q[k][j] < INFINITY) {
                    /* If new path shorter, update. */
                    if (Q[i][k] + Q[k][j] < Q[i][j]) {
                        Q[i][j] = Q[i][k] + Q[k][j];
                    }
                }
            }
        }
        /* After using node k as intermediate, show updated matrix. */
        printf("\nDistance matrix after considering %c as intermediate (k = %d):\n", 'A' + k, k);
        display_matrix(Q, n);
    }
}

