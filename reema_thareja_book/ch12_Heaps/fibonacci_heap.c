/***************************************************************
 * Fibonacci Heap (Min or Max Mode) - Fully Commented Version
 * -------------------------------------------------------------
 * Features:
 *   - Choose MIN or MAX heap at runtime.
 *   - Insert key.
 *   - Find extreme (min in MIN mode, max in MAX mode).
 *   - Extract extreme.
 *   - Improve key (Decrease for MIN, Increase for MAX).
 *   - Delete key (improve to sentinel then extract).
 *   - Merge (union) with another heap of the same mode.
 *   - Linear DFS search (educational).
 *   - Structured print.
 *   - Complete memory cleanup.
 *
 * Structure Notes:
 *   We store a pointer named 'ext' (extreme root) instead of 'min'.
 *   For MIN mode: ext points to smallest key root.
 *   For MAX mode: ext points to largest key root.
 *
 * Complexity (Amortized):
 *   Insert:            O(1)
 *   Find Extreme:      O(1)
 *   Union:             O(1)
 *   Improve Key:       O(1)
 *   Extract Extreme:   O(log n)
 *   Delete:            O(log n)
 *
 * Comment Style:
 *   - ALGORITHM block above each function.
 *   - Plain English comment above EVERY SINGLE line of code.
 ***************************************************************/

 /* Include stdio for printf / scanf IO */
#include <stdio.h>
 /* Include stdlib for malloc, free, exit */
#include <stdlib.h>
 /* Include stdbool for bool, true, false */
#include <stdbool.h>
 /* Include limits for INT_MIN / INT_MAX sentinels */
#include <limits.h>
 /* Include math for log function (used in consolidation) */
#include <math.h>

/* ================================================================
   DATA STRUCTURES
   ------------------------------------------------
   FibNode:
     key      -> Integer priority/value.
     degree   -> Number of children (order).
     mark     -> For cascading cuts (true if lost a child).
     parent   -> Pointer to parent node (NULL if root).
     child    -> Pointer to ONE child (children form circular DLL).
     left     -> Left sibling in circular doubly linked list.
     right    -> Right sibling in circular doubly linked list.
   FibHeap:
     ext      -> Pointer to extreme node (min OR max based on mode).
     n        -> Total node count.
     is_min   -> true for MIN‑heap mode, false for MAX‑heap mode.
   ================================================================ */

 /* Define struct for Fibonacci heap node */
typedef struct FibNode {
    /* Store the key (priority value) */
    int key;
    /* Store number of child nodes (degree of tree) */
    int degree;
    /* Boolean: has this node lost a child since becoming a child? */
    bool mark;
    /* Pointer to parent node (NULL if root) */
    struct FibNode *parent;
    /* Pointer to one child (others reachable via siblings) */
    struct FibNode *child;
    /* Pointer to left sibling in circular list */
    struct FibNode *left;
    /* Pointer to right sibling in circular list */
    struct FibNode *right;
} FibNode;

 /* Define struct for Fibonacci heap */
typedef struct FibHeap {
    /* Pointer to extreme root (min if is_min, max if !is_min) */
    FibNode *ext;
    /* Total number of nodes currently in heap */
    int n;
    /* Mode flag: true = min-heap, false = max-heap */
    bool is_min;
} FibHeap;

/* ================================================================
   FUNCTION: heap_better
   PURPOSE:
     Compare two integer keys according to heap mode.
   ALGORITHM:
     1. If is_min is true -> return (a < b).
     2. Else (max mode)   -> return (a > b).
   ================================================================ */
 /* Return true if key 'a' is a better (more extreme) key than 'b' */
static bool heap_better(const FibHeap *heap, int a, int b) {
    /* If heap is in MIN mode choose smaller key as better */
    if (heap->is_min) {
        /* Return whether a is strictly less than b */
        return a < b;
    }
    /* Otherwise heap is in MAX mode choose larger key as better */
    return a > b;
}

/* ================================================================
   FUNCTION: create_node
   PURPOSE:
     Allocate and initialize a single Fibonacci heap node.
   ALGORITHM:
     1. malloc node.
     2. Set key.
     3. Set degree=0, mark=false.
     4. Set parent/child=NULL.
     5. Make left/right point to itself (1-node circular list).
     6. Return node (or NULL on failure).
   ================================================================ */
 /* Create a new Fibonacci heap node with provided key */
