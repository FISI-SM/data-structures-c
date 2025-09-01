/***************************************************************
 * Binomial Heap (Min or Max) with Merge Option
 * -------------------------------------------------------------
 * Operations:
 *   - Create (select min or max mode)
 *   - Insert key
 *   - Find extreme (min for min-heap, max for max-heap)
 *   - Extract extreme
 *   - Improve key (decrease for min-heap / increase for max-heap)
 *   - Delete key
 *   - Merge another heap (same mode) via menu
 *   - Print entire structure
 *   - Free all memory
 *
 * Commenting Style:
 *   - ALGORITHM block above each function.
 *   - Plain English comment above EVERY SINGLE code line.
 ***************************************************************/

 /* Include stdio for input/output (printf, scanf) */
#include <stdio.h>
 /* Include stdlib for dynamic memory (malloc, free) */
#include <stdlib.h>
 /* Include stdbool for bool, true, false */
#include <stdbool.h>
 /* Include limits for INT_MIN and INT_MAX sentinel values */
#include <limits.h>

/* ================================================================
   DATA STRUCTURES
   ------------------------------------------------
   BinomialNode:
     - key: integer value stored in the node.
     - degree: number of children (order of binomial tree).
     - parent: pointer to parent node (NULL if root).
     - child: pointer to leftmost child.
     - sibling: pointer to next root or next sibling in child list.
   BinomialHeap:
     - head: pointer to first root in root list (sorted by degree).
     - is_min: if true behaves as min-heap (smaller key is better),
               if false behaves as max-heap (larger key is better).
   ================================================================ */

 /* Define a structure for a binomial heap node */
typedef struct BinomialNode {
    /* Store the key (value) of this node */
    int key;
    /* Store number of children (degree of this binomial tree root) */
    int degree;
    /* Pointer to parent (NULL if this node is a root) */
    struct BinomialNode *parent;
    /* Pointer to leftmost child (NULL if none) */
    struct BinomialNode *child;
    /* Pointer to immediate right sibling (another root or child sibling) */
    struct BinomialNode *sibling;
} BinomialNode;

 /* Define a structure for the entire binomial heap */
typedef struct BinomialHeap {
    /* Pointer to the head (first root) in the root list */
    BinomialNode *head;
    /* Flag indicating if this heap is a min-heap (true) or max-heap (false) */
    bool is_min;
} BinomialHeap;

/* ================================================================
   FUNCTION: create_node
   PURPOSE:
     Allocate and initialize a binomial node with a given key.
   ALGORITHM:
     1. Allocate a BinomialNode.
     2. If allocation fails return NULL.
     3. Set key, degree=0, parent/child/sibling=NULL.
     4. Return node pointer.
   ================================================================ */
 /* Create a new node with the specified key */
static BinomialNode *create_node(int key) {
    /* Allocate memory for one BinomialNode */
    BinomialNode *node = (BinomialNode *)malloc(sizeof(BinomialNode));
    /* Check if allocation failed */
    if (!node) {
        /* Report allocation failure */
        printf("Memory allocation failed for BinomialNode.\n");
        /* Return NULL to indicate failure */
        return NULL;
    }
    /* Set the node's key to the provided value */
    node->key = key;
    /* Initialize degree to zero (no children yet) */
    node->degree = 0;
    /* Initialize parent pointer to NULL (not linked yet) */
    node->parent = NULL;
    /* Initialize child pointer to NULL (no children yet) */
    node->child = NULL;
    /* Initialize sibling pointer to NULL (not in list yet) */
    node->sibling = NULL;
    /* Return pointer to the newly created node */
    return node;
}

/* ================================================================
   FUNCTION: create_heap
   PURPOSE:
     Allocate and initialize an empty binomial heap in chosen mode.
   ALGORITHM:
     1. Allocate BinomialHeap.
     2. If failure return NULL.
     3. Set head=NULL, set is_min flag.
     4. Return heap pointer.
   ================================================================ */
 /* Create a new empty binomial heap (min or max depending on flag) */
