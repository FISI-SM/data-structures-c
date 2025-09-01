/***************************************************************
 * Priority Queue (Binary Heap) - Min or Max Mode
 * -------------------------------------------------------------
 * Features:
 *   - Choose MIN-HEAP or MAX-HEAP at startup.
 *   - Enqueue (value, priority).
 *   - Peek (inspect top element without removing).
 *   - Dequeue (remove top element).
 *   - Dynamic array growth (automatic capacity doubling).
 *   - Flat array print (internal layout).
 *   - Simple tree-level print (each heap level on its own line).
 *
 * Commenting Style:
 *   - ALGORITHM block above every function.
 *   - A separate beginner-friendly comment above EVERY SINGLE line
 *     of executable code (including braces and declarations).
 ***************************************************************/

 /* Include standard I/O header for printf and scanf */
#include <stdio.h>
 /* Include standard library header for malloc, realloc, free, exit */
#include <stdlib.h>
 /* Include stdbool so we can use bool, true, and false */
#include <stdbool.h>

/* ================================================================
   DATA STRUCTURES
   ------------------------------------------------
   PQNode:
     - Holds a user value and an associated priority.
   PriorityQueue:
     - Dynamic array of PQNode (binary heap).
     - size: number of items stored.
     - capacity: allocated slots.
     - is_min: if true -> min-heap (smaller priority at top),
               if false -> max-heap (larger priority at top).
   ================================================================ */

 /* Define a structure to represent one priority queue entry */
typedef struct {
    /* Store the user-supplied value (can be any int meaning) */
    int value;
    /* Store the priority of this value (ordering depends on heap mode) */
    int priority;
} PQNode;

 /* Define the structure representing the priority queue (heap) */
typedef struct {
    /* Pointer to dynamic array holding heap nodes */
    PQNode *data;
    /* Current number of valid elements in the heap */
    int size;
    /* Allocated capacity (length) of the 'data' array */
    int capacity;
    /* Flag: true means we behave as min-heap, false as max-heap */
    bool is_min;
} PriorityQueue;

/* ================================================================
   FUNCTION: pq_create
   PURPOSE:
     Create a priority queue with a starting capacity and mode.
   ALGORITHM:
     1. If requested capacity <= 0 use default (16).
     2. Allocate PriorityQueue struct.
     3. On failure return NULL.
     4. Allocate data array with given capacity.
     5. On failure free struct and return NULL.
     6. Initialize size=0, set capacity and is_min flag.
     7. Return pointer to initialized queue.
   ================================================================ */
 /* Create a new priority queue (min or max) with initial capacity */
PriorityQueue *pq_create(int capacity, bool is_min) {
    /* Check if user passed a non-positive capacity and replace with default */
    if (capacity <= 0) capacity = 16;
    /* Allocate memory for the PriorityQueue structure */
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    /* Check if the structure allocation failed */
    if (!pq) {
        /* Inform the user about allocation failure */
        printf("Memory allocation failed for PQ structure.\n");
        /* Return NULL to indicate creation failure */
        return NULL;
    }
    /* Allocate memory for the dynamic array of PQNode elements */
    pq->data = (PQNode *)malloc(sizeof(PQNode) * capacity);
    /* Check if allocation for the data array failed */
    if (!pq->data) {
        /* Inform the user about the data allocation failure */
        printf("Memory allocation failed for PQ data array.\n");
        /* Free previously allocated structure to avoid memory leak */
        free(pq);
        /* Return NULL to indicate overall failure */
        return NULL;
    }
    /* Initialize the current number of elements to zero */
    pq->size = 0;
    /* Store the capacity inside the structure */
    pq->capacity = capacity;
    /* Store whether this heap will behave as a min-heap or max-heap */
    pq->is_min = is_min;
    /* Return the pointer to the fully initialized priority queue */
    return pq;
}

