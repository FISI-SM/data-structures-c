/* === Include standard input/output functions (printf, scanf). === */
#include <stdio.h>
/* === Include standard library for general utilities (exit). === */
#include <stdlib.h>
/* === Include limits for big numbers if needed. === */
#include <limits.h>

/* === Maximum number of vertices we will support. === */
#define MAX 10
/* === A large number we use to mean "no edge" (infinity). === */
#define INF 1000000000

/* === Global adjacency matrix to store input graph edge weights. === */
int adj[MAX][MAX];
/* === Global array to store MST edges: each row holds (u,v). === */
int tree[MAX][2];
/* === Global: number of vertices actually in the current graph. === */
int n = 0;

/* === Read number of nodes and its adjacency matrix from user. === */
void readmatrix(void);
/* === Run Prim's algorithm starting from 'src'; return MST cost. === */
int spanningtree(int src);
/* === Display edges collected in tree[][] and final cost. === */
void display(int cost);

/* === Program entry point. === */
int main(void)
{
    /* === Will hold the starting vertex for Prim's algorithm. === */
    int source;
    /* === Will hold the total cost returned by spanningtree(). === */
    int treecost;

    /* === Read graph size and adjacency matrix from the user. === */
    readmatrix();

    /* === Ask which vertex to start from (0..n-1). === */
    printf("\nEnter the Source (0 to %d): ", n - 1);
    /* === Read the chosen start vertex. === */
    if (scanf("%d", &source) != 1) {
        /* === Input failed; print error and quit. === */
        fprintf(stderr, "Input error.\n");
        return 1;
    }
    /* === Validate that source is within range. === */
    if (source < 0 || source >= n) {
        /* === Bad input; quit. === */
        fprintf(stderr, "Invalid source vertex.\n");
        return 1;
    }

    /* === Run Prim's algorithm from the chosen source. === */
    treecost = spanningtree(source);

    /* === Show the resulting MST edges and cost. === */
    display(treecost);

    /* === Normal exit. === */
    return 0;
}

/* === Read number of nodes and adjacency matrix from the user. === */
void readmatrix(void)
{
    /* === Loop counters. === */
    int i, j;
    /* === Temporary variable to read each weight. === */
    int w;

    /* === Ask for number of nodes. === */
    printf("\nEnter the number of nodes in the Graph (max %d): ", MAX);
    /* === Read n. === */
    if (scanf("%d", &n) != 1) {
        /* === Failed to read; abort. === */
        fprintf(stderr, "Input error.\n");
        exit(1);
    }
    /* === Validate range of n. === */
    if (n <= 0 || n > MAX) {
        /* === Invalid; abort. === */
        fprintf(stderr, "Invalid number of nodes.\n");
        exit(1);
    }

    /* === Prompt for adjacency matrix. === */
    printf("\nEnter the %d x %d adjacency (weight) matrix:\n", n, n);
    printf("(Use 0 for NO EDGE between DIFFERENT vertices. Diagonal may be 0.)\n");

    /* === Read each matrix entry row by row. === */
    for (i = 0; i < n; i++) {
        /* === Loop across columns. === */
        for (j = 0; j < n; j++) {
            /* === Read weight w for edge i->j. === */
            if (scanf("%d", &w) != 1) {
                /* === Bad input; abort. === */
                fprintf(stderr, "Input error while reading matrix.\n");
                exit(1);
            }
            /* === If i!=j and w==0, treat as NO EDGE by storing INF. === */
            if (i != j && w == 0) {
                adj[i][j] = INF;
            }
            /* === Otherwise store the given weight (can be 0 on diagonal). === */
            else {
                adj[i][j] = w;
            }
        }
    }
}

/* === Build a Minimum Spanning Tree using Prim's algorithm. === */
/* === Returns total MST cost; fills global tree[][] with edges. === */
int spanningtree(int src)
{
    /* === visited[v] is 1 once vertex v is in the MST. === */
    int visited[MAX];
    /* === d[v] stores the BEST (smallest) edge weight from MST to v. === */
    int d[MAX];
    /* === parent[v] remembers which MST vertex connects to v cheaply. === */
    int parent[MAX];
    /* === Loop counters. === */
    int i, j;
    /* === Track current min edge weight candidate. === */
    int min;
    /* === Vertex chosen this round. === */
    int u = -1;
    /* === Neighbor scan variable. === */
    int v;
    /* === Running total cost of MST. === */
    int cost = 0;
    /* === Count of edges stored in tree[][] (starts at 0). === */
    int k = 0;

    /* === Initialize arrays based on starting source vertex. === */
    for (i = 0; i < n; i++) {
        /* === Best known edge to i is weight from src->i initially. === */
        d[i] = adj[src][i];
        /* === None visited yet. === */
        visited[i] = 0;
        /* === Source is initial parent guess for all vertices. === */
        parent[i] = src;
    }

    /* === Mark source itself as in the MST. === */
    visited[src] = 1;
    /* === Source has no parent; mark with -1. === */
    parent[src] = -1;
    /* === Distance to add when we pick source is 0. === */
    d[src] = 0;

    /* === Repeat to pick n-1 additional vertices (MST has n-1 edges). === */
    for (i = 1; i < n; i++) {
        /* === Start with big min before scanning. === */
        min = INF;
        /* === Reset u to -1 in case no edge found (disconnected). === */
        u = -1;

        /* === Scan all vertices to find unvisited with smallest d[]. === */
        for (j = 0; j < n; j++) {
            /* === Only consider vertices not yet in MST. === */
            if (!visited[j] && d[j] < min) {
                /* === Found new best candidate. === */
                min = d[j];
                u = j;
            }
        }

        /* === If u stayed -1, graph is disconnected → MST incomplete. === */
        if (u == -1 || min == INF) {
            /* === Break early; we can't reach remaining vertices. === */
            printf("\nWarning: Graph is disconnected; MST incomplete.\n");
            break;
        }

        /* === Include vertex u in MST. === */
        visited[u] = 1;
        /* === Add connecting edge weight to total cost. === */
        cost += d[u];
        /* === Record the MST edge (parent[u] -> u) in tree[k]. === */
        tree[k][0] = parent[u];
        tree[k][1] = u;
        /* === Advance edge counter. === */
        k++;

        /* === Update best edges (d[]) for vertices still outside MST. === */
        for (v = 0; v < n; v++) {
            /* === If v not visited and edge u->v cheaper than current best... === */
            if (!visited[v] && adj[u][v] < d[v]) {
                /* === Update best cost to reach v. === */
                d[v] = adj[u][v];
                /* === Remember u as the parent that connects v cheaply. === */
                parent[v] = u;
            }
        }
    }

    /* === Return total MST cost (may be partial if disconnected). === */
    return cost;
}

/* === Print MST edges stored in tree[][] plus total cost. === */
void display(int cost)
{
    /* === Loop counter for edges. === */
    int i;

    /* === Print heading. === */
    printf("\nThe Edges of the Minimum Spanning Tree are:\n");

    /* === Print each stored edge: tree[i][0] -- tree[i][1]. === */
    for (i = 0; i < n - 1; i++) {
        /* === If the parent was -1 (source), skip printing bogus edge. === */
        if (tree[i][0] == -1) {
            /* === Skip the root edge line. === */
            continue;
        }
        /* === Print edge endpoints as numbers. === */
        printf("%d %d\n", tree[i][0], tree[i][1]);
    }

    /* === Print total MST cost. === */
    printf("\nThe Total cost of the Minimum Spanning Tree is: %d\n", cost);
}