static BinomialHeap *create_heap(bool is_min) {
    /* Allocate memory for one BinomialHeap */
    BinomialHeap *heap = (BinomialHeap *)malloc(sizeof(BinomialHeap));
    /* Check if allocation failed */
    if (!heap) {
        /* Report error to user */
        printf("Memory allocation failed for BinomialHeap.\n");
        /* Return NULL to indicate failure */
        return NULL;
    }
    /* Initialize head to NULL (empty root list) */
    heap->head = NULL;
    /* Store whether this heap is min-heap or max-heap */
    heap->is_min = is_min;
    /* Return the initialized heap pointer */
    return heap;
}

/* ================================================================
   FUNCTION: heap_better
   PURPOSE:
     Compare two keys under heap mode.
   ALGORITHM:
     1. If is_min -> better means a < b.
     2. Else (max) -> better means a > b.
   ================================================================ */
 /* Return true if key a outranks key b given heap mode */
static bool heap_better(BinomialHeap *heap, int a, int b) {
    /* If heap is min-heap we prefer smaller keys */
    if (heap->is_min) {
        /* Return true if a is strictly smaller than b */
        return a < b;
    } else {
        /* Return true if a is strictly larger for max-heap */
        return a > b;
    }
}

/* ================================================================
   FUNCTION: binomial_link
   PURPOSE:
     Make root y a child of root z (z remains root) preserving order.
   ALGORITHM:
     1. Set y->parent = z.
     2. Insert y before z->child (y->sibling = z->child).
     3. Set z->child = y.
     4. Increment z->degree.
   NOTE:
     - Caller must ensure z's key is "better" than y's key already.
   ================================================================ */
 /* Link tree rooted at y under root z (z key is better) */
static void binomial_link(BinomialNode *y, BinomialNode *z) {
    /* Make z the parent of y */
    y->parent = z;
    /* Point y's sibling to the current leftmost child of z */
    y->sibling = z->child;
    /* Make y the new leftmost child of z */
    z->child = y;
    /* Increase z's degree because it gained a child */
    z->degree++;
}

/* ================================================================
   FUNCTION: merge_root_lists
   PURPOSE:
     Merge two root lists (ordered by degree) without linking trees.
   ALGORITHM:
     1. Use a dummy head and tail pointer.
     2. While both lists non-empty:
        - take root with smaller degree first.
     3. Append remaining nodes of the non-empty list.
     4. Return merged list (dummy.sibling).
   ================================================================ */
 /* Merge two root lists by ascending degree into one list */
static BinomialNode *merge_root_lists(BinomialNode *h1, BinomialNode *h2) {
    /* Create a dummy node for simpler list construction */
    BinomialNode dummy;
    /* Initialize dummy's sibling to NULL (start state) */
    dummy.sibling = NULL;
    /* Tail pointer starts at dummy */
    BinomialNode *tail = &dummy;
    /* Loop while both lists still have nodes */
    while (h1 && h2) {
        /* If h1 degree is <= h2 degree choose h1 first */
        if (h1->degree <= h2->degree) {
            /* Append h1 to the result list */
            tail->sibling = h1;
            /* Advance h1 to its next sibling */
            h1 = h1->sibling;
        } else {
            /* Append h2 otherwise */
            tail->sibling = h2;
            /* Advance h2 */
            h2 = h2->sibling;
        }
        /* Move tail to the newly appended node */
        tail = tail->sibling;
    }
    /* Link remaining part (one of h1 or h2 or NULL) */
    tail->sibling = h1 ? h1 : h2;
    /* Return merged head skipping dummy */
    return dummy.sibling;
}

/* ================================================================
   FUNCTION: union_heaps
   PURPOSE:
     Produce the union of two root lists, linking trees of equal degree
     according to heap order.
   ALGORITHM:
     1. Merge root lists by degree (no linking).
     2. If merged empty return NULL.
     3. Use prev, curr, next traversal.
     4. While next != NULL:
        a. If degrees of curr and next differ OR (next->sibling exists and same degree as curr):
           - advance prev=curr; curr=next; next=next->sibling.
        b. Else (degrees equal):
           i. If curr key better than next key:
               - link next under curr
               - curr->sibling = next->sibling
               - next = curr->sibling
           ii. Else:
               - if prev == NULL head = next else prev->sibling = next
               - link curr under next
               - curr = next
               - next = curr->sibling
     5. Return head.
   ================================================================ */
 /* Union two binomial heaps' root lists into one valid root list */