/* ================================================================
   FUNCTION: pq_free
   PURPOSE:
     Free all memory used by the priority queue.
   ALGORITHM:
     1. If pq == NULL do nothing.
     2. Free data array.
     3. Free struct.
   ================================================================ */
 /* Release all heap-allocated memory for the priority queue */
void pq_free(PriorityQueue *pq) {
    /* Immediately return if pq is NULL (nothing to free) */
    if (!pq) return;
    /* Free the dynamic array of PQNode elements */
    free(pq->data);
    /* Free the PriorityQueue structure itself */
    free(pq);
}

/* ================================================================
   FUNCTION: pq_swap
   PURPOSE:
     Swap two PQNode elements in-place.
   ALGORITHM:
     1. Store first in temp.
     2. Copy second into first slot.
     3. Copy temp into second slot.
   ================================================================ */
 /* Swap two PQNode values pointed to by a and b */
void pq_swap(PQNode *a, PQNode *b) {
    /* Store the contents of *a in a temporary variable */
    PQNode temp = *a;
    /* Copy the contents of *b into location *a */
    *a = *b;
    /* Copy the original *a (temp) into location *b */
    *b = temp;
}

/* ================================================================
   FUNCTION: pq_ensure_capacity
   PURPOSE:
     Grow the underlying array when full.
   ALGORITHM:
     1. If size < capacity -> return.
     2. Else capacity *= 2.
     3. Realloc data array.
     4. If realloc fails -> print error and exit.
     5. Assign new pointer and updated capacity back to queue.
   ================================================================ */
 /* Make sure there is space for the next insertion (grow if needed) */
void pq_ensure_capacity(PriorityQueue *pq) {
    /* If current size is still below capacity, nothing to do */
    if (pq->size < pq->capacity) return;
    /* Double the capacity to amortize reallocation cost */
    pq->capacity *= 2;
    /* Attempt to reallocate the underlying data array */
    PQNode *new_data = (PQNode *)realloc(pq->data, pq->capacity * sizeof(PQNode));
    /* Check if reallocation failed (out of memory) */
    if (!new_data) {
        /* Inform user about critical memory error */
        printf("Failed to resize priority queue.\n");
        /* Exit the program since continuing is unsafe */
        exit(EXIT_FAILURE);
    }
    /* Update the data pointer to the newly reallocated memory */
    pq->data = new_data;
}

/* ================================================================
   FUNCTION: pq_better
   PURPOSE:
     Determine if priority 'a' should be above priority 'b' in heap.
   ALGORITHM:
     1. If is_min is true -> return (a < b).
     2. Else (max-heap) -> return (a > b).
   ================================================================ */
 /* Return true if priority 'a' outranks priority 'b' given heap mode */
bool pq_better(PriorityQueue *pq, int a, int b) {
    /* If this is a min-heap we prefer smaller numerical priorities */
    if (pq->is_min) {
        /* Return true if a is less than b (higher priority in min-heap) */
        return a < b;
    } else {
        /* Otherwise this is a max-heap: return true if a is greater than b */
        return a > b;
    }
}

/* ================================================================
   FUNCTION: pq_heapify_up
   PURPOSE:
     Restore heap property from a newly inserted node upward.
   ALGORITHM:
     1. Set i = inserted index.
     2. While i > 0:
         a. parent = (i - 1)/2.
         b. If child better than parent -> swap & i = parent.
         c. Else stop.
   ================================================================ */
 /* Bubble the element at 'index' upward until heap order holds */
void pq_heapify_up(PriorityQueue *pq, int index) {
    /* Keep looping while we are not at the root */
    while (index > 0) {
        /* Compute this node's parent index */
        int parent = (index - 1) / 2;
        /* Check if current node has better priority than parent */
        if (pq_better(pq, pq->data[index].priority, pq->data[parent].priority)) {
            /* Swap child and parent to move the better node up */
            pq_swap(&pq->data[index], &pq->data[parent]);
            /* Update index to parent's index to continue bubbling */
            index = parent;
        } else {
            /* If parent is already better, we stop the upward adjustment */
            break;
        }
    }
}