static FibNode *create_node(int key) {
    /* Allocate memory for node */
    FibNode *node = (FibNode *)malloc(sizeof(FibNode));
    /* Check allocation success */
    if (!node) {
        /* Inform user of failure */
        printf("Memory allocation failed for FibNode.\n");
        /* Return NULL to signal failure */
        return NULL;
    }
    /* Store the supplied key */
    node->key = key;
    /* Initialize degree to zero (no children yet) */
    node->degree = 0;
    /* Initialize mark to false (has not lost children) */
    node->mark = false;
    /* Set parent pointer to NULL (root initially) */
    node->parent = NULL;
    /* Set child pointer to NULL (no child yet) */
    node->child = NULL;
    /* Set left pointer to itself (circular list single node) */
    node->left = node;
    /* Set right pointer to itself */
    node->right = node;
    /* Return pointer to initialized node */
    return node;
}

/* ================================================================
   FUNCTION: create_heap
   PURPOSE:
     Allocate and initialize an empty Fibonacci heap in chosen mode.
   ALGORITHM:
     1. malloc heap.
     2. Set ext=NULL.
     3. Set n=0.
     4. Set mode flag is_min.
     5. Return heap pointer (or NULL on failure).
   ================================================================ */
 /* Create a new Fibonacci heap selecting min or max mode */
static FibHeap *create_heap(bool is_min) {
    /* Allocate memory for heap structure */
    FibHeap *heap = (FibHeap *)malloc(sizeof(FibHeap));
    /* Check allocation success */
    if (!heap) {
        /* Inform user of failure */
        printf("Memory allocation failed for FibHeap.\n");
        /* Return NULL to indicate failure */
        return NULL;
    }
    /* Initialize extreme pointer to NULL (empty) */
    heap->ext = NULL;
    /* Initialize node count to zero */
    heap->n = 0;
    /* Store the mode flag */
    heap->is_min = is_min;
    /* Return heap pointer */
    return heap;
}

/* ================================================================
   FUNCTION: add_root
   PURPOSE:
     Insert a root node into the circular root list and update extreme.
   ALGORITHM:
     1. If heap empty -> node becomes only root (self circle) and ext=node.
     2. Else splice node next to ext (before ext).
     3. If node key is better than ext key -> update ext.
   ================================================================ */
 /* Add a node to the root list and update extreme pointer */
static void add_root(FibHeap *heap, FibNode *node) {
    /* If there is currently no extreme (heap empty) */
    if (!heap->ext) {
        /* Form single-node circular list (already self-linked, kept for clarity) */
        node->left = node;
        node->right = node;
        /* Set heap extreme pointer to this node */
        heap->ext = node;
    } else {
        /* Insert node to the immediate left of current extreme */
        node->left = heap->ext->left;
        node->right = heap->ext;
        heap->ext->left->right = node;
        heap->ext->left = node;
        /* If new node outranks current extreme update extreme pointer */
        if (heap_better(heap, node->key, heap->ext->key)) {
            heap->ext = node;
        }
    }
}

/* ================================================================
   FUNCTION: fib_union
   PURPOSE:
     Merge two heaps of the same mode into one by concatenating root lists.
   ALGORITHM:
     1. Handle NULL cases (return other heap).
     2. If one empty -> return the other.
     3. Concatenate circular lists:
        - Connect h1.ext left/right with h2.ext left/right.
     4. Update extreme pointer comparing h2.ext with h1.ext.
     5. Add node counts.
     6. Return h1 (merged).
   NOTE:
     Caller must ensure both heaps have same mode.
   ================================================================ */
 /* Union two Fibonacci heaps with same mode */
static FibHeap *fib_union(FibHeap *h1, FibHeap *h2) {
    /* If first heap is NULL return second */
    if (!h1) return h2;
    /* If second heap is NULL return first */
    if (!h2) return h1;
    /* If first heap has no nodes adopt second's list */
    if (!h1->ext) {
        h1->ext = h2->ext;
        h1->n = h2->n;
        return h1;
    }
    /* If second heap empty nothing to merge */
    if (!h2->ext) {
        return h1;
    }
    /* Splice the two circular root lists */
    FibNode *h1Left = h1->ext->left;
    FibNode *h2Left = h2->ext->left;
    h1Left->right = h2->ext;
    h2->ext->left = h1Left;
    h2Left->right = h1->ext;
    h1->ext->left = h2Left;
    /* Update extreme if h2's extreme is better */
    if (heap_better(h1, h2->ext->key, h1->ext->key)) {
        h1->ext = h2->ext;
    }
    /* Add node counts */
    h1->n += h2->n;
    /* Return merged heap */
    return h1;
}