static BinomialNode *union_heaps(BinomialHeap *heap, BinomialNode *h1, BinomialNode *h2) {
    /* Merge the two root lists by degree */
    BinomialNode *head = merge_root_lists(h1, h2);
    /* If merged list empty return NULL */
    if (!head) return NULL;
    /* Initialize prev pointer to NULL at start */
    BinomialNode *prev = NULL;
    /* Initialize curr pointer to head */
    BinomialNode *curr = head;
    /* Initialize next pointer to curr's sibling */
    BinomialNode *next = curr->sibling;
    /* Traverse root list while next is not NULL */
    while (next) {
        /* Check if we should defer linking due to degree pattern */
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            /* Advance prev to curr */
            prev = curr;
            /* Advance curr to next */
            curr = next;
            /* Advance next to curr's sibling */
            next = curr->sibling;
        }
        /* Otherwise degrees equal and safe to link */
        else {
            /* If curr's key outranks next's key under mode keep curr as root */
            if (heap_better(heap, curr->key, next->key)) {
                /* Remove next from list by skipping it */
                curr->sibling = next->sibling;
                /* Link next under curr */
                binomial_link(next, curr);
                /* Advance next to curr's new sibling */
                next = curr->sibling;
            }
            /* Else next's key outranks curr's so next becomes root */
            else {
                /* If curr was head update head to next */
                if (prev == NULL) {
                    /* Set new head to next */
                    head = next;
                } else {
                    /* Otherwise bypass curr by linking prev to next */
                    prev->sibling = next;
                }
                /* Link curr under next */
                binomial_link(curr, next);
                /* Move curr pointer to next (new root) */
                curr = next;
                /* Advance next to curr's sibling */
                next = curr->sibling;
            }
        }
    }
    /* Return the final unified root list head */
    return head;
}

/* ================================================================
   FUNCTION: insert_key
   PURPOSE:
     Insert a key into the heap by uniting with a single-node heap.
   ALGORITHM:
     1. Create node.
     2. Union existing head with the node (as a separate root list).
     3. Assign result to heap->head.
   ================================================================ */
 /* Insert a single key into the binomial heap */
static bool insert_key(BinomialHeap *heap, int key) {
    /* Check for invalid heap pointer */
    if (!heap) return false;
    /* Create a node for the new key */
    BinomialNode *node = create_node(key);
    /* Check node creation success */
    if (!node) return false;
    /* Union current root list with new singleton node */
    heap->head = union_heaps(heap, heap->head, node);
    /* Return true to indicate insertion succeeded */
    return true;
}

/* ================================================================
   FUNCTION: find_extreme_node
   PURPOSE:
     Find root with smallest key (min-heap) or largest key (max-heap).
   ALGORITHM:
     1. If head NULL return NULL.
     2. Initialize best=head.
     3. Traverse siblings:
        - if heap_better(heap, current->key, best->key) update best.
     4. Return best.
   ================================================================ */
 /* Find the extreme root (min or max depending on mode) */
static BinomialNode *find_extreme_node(BinomialHeap *heap) {
    /* If heap invalid or empty return NULL */
    if (!heap || !heap->head) return NULL;
    /* Start traversal at head */
    BinomialNode *curr = heap->head;
    /* Initialize best pointer to first root */
    BinomialNode *best = curr;
    /* Move to next root */
    curr = curr->sibling;
    /* Traverse remaining roots */
    while (curr) {
        /* If current outranks best update best pointer */
        if (heap_better(heap, curr->key, best->key)) {
            /* Set best to current */
            best = curr;
        }
        /* Advance to next sibling root */
        curr = curr->sibling;
    }
    /* Return pointer to extreme root node */
    return best;
}

