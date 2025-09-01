/***************************************************************
 * Binary Heap (Min or Max) - Fully Commented Implementation
 * Features:
 *   - Dynamic array storage
 *   - Min-heap or Max-heap selectable at creation
 *   - Insert, Peek, Extract top
 *   - Build heap from array (O(n))
 *   - Change key (increase/decrease logic unified)
 *   - Remove arbitrary value (linear search + sift)
 *   - Clear / Free
 *   - Interactive menu for experimentation
 * Commenting style:
 *   - ALGORITHM block before each function (steps in plain English)
 *   - Line-by-line beginner-friendly comments inside functions
 ***************************************************************/

#include <stdio.h>    // For printf, scanf
#include <stdlib.h>   // For malloc, realloc, free, exit
#include <stdbool.h>  // For bool, true, false
#include <limits.h>   // For INT_MIN / INT_MAX sentinels (optional)

/* ================================================================
   STRUCT: BinaryHeap
   Fields:
     data     -> Pointer to dynamic int array storing heap elements.
     size     -> Current number of elements actually in the heap.
     capacity -> Allocated slots in 'data'.
     is_min   -> If true, behaves as a min-heap (parent <= children).
                 If false, behaves as a max-heap (parent >= children).
   ================================================================ */
typedef struct BinaryHeap {
    int *data;          // Dynamic array to hold heap elements
    int size;           // Number of valid elements currently stored
    int capacity;       // Allocated capacity of the array
    bool is_min;        // Flag: true = min-heap, false = max-heap
} BinaryHeap;

/* ================================================================
   FUNCTION: bh_create
   PURPOSE:
     Create a heap with an initial capacity and choose min or max mode.
   ALGORITHM:
     1. Allocate heap struct.
     2. Allocate data array with given capacity (at least 1).
     3. Initialize size to 0, set is_min flag.
     4. Return pointer (NULL if any allocation fails).
   ================================================================ */
// Create a new heap with given starting capacity and type (min or max)
static BinaryHeap* bh_create(int initial_capacity, bool is_min) {
    // If user passes non-positive capacity, default to 16
    if (initial_capacity <= 0) {
        initial_capacity = 16;
    }
    // Allocate memory for the BinaryHeap structure
    BinaryHeap *h = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    // Check if allocation failed
    if (!h) {
        // Print error message
        printf("Failed to allocate heap structure.\n");
        // Return NULL to signal failure
        return NULL;
    }
    // Allocate memory for the internal data array
    h->data = (int*)malloc(initial_capacity * sizeof(int));
    // Check if data array allocation failed
    if (!h->data) {
        // Print error message
        printf("Failed to allocate heap array.\n");
        // Free the previously allocated heap struct
        free(h);
        // Return NULL to signal failure
        return NULL;
    }
    // Initialize the current size to zero
    h->size = 0;
    // Store the capacity
    h->capacity = initial_capacity;
    // Store whether this is a min-heap or max-heap
    h->is_min = is_min;
    // Return the newly created heap pointer
    return h;
}

/* ================================================================
   FUNCTION: bh_free
   PURPOSE:
     Release all memory used by the heap.
   ALGORITHM:
     1. If heap NULL, return.
     2. Free internal array.
     3. Free heap struct.
   ================================================================ */
// Free all memory used by the heap
static void bh_free(BinaryHeap *h) {
    // If heap pointer itself is NULL do nothing
    if (!h) return;
    // Free the internal array of data
    free(h->data);
    // Free the heap structure
    free(h);
}

/* ================================================================
   FUNCTION: bh_parent_index / bh_left_child_index / bh_right_child_index
   PURPOSE:
     Compute array indices for heap relationships.
   ALGORITHM:
     - parent(i) = (i - 1) / 2
     - left(i)   = 2*i + 1
     - right(i)  = 2*i + 2
   ================================================================ */
// Return the parent index of i
static int bh_parent_index(int i) {
    // Compute parent using integer division
    return (i - 1) / 2;
}
// Return the left child index of i
static int bh_left_child_index(int i) {
    // Compute left child
    return 2 * i + 1;
}
// Return the right child index of i
static int bh_right_child_index(int i) {
    // Compute right child
    return 2 * i + 2;
}

/* ================================================================
   FUNCTION: bh_compare
   PURPOSE:
     Decide ordering between two values given heap type.
   ALGORITHM:
     - If min-heap: return (a < b).
     - If max-heap: return (a > b).
   ================================================================ */