/* ================================================================
   FUNCTION: pq_heapify_down
   PURPOSE:
     Restore heap property from a displaced root downward.
   ALGORITHM:
     1. Set i = starting index.
     2. Loop:
         a. left = 2*i+1, right = 2*i+2.
         b. If no left -> stop.
         c. pick best child = left or right depending on better priority.
         d. If child better than current -> swap and i = child.
         e. Else stop.
   ================================================================ */
 /* Push the element at 'index' downward until heap order is satisfied */
void pq_heapify_down(PriorityQueue *pq, int index) {
    /* Enter loop to move node down as needed */
    while (1) {
        /* Compute left child index */
        int left = 2 * index + 1;
        /* Compute right child index */
        int right = 2 * index + 2;
        /* If left child does not exist, we are at a leaf -> stop */
        if (left >= pq->size) break;
        /* Assume best child is the left child initially */
        int best = left;
        /* If right child exists, compare right with current 'best' child */
        if (right < pq->size &&
            pq_better(pq, pq->data[right].priority, pq->data[best].priority)) {
            /* Set best to right child if it outranks left */
            best = right;
        }
        /* Check if the best child outranks the current node */
        if (pq_better(pq, pq->data[best].priority, pq->data[index].priority)) {
            /* Swap current node with the better child */
            pq_swap(&pq->data[index], &pq->data[best]);
            /* Move index down to the child's former position */
            index = best;
        } else {
            /* Heap property satisfied -> stop loop */
            break;
        }
    }
}

/* ================================================================
   FUNCTION: pq_enqueue
   PURPOSE:
     Insert a new (value, priority) pair into the heap.
   ALGORITHM:
     1. Ensure capacity.
     2. Place node at end (index = size).
     3. size++.
     4. Heapify up from that index.
   ================================================================ */
 /* Insert a new element with its priority into the priority queue */
void pq_enqueue(PriorityQueue *pq, int value, int priority) {
    /* Make sure there is room for one more element */
    pq_ensure_capacity(pq);
    /* Place the new value at the end of the array */
    pq->data[pq->size].value = value;
    /* Store the new element's priority at the same position */
    pq->data[pq->size].priority = priority;
    /* Increase the size to include the newly inserted element */
    pq->size++;
    /* Restore heap ordering by bubbling the new element upward */
    pq_heapify_up(pq, pq->size - 1);
}

/* ================================================================
   FUNCTION: pq_peek
   PURPOSE:
     View the top value without removing it.
   ALGORITHM:
     1. If size == 0 -> return false.
     2. Else *out = data[0].value; return true.
   ================================================================ */
 /* Retrieve the top element's value without removing it */
bool pq_peek(PriorityQueue *pq, int *out_value) {
    /* If queue is empty we cannot peek */
    if (pq->size == 0) return false;
    /* Assign the root value to the output variable */
    *out_value = pq->data[0].value;
    /* Indicate success */
    return true;
}

/* ================================================================
   FUNCTION: pq_dequeue
   PURPOSE:
     Remove and return the top element.
   ALGORITHM:
     1. If empty -> return false.
     2. Save root value for output.
     3. Move last element to index 0.
     4. size--.
     5. Heapify down from root (if size > 0).
     6. Return true.
   ================================================================ */
 /* Remove the top-priority element from the heap (if any) */
bool pq_dequeue(PriorityQueue *pq, int *out_value) {
    /* If heap is empty we cannot dequeue anything */
    if (pq->size == 0) return false;
    /* Store the root node's value in out_value for the caller */
    *out_value = pq->data[0].value;
    /* Move the last element into the root position */
    pq->data[0] = pq->data[pq->size - 1];
    /* Decrement the size to discard the moved element's old slot */
    pq->size--;
    /* If we still have elements, fix ordering by heapifying down */
    if (pq->size > 0) pq_heapify_down(pq, 0);
    /* Indicate that the dequeue succeeded */
    return true;
}