/* ================================================================
   FUNCTION: extract_extreme
   PURPOSE:
     Remove and return extreme root (min or max) from the heap.
   ALGORITHM:
     1. If empty -> fail.
     2. Traverse root list to find extreme and track its previous.
     3. Remove extreme root from list.
     4. Reverse its child list to prepare as separate root list.
     5. Set children's parent to NULL.
     6. Union original list (minus extreme) with reversed child list.
     7. Return extreme key via out parameter.
   ================================================================ */
 /* Extract the extreme (min/max) key from the heap */
static bool extract_extreme(BinomialHeap *heap, int *out_key) {
    /* Fail if heap invalid or empty */
    if (!heap || !heap->head) return false;
    /* Initialize previous pointer to NULL */
    BinomialNode *prev_ext = NULL;
    /* Initialize extreme pointer to head initially */
    BinomialNode *ext = heap->head;
    /* Initialize traversal previous pointer */
    BinomialNode *prev = NULL;
    /* Initialize current pointer for scanning roots */
    BinomialNode *curr = heap->head;
    /* Loop across roots to find the true extreme */
    while (curr) {
        /* If curr outranks ext update ext and prev_ext */
        if (heap_better(heap, curr->key, ext->key)) {
            /* Update extreme node pointer */
            ext = curr;
            /* Update previous pointer to current's predecessor */
            prev_ext = prev;
        }
        /* Advance prev to curr */
        prev = curr;
        /* Advance curr to sibling */
        curr = curr->sibling;
    }
    /* If extreme not head adjust the previous's sibling */
    if (prev_ext) {
        /* Skip the extreme root in the list */
        prev_ext->sibling = ext->sibling;
    } else {
        /* Extreme is head so move head to next root */
        heap->head = ext->sibling;
    }
    /* Get pointer to extreme's leftmost child */
    BinomialNode *child = ext->child;
    /* Initialize reversed list head to NULL */
    BinomialNode *rev_head = NULL;
    /* Reverse child list so degrees ascend properly after union */
    while (child) {
        /* Store next sibling before rewiring */
        BinomialNode *next = child->sibling;
        /* Reset parent to NULL (will become root) */
        child->parent = NULL;
        /* Insert child at front of reversed list */
        child->sibling = rev_head;
        /* Update reversed list head */
        rev_head = child;
        /* Advance to original next child */
        child = next;
    }
    /* If caller wants the extracted key provide it */
    if (out_key) *out_key = ext->key;
    /* Free the extracted root node */
    free(ext);
    /* Union remaining heap root list with reversed children list */
    heap->head = union_heaps(heap, heap->head, rev_head);
    /* Return success indicator */
    return true;
}

/* ================================================================
   FUNCTION: improve_key
   PURPOSE:
     Improve a node's priority:
       - If min-heap: new_key must be <= old key (decrease).
       - If max-heap: new_key must be >= old key (increase).
     Then bubble node up while it outranks its parent.
   ALGORITHM:
     1. Reject if node NULL.
     2. If min mode and new_key > old -> fail.
        If max mode and new_key < old -> fail.
     3. Assign key = new_key.
     4. While parent exists and node outranks parent:
         - swap keys with parent
         - move node pointer to parent
     5. Return true.
   NOTE:
     Swapping only keys (not whole nodes) keeps links simple.
   ================================================================ */
 /* Improve a node's key value according to heap mode rules */
static bool improve_key(BinomialHeap *heap, BinomialNode *node, int new_key) {
    /* Reject operation if node pointer invalid */
    if (!node) return false;
    /* If heap is min and new key is larger (worse) reject */
    if (heap->is_min && new_key > node->key) {
        /* Inform user of improper direction */
        printf("New key must be <= current key for min-heap.\n");
        /* Return failure */
        return false;
    }
    /* If heap is max and new key is smaller (worse) reject */
    if (!heap->is_min && new_key < node->key) {
        /* Inform user of improper direction */
        printf("New key must be >= current key for max-heap.\n");
        /* Return failure */
        return false;
    }
    /* Assign the improved key */
    node->key = new_key;
    /* Create a variable to walk upward */
    BinomialNode *curr = node;
    /* While current has a parent and outranks that parent */
    while (curr->parent && heap_better(heap, curr->key, curr->parent->key)) {
        /* Store current key temporarily */
        int temp = curr->key;
        /* Replace current key with parent key */
        curr->key = curr->parent->key;
        /* Place stored key into parent */
        curr->parent->key = temp;
        /* Move current pointer upward to parent */
        curr = curr->parent;
    }
    /* Return success */
    return true;
}