// Compare two integers respecting heap mode (returns true if a should be "above" b)
static bool bh_compare(BinaryHeap *h, int a, int b) {
    // If heap is a min-heap we want smaller element on top
    if (h->is_min) {
        // Return true if a is smaller than b
        return a < b;
    } else {
        // Otherwise for max-heap we want larger element on top
        return a > b;
    }
}

/* ================================================================
   FUNCTION: bh_swap
   PURPOSE:
     Swap two elements in the heap array.
   ALGORITHM:
     1. Store data[i] in temp.
     2. data[i] = data[j]
     3. data[j] = temp
   ================================================================ */
// Swap two elements inside the heap's data array
static void bh_swap(BinaryHeap *h, int i, int j) {
    // Store element at i in a temporary variable
    int temp = h->data[i];
    // Move element at j into i
    h->data[i] = h->data[j];
    // Move original element from i into j
    h->data[j] = temp;
}

/* ================================================================
   FUNCTION: bh_ensure_capacity
   PURPOSE:
     Ensure there is space for at least one more element.
   ALGORITHM:
     1. If size < capacity -> do nothing.
     2. Else double capacity.
     3. Reallocate data array.
     4. On failure print error & exit (simplified error handling).
   ================================================================ */
// Grow the internal array if we have no free slots
static void bh_ensure_capacity(BinaryHeap *h) {
    // If we still have space we do nothing
    if (h->size < h->capacity) return;
    // Compute new capacity by doubling
    int new_capacity = h->capacity * 2;
    // Reallocate the data array to the new capacity
    int *new_data = (int*)realloc(h->data, new_capacity * sizeof(int));
    // Check for allocation failure
    if (!new_data) {
        // Print out-of-memory error
        printf("Out of memory while resizing heap.\n");
        // Exit the program (simplistic critical failure strategy)
        exit(EXIT_FAILURE);
    }
    // Update the data pointer
    h->data = new_data;
    // Store the new capacity
    h->capacity = new_capacity;
}

/* ================================================================
   FUNCTION: bh_heapify_up
   PURPOSE:
     Restore heap property after inserting at end.
   ALGORITHM:
     1. Start at inserted index i = size-1.
     2. While i > 0 and data[i] should be above parent:
         a. Swap with parent.
         b. Move i to parent index.
   ================================================================ */
// Bubble the last inserted element up to correct position
static void bh_heapify_up(BinaryHeap *h, int index) {
    // Keep track of current index while we move up
    int i = index;
    // Loop while not at root and current outranks its parent
    while (i > 0) {
        // Find parent index
        int p = bh_parent_index(i);
        // If current element belongs above parent
        if (bh_compare(h, h->data[i], h->data[p])) {
            // Swap current with parent
            bh_swap(h, i, p);
            // Move current index to parent index
            i = p;
        } else {
            // Otherwise heap property satisfied; stop
            break;
        }
    }
}

/* ================================================================
   FUNCTION: bh_heapify_down
   PURPOSE:
     Restore heap property after removing the top element.
   ALGORITHM:
     1. Start at root index 0.
     2. While current has at least one child:
         a. Determine better child (min or max based on mode).
         b. If current violates ordering with that child -> swap.
         c. Else stop.
         d. Move index to child and continue.
   ================================================================ */
// Push the root element down to its proper position
static void bh_heapify_down(BinaryHeap *h, int index) {
    // Start from given index (usually 0)
    int i = index;
    // Loop until no children
    while (1) {
        // Compute left child index
        int left = bh_left_child_index(i);
        // Compute right child index
        int right = bh_right_child_index(i);
        // If left child is outside size => no children => stop
        if (left >= h->size) break;
        // Assume best child is left first
        int best = left;
        // If right child exists
        if (right < h->size) {
            // Decide if right child outranks left child
            if (bh_compare(h, h->data[right], h->data[left])) {
                // Update best child to right
                best = right;
            }
        }
        // Check if best child outranks current
        if (bh_compare(h, h->data[best], h->data[i])) {
            // Swap current with best child
            bh_swap(h, i, best);
            // Move down to best child's position
            i = best;
        } else {
            // No violation => heap property satisfied => stop
            break;
        }
    }
}

/* ================================================================
   FUNCTION: bh_insert
   PURPOSE:
     Insert a new value into the heap.
   ALGORITHM:
     1. Ensure capacity.
     2. Place new value at data[size].
     3. Increment size.
     4. Heapify up from that index.
   ================================================================ */