/* ================================================================
   FUNCTION: insert_key
   PURPOSE:
     Insert a key into heap (O(1) amortized).
   ALGORITHM:
     1. Create node.
     2. Add root.
     3. Increment n.
     4. Return success/failure.
   ================================================================ */
 /* Insert a new key into the Fibonacci heap */
static bool insert_key(FibHeap *heap, int key) {
    /* Reject if heap pointer invalid */
    if (!heap) return false;
    /* Create node with key */
    FibNode *node = create_node(key);
    /* If allocation failed return false */
    if (!node) return false;
    /* Add node to root list */
    add_root(heap, node);
    /* Increment node count */
    heap->n++;
    /* Return success */
    return true;
}

/* ================================================================
   FUNCTION: find_extreme
   PURPOSE:
     Return pointer to extreme node (min or max depending on mode).
   ALGORITHM:
     1. Return heap->ext (may be NULL).
   ================================================================ */
 /* Return extreme node pointer (NULL if empty) */
static FibNode *find_extreme(FibHeap *heap) {
    /* If invalid heap return NULL */
    if (!heap) return NULL;
    /* Return extreme pointer (min or max) */
    return heap->ext;
}

/* ================================================================
   FUNCTION: fib_link
   PURPOSE:
     Make node y a child of node x (used when merging equal degrees).
   ALGORITHM:
     1. Remove y from root list.
     2. Set y->parent = x.
     3. If x has no child list -> y forms single-node child list.
        Else splice y into child circular list.
     4. Increase x->degree.
     5. Set y->mark = false.
   PRECONDITION:
     x key is better than y key.
   ================================================================ */
 /* Link tree rooted at y underneath x (x becomes parent) */
static void fib_link(FibHeap *heap, FibNode *y, FibNode *x) {
    /* Detach y from its circular list neighbors */
    y->left->right = y->right;
    y->right->left = y->left;
    /* Set parent pointer */
    y->parent = x;
    /* If x currently has no children */
    if (!x->child) {
        /* y becomes only child (self circular) */
        y->left = y;
        y->right = y;
        x->child = y;
    } else {
        /* Splice y into existing child list next to x->child */
        y->left = x->child->left;
        y->right = x->child;
        x->child->left->right = y;
        x->child->left = y;
    }
    /* Increase x's degree to reflect one more child */
    x->degree++;
    /* Reset y's mark because it is newly linked */
    y->mark = false;
    /* Suppress unused heap warning (not using heap directly here) */
    (void)heap;
}

/* ================================================================
   FUNCTION: consolidate
   PURPOSE:
     After extract, combine roots of same degree ensuring at most one
     root per degree. Maintains correct extreme pointer.
   ALGORITHM:
     1. Compute array size ~ log2(n)+2.
     2. Initialize array A with NULL.
     3. Iterate over each root in root list:
        a. Isolate root w into x.
        b. While A[x.degree] non-NULL:
            i.   y = A[d].
            ii.  If y key better than x key swap (so x best).
            iii. fib_link(y, x).
            iv.  A[d] = NULL.
            v.   d = x.degree.
        c. Place x into A[x.degree].
     4. Rebuild root list from array entries updating extreme pointer.
   ================================================================ */
 /* Consolidate root list so each degree appears at most once */