/* ================================================================
   FUNCTION: pq_print_array
   PURPOSE:
     Print the internal array (level-order) showing (value,priority).
   ALGORITHM:
     1. Loop i=0..size-1 and print pair.
   ================================================================ */
 /* Print the heap's internal array for debugging/inspection */
void pq_print_array(PriorityQueue *pq) {
    /* Print a label to describe the output */
    printf("PQ array: ");
    /* Loop through each element in the heap array */
    for (int i = 0; i < pq->size; i++) {
        /* Print a tuple with value and priority */
        printf("(%d,p=%d) ", pq->data[i].value, pq->data[i].priority);
    }
    /* Print a newline after finishing the array */
    printf("\n");
}

/* ================================================================
   FUNCTION: pq_print_tree
   PURPOSE:
     Print each level of the heap on its own line (simple visualization).
   ALGORITHM:
     1. Track current level size (1,2,4,...).
     2. Print nodes sequentially.
     3. When printed count == expected count -> newline, advance level.
   ================================================================ */
 /* Print the heap in a simple tree-style layout (levels) */
void pq_print_tree(PriorityQueue *pq) {
    /* Start at level 0 (root level) */
    int level = 0;
    /* Number of nodes expected in the current level (2^level) */
    int count = 1;
    /* Counter for how many nodes printed so far in this level */
    int printed = 0;
    /* Print a label heading for the tree output */
    printf("Heap Tree:\n");
    /* Iterate over all elements in level-order (array order) */
    for (int i = 0; i < pq->size; i++) {
        /* Print current node's (value, priority) pair */
        printf("(%d,p=%d) ", pq->data[i].value, pq->data[i].priority);
        /* Increment how many we've printed on this line */
        printed++;
        /* If we've printed the entire level's expected nodes */
        if (printed == count) {
            /* Output a newline to start the next level visually */
            printf("\n");
            /* Move to the next level */
            level++;
            /* Compute the next level's expected node count (2^level) */
            count = 1 << level;
            /* Reset printed counter for the new level */
            printed = 0;
        }
    }
    /* Print a final newline to finish formatting cleanly */
    printf("\n");
}

/* ================================================================
   FUNCTION: interactive_menu
   PURPOSE:
     Allow user to interact with the priority queue (insert, peek, etc.).
   ALGORITHM:
     1. Ask user for heap mode (min or max).
     2. Create queue with chosen mode.
     3. Loop:
        a. Show menu.
        b. Read choice.
        c. Execute corresponding action.
        d. On Quit -> break loop.
     4. Free queue before exiting.
   ================================================================ */
 /* Provide an interactive menu for using the priority queue */
