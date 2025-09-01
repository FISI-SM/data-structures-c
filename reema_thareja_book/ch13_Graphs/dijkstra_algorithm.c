// Include the standard input-output library for printf and scanf
#include <stdio.h>

// Define a constant MAX which is the maximum number of vertices
#define MAX 10

// Define a constant INF for representing infinity (a very large number)
#define INF 9999

// Function to print the shortest path from the source to a given node
void print_path(int parent[MAX], int v) {
    // If the current node has no parent, we are at the start node
    if (parent[v] == -1) {
        printf("%c", 'A' + v); // Print the start node as a letter (A, B, C...)
        return;
    }
    // Recursively print the path to the parent of the current node
    print_path(parent, parent[v]);
    // Print an arrow and then the current node as a letter
    printf(" -> %c", 'A' + v);
}

// Function that implements Dijkstra's algorithm
void dijkstra(int graph[MAX][MAX], int n, int src) {
    // dist[] stores the shortest distance from src to every node
    int dist[MAX];
    // visited[] keeps track of which nodes are finalized
    int visited[MAX];
    // parent[] stores the parent of each node in the shortest path
    int parent[MAX];
    int count, i, j, u, min;

    // Initialize distances, visited, and parent arrays
    for (i = 0; i < n; i++) {
        dist[i] = graph[src][i];   // Initially, distance is the weight from src
        visited[i] = 0;            // No node is visited yet
        if (graph[src][i] != INF && i != src)
            parent[i] = src;       // Parent of directly connected nodes is src
        else
            parent[i] = -1;        // Otherwise, parent is unknown
    }

    // Distance from source to itself is always 0
    dist[src] = 0;
    // Mark the source as visited
    visited[src] = 1;

    // Repeat until we have found shortest paths for all nodes
    for (count = 1; count < n - 1; count++) {
        min = INF;
        u = -1;

        // Find the unvisited node with the smallest distance
        for (i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        // If there is no reachable unvisited node, stop
        if (u == -1)
            break;

        // Mark this node as visited
        visited[u] = 1;

        // Update distances of all neighbors of u
        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[u][j] != INF) {
                // If going through u gives a shorter path to j
                if (dist[u] + graph[u][j] < dist[j]) {
                    dist[j] = dist[u] + graph[u][j]; // Update distance
                    parent[j] = u;                   // Update parent
                }
            }
        }
    }

    // Print the results
    printf("\nShortest paths from source %c:\n", 'A' + src);
    for (i = 0; i < n; i++) {
        if (dist[i] == INF) {
            // If the node is unreachable
            printf("To %c: unreachable\n", 'A' + i);
        } else {
            // Print the total distance
            printf("To %c (distance %d): ", 'A' + i, dist[i]);
            // Print the path
            print_path(parent, i);
            printf("\n");
        }
    }
}

// Main function
int main() {
    int graph[MAX][MAX];  // The adjacency matrix of the graph
    int n, i, j, src;

    // Ask user for the number of vertices
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    // Read the adjacency matrix
    printf("Enter the adjacency matrix (use %d for INF):\n", INF);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Ask for the source node
    printf("Enter source vertex (0 = A, 1 = B, etc.): ");
    scanf("%d", &src);

    // Run Dijkstra's algorithm
    dijkstra(graph, n, src);

    return 0; // End of program
}

