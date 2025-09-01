// Include standard input/output functions like printf() and scanf().
#include <stdio.h>

// Include standard library functions like malloc() (not used here) and exit codes.
#include <stdlib.h>

// Define the maximum number of vertices our program will handle.
#define MAX 10

// Forward declare the BFS function so main() can call it before its full definition appears.
void breadth_first_search(int adj[][MAX], int visited[], int n, int start);

// The main() function is where the program starts running.
int main(void)
{
    // This array tracks whether each vertex was visited (0 = no, 1 = yes).
    int visited[MAX] = {0};
    // This 2D array holds the adjacency matrix (1 = edge, 0 = no edge).
    int adj[MAX][MAX];
    // Loop counters for reading the matrix.
    int i, j;
    // Number of vertices in the graph that the user will enter.
    int n;
    // The starting vertex for BFS (0-based).
    int start;

    // Ask the user how many vertices are in the graph.
    printf("Enter number of vertices (max %d): ", MAX);
    // Read the number of vertices from the keyboard.
    if (scanf("%d", &n) != 1) {
        // If input fails, print an error.
        fprintf(stderr, "Input error: expected an integer.\n");
        // Exit with error code 1.
        return 1;
    }

    // Check that the entered number is within our allowed range.
    if (n < 0 || n > MAX) {
        // Warn if the number is invalid.
        fprintf(stderr, "Error: number of vertices must be between 0 and %d.\n", MAX);
        // Exit with error code 1.
        return 1;
    }

    // Tell the user to enter the adjacency matrix values row by row.
    printf("Enter the %d x %d adjacency matrix (0/1 values):\n", n, n);
    // Outer loop: go through each row i.
    for (i = 0; i < n; i++) {
        // Inner loop: go through each column j in row i.
        for (j = 0; j < n; j++) {
            // Read the 0 or 1 value for adj[i][j].
            if (scanf("%d", &adj[i][j]) != 1) {
                // If input fails, print error and exit.
                fprintf(stderr, "Input error: expected an integer.\n");
                return 1;
            }
        }
    }

    // Ask the user which vertex to start BFS from (0-based index).
    printf("Enter start vertex (0 to %d): ", n - 1);
    // Read the start vertex.
    if (scanf("%d", &start) != 1) {
        // Handle bad input.
        fprintf(stderr, "Input error: expected an integer.\n");
        return 1;
    }

    // Check start vertex is valid.
    if (start < 0 || start >= n) {
        // Warn and exit if user gave an invalid start vertex.
        fprintf(stderr, "Error: start vertex must be between 0 and %d.\n", n - 1);
        return 1;
    }

    // Print a header to show traversal output will follow.
    printf("\nBFS visit order:\n");

    // Call the BFS function to traverse the graph from 'start'.
    breadth_first_search(adj, visited, n, start);

    // Print a newline so the shell prompt appears on a new line after BFS output.
    printf("\n");

    // Return 0 to show the program finished normally.
    return 0;
}

// This function performs Breadth-First Search starting at 'start'.
void breadth_first_search(int adj[][MAX], int visited[], int n, int start)
{
    // This array acts as our queue to store vertices to visit next.
    int queue[MAX];
    // 'front' points to the next element to remove from the queue.
    int front = 0;
    // 'rear' points to the position where we will add the next element.
    int rear = 0;
    // Loop counter for scanning neighbors.
    int i;
    // This variable will hold the vertex currently being processed.
    int v;

    // Put the starting vertex in the queue (enqueue).
    queue[rear++] = start;
    // Mark the starting vertex as visited so we do not add it again.
    visited[start] = 1;

    // Keep going while there are still vertices waiting in the queue.
    while (front < rear) {
        // Remove the next vertex from the queue (dequeue).
        v = queue[front++];

        // If v is between 0 and 25, print a letter A..Z to make it friendly.
        if (v >= 0 && v < 26) {
            // Print the letter name for this vertex.
            printf("%c ", 'A' + v);
        } else {
            // Otherwise just print the number.
            printf("%d ", v);
        }

        // Scan across row v of the adjacency matrix to find neighbors.
        for (i = 0; i < n; i++) {
            // If there is an edge from v to i AND i has not been visited yet...
            if (adj[v][i] == 1 && visited[i] == 0) {
                // Add i to the queue so we visit it later.
                queue[rear++] = i;
                // Mark i visited immediately so we do not enqueue it again.
                visited[i] = 1;
            }
        }
    }
}