static void consolidate(FibHeap *heap) {
    /* If heap invalid or empty nothing to do */
    if (!heap || !heap->ext) return;
    /* Calculate maximum possible degree bound (log2(n)) plus cushion */
    int max_degree = (int)(log((double)heap->n) / log(2.0)) + 5;
    /* Allocate degree table initialized to NULL */
    FibNode **A = (FibNode **)calloc((size_t)max_degree, sizeof(FibNode *));
    /* If allocation fails print warning and return (heap remains valid) */
    if (!A) {
        printf("Warning: consolidation skipped (memory failure).\n");
        return;
    }
    /* Remember starting root for traversal */
    FibNode *start = heap->ext;
    /* Current traversal pointer */
    FibNode *w = start;
    /* Boolean for circular traversal first pass */
    bool first_pass = true;
    /* Traverse all roots once */
    while (first_pass || w != start) {
        /* After first root processed mark first_pass false */
        first_pass = false;
        /* Store next root before detaching */
        FibNode *next = w->right;
        /* Detach w from root list (isolate) */
        w->left->right = w->right;
        w->right->left = w->left;
        w->left = w->right = w;
        /* Work with x pointer referencing w */
        FibNode *x = w;
        /* Current degree of x */
        int d = x->degree;
        /* While a root of same degree already recorded */
        while (A[d]) {
            /* Retrieve existing root y of same degree */
            FibNode *y = A[d];
            /* Ensure x holds the better (more extreme) key root */
            if (heap_better(heap, y->key, x->key)) {
                FibNode *temp = x;
                x = y;
                y = temp;
            }
            /* Link y beneath x */
            fib_link(heap, y, x);
            /* Clear array slot for this degree */
            A[d] = NULL;
            /* Update d to x's new degree after link */
            d = x->degree;
        }
        /* Place x in array slot for its final degree */
        A[d] = x;
        /* Advance w to next original root */
        w = next;
    }
    /* Reset extreme pointer to NULL before rebuilding root list */
    heap->ext = NULL;
    /* Iterate over array of degree buckets */
    for (int i = 0; i < max_degree; i++) {
        /* If bucket not empty attach tree back to root list */
        if (A[i]) {
            /* Remove parent pointer (should be NULL already) */
            A[i]->parent = NULL;
            /* If heap has no roots yet set extreme to this */
            if (!heap->ext) {
                A[i]->left = A[i];
                A[i]->right = A[i];
                heap->ext = A[i];
            } else {
                /* Insert A[i] into circular root list */
                A[i]->left = heap->ext->left;
                A[i]->right = heap->ext;
                heap->ext->left->right = A[i];
                heap->ext->left = A[i];
                /* Update extreme if this root outranks current */
                if (heap_better(heap, A[i]->key, heap->ext->key)) {
                    heap->ext = A[i];
                }
            }
        }
    }
    /* Free the helper array */
    free(A);
}

/* ================================================================
   FUNCTION: extract_extreme
   PURPOSE:
     Remove and return extreme root (min or max).
   ALGORITHM:
     1. Let z = heap->ext.
     2. If z has children: for each child c add to root list (parent=NULL).
     3. Remove z from root list.
     4. If z was only node -> ext=NULL, else set ext=z->right and consolidate().
     5. Decrement n.
     6. Return z->key (free z).
   ================================================================ */
 /* Extract the extreme key (min or max depending on mode) */
static bool extract_extreme(FibHeap *heap, int *out_key) {
    /* Fail if heap invalid or empty */
    if (!heap || !heap->ext) return false;
    /* Store pointer to extreme node */
    FibNode *z = heap->ext;
    /* If extreme node has children we must add them to root list */
    if (z->child) {
        /* Start at one child */
        FibNode *c = z->child;
        /* Keep starting child pointer for circular loop */
        FibNode *cstart = c;
        /* Set first pass flag for circular iteration */
        bool first_pass = true;
        /* Iterate over all children */
        while (first_pass || c != cstart) {
            /* After first iteration set flag false */
            first_pass = false;
            /* Store next child (since we re-link c) */
            FibNode *next = c->right;
            /* Detach c from child sibling ring */
            c->left->right = c->right;
            c->right->left = c->left;
            /* Make c a singleton circular list */
            c->left = c;
            c->right = c;
            /* Reset parent pointer since c becomes root */
            c->parent = NULL;
            /* Insert c into root list (reuse add_root logic inline) */
            c->left = heap->ext->left;
            c->right = heap->ext;
            heap->ext->left->right = c;
            heap->ext->left = c;
            /* Update extreme pointer if necessary */
            if (heap_better(heap, c->key, heap->ext->key)) {
                heap->ext = c;
            }
            /* Advance to saved next child */
            c = next;
        }
    }
    /* Remove z from root list */
    z->left->right = z->right;
    z->right->left = z->left;
    /* If z was the only node in the heap */
    if (z == z->right) {
        /* Heap becomes empty */
        heap->ext = NULL;
    } else {
        /* Temporarily move extreme pointer to a neighbor */
        heap->ext = z->right;
        /* Consolidate to restore degree uniqueness */
        consolidate(heap);
    }
    /* Decrement node count */
    heap->n--;
    /* Output extracted key if caller requested */
    if (out_key) *out_key = z->key;
    /* Free extracted node */
    free(z);
    /* Return success */
    return true;
}