// Insert a new value into the heap
static void bh_insert(BinaryHeap *h, int value) {
    // Make sure there is room for the new element
    bh_ensure_capacity(h);
    // Place the value at the end of the array
    h->data[h->size] = value;
    // Increment the size to include the new element
    h->size++;
    // Restore heap property by bubbling new element up
    bh_heapify_up(h, h->size - 1);
}

/* ================================================================
   FUNCTION: bh_peek
   PURPOSE:
     View the top element without removing it.
   ALGORITHM:
     1. If size=0 -> error sentinel / message.
     2. Return data[0].
   ================================================================ */
// Return the top element (min or max) without removing it
static bool bh_peek(BinaryHeap *h, int *out_value) {
    // If heap is empty we cannot peek
    if (h->size == 0) {
        // Inform caller via return false
        return false;
    }
    // Set output parameter to root element
    *out_value = h->data[0];
    // Indicate success
    return true;
}

/* ================================================================
   FUNCTION: bh_extract_top
   PURPOSE:
     Remove and return the top (root) element.
   ALGORITHM:
     1. If empty -> fail.
     2. Save root value.
     3. Move last element into root.
     4. Decrement size.
     5. Heapify down from root.
     6. Return saved value.
   ================================================================ */
// Remove and return the top element from the heap
static bool bh_extract_top(BinaryHeap *h, int *out_value) {
    // If heap empty cannot extract
    if (h->size == 0) {
        // Return false to indicate failure
        return false;
    }
    // Store root value for returning
    *out_value = h->data[0];
    // Move last element to root position
    h->data[0] = h->data[h->size - 1];
    // Decrement size to forget the last slot
    h->size--;
    // Restore heap property by pushing root down
    if (h->size > 0) {
        bh_heapify_down(h, 0);
    }
    // Indicate success
    return true;
}

/* ================================================================
   FUNCTION: bh_build_from_array
   PURPOSE:
     Build heap from an existing array in O(n) time.
   ALGORITHM:
     1. Ensure capacity >= n (realloc if needed).
     2. Copy array into data; set size=n.
     3. For i = parent(last) down to 0: heapify_down(i).
   ================================================================ */
// Build a heap from a raw array of integers
static void bh_build_from_array(BinaryHeap *h, const int *arr, int n) {
    // If n exceeds current capacity, reallocate to at least n
    if (n > h->capacity) {
        // Allocate new array big enough for n
        int *new_data = (int*)realloc(h->data, n * sizeof(int));
        // Check for allocation failure
        if (!new_data) {
            printf("Out of memory building heap.\n");
            exit(EXIT_FAILURE);
        }
        // Update data pointer
        h->data = new_data;
        // Update capacity
        h->capacity = n;
    }
    // Copy the incoming array elements into the heap data
    for (int i = 0; i < n; i++) {
        h->data[i] = arr[i];
    }
    // Set heap size to n
    h->size = n;
    // Compute index of last internal node (parent of last element)
    int start = bh_parent_index(h->size - 1);
    // Perform heapify_down from each internal node backwards
    for (int i = start; i >= 0; i--) {
        bh_heapify_down(h, i);
    }
}

/* ================================================================
   FUNCTION: bh_find_value
   PURPOSE:
     Linear search for a value (for remove/change operations).
   ALGORITHM:
     1. For i=0..size-1: if data[i]==value return i.
     2. Return -1 if not found.
   NOTE:
     This is O(n); binary heaps don't support fast arbitrary search.
   ================================================================ */
// Find the index of a specific value (returns -1 if not found)
static int bh_find_value(BinaryHeap *h, int value) {
    // Loop through all current elements
    for (int i = 0; i < h->size; i++) {
        // If we find the target value
        if (h->data[i] == value) {
            // Return its index
            return i;
        }
    }
    // Value not found
    return -1;
}

/* ================================================================
   FUNCTION: bh_change_key
   PURPOSE:
     Change the value at a given index to a new value and re-heapify.
   ALGORITHM:
     1. Store old value.
     2. Set data[index] = new_value.
     3. If new value outranks parent: heapify_up.
     4. Else heapify_down.
   ================================================================ */