/* ================================================================
   FUNCTION: delete_node
   PURPOSE:
     Delete a node by improving its key to the extreme sentinel
     then extracting the extreme root.
     - For min-heap: improve to INT_MIN.
     - For max-heap: improve to INT_MAX.
   ALGORITHM:
     1. Determine sentinel (INT_MIN or INT_MAX).
     2. Call improve_key with sentinel.
     3. Extract extreme root (should remove this node).
     4. Return success/failure.
   ================================================================ */
 /* Delete a node from the heap (improve then extract) */
static bool delete_node(BinomialHeap *heap, BinomialNode *node) {
    /* Fail if heap or node invalid */
    if (!heap || !node) return false;
    /* Choose sentinel based on heap mode */
    int sentinel = heap->is_min ? INT_MIN : INT_MAX;
    /* Attempt to improve node to sentinel */
    if (!improve_key(heap, node, sentinel)) {
        /* Return failure if improvement invalid */
        return false;
    }
    /* Prepare variable to receive extracted key (unused) */
    int dummy;
    /* Extract the extreme which should now be this node */
    return extract_extreme(heap, &dummy);
}

/* ================================================================
   FUNCTION: find_node_depth_first
   PURPOSE:
     Find first node with a given key using DFS (inefficient but simple).
   ALGORITHM:
     1. If root NULL return NULL.
     2. If root->key == key return root.
     3. Recursively search child; if found return.
     4. Recursively search sibling; return result.
   ================================================================ */
 /* Depth-first search for a node with a specific key */
static BinomialNode *find_node_depth_first(BinomialNode *root, int key) {
    /* If root is NULL return NULL not found */
    if (!root) return NULL;
    /* If root key matches target return root */
    if (root->key == key) return root;
    /* Search in root's child subtree */
    BinomialNode *found = find_node_depth_first(root->child, key);
    /* If found in child subtree return it */
    if (found) return found;
    /* Otherwise search in sibling subtree */
    return find_node_depth_first(root->sibling, key);
}

/* ================================================================
   FUNCTION: print_tree_recursive
   PURPOSE:
     Print a single binomial tree with indentation by depth.
   ALGORITHM:
     1. If node NULL return.
     2. Print indent spaces (2 * level).
     3. Print key and degree.
     4. Recurse on child with level+1.
     5. Recurse on sibling with same level.
   ================================================================ */
 /* Recursively print a binomial tree from a given node */
static void print_tree_recursive(BinomialNode *node, int level) {
    /* Do nothing if node is NULL */
    if (!node) return;
    /* Print indentation proportional to level */
    for (int i = 0; i < level; i++) {
        /* Print two spaces per level */
        printf("  ");
    }
    /* Print node key and degree */
    printf("Key=%d (deg=%d)\n", node->key, node->degree);
    /* Recurse on first child at next level */
    print_tree_recursive(node->child, level + 1);
    /* Recurse on next sibling at same level */
    print_tree_recursive(node->sibling, level);
}

/* ================================================================
   FUNCTION: print_heap
   PURPOSE:
     Print each binomial tree in the heap.
   ALGORITHM:
     1. If empty print notice.
     2. For each root:
         - print header "Tree (degree d):"
         - print tree recursively
   ================================================================ */
 /* Print the entire binomial heap structure (all trees) */
static void print_heap(BinomialHeap *heap) {
    /* If heap invalid or empty announce emptiness */
    if (!heap || !heap->head) {
        /* Print empty message */
        printf("[Heap is empty]\n");
        /* Return early */
        return;
    }
    /* Start at first root */
    BinomialNode *curr = heap->head;
    /* Traverse each root in root list */
    while (curr) {
        /* Print tree header */
        printf("Tree (degree %d):\n", curr->degree);
        /* Print tree nodes recursively */
        print_tree_recursive(curr, 1);
        /* Advance to next root */
        curr = curr->sibling;
    }
}