/* ================================================================
   FUNCTION: cut
   PURPOSE:
     Remove node x from parent y's child list and add x to root list.
   ALGORITHM:
     1. If x only child -> y->child=NULL else fix siblings and y->child.
     2. y->degree--.
     3. Insert x into root list.
     4. x->parent=NULL, x->mark=false.
   ================================================================ */
 /* Cut child x from parent y and move x to root list */
static void cut(FibHeap *heap, FibNode *x, FibNode *y) {
    /* If x is only child of y */
    if (x->right == x) {
        /* Remove child pointer from y */
        y->child = NULL;
    } else {
        /* Detach x from circular child list */
        x->left->right = x->right;
        x->right->left = x->left;
        /* If y->child pointed to x shift to another child */
        if (y->child == x) {
            y->child = x->right;
        }
    }
    /* Decrement parent's degree */
    y->degree--;
    /* Insert x into root list (similar to add_root) */
    x->left = heap->ext->left;
    x->right = heap->ext;
    heap->ext->left->right = x;
    heap->ext->left = x;
    /* Reset x's parent to NULL (now root) */
    x->parent = NULL;
    /* Reset mark because it just became a root */
    x->mark = false;
}

/* ================================================================
   FUNCTION: cascading_cut
   PURPOSE:
     Perform cascading cuts up the ancestor chain:
     - If parent not marked, mark and stop.
     - Else cut parent and continue upward.
   ALGORITHM:
     1. Let z = x->parent.
     2. While z != NULL:
        a. If x->mark == false: set x->mark=true; break.
        b. Else cut(x,z); x=z; z=z->parent.
   ================================================================ */
 /* Recursively apply cascading cuts starting from x upward */
static void cascading_cut(FibHeap *heap, FibNode *x) {
    /* Get parent pointer */
    FibNode *z = x->parent;
    /* Traverse upward while parent exists */
    while (z) {
        /* If current node not previously marked */
        if (!x->mark) {
            /* Mark it and stop cascading */
            x->mark = true;
            /* Break out of loop */
            break;
        }
        /* Otherwise already marked so cut it from its parent */
        cut(heap, x, z);
        /* Move x pointer up to former parent */
        x = z;
        /* Move z to next ancestor */
        z = x->parent;
    }
}

/* ================================================================
   FUNCTION: improve_key
   PURPOSE:
     Improve node's key toward the heap extreme:
       - MIN mode: new_key must be <= old key (decrease).
       - MAX mode: new_key must be >= old key (increase).
     Then cascade cuts if necessary and update extreme pointer.
   ALGORITHM:
     1. Validate direction (reject if not improving).
     2. Set x->key = new_key.
     3. Let y = x->parent.
     4. If y exists and x now outranks y:
          cut(x,y); cascading_cut(y).
     5. If x outranks heap->ext update heap->ext.
   ================================================================ */
 /* Improve a node's key (decrease in MIN / increase in MAX mode) */
static bool improve_key(FibHeap *heap, FibNode *x, int new_key) {
    /* Fail if inputs invalid */
    if (!heap || !x) return false;
    /* Check direction validity for MIN mode */
    if (heap->is_min && new_key > x->key) {
        printf("New key must be <= current key in MIN mode.\n");
        return false;
    }
    /* Check direction validity for MAX mode */
    if (!heap->is_min && new_key < x->key) {
        printf("New key must be >= current key in MAX mode.\n");
        return false;
    }
    /* Assign improved key */
    x->key = new_key;
    /* Get parent reference */
    FibNode *y = x->parent;
    /* If parent exists and x violates ordering by being better */
    if (y && heap_better(heap, x->key, y->key)) {
        /* Cut x from its parent */
        cut(heap, x, y);
        /* Cascade upward if necessary */
        cascading_cut(heap, y);
    }
    /* If x outranks current extreme update extreme pointer */
    if (heap_better(heap, x->key, heap->ext->key)) {
        heap->ext = x;
    }
    /* Return success */
    return true;
}

/* ================================================================
   FUNCTION: delete_key
   PURPOSE:
     Delete node x by first improving it to sentinel extreme then extracting.
     - MIN mode uses INT_MIN sentinel.
     - MAX mode uses INT_MAX sentinel.
   ALGORITHM:
     1. Determine sentinel (INT_MIN or INT_MAX).
     2. Call improve_key(x, sentinel).
     3. Call extract_extreme.
     4. Return result.
   ================================================================ */
 /* Delete a node from the heap using improve + extract */