// Change the key stored at an index to a new value and fix heap order
static bool bh_change_key(BinaryHeap *h, int index, int new_value) {
    // Check if index is out of bounds
    if (index < 0 || index >= h->size) {
        // Return false indicating failure
        return false;
    }
    // Store the old value
    int old_value = h->data[index];
    // Overwrite with new value
    h->data[index] = new_value;
    // If new value outranks old direction (i.e. moves up)
    if (index > 0) {
        // Get parent index
        int p = bh_parent_index(index);
        // If new value should be above parent
        if (bh_compare(h, h->data[index], h->data[p])) {
            // Heapify up
            bh_heapify_up(h, index);
            // Return success
            return true;
        }
    }
    // Otherwise push it down if it violates with children
    bh_heapify_down(h, index);
    // Return success
    return true;
}

/* ================================================================
   FUNCTION: bh_remove_value
   PURPOSE:
     Remove first occurrence of a specific value.
   ALGORITHM:
     1. Find index via linear search.
     2. If not found -> false.
     3. Swap element with last.
     4. Reduce size.
     5. Heapify_up (if new element outranks parent) else heapify_down.
   ================================================================ */
// Remove a specific value from the heap (first match)
static bool bh_remove_value(BinaryHeap *h, int value) {
    // Find index of target value
    int idx = bh_find_value(h, value);
    // If not found return false
    if (idx == -1) return false;
    // Move last element into idx position
    h->data[idx] = h->data[h->size - 1];
    // Decrement size to remove last slot
    h->size--;
    // If we removed the last element only, we are done
    if (idx >= h->size) {
        return true;
    }
    // Attempt to move the replaced element up if needed
    if (idx > 0) {
        int p = bh_parent_index(idx);
        if (bh_compare(h, h->data[idx], h->data[p])) {
            bh_heapify_up(h, idx);
            return true;
        }
    }
    // Otherwise settle it downward
    bh_heapify_down(h, idx);
    // Return success
    return true;
}

/* ================================================================
   FUNCTION: bh_print
   PURPOSE:
     Print the internal array (level order representation).
   ALGORITHM:
     1. Loop i=0..size-1 printing data[i].
   NOTE:
     This is NOT a pretty tree, but shows logical contents.
   ================================================================ */
// Print the heap's internal array representation
static void bh_print(BinaryHeap *h) {
    // If heap is empty mention it
    if (h->size == 0) {
        printf("[empty]\n");
        return;
    }
    // Print opening bracket
    printf("[ ");
    // Loop through all elements
    for (int i = 0; i < h->size; i++) {
        // Print each value
        printf("%d ", h->data[i]);
    }
    // Print closing bracket and newline
    printf("]\n");
}

/* ================================================================
   FUNCTION: bh_clear
   PURPOSE:
     Remove all elements but keep allocated memory for reuse.
   ALGORITHM:
     1. Set size=0.
     2. (Data remains allocated.)
   ================================================================ */
// Clear all elements in the heap without freeing memory
static void bh_clear(BinaryHeap *h) {
    // Reset size to zero
    h->size = 0;
}

/* ================================================================
   FUNCTION: interactive_menu
   PURPOSE:
     Provide a user-driven interface to test heap operations.
   ALGORITHM:
     LOOP:
       1. Show menu.
       2. Read choice.
       3. Perform selected operation (insert, extract, etc.).
       4. Repeat until Quit.
   ================================================================ */
