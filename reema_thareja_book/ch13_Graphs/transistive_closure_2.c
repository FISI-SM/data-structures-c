/* ------------------------------------------------------------------------- */
/* TRANSITIVE CLOSURE OF A DIRECTED GRAPH (Warshall-style algorithm)         */
/*                                                                           */
/* This program reads:                                                       */
/*   - The number of vertices n.                                             */
/*   - An n x n adjacency matrix A (0 or 1) describing a directed graph.     */
/* It then computes the transitive closure matrix T, where T[i][j] = 1 if    */
/* there is *any* path (of length >= 1) from vertex i to vertex j in the     */
/* graph, otherwise 0.                                                       */
/*                                                                           */
/* The algorithm used is the classic Warshall transitive-closure algorithm:  */
/*                                                                           */
/*   for k = 0..n-1                                                           */
/*     for i = 0..n-1                                                         */
/*       for j = 0..n-1                                                       */
/*         T[i][j] = T[i][j] OR (T[i][k] AND T[k][j])                        */
/*                                                                           */
/* The pseudo-steps you gave (Transitive_Closure(A,t,n)) correspond to this  */
/* triple-loop structure. In the pseudo-code, indices ran 1..n; here in C we */
/* use 0..n-1, which is the normal C array indexing.                         */
/*                                                                           */
/* ---------------------------- BEGINNER NOTES ----------------------------- */
/* 1. "OR" means logical OR: in C we write it as ||  (two vertical bars).    */
/* 2. "AND" means logical AND: in C we write it as && (two ampersands).      */
/* 3. We store graph edges as ints (0 or 1). We treat any non-zero as TRUE.   */
/* 4. We copy the original adjacency matrix A into T before we start, so T   */
/*    begins as the direct-edge info and grows as we discover paths.          */
/* 5. No Windows-specific headers are used. This is Kali Linux friendly.     */
/*                                                                           */
/* ---------------------------- COMPILE / RUN ------------------------------ */
/*   gcc transitive_closure_with_line_by_line_comments.c -o trans_closure    */
/*   ./trans_closure                                                         */
/* ------------------------------------------------------------------------- */

/* Include stdio.h so we can use printf() and scanf() for input and output. */
#include <stdio.h>

/* We pick a maximum number of vertices to keep things simple for beginners. */
/* You can increase MAX if you need a bigger graph.                          */
#define MAX 20

/* ------------------------------------------------------------------------- */
/* print_matrix: helper function to show an n x n matrix of ints.            */
/* We print each value (0 or 1) with a space so it is easy to read.          */
/* ------------------------------------------------------------------------- */
/* This function prints the matrix whose first element is matrix[0][0].      */
/* Parameter n tells us how many rows and columns to print.                  */
/* We use two nested loops: outer loop picks a row (i), inner loop prints    */
/* every column (j) in that row.                                             */
/* After printing one whole row we print a newline so the next row starts     */
/* on a new line.                                                            */
void print_matrix(int n, int matrix[MAX][MAX])
{
    /* Start a loop that goes through every row from 0 up to n-1. */
    int i; /* i will hold the current row index. */
    int j; /* j will hold the current column index. */

    /* Loop over all rows. */
    for (i = 0; i < n; i++) {
        /* For each row, loop over all columns. */
        for (j = 0; j < n; j++) {
            /* Print the value at row i, column j followed by a space. */
            printf("%d ", matrix[i][j]);
        }
        /* After finishing one row, move to the next line on the screen. */
        printf("\n");
    }
}