static bool delete_key(FibHeap *heap, FibNode *x) {
    /* Validate input pointers */
    if (!heap || !x) return false;
    /* Select sentinel extreme value based on mode */
    int sentinel = heap->is_min ? INT_MIN : INT_MAX;
    /* Improve key to sentinel */
    if (!improve_key(heap, x, sentinel)) return false;
    /* Extract the extreme (which should now be x) */
    int dummy;
    /* Return result of extraction */
    return extract_extreme(heap, &dummy);
}

/* ================================================================
   FUNCTION: search_dfs
   PURPOSE:
     Linear DFS search for first node matching key (educational only).
   ALGORITHM:
     1. If root NULL return NULL.
     2. Traverse circular list:
        a. If node key == key return node.
        b. Recurse into child; if found return.
     3. Return NULL if not located.
   ================================================================ */
 /* Depth-first search for a key starting at a circular root list */
static FibNode *search_dfs(FibNode *root, int key) {
    /* Return NULL if root is NULL */
    if (!root) return NULL;
    /* Save starting pointer for circular traversal */
    FibNode *start = root;
    /* Current pointer for iteration */
    FibNode *cur = start;
    /* Track first pass of loop */
    bool first_pass = true;
    /* Iterate over circular list */
    while (first_pass || cur != start) {
        /* After first loop set flag false */
        first_pass = false;
        /* If key matches return current node */
        if (cur->key == key) return cur;
        /* If node has children search recursively */
        if (cur->child) {
            FibNode *found = search_dfs(cur->child, key);
            if (found) return found;
        }
        /* Advance to next sibling */
        cur = cur->right;
    }
    /* Return NULL if not found */
    return NULL;
}

/* ================================================================
   FUNCTION: print_recursive
   PURPOSE:
     Print a circular list of nodes (roots or siblings) and their subtrees.
   ALGORITHM:
     1. If root NULL return.
     2. For each node in circular list:
        a. Print indent spaces.
        b. Print key, degree, mark.
        c. Recurse into child with level+1.
   ================================================================ */
 /* Recursively print a circular list of nodes with indentation */
static void print_recursive(FibNode *root, int level) {
    /* Return early if list empty */
    if (!root) return;
    /* Remember start of circular list */
    FibNode *start = root;
    /* Set current node pointer */
    FibNode *cur = start;
    /* First pass flag for circular traversal */
    bool first_pass = true;
    /* Loop over each node exactly once */
    while (first_pass || cur != start) {
        /* Mark that first iteration is done */
        first_pass = false;
        /* Print indentation (two spaces per level) */
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        /* Print node details: key, degree, mark flag */
        printf("Key=%d (deg=%d mark=%c)\n", cur->key, cur->degree, cur->mark ? 'Y' : 'N');
        /* Recurse into child list if exists */
        if (cur->child) {
            print_recursive(cur->child, level + 1);
        }
        /* Move to next node in circular list */
        cur = cur->right;
    }
}

/* ================================================================
   FUNCTION: print_heap
   PURPOSE:
     Display entire heap structure from root list.
   ALGORITHM:
     1. If heap empty print message.
     2. Print summary (mode, nodes, extreme key).
     3. Call print_recursive(heap->ext, 0).
   ================================================================ */
 /* Print complete heap information and structure */
static void print_heap(FibHeap *heap) {
    /* If heap invalid or empty show message */
    if (!heap || !heap->ext) {
        printf("[Heap is empty]\n");
        return;
    }
    /* Print summary header */
    printf("%s-Heap | Nodes=%d | Extreme=%d\n",
           heap->is_min ? "MIN" : "MAX", heap->n, heap->ext->key);
    /* Print all roots and subtrees */
    print_recursive(heap->ext, 0);
}

/* ================================================================
   FUNCTION: free_subtree
   PURPOSE:
     Free all nodes in a circular list and their descendants.
   ALGORITHM:
     1. If root NULL return.
     2. Traverse circular list:
        a. Save next (cur->right).
        b. Recurse free on child.
        c. Free cur.
        d. Continue until back at start.
   ================================================================ */
 /* Recursively free circular list of nodes (and their children) */
static void free_subtree(FibNode *root) {
    /* If list is empty nothing to free */
    if (!root) return;
    /* Save starting pointer */
    FibNode *start = root;
    /* Current node pointer */
    FibNode *cur = start;
    /* Track first iteration */
    bool first_pass = true;
    /* Traverse entire ring */
    while (first_pass || cur != start) {
        /* Mark first iteration done */
        first_pass = false;
        /* Save next pointer before freeing current */
        FibNode *next = cur->right;
        /* If current has children free them recursively */
        if (cur->child) {
            free_subtree(cur->child);
        }
        /* Free current node */
        free(cur);
        /* Move to next node */
        cur = next;
    }
}