// Provide an interactive menu for experimenting with the heap
static void interactive_menu(void) {
    // Ask user to choose min-heap (1) or max-heap (0)
    int heap_type_choice;
    // Prompt the user
    printf("Create heap - enter 1 for MIN-heap or 0 for MAX-heap: ");
    // Read the choice
    if (scanf("%d", &heap_type_choice) != 1) {
        // On invalid input: flush and default to min-heap
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        heap_type_choice = 1;
    }
    // Determine boolean for min-heap
    bool is_min = (heap_type_choice != 0);
    // Create a heap with initial capacity 16
    BinaryHeap *heap = bh_create(16, is_min);
    // Check if creation failed
    if (!heap) {
        // Print error and return
        printf("Failed to create heap.\n");
        return;
    }
    // Print mode information
    printf("Created a %s-heap.\n", heap->is_min ? "MIN" : "MAX");

    // Variable to store user menu choice
    int choice;
    // Buffer for building from array (we allocate once for convenience)
    int build_arr[256];
    // Interactive infinite loop
    while (1) {
        // Print menu header
        printf("\n=== Binary Heap Menu ===\n");
        // Print options
        printf("1. Insert value\n");
        printf("2. Peek top\n");
        printf("3. Extract top\n");
        printf("4. Change key (by value -> new value)\n");
        printf("5. Remove value\n");
        printf("6. Build heap from array\n");
        printf("7. Print heap array\n");
        printf("8. Clear heap\n");
        printf("9. Quit\n");
        // Prompt for user choice
        printf("Enter choice: ");
        // Read choice
        if (scanf("%d", &choice) != 1) {
            // Flush invalid input
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            // Skip to next loop
            continue;
        }

        // Handle Insert
        if (choice == 1) {
            // Ask user for value
            int val;
            printf("Enter value to insert: ");
            // Read value
            if (scanf("%d", &val) == 1) {
                // Insert into heap
                bh_insert(heap, val);
                // Confirm insertion
                printf("Inserted %d.\n", val);
            } else {
                // Handle invalid input
                printf("Invalid number.\n");
            }
        }
        // Handle Peek
        else if (choice == 2) {
            // Variable to hold peeked value
            int top;
            // Attempt to peek
            if (bh_peek(heap, &top)) {
                // Print top value
                printf("Top element: %d\n", top);
            } else {
                // Report empty heap
                printf("Heap is empty.\n");
            }
        }
        // Handle Extract
        else if (choice == 3) {
            // Variable to hold extracted value
            int top;
            // Attempt to extract
            if (bh_extract_top(heap, &top)) {
                // Print extracted value
                printf("Extracted top element: %d\n", top);
            } else {
                // Report heap empty
                printf("Heap is empty.\n");
            }
        }
        // Handle Change Key
        else if (choice == 4) {
            // Ask which existing value to change
            int old_val, new_val;
            printf("Enter existing value to change: ");
            // Read old value
            if (scanf("%d", &old_val) != 1) {
                printf("Invalid.\n");
                continue;
            }
            // Ask for new value
            printf("Enter new value: ");
            // Read new value
            if (scanf("%d", &new_val) != 1) {
                printf("Invalid.\n");
                continue;
            }
            // Find index of the old value
            int idx = bh_find_value(heap, old_val);
            // If not found report
            if (idx == -1) {
                printf("Value %d not found.\n", old_val);
            } else {
                // Change key in place
                bh_change_key(heap, idx, new_val);
                // Confirm update
                printf("Changed value %d to %d.\n", old_val, new_val);
            }
        }
        // Handle Remove Value
        else if (choice == 5) {
            // Ask for value to remove
            int val;
            printf("Enter value to remove: ");
            // Read value
            if (scanf("%d", &val) != 1) {
                printf("Invalid number.\n");
                continue;
            }
            // Attempt removal
            if (bh_remove_value(heap, val)) {
                printf("Removed %d.\n", val);
            } else {
                printf("Value %d not found.\n", val);
            }
        }
        // Handle Build from Array
        else if (choice == 6) {
            // Ask how many elements to build
            int count;
            printf("Enter number of elements (<=256): ");
            // Read count
            if (scanf("%d", &count) != 1 || count < 0 || count > 256) {
                printf("Invalid count.\n");
                continue;
            }
            // Read each element
            printf("Enter %d integers:\n", count);
            for (int i = 0; i < count; i++) {
                if (scanf("%d", &build_arr[i]) != 1) {
                    printf("Invalid input. Aborting build.\n");
                    count = i;
                    break;
                }
            }
            // Build heap from array
            bh_build_from_array(heap, build_arr, count);
            // Confirm build
            printf("Built heap from array of %d elements.\n", count);
        }
        // Handle Print
        else if (choice == 7) {
            // Print the internal heap array
            bh_print(heap);
        }
        // Handle Clear
        else if (choice == 8) {
            // Reset size to zero
            bh_clear(heap);
            // Confirm clearing
            printf("Heap cleared.\n");
        }
        // Handle Quit
        else if (choice == 9) {
            // Announce exit
            printf("Exiting menu...\n");
            // Break from loop
            break;
        }
        // Handle invalid choice values
        else {
            // Inform user
            printf("Invalid choice.\n");
        }
    }
    // After finishing menu, free the heap
    bh_free(heap);
}

/* ================================================================
   FUNCTION: main
   PURPOSE:
     Entry point. Just calls the interactive menu.
   ALGORITHM:
     1. Print welcome.
     2. Call interactive_menu().
     3. Return 0.
   ================================================================ */
// Program entry point
int main(void) {
    // Print a greeting
    printf("=== Binary Heap (Min / Max) Demo ===\n");
    // Launch the interactive menu
    interactive_menu();
    // Return success code
    return 0;
}