/* ================================================================
   FUNCTION: free_nodes
   PURPOSE:
     Recursively free tree nodes (children then siblings).
   ALGORITHM:
     1. If node NULL return.
     2. Free child subtree.
     3. Free sibling subtree.
     4. Free node itself.
   ================================================================ */
 /* Recursively free a binomial tree (including siblings) */
static void free_nodes(BinomialNode *node) {
    /* If node is NULL nothing to free */
    if (!node) return;
    /* Recursively free the child subtree */
    free_nodes(node->child);
    /* Recursively free the sibling subtree */
    free_nodes(node->sibling);
    /* Free this node's memory */
    free(node);
}

/* ================================================================
   FUNCTION: free_heap
   PURPOSE:
     Free all nodes and the heap structure.
   ALGORITHM:
     1. If heap NULL return.
     2. Free nodes from head.
     3. Free heap struct.
   ================================================================ */
 /* Free the entire binomial heap and its resources */
static void free_heap(BinomialHeap *heap) {
    /* Return if heap pointer NULL */
    if (!heap) return;
    /* Free all nodes reachable from head */
    free_nodes(heap->head);
    /* Free the heap structure itself */
    free(heap);
}

/* ================================================================
   FUNCTION: merge_into_heap
   PURPOSE:
     Merge another heap (same mode) into an existing heap.
   ALGORITHM:
     1. If mode mismatch -> abort with message.
     2. Perform union with both head lists.
     3. Free the temporary heap container (not its nodes).
   ================================================================ */
 /* Merge second heap into first if modes match */
static bool merge_into_heap(BinomialHeap *dest, BinomialHeap *src) {
    /* Reject if either heap pointer invalid */
    if (!dest || !src) return false;
    /* Reject if heap modes differ (would violate ordering) */
    if (dest->is_min != src->is_min) {
        /* Inform user of mismatch */
        printf("Cannot merge heaps of different modes.\n");
        /* Return failure */
        return false;
    }
    /* Union the root lists and store in destination head */
    dest->head = union_heaps(dest, dest->head, src->head);
    /* Set src->head to NULL to avoid double-free of nodes */
    src->head = NULL;
    /* Free source heap structure only */
    free_heap(src);
    /* Return success */
    return true;
}

/* ================================================================
   FUNCTION: interactive_menu
   PURPOSE:
     Provide a user-driven interface for all heap operations including merge.
   ALGORITHM:
     1. Ask user for mode (min or max).
     2. Create main heap.
     3. LOOP:
        a. Show menu.
        b. Read choice.
        c. Switch:
           - Insert: read key and insert.
           - Find extreme: locate extreme and print.
           - Extract extreme: remove and print value.
           - Improve key: read old key, new key, find node, improve.
           - Delete key: read key, find node, delete.
           - Print: print heap.
           - Merge: build second heap (same mode), union into main.
           - Quit: break loop.
     4. Free main heap at end.
   ================================================================ */
 /* Provide interactive user menu for binomial heap operations */
