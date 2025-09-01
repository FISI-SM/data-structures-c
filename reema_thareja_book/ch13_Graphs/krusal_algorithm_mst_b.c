/* Include standard input and output functions like printf() and scanf(). */
#include <stdio.h>

/* Include standard library for memory (malloc, free) and qsort(). */
#include <stdlib.h>

/* Structure to hold one edge in the graph. */
struct Edge {
    /* One endpoint vertex number (0 to V-1). */
    int u;
    /* The other endpoint vertex number (0 to V-1). */
    int v;
    /* Weight (cost) of this edge. */
    int w;
};

/* Structure used for union-find (disjoint set). */
struct Subset {
    /* Parent index in the union-find tree. */
    int parent;
    /* Rank used to keep the union-find tree shallow. */
    int rank;
};

/* Forward declare: compare function for qsort() to sort edges by weight. */
int compareEdges(const void *a, const void *b);

/* Forward declare: find() returns the representative (root) of a set. */
int find(struct Subset subsets[], int i);

/* Forward declare: Union() merges two sets in union-find. */
void Union(struct Subset subsets[], int x, int y);

/* The program starts running here. */
int main(void)
{
    /* Number of vertices in the graph. */
    int V;
    /* Number of edges in the graph. */
    int E;
    /* Loop counter for reading edges. */
    int i;
    /* Total MST cost accumulator. */
    int totalCost = 0;
    /* Count of edges actually chosen for the MST. */
    int mstCount = 0;
    /* Array that will hold the MST edges we pick (size V-1 max). */
    struct Edge *mstEdges = NULL;
    /* Array of all edges we read from the user. */
    struct Edge *edges = NULL;
    /* Array of union-find subsets (one per vertex). */
    struct Subset *subsets = NULL;

    /* Ask the user how many vertices are in the graph. */
    printf("Enter number of vertices: ");
    /* Read the vertex count. */
    if (scanf("%d", &V) != 1) {
        /* If input fails, print error and stop. */
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    /* Ask the user how many edges are in the graph. */
    printf("Enter number of edges: ");
    /* Read the edge count. */
    if (scanf("%d", &E) != 1) {
        /* Error reading edge count. */
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    /* Allocate memory to store all edges (size E). */
    edges = (struct Edge *)malloc(E * sizeof(struct Edge));
    /* Check allocation success. */
    if (edges == NULL) {
        /* Allocation failed; exit. */
        fprintf(stderr, "Out of memory (edges).\n");
        return 1;
    }

    /* Allocate memory to store MST edges (we need at most V-1). */
    mstEdges = (struct Edge *)malloc((V - 1) * sizeof(struct Edge));
    /* Check allocation success. */
    if (mstEdges == NULL) {
        /* Allocation failed; clean up and exit. */
        fprintf(stderr, "Out of memory (mstEdges).\n");
        free(edges);
        return 1;
    }

    /* Allocate union-find subsets (one per vertex). */
    subsets = (struct Subset *)malloc(V * sizeof(struct Subset));
    /* Check allocation success. */
    if (subsets == NULL) {
        /* Allocation failed; clean up and exit. */
        fprintf(stderr, "Out of memory (subsets).\n");
        free(edges);
        free(mstEdges);
        return 1;
    }

    /* Tell the user how to enter each edge. */
    printf("Enter each edge as: u v w  (vertices 0..%d, weight w)\n", V - 1);

    /* Loop to read all E edges. */
    for (i = 0; i < E; i++) {
        /* Read u, v, w for the i-th edge. */
        if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w) != 3) {
            /* Bad input; clean up and exit. */
            fprintf(stderr, "Input error while reading edges.\n");
            free(edges);
            free(mstEdges);
            free(subsets);
            return 1;
        }
        /* Optional: you could validate u,v range here; skipping for brevity. */
    }

    /* Sort all edges in nondecreasing order of weight using qsort(). */
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    /* Initialize union-find sets: each vertex is its own parent at start. */
    for (i = 0; i < V; i++) {
        /* Parent of i is itself. */
        subsets[i].parent = i;
        /* Rank starts at 0. */
        subsets[i].rank = 0;
    }

    /* Loop through edges in sorted order; stop when we have V-1 MST edges. */
    for (i = 0; i < E && mstCount < V - 1; i++) {
        /* Find the set representative for this edge's u endpoint. */
        int set_u = find(subsets, edges[i].u);
        /* Find the set representative for this edge's v endpoint. */
        int set_v = find(subsets, edges[i].v);

        /* If they are in different sets, adding this edge will not form a cycle. */
        if (set_u != set_v) {
            /* Store this edge in our MST edge list. */
            mstEdges[mstCount] = edges[i];
            /* Add this edge's weight to the running MST cost. */
            totalCost += edges[i].w;
            /* Count this edge toward the MST total. */
            mstCount++;
            /* Union the two sets so future edges know they are connected. */
            Union(subsets, set_u, set_v);
        }
    }

    /* Print a blank line before listing the MST edges. */
    printf("\nEdges in the Minimum Spanning Tree:\n");

    /* Loop to print each MST edge we selected. */
    for (i = 0; i < mstCount; i++) {
        /* Print endpoints and weight for MST edge i. */
        printf("%d -- %d  (weight %d)\n",
               mstEdges[i].u, mstEdges[i].v, mstEdges[i].w);
    }

    /* Print the total MST cost. */
    printf("Total cost of Minimum Spanning Tree: %d\n", totalCost);

    /* If we picked fewer than V-1 edges, the graph was disconnected. */
    if (mstCount < V - 1) {
        /* Warn the user that a full MST was not possible. */
        printf("Warning: Graph is disconnected; MST incomplete.\n");
    }

    /* Free memory for edges array. */
    free(edges);
    /* Free memory for MST edges array. */
    free(mstEdges);
    /* Free memory for subset array. */
    free(subsets);

    /* Return success from main(). */
    return 0;
}