/* ------------------------------------------------------------------------- */
/* transitive_closure: compute reachability using Warshall algorithm.        */
/*                                                                           */
/* Parameters:                                                               */
/*   n  -> number of vertices in the graph (we assume 0..n-1).               */
/*   A  -> the original adjacency matrix (input).                            */
/*   T  -> the matrix we will fill with the transitive closure (output).     */
/*                                                                           */
/* Process overview (maps to your pseudo-steps):                             */
/*   Step 1: Initialize i, j, k (we do via loops).                           */
/*   Step 2-4: Copy A into T.                                                */
/*   Step 5-12: Triple nested loops updating T using OR/AND rule.            */
/* ------------------------------------------------------------------------- */
void transitive_closure(int n, int A[MAX][MAX], int T[MAX][MAX])
{
    /* Declare loop counters i, j, k. */
    int i;
    int j;
    int k;

    /* ---------------- Initialization / Copy (Steps 2-4 in pseudo) -------- */
    /* We copy every A[i][j] into T[i][j].                                   */
    /* This means T starts as the direct-edge matrix.                        */
    for (i = 0; i < n; i++) {            /* Loop over each row i. */
        for (j = 0; j < n; j++) {        /* Loop over each column j. */
            /* If there is a direct edge from i to j (A[i][j] == 1) we copy 1. */
            /* Otherwise we copy 0.                                            */
            T[i][j] = A[i][j];
        }
    }

    /* ---------------- Main Warshall Update (Steps 5-12) ------------------- */
    /* We consider each intermediate vertex k one at a time.                 */
    /* If i can reach k and k can reach j, then i can reach j (through k).    */
    for (k = 0; k < n; k++) {            /* Pick an intermediate vertex k. */
        for (i = 0; i < n; i++) {        /* For every start vertex i...    */
            for (j = 0; j < n; j++) {    /* ...check every end vertex j.   */
                /* Compute: T[i][j] = T[i][j] OR (T[i][k] AND T[k][j]). */
                /* We use logical operators || (OR) and && (AND).      */
                if (T[i][j] || (T[i][k] && T[k][j])) {
                    /* If condition is true, set reachability to 1. */
                    T[i][j] = 1;
                } else {
                    /* Otherwise, keep (or set) reachability to 0. */
                    T[i][j] = 0;
                }
            }
        }
    }
}

/* ------------------------------------------------------------------------- */
/* main: entry point of our program.                                         */
/* We ask the user for the number of vertices (n).                           */
/* We then read an n x n adjacency matrix A from standard input.             */
/* We call transitive_closure() to fill T.                                   */
/* Finally, we print both the original matrix and the closure matrix.        */
/* ------------------------------------------------------------------------- */
int main(void)
{
    /* i and j will be used for reading the matrix from the user. */
    int i;
    int j;

    /* n will hold the number of vertices in the graph. */
    int n;

    /* Declare the adjacency matrix A with MAX x MAX size. */
    /* We will only use the top-left n x n portion.         */
    int A[MAX][MAX];

    /* Declare the transitive closure matrix T. */
    int T[MAX][MAX];

    /* Ask the user to enter the number of vertices. */
    printf("Enter number of vertices (<= %d): ", MAX);

    /* Read n from the keyboard. */
    if (scanf("%d", &n) != 1) {
        /* If reading failed, print error and stop. */
        printf("Error: could not read number.\n");
        return 1; /* Return non-zero to show failure. */
    }

    /* Check that n is within our allowed range. */
    if (n < 1 || n > MAX) {
        /* Tell the user the number is out of range. */
        printf("Error: n must be between 1 and %d.\n", MAX);
        return 1; /* Stop program with error. */
    }

    /* Tell the user to input the adjacency matrix values. */
    printf("\nEnter the %d x %d adjacency matrix (0 or 1 values):\n", n, n);

    /* Loop over each row to read input values. */
    for (i = 0; i < n; i++) {
        /* Loop over each column in the current row. */
        for (j = 0; j < n; j++) {
            /* Read the next integer into A[i][j]. */
            if (scanf("%d", &A[i][j]) != 1) {
                /* If reading failed, print error and stop. */
                printf("Error: bad matrix input.\n");
                return 1; /* Stop program with error. */
            }
            /* Force any non-zero to become 1 so we keep clean 0/1 data. */
            A[i][j] = (A[i][j] != 0) ? 1 : 0;
        }
    }

    /* Call our function to compute the transitive closure. */
    transitive_closure(n, A, T);

    /* Print a blank line for readability. */
    printf("\nOriginal adjacency matrix (A):\n");

    /* Print the original matrix using our helper. */
    print_matrix(n, A);

    /* Print another blank line for readability. */
    printf("\nTransitive closure matrix (T):\n");

    /* Print the closure matrix. */
    print_matrix(n, T);

    /* Return 0 to show the program finished successfully. */
    return 0;
}