void interactive_menu(void) {
    /* Declare an integer to store the user's heap mode choice */
    int mode_choice;
    /* Prompt user to select min-heap (1) or max-heap (2) */
    printf("Choose heap mode: 1 = MIN-heap, 2 = MAX-heap: ");
    /* Attempt to read the mode choice from input */
    if (scanf("%d", &mode_choice) != 1) {
        /* If reading fails, clear invalid input characters */
        while (getchar() != '\n');
        /* Default to min-heap when input is invalid */
        mode_choice = 1;
    }
    /* Determine if this should be a min-heap based on user entry */
    bool is_min = (mode_choice != 2);
    /* Create a priority queue with initial capacity 16 and chosen mode */
    PriorityQueue *pq = pq_create(16, is_min);
    /* Check if creation failed (null pointer) */
    if (!pq) {
        /* Report failure and return early */
        printf("Failed to create priority queue.\n");
        /* Return because we cannot proceed without a queue */
        return;
    }
    /* Inform user of the mode selected */
    printf("Created a %s-heap priority queue.\n", pq->is_min ? "MIN" : "MAX");
    /* Declare variable to hold the user's menu selection each loop */
    int choice;
    /* Start an infinite loop to repeatedly show the menu */
    while (1) {
        /* Print a blank line for readability */
        printf("\n");
        /* Print a menu heading */
        printf("=== Priority Queue Menu ===\n");
        /* Show option 1 for enqueue */
        printf("1. Enqueue (value, priority)\n");
        /* Show option 2 for peek (view top element) */
        printf("2. Peek (view top value)\n");
        /* Show option 3 for dequeue (remove top element) */
        printf("3. Dequeue (remove top value)\n");
        /* Show option 4 for printing array representation */
        printf("4. Print internal array\n");
        /* Show option 5 for printing simple tree layout */
        printf("5. Print tree levels\n");
        /* Show option 6 for quitting the program */
        printf("6. Quit\n");
        /* Prompt for user input choice */
        printf("Enter choice: ");
        /* Attempt to read the integer choice */
        if (scanf("%d", &choice) != 1) {
            /* If input invalid, clear characters until newline */
            while (getchar() != '\n');
            /* Continue loop to re-display menu */
            continue;
        }
        /* Check if user chose to Enqueue */
        if (choice == 1) {
            /* Declare variable to store new value */
            int value;
            /* Declare variable to store new priority */
            int priority;
            /* Prompt for the value to insert */
            printf("Enter value: ");
            /* Read the value */
            if (scanf("%d", &value) != 1) {
                /* If invalid input, clear and report */
                while (getchar() != '\n');
                printf("Invalid value input.\n");
                continue;
            }
            /* Prompt for the priority */
            printf("Enter priority: ");
            /* Read the priority */
            if (scanf("%d", &priority) != 1) {
                /* If invalid input, clear and report */
                while (getchar() != '\n');
                printf("Invalid priority input.\n");
                continue;
            }
            /* Insert the (value, priority) pair */
            pq_enqueue(pq, value, priority);
            /* Confirm insertion to user */
            printf("Inserted (%d, p=%d).\n", value, priority);
        }
        /* Check if user chose to Peek */
        else if (choice == 2) {
            /* Variable to receive top element's value */
            int top_value;
            /* Attempt to peek at the top */
            if (pq_peek(pq, &top_value)) {
                /* If success, print the top value */
                printf("Top value: %d\n", top_value);
            } else {
                /* If heap empty, inform the user */
                printf("Priority queue is empty.\n");
            }
        }
        /* Check if user chose to Dequeue */
        else if (choice == 3) {
            /* Variable to receive the dequeued value */
            int removed;
            /* Attempt to remove the top element */
            if (pq_dequeue(pq, &removed)) {
                /* Print the removed value */
                printf("Dequeued value: %d\n", removed);
            } else {
                /* Inform user the queue was empty */
                printf("Priority queue is empty.\n");
            }
        }
        /* Check if user wants to print the internal array */
        else if (choice == 4) {
            /* Call function that prints the flat array */
            pq_print_array(pq);
        }
        /* Check if user wants to print the tree layout */
        else if (choice == 5) {
            /* Call function that prints level-by-level tree */
            pq_print_tree(pq);
        }
        /* Check if user wants to quit */
        else if (choice == 6) {
            /* Inform user we are exiting the menu loop */
            printf("Exiting...\n");
            /* Break out of the infinite loop */
            break;
        }
        /* Handle any unrecognized menu choice */
        else {
            /* Tell user the choice was invalid */
            printf("Invalid menu choice.\n");
        }
    }
    /* After leaving the loop, free the priority queue's memory */
    pq_free(pq);
}

/* ================================================================
   FUNCTION: main
   PURPOSE:
     Program entry point: show banner, run menu.
   ALGORITHM:
     1. Print a title banner.
     2. Call interactive_menu().
     3. Return 0 for success.
   ================================================================ */
 /* Main function - entry point of the program */
int main(void) {
    /* Print an initial descriptive title banner */
    printf("=== Priority Queue (Min or Max Heap) Demo ===\n");
    /* Launch the interactive user menu */
    interactive_menu();
    /* Return success status code to the operating system */
    return 0;
}