/* ================================================================
   FUNCTION: free_heap
   PURPOSE:
     Free all nodes and the heap structure.
   ALGORITHM:
     1. If heap NULL return.
     2. If ext non-NULL free_subtree(ext).
     3. Free heap struct.
   ================================================================ */
 /* Free entire Fibonacci heap including all nodes */
static void free_heap(FibHeap *heap) {
    /* If heap pointer invalid nothing to do */
    if (!heap) return;
    /* If heap not empty free its root ring */
    if (heap->ext) {
        free_subtree(heap->ext);
    }
    /* Free heap structure itself */
    free(heap);
}

/* ================================================================
   FUNCTION: merge_into
   PURPOSE:
     Merge (union) second heap into first if modes match.
   ALGORITHM:
     1. Verify both heaps non-NULL and same mode.
     2. fib_union(dest, src).
     3. Set src->ext=NULL (avoid accidental double free if caller frees).
   ================================================================ */
 /* Merge src heap into dest heap (same mode required) */
static bool merge_into(FibHeap *dest, FibHeap *src) {
    /* Reject null heaps */
    if (!dest || !src) return false;
    /* Reject different modes */
    if (dest->is_min != src->is_min) {
        printf("Cannot merge heaps of different modes.\n");
        return false;
    }
    /* Perform union */
    fib_union(dest, src);
    /* Reset src extreme pointer for safety */
    src->ext = NULL;
    /* Return success */
    return true;
}

/* ================================================================
   FUNCTION: interactive_menu
   PURPOSE:
     Let user perform all supported operations on a single heap.
   ALGORITHM:
     1. Ask for mode (1=MIN, 2=MAX).
     2. Create primary heap.
     3. LOOP:
        a. Display menu.
        b. Read choice.
        c. Execute matching operation.
        d. Break on quit.
     4. Free heap before exit.
   ================================================================ */
 /* Provide an interactive textual menu for the Fibonacci heap */
