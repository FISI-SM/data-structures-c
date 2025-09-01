/* Include standard input and output functions like printf() and scanf(). */
#include <stdio.h>

/* Include standard library for general utilities (not strictly needed but good practice). */
#include <stdlib.h>

/* Include limits.h so we can use a large number like INT_MAX if we want. */
#include <limits.h>

/* Set the largest number of vertices we will allow in this simple program. */
#define MAX 20

/* Set a large number to stand for "no edge" (infinity for our purposes). */
#define INF 1000000000

/* Declare the function that will run Prim's algorithm and build the MST. */
void prim_mst(int cost[MAX][MAX], int n);

/* The program starts running here. */
int main(void)
{
    /* Declare the matrix that will hold all edge weights between vertices. */
    int cost[MAX][MAX];
    /* Variable to hold the number of vertices the user enters. */
    int n;
    /* Loop counters for reading the matrix from the user. */
    int i, j;
    /* Temporary variable to read each weight before storing. */
    int w;

    /* Ask the user how many vertices are in the graph. */
    printf("Enter number of vertices (max %d): ", MAX);
    /* Read that number from the keyboard. */
    if (scanf("%d", &n) != 1) {
        /* If input fails, print an error message. */
        fprintf(stderr, "Input error: expected an integer.\n");
        /* Stop the program with a nonzero error code. */
        return 1;
    }

    /* Check that the number of vertices is within the allowed range. */
    if (n <= 0 || n > MAX) {
        /* Tell the user the number they entered is not OK. */
        fprintf(stderr, "Error: number of vertices must be between 1 and %d.\n", MAX);
        /* Stop the program with a nonzero error code. */
        return 1;
    }

    /* Tell the user how to enter the edge weights. */
    printf("Enter the %d x %d weight matrix.\n", n, n);
    /* Explain that 0 (off‑diagonal) means no edge; diagonal is normally 0. */
    printf("(Use 0 for NO EDGE between DIFFERENT vertices.)\n");

    /* Loop over every row of the matrix. */
    for (i = 0; i < n; i++) {
        /* Loop over every column in this row. */
        for (j = 0; j < n; j++) {
            /* Read the weight for the edge from i to j. */
            if (scanf("%d", &w) != 1) {
                /* If the user did not type a number, report error. */
                fprintf(stderr, "Input error: expected an integer weight.\n");
                /* Stop the program. */
                return 1;
            }
            /* If i and j are different AND user typed 0, treat as NO EDGE. */
            if (i != j && w == 0) {
                /* Store INF so Prim's algorithm will ignore this edge. */
                cost[i][j] = INF;
            }
            /* Otherwise store the weight as given. */
            else {
                cost[i][j] = w;
            }
        }
    }

    /* Print a blank line to separate input from output. */
    printf("\n");

    /* Call Prim's algorithm function to build and print the MST. */
    prim_mst(cost, n);

    /* Return 0 to show the program ended normally. */
    return 0;
}

/* This function runs Prim's algorithm on the cost matrix and prints the MST. */
void prim_mst(int cost[MAX][MAX], int n)
{
    /* key[v] holds the MINIMUM edge weight that connects v to the growing MST. */
    int key[MAX];
    /* parent[v] stores the vertex that brings v into the MST with the min edge. */
    int parent[MAX];
    /* in_mst[v] is 1 if vertex v is already included in the MST, else 0. */
    int in_mst[MAX];
    /* Loop counters. */
    int i, j;
    /* Will hold the index of the next vertex we choose to add to the MST. */
    int u;
    /* Track total weight of the MST as we go. */
    int total_weight = 0;

    /* Initialize every key value to a very large number (infinity). */
    for (i = 0; i < n; i++) {
        /* Start with large cost so any real edge will be smaller. */
        key[i] = INF;
        /* At start, no vertex has a parent chosen yet. */
        parent[i] = -1;
        /* No vertex is inside the MST yet. */
        in_mst[i] = 0;
    }

    /* Choose vertex 0 as the starting point (you could choose any). */
    key[0] = 0;

    /* Repeat until we have added all vertices to the MST. */
    for (i = 0; i < n; i++) {
        /* Set u to -1 so we can find the vertex with the smallest key not in MST. */
        u = -1;
        /* Scan all vertices to find the smallest key among those not in MST. */
        for (j = 0; j < n; j++) {
            /* Check that vertex j is not yet in MST. */
            if (!in_mst[j]) {
                /* If u not chosen yet OR this key is smaller than current best... */
                if (u == -1 || key[j] < key[u]) {
                    /* Remember j as the new best choice. */
                    u = j;
                }
            }
        }

        /* Mark the chosen vertex u as now part of the MST. */
        in_mst[u] = 1;

        /* If u has a parent (not the starting vertex), add that edge's weight. */
        if (parent[u] != -1) {
            /* Add the weight of the edge parent[u] -> u to the total MST weight. */
            total_weight += cost[parent[u]][u];
        }

        /* Update key[] and parent[] values using edges out of the newly added u. */
        for (j = 0; j < n; j++) {
            /* If there is an edge u->j and j not yet in MST and cost is smaller... */
            if (!in_mst[j] && cost[u][j] < key[j]) {
                /* Update key so we remember this cheaper connection for j. */
                key[j] = cost[u][j];
                /* Record that j would join the MST via u. */
                parent[j] = u;
            }
        }
    }

    /* Print a heading so the user knows what follows. */
    printf("Edges in the Minimum Spanning Tree:\n");

    /* Loop through vertices 1..n-1 to print edges (vertex 0 has no parent). */
    for (i = 1; i < n; i++) {
        /* Print the parent and child as letters if small index, else numbers. */
        if (parent[i] >= 0 && parent[i] < 26 && i < 26) {
            /* Print output like A - B : 3 */
            printf("%c - %c : %d\n", 'A' + parent[i], 'A' + i, cost[parent[i]][i]);
        } else {
            /* Fallback printing with numbers if outside letter range. */
            printf("%d - %d : %d\n", parent[i], i, cost[parent[i]][i]);
        }
    }

    /* Finally print the total cost of the MST. */
    printf("Total MST weight = %d\n", total_weight);
}

