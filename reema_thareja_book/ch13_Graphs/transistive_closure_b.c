/* Include the standard input/output header so we can use printf() and scanf(). */
#include <stdio.h>

/* Include the standard library header so we can use malloc() and free(). */
#include <stdlib.h>

/* Set a hard limit on how many graph nodes (vertices) we will allow. */
#define MAX_NODES 10

/* Define a structure to represent ONE neighbor in the adjacency list of a vertex. */
struct Node {
    /* This integer stores the neighbor's vertex number (0 to n-1). */
    int vertex;
    /* This pointer links to the NEXT neighbor in the list (NULL means end). */
    struct Node *next;
};

/* Tell the compiler that these three functions are defined later in the file. */
void createGraph(struct Node *Adj[], int no_of_nodes);
void displayGraph(struct Node *Adj[], int no_of_nodes);
void deleteGraph(struct Node *Adj[], int no_of_nodes);

/* The program starts running here. */
int main(void) {
    /* Declare an array of adjacency-list head pointers (one list per vertex). */
    struct Node *Adj[MAX_NODES];
    /* Variables to hold loop counter and number of vertices the user enters. */
    int i, no_of_nodes;

    /* Ask the user how many nodes (vertices) are in the graph. */
    printf("\nEnter the number of nodes in G (max %d): ", MAX_NODES);
    /* Read that number from the keyboard. */
    if (scanf("%d", &no_of_nodes) != 1) {
        /* If reading failed, print an error and stop the program. */
        fprintf(stderr, "Input error: expected an integer.\n");
        /* Return non-zero to show something went wrong. */
        return 1;
    }

    /* If the user asked for too many nodes, warn and stop. */
    if (no_of_nodes < 0 || no_of_nodes > MAX_NODES) {
        /* Print a clear error message. */
        fprintf(stderr, "Error: number of nodes must be between 0 and %d.\n", MAX_NODES);
        /* Stop the program with error code. */
        return 1;
    }

    /* Initialize every adjacency list head to NULL (no neighbors yet). */
    for (i = 0; i < no_of_nodes; i++) {
        /* Set the head of list i to empty (NULL). */
        Adj[i] = NULL;
    }

    /* Build (create) the graph by reading neighbors from the user. */
    createGraph(Adj, no_of_nodes);

    /* Print a blank line for neat spacing. */
    printf("\n");

    /* Show (display) the graph so the user can see the adjacency lists. */
    displayGraph(Adj, no_of_nodes);

    /* Free all memory we allocated for the graph's adjacency lists. */
    deleteGraph(Adj, no_of_nodes);

    /* Return 0 to the operating system to show the program ended normally. */
    return 0;
}

/* This function reads neighbor information from the user and builds adjacency lists. */
void createGraph(struct Node *Adj[], int no_of_nodes) {
    /* Pointer for each newly created node (neighbor). */
    struct Node *new_node;
    /* Pointer that will always point to the LAST node added in the current list. */
    struct Node *last;
    /* Loop counters for vertices and neighbors. */
    int i, j;
    /* Number of neighbors the current vertex has. */
    int n;
    /* Stores the neighbor vertex number read from the user. */
    int val;

    /* Loop over each vertex in the graph (0 to no_of_nodes-1). */
    for (i = 0; i < no_of_nodes; i++) {
        /* Start with no last node yet for this vertex's list. */
        last = NULL;

        /* Ask the user how many neighbors this vertex has. */
        printf("\nEnter the number of neighbours of %d: ", i);
        /* Read how many neighbors. */
        if (scanf("%d", &n) != 1) {
            /* If bad input, print error and skip building further neighbors. */
            fprintf(stderr, "Input error: expected an integer.\n");
            /* Skip to next vertex by continuing the for-loop. */
            continue;
        }

        /* Loop to read each neighbor for this vertex. */
        for (j = 1; j <= n; j++) {
            /* Ask for the j-th neighbor of vertex i. */
            printf("  Enter neighbour %d of %d: ", j, i);
            /* Read the neighbor vertex number. */
            if (scanf("%d", &val) != 1) {
                /* Report bad input and break out of the neighbor loop. */
                fprintf(stderr, "Input error: expected an integer.\n");
                /* Stop reading more neighbors for this vertex. */
                break;
            }

            /* Check that the neighbor value is within 0..no_of_nodes-1. */
            if (val < 0 || val >= no_of_nodes) {
                /* Warn if the neighbor number is invalid. */
                fprintf(stderr, "  Warning: %d is not a valid vertex. Skipping.\n", val);
                /* Skip adding this neighbor node and continue with next. */
                continue;
            }

            /* Allocate memory for the new neighbor node. */
            new_node = (struct Node *)malloc(sizeof(struct Node));
            /* Check if malloc failed (out of memory). */
            if (new_node == NULL) {
                /* Print an error and stop building this adjacency list. */
                fprintf(stderr, "  Error: out of memory while adding neighbour.\n");
                /* Break out because we can't continue safely. */
                break;
            }

            /* Store the neighbor's vertex number in the new node. */
            new_node->vertex = val;
            /* Since it is the new tail, its next pointer is NULL for now. */
            new_node->next = NULL;

            /* If this is the FIRST neighbor for vertex i, attach directly to head. */
            if (Adj[i] == NULL) {
                /* Head now points to the new node. */
                Adj[i] = new_node;
            }
            /* Otherwise, attach this new node after the current last node. */
            else {
                /* Link the old last node to the new node. */
                last->next = new_node;
            }

            /* Update last so it points to the new tail of the list. */
            last = new_node;
        }
    }
}

/* This function prints the adjacency list for each vertex in the graph. */
void displayGraph(struct Node *Adj[], int no_of_nodes) {
    /* Pointer used to walk through each vertex's neighbor list. */
    struct Node *ptr;
    /* Loop counter for vertices. */
    int i;

    /* Loop over each vertex in order. */
    for (i = 0; i < no_of_nodes; i++) {
        /* Start walking from the head of the i-th list. */
        ptr = Adj[i];

        /* Print a label for this vertex's neighbors. */
        printf("Neighbours of node %d:", i);

        /* Walk along the linked list until we hit NULL (end). */
        while (ptr != NULL) {
            /* Print the neighbor vertex number with a space in front for spacing. */
            printf(" %d", ptr->vertex);
            /* Move to the next neighbor in the list. */
            ptr = ptr->next;
        }

        /* Print a newline so the next vertex appears on a new line. */
        printf("\n");
    }
}

/* This function frees (deletes) all the nodes in every adjacency list. */
void deleteGraph(struct Node *Adj[], int no_of_nodes) {
    /* Loop counter for vertices. */
    int i;
    /* Pointer to walk the list. */
    struct Node *ptr;
    /* Temporary pointer used to free the current node safely. */
    struct Node *temp;

    /* Go through each vertex one by one. */
    for (i = 0; i < no_of_nodes; i++) {
        /* Start at the head of the i-th list. */
        ptr = Adj[i];

        /* Walk through the list and free each neighbor node. */
        while (ptr != NULL) {
            /* Remember the current node so we can free it. */
            temp = ptr;
            /* Move ptr ahead to the next node before freeing. */
            ptr = ptr->next;
            /* Give the memory for this node back to the system. */
            free(temp);
        }

        /* After freeing all nodes, set the list head to NULL to show it's empty. */
        Adj[i] = NULL;
    }
}