static void interactive_menu(void) {
    /* Declare variable for mode selection */
    int mode_choice;
    /* Prompt user to choose heap mode */
    printf("Select heap mode (1 = MIN-heap, 2 = MAX-heap): ");
    /* Read user input */
    if (scanf("%d", &mode_choice) != 1) {
        /* Clear invalid input */
        while (getchar() != '\n');
        /* Default to MIN-heap */
        mode_choice = 1;
    }
    /* Determine boolean flag for MIN mode */
    bool is_min = (mode_choice != 2);
    /* Create primary heap with selected mode */
    FibHeap *heap = create_heap(is_min);
    /* Check for creation failure */
    if (!heap) {
        /* Abort if heap could not be created */
        return;
    }
    /* Print confirmation of mode */
    printf("Created a %s Fibonacci heap.\n", heap->is_min ? "MIN" : "MAX");
    /* Declare variable to store menu choice */
    int choice;
    /* Begin interactive loop */
    while (1) {
        /* Print blank line for readability */
        printf("\n");
        /* Print menu header */
        printf("=== Fibonacci %s-Heap Menu ===\n", heap->is_min ? "MIN" : "MAX");
        /* Print list of operations */
        printf("1. Insert key\n");
        printf("2. Find %s key\n", heap->is_min ? "minimum" : "maximum");
        printf("3. Extract %s key\n", heap->is_min ? "minimum" : "maximum");
        printf("4. %s a key (improve)\n", heap->is_min ? "Decrease" : "Increase");
        printf("5. Delete a key\n");
        printf("6. Search for a key\n");
        printf("7. Print heap\n");
        printf("8. Merge another heap\n");
        printf("9. Quit\n");
        /* Prompt for user selection */
        printf("Enter choice: ");
        /* Attempt to read integer choice */
        if (scanf("%d", &choice) != 1) {
            /* Clear invalid input */
            while (getchar() != '\n');
            /* Continue loop */
            continue;
        }
        /* Handle insertion */
        if (choice == 1) {
            int key;
            printf("Enter key to insert: ");
            if (scanf("%d", &key) != 1) {
                while (getchar() != '\n');
                printf("Invalid key.\n");
                continue;
            }
            if (insert_key(heap, key)) {
                printf("Inserted key %d.\n", key);
            } else {
                printf("Insertion failed.\n");
            }
        }
        /* Handle find extreme */
        else if (choice == 2) {
            FibNode *ext = find_extreme(heap);
            if (ext) {
                printf("Extreme (%s) key: %d\n",
                       heap->is_min ? "min" : "max", ext->key);
            } else {
                printf("Heap is empty.\n");
            }
        }
        /* Handle extract extreme */
        else if (choice == 3) {
            int k;
            if (extract_extreme(heap, &k)) {
                printf("Extracted %s key: %d\n",
                       heap->is_min ? "minimum" : "maximum", k);
            } else {
                printf("Heap is empty (nothing extracted).\n");
            }
        }
        /* Handle improve key (decrease for min / increase for max) */
        else if (choice == 4) {
            int old_key, new_key;
            printf("Enter existing key to %s: ", heap->is_min ? "decrease" : "increase");
            if (scanf("%d", &old_key) != 1) {
                while (getchar() != '\n');
                printf("Invalid key.\n");
                continue;
            }
            printf("Enter new key (%s %d): ",
                   heap->is_min ? "<= current" : ">= current", old_key);
            if (scanf("%d", &new_key) != 1) {
                while (getchar() != '\n');
                printf("Invalid key.\n");
                continue;
            }
            FibNode *node = search_dfs(heap->ext, old_key);
            if (!node) {
                printf("Key %d not found.\n", old_key);
            } else {
                if (improve_key(heap, node, new_key)) {
                    printf("%s key from %d to %d.\n",
                           heap->is_min ? "Decreased" : "Increased", old_key, new_key);
                } else {
                    printf("Key improvement failed.\n");
                }
            }
        }
        /* Handle delete key */
        else if (choice == 5) {
            int del_key;
            printf("Enter key to delete: ");
            if (scanf("%d", &del_key) != 1) {
                while (getchar() != '\n');
                printf("Invalid key.\n");
                continue;
            }
            FibNode *node = search_dfs(heap->ext, del_key);
            if (!node) {
                printf("Key %d not found.\n", del_key);
            } else {
                if (delete_key(heap, node)) {
                    printf("Deleted key %d.\n", del_key);
                } else {
                    printf("Delete failed.\n");
                }
            }
        }
        /* Handle search */
        else if (choice == 6) {
            int s_key;
            printf("Enter key to search: ");
            if (scanf("%d", &s_key) != 1) {
                while (getchar() != '\n');
                printf("Invalid key.\n");
                continue;
            }
            FibNode *found = search_dfs(heap->ext, s_key);
            if (found) {
                printf("Key %d FOUND.\n", s_key);
            } else {
                printf("Key %d NOT found.\n", s_key);
            }
        }
        /* Handle print */
        else if (choice == 7) {
            print_heap(heap);
        }
        /* Handle merge */
        else if (choice == 8) {
            int count;
            printf("Enter number of keys in other heap: ");
            if (scanf("%d", &count) != 1 || count < 0) {
                while (getchar() != '\n');
                printf("Invalid count.\n");
                continue;
            }
            FibHeap *other = create_heap(heap->is_min);
            if (!other) {
                printf("Could not create other heap.\n");
                continue;
            }
            for (int i = 0; i < count; i++) {
                int k;
                printf("Enter key %d: ", i + 1);
                if (scanf("%d", &k) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid input; stopping further inserts.\n");
                    break;
                }
                if (!insert_key(other, k)) {
                    printf("Failed to insert %d into other heap.\n", k);
                }
            }
            if (merge_into(heap, other)) {
                printf("Merged heaps. New total nodes: %d\n", heap->n);
            } else {
                printf("Merge failed.\n");
            }
            free_heap(other);
        }
        /* Handle quit */
        else if (choice == 9) {
            printf("Exiting...\n");
            break;
        }
        /* Handle invalid choice */
        else {
            printf("Invalid choice.\n");
        }
    }
    /* Free main heap after loop */
    free_heap(heap);
}

/* ================================================================
   FUNCTION: main
   PURPOSE:
     Entry point: print banner and invoke interactive menu.
   ALGORITHM:
     1. Print introductory banner.
     2. Call interactive_menu().
     3. Return 0.
   ================================================================ */
 /* Program entry point */
int main(void) {
    /* Print a descriptive banner for user */
    printf("=== Fibonacci Heap (Min / Max Mode) Demo ===\n");
    /* Launch interactive menu loop */
    interactive_menu();
    /* Return success status code */
    return 0;
}