/* Compare two edges by weight for qsort(); must return negative, zero, or positive. */
int compareEdges(const void *a, const void *b)
{
    /* Cast the generic pointers back to Edge pointers. */
    const struct Edge *e1 = (const struct Edge *)a;
    /* Cast the second pointer. */
    const struct Edge *e2 = (const struct Edge *)b;
    /* Return difference in weights (ascending order). */
    return e1->w - e2->w;
}

/* Find the set representative for element i (with path compression). */
int find(struct Subset subsets[], int i)
{
    /* If i is not its own parent, recursively find its top parent. */
    if (subsets[i].parent != i) {
        /* Compress the path by pointing i directly to the root. */
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    /* Return the ultimate parent (root). */
    return subsets[i].parent;
}

/* Union two sets x and y using union by rank. */
void Union(struct Subset subsets[], int x, int y)
{
    /* Find roots for x and y. */
    int rootX = find(subsets, x);
    /* Find root for y. */
    int rootY = find(subsets, y);

    /* If they are already in the same set, do nothing. */
    if (rootX == rootY) {
        /* Early return: no merge needed. */
        return;
    }

    /* If rank of rootX is less than rank of rootY, attach X under Y. */
    if (subsets[rootX].rank < subsets[rootY].rank) {
        /* Make rootY the parent of rootX. */
        subsets[rootX].parent = rootY;
    }
    /* Else if rank of rootX greater, attach Y under X. */
    else if (subsets[rootX].rank > subsets[rootY].rank) {
        /* Make rootX the parent of rootY. */
        subsets[rootY].parent = rootX;
    }
    /* Else ranks equal: make one root the parent and bump rank. */
    else {
        /* Attach rootY under rootX. */
        subsets[rootY].parent = rootX;
        /* Increase rank of rootX because its tree just got taller. */
        subsets[rootX].rank++;
    }
}