static void interactive_menu(void) {
    /* Variable for user mode selection */
    int mode_choice;
    /* Prompt user to choose min or max heap */
    printf("Select heap mode: 1 = MIN-heap, 2 = MAX-heap: ");
    /* Read user mode choice */
    if (scanf("%d", &mode_choice) != 1) {
        /* Clear invalid input characters */
        while (getchar() != '\n');
        /* Default to min-heap mode */
        mode_choice = 1;
    }
    /* Determine if mode is min (true) or max (false) */
    bool is_min = (mode_choice != 2);
    /* Create the main binomial heap in chosen mode */
    BinomialHeap *heap = create_heap(is_min);
    /* Check creation success */
    if (!heap) {
        /* Abort if heap could not be created */
        return;
    }
    /* Inform user that heap was created and which type */
    printf("Created a %s binomial heap.\n", heap->is_min ? "MIN-heap" : "MAX-heap");
    /* Variable for storing menu choice each loop */
    int choice;
    /* Begin interactive loop */
    while (1) {
        /* Print a blank line for visual separation */
        printf("\n");
        /* Print menu header */
        printf("=== Binomial Heap Menu ===\n");
        /* Print option 1 (insert) */
        printf("1. Insert key\n");
        /* Print option 2 (find extreme) */
        printf("2. Find %s key\n", heap->is_min ? "minimum" : "maximum");
        /* Print option 3 (extract extreme) */
        printf("3. Extract %s key\n", heap->is_min ? "minimum" : "maximum");
        /* Print option 4 (improve key) */
        printf("4. %s a key (improve priority)\n", heap->is_min ? "Decrease" : "Increase");
        /* Print option 5 (delete key) */
        printf("5. Delete a key\n");
        /* Print option 6 (print heap) */
        printf("6. Print heap\n");
        /* Print option 7 (merge second heap) */
        printf("7. Merge another heap\n");
        /* Print option 8 (quit) */
        printf("8. Quit\n");
        /* Prompt user for numeric choice */
        printf("Enter choice: ");
        /* Attempt to read choice */
        if (scanf("%d", &choice) != 1) {
            /* Clear invalid input */
            while (getchar() != '\n');
            /* Continue to re-display menu */
            continue;
        }
        /* Handle insert option */
        if (choice == 1) {
            /* Variable to hold key input */
            int key;
            /* Prompt for key */
            printf("Enter key to insert: ");
            /* Read key value */
            if (scanf("%d", &key) != 1) {
                /* Clear invalid input */
                while (getchar() != '\n');
                /* Inform user of invalid entry */
                printf("Invalid key input.\n");
                /* Skip rest of iteration */
                continue;
            }
            /* Attempt insertion and provide feedback */
            if (insert_key(heap, key)) {
                /* Report success */
                printf("Inserted key %d.\n", key);
            } else {
                /* Report failure */
                printf("Insertion failed.\n");
            }
        }
        /* Handle find extreme option */
        else if (choice == 2) {
            /* Find pointer to extreme node */
            BinomialNode *ext = find_extreme_node(heap);
            /* If none found heap is empty */
            if (!ext) {
                /* Inform user of emptiness */
                printf("Heap is empty.\n");
            } else {
                /* Print extreme key */
                printf("%s key: %d\n", heap->is_min ? "Minimum" : "Maximum", ext->key);
            }
        }
        /* Handle extract extreme option */
        else if (choice == 3) {
            /* Variable to store extracted key */
            int ext_key;
            /* Attempt extraction */
            if (extract_extreme(heap, &ext_key)) {
                /* Report extracted key */
                printf("Extracted %s key: %d\n", heap->is_min ? "minimum" : "maximum", ext_key);
            } else {
                /* Report empty heap */
                printf("Heap is empty (cannot extract).\n");
            }
        }
        /* Handle improve key option */
        else if (choice == 4) {
            /* Variable for old key to find */
            int old_key;
            /* Variable for new improved key */
            int new_key;
            /* Prompt user for existing key */
            printf("Enter existing key to %s: ", heap->is_min ? "decrease" : "increase");
            /* Read old key */
            if (scanf("%d", &old_key) != 1) {
                /* Clear invalid input */
                while (getchar() != '\n');
                /* Inform user */
                printf("Invalid key input.\n");
                /* Continue loop */
                continue;
            }
            /* Prompt for new key value */
            printf("Enter new key (must be %s current): ",
                   heap->is_min ? "<= (smaller or equal to)" : ">= (greater or equal to)");
            /* Read new key value */
            if (scanf("%d", &new_key) != 1) {
                /* Clear invalid characters */
                while (getchar() != '\n');
                /* Inform user */
                printf("Invalid key input.\n");
                /* Continue loop */
                continue;
            }
            /* Find node with old key */
            BinomialNode *target = find_node_depth_first(heap->head, old_key);
            /* If not found inform user */
            if (!target) {
                /* Report missing key */
                printf("Key %d not found.\n", old_key);
            } else {
                /* Attempt improvement */
                if (improve_key(heap, target, new_key)) {
                    /* Report success */
                    printf("%s key from %d to %d.\n",
                           heap->is_min ? "Decreased" : "Increased", old_key, new_key);
                } else {
                    /* Report failure */
                    printf("Key improvement failed.\n");
                }
            }
        }
        /* Handle delete key option */
        else if (choice == 5) {
            /* Variable for key to delete */
            int del_key;
            /* Prompt for key */
            printf("Enter key to delete: ");
            /* Read key */
            if (scanf("%d", &del_key) != 1) {
                /* Clear invalid input */
                while (getchar() != '\n');
                /* Report invalid */
                printf("Invalid key input.\n");
                /* Continue loop */
                continue;
            }
            /* Find node with that key */
            BinomialNode *target = find_node_depth_first(heap->head, del_key);
            /* If not found report */
            if (!target) {
                /* Inform user key not found */
                printf("Key %d not found.\n", del_key);
            } else {
                /* Attempt deletion */
                if (delete_node(heap, target)) {
                    /* Report success */
                    printf("Deleted key %d.\n", del_key);
                } else {
                    /* Report failure */
                    printf("Delete operation failed.\n");
                }
            }
        }
        /* Handle print heap option */
        else if (choice == 6) {
            /* Call print function */
            print_heap(heap);
        }
        /* Handle merge option */
        else if (choice == 7) {
            /* Ask number of keys for second heap */
            int count;
            /* Prompt user for number of keys */
            printf("Enter number of keys in second heap to merge: ");
            /* Read count */
            if (scanf("%d", &count) != 1 || count < 0) {
                /* Clear invalid input */
                while (getchar() != '\n');
                /* Report invalid */
                printf("Invalid count.\n");
                /* Continue loop */
                continue;
            }
            /* Create second heap with same mode as main heap */
            BinomialHeap *h2 = create_heap(heap->is_min);
            /* Check creation success */
            if (!h2) {
                /* Report failing creation */
                printf("Failed to create second heap.\n");
                /* Continue menu */
                continue;
            }
            /* Loop to insert each key */
            for (int i = 0; i < count; i++) {
                /* Prompt for key i */
                printf("Enter key %d: ", i + 1);
                /* Variable for this key */
                int k;
                /* Read key value */
                if (scanf("%d", &k) != 1) {
                    /* Clear invalid input */
                    while (getchar() != '\n');
                    /* Report invalid key */
                    printf("Invalid key input (skipping remaining keys).\n");
                    /* Break out of insertion loop */
                    break;
                }
                /* Insert the key into second heap */
                if (!insert_key(h2, k)) {
                    /* Report failure to insert */
                    printf("Insertion failed for key %d.\n", k);
                }
            }
            /* Perform the merge of h2 into main heap */
            if (merge_into_heap(heap, h2)) {
                /* Report success */
                printf("Merged second heap successfully.\n");
            } else {
                /* Report failure */
                printf("Merge failed.\n");
                /* Free second heap if merge failed and not freed yet */
                free_heap(h2);
            }
        }
        /* Handle quit option */
        else if (choice == 8) {
            /* Inform user of exit */
            printf("Exiting...\n");
            /* Break out of loop */
            break;
        }
        /* Handle invalid menu choice */
        else {
            /* Inform user of invalid selection */
            printf("Invalid choice.\n");
        }
    }
    /* Free the main heap before exiting */
    free_heap(heap);
}

/* ================================================================
   FUNCTION: main
   PURPOSE:
     Entry point: show banner and start menu.
   ALGORITHM:
     1. Print banner.
     2. Call interactive_menu().
     3. Return 0.
   ================================================================ */
 /* Program entry point */
int main(void) {
    /* Print introductory banner for the program */
    printf("=== Binomial Heap (Min/Max) with Merge Demo ===\n");
    /* Run the interactive menu to manipulate the heap */
    interactive_menu();
    /* Return success exit status */
    return 0;
}

