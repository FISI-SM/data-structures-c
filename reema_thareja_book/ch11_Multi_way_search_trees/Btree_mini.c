// Include the standard I/O header for printf and related functions.
#include <stdio.h>
// Include <stdbool.h> so we can use the bool / true / false types in C.
#include <stdbool.h>
// Include <stdlib.h> for malloc, free, and EXIT_* macros.
#include <stdlib.h>

// -----------------------------------------------------------------------------
// Define the **minimum degree** of the B-tree (often called 't' in textbooks).
// Rules for a B-tree node given min_degree = t:
//   - Max keys in a node = 2*t - 1
//   - Min keys in a *non-root* node = t - 1
//   - Max children = 2*t
//   - Min children in a *non-root* internal node = t
// -----------------------------------------------------------------------------
#define MIN_DEGREE 3

// -----------------------------------------------------------------------------
// Define the BTreeNode structure: represents a single node in the B-tree.
// -----------------------------------------------------------------------------
typedef struct BTreeNode {
    // Pointer to dynamic array of keys (size = 2*t - 1).
    int *keys;
    // Pointer to dynamic array of child pointers (size = 2*t).
    struct BTreeNode **children;
    // Current number of keys actually stored in this node.
    int num_keys;
    // True if this node is a leaf (has no children).
    bool is_leaf;
    // Store the min_degree (t) in each node for convenience in functions.
    int min_degree;
} BTreeNode;

// -----------------------------------------------------------------------------
// Define the BTree structure: holds global tree info (root + min_degree).
// -----------------------------------------------------------------------------
typedef struct BTree {
    // Pointer to the root node (NULL when tree empty).
    BTreeNode *root;
    // Global minimum degree (t) for the entire tree.
    int min_degree;
} BTree;

// ============================================================================
// create_node(min_degree, is_leaf)
// Create and initialize a single B-tree node (leaf or internal).
// Returns pointer to node, or NULL on allocation failure.
// ============================================================================
BTreeNode *create_node(int min_degree, bool is_leaf) {
    // Allocate memory for the node structure itself.
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    // Check allocation success.
    if (!node) {
        // Report allocation failure to user.
        printf("Memory allocation failed for node\n");
        // Return NULL so caller can handle the error.
        return NULL;
    }

    // Record this node's min_degree (t) for size calculations.
    node->min_degree = min_degree;
    // Record whether this node is a leaf.
    node->is_leaf = is_leaf;
    // Start with 0 keys stored.
    node->num_keys = 0;

    // Allocate the keys array: capacity = 2*t - 1 keys.
    node->keys = (int *)malloc((2 * min_degree - 1) * sizeof(int));
    // Check allocation success for keys.
    if (!node->keys) {
        // Report allocation failure.
        printf("Memory allocation failed for keys\n");
        // Free node struct before returning (avoid leak).
        free(node);
        // Return NULL to caller.
        return NULL;
    }

    // Allocate the children pointer array: capacity = 2*t child pointers.
    node->children = (BTreeNode **)malloc((2 * min_degree) * sizeof(BTreeNode *));
    // Check allocation success for children pointers.
    if (!node->children) {
        // Report allocation failure.
        printf("Memory allocation failed for children\n");
        // Free previously allocated keys array.
        free(node->keys);
        // Free node struct.
        free(node);
        // Return NULL to caller.
        return NULL;
    }

    // Initialize each child pointer slot to NULL (safe starting state).
    for (int i = 0; i < 2 * min_degree; i++) {
        node->children[i] = NULL;
    }

    // Return the fully initialized node.
    return node;
}

// ============================================================================
// create_btree(min_degree)
// Allocate and initialize an empty B-tree wrapper struct.
// Returns pointer to tree, or NULL on allocation failure.
// ============================================================================
BTree *create_btree(int min_degree) {
    // Allocate memory for the BTree wrapper struct.
    BTree *btree = (BTree *)malloc(sizeof(BTree));
    // Check allocation success.
    if (!btree) {
        // Report error to user.
        printf("Memory allocation failed for B-tree\n");
        // Return NULL to signal failure.
        return NULL;
    }

    // Record min_degree for the entire tree.
    btree->min_degree = min_degree;
    // Tree starts empty: no root node yet.
    btree->root = NULL;

    // Return the newly created empty B-tree.
    return btree;
}

// ============================================================================
// search(node, key)
// Search for a key in the subtree rooted at 'node'.
// Returns pointer to the node containing the key, or NULL if not found.
// Standard B-tree search based on CLRS algorithm.
// ============================================================================
BTreeNode *search(BTreeNode *node, int key) {
    // If subtree empty (node NULL), key not found.
    if (node == NULL)
        return NULL;

    // Start scan index at 0.
    int i = 0;
    // Move right through keys while searched key is greater.
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }

    // If we stopped within range and keys[i] == key, found!
    if (i < node->num_keys && key == node->keys[i])
        return node;

    // If this node is a leaf, key cannot be deeper → not found.
    if (node->is_leaf)
        return NULL;

    // Recurse into appropriate child subtree.
    return search(node->children[i], key);
}

// ============================================================================
// split_child(parent, index, full_child)
// Split a full child node of 'parent' located at child slot 'index'.
// Precondition: full_child has 2*t - 1 keys (is full).
// After split: full_child keeps t-1 keys; new_child gets t-1 keys;
//              median key (at t-1 index) moves up into parent.
// ============================================================================
void split_child(BTreeNode *parent, int index, BTreeNode *full_child) {
    // Get the min_degree (t) from the full child (all nodes store t).
    int t = full_child->min_degree;

    // Allocate a new node of the same type (leaf-ness matches full_child).
    BTreeNode *new_child = create_node(t, full_child->is_leaf);
    // Set the number of keys in new_child: it will receive t-1 keys.
    new_child->num_keys = t - 1;

    // Copy the top t-1 keys from full_child into new_child.
    for (int i = 0; i < t - 1; i++) {
        new_child->keys[i] = full_child->keys[i + t];
    }

    // If full_child is not a leaf, we must also move the top t child pointers.
    if (!full_child->is_leaf) {
        for (int i = 0; i < t; i++) {
            new_child->children[i] = full_child->children[i + t];
        }
    }

    // Reduce the key count of full_child: it now keeps only t-1 keys.
    full_child->num_keys = t - 1;

    // Shift parent's children pointers right to open a slot after 'index'.
    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    // Link new_child into the parent's child array at index+1.
    parent->children[index + 1] = new_child;

    // Shift parent's keys right to open a slot at 'index' for promoted key.
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    // Promote full_child's median key (at t-1) into the parent.
    parent->keys[index] = full_child->keys[t - 1];

    // Increase parent's key count: it gained one key.
    parent->num_keys++;
}

// ============================================================================
// insert_non_full(node, key)
// Insert 'key' into a node that is known to be NOT FULL when called.
// If node is leaf: insert in sorted position.
// If internal: find child; split child if full; recurse into correct child.
// ============================================================================
void insert_non_full(BTreeNode *node, int key) {
    // Start at last key index (num_keys - 1).
    int i = node->num_keys - 1;

    // If this node is a leaf, we insert the key directly here.
    if (node->is_leaf) {
        // Shift keys greater than 'key' one slot to the right.
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        // Optional: detect duplicates (ignore duplicate inserts).
        if (i >= 0 && node->keys[i] == key) {
            // Duplicate found; do not insert again (comment out to allow dups).
            return;
        }
        // Place the new key at the gap (i+1).
        node->keys[i + 1] = key;
        // Increase key count in this leaf.
        node->num_keys++;
    } else {
        // Internal node case: move i left past keys > key.
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        // Child index to descend into is i+1 (first key > key or end).
        i++;

        // Defensive: ensure child pointer is non-NULL (should be in a valid tree).
        if (node->children[i] == NULL) {
            printf("Error: child[%d] is NULL in insert_non_full (tree corrupt?)\n", i);
            return;
        }

        // If the chosen child is full, we must split it before descending.
        if (node->children[i]->num_keys == 2 * node->min_degree - 1) {
            // Split the full child at index i.
            split_child(node, i, node->children[i]);

            // After split, the middle key moved up; decide which side to descend.
            if (node->keys[i] < key)
                i++;  // If key belongs in the new right child, advance index.
        }

        // Recurse into the correct child (now guaranteed not full).
        insert_non_full(node->children[i], key);
    }
}

// ============================================================================
// insert(btree, key)
// Public insertion function: handles empty tree and full root cases.
// 1. If tree empty → create root leaf and insert key.
// 2. If root full → allocate new root, split old root, attach children.
// 3. Insert key into new or existing root (root now not full).
// ============================================================================
void insert(BTree *btree, int key) {
    // If there is no root, create one and store the key there.
    if (btree->root == NULL) {
        // Create a new leaf root node.
        btree->root = create_node(btree->min_degree, true);
        // If creation failed, bail out.
        if (!btree->root) {
            printf("Failed to create root node\n");
            return;
        }
        // Store the key in the empty root.
        btree->root->keys[0] = key;
        // Root now contains 1 key.
        btree->root->num_keys = 1;
        // Report insertion.
        printf("Inserted %d as root\n", key);
        // Done.
        return;
    }

    // If the root is full, we must split it and grow the tree height by 1.
    if (btree->root->num_keys == 2 * btree->min_degree - 1) {
        // Create a new root (internal node).
        BTreeNode *new_root = create_node(btree->min_degree, false);
        // If creation failed, bail out.
        if (!new_root) {
            printf("Failed to create new root\n");
            return;
        }
        // Make the old root the 0th child of the new root.
        new_root->children[0] = btree->root;
        // Split the old root into two children of new_root.
        split_child(new_root, 0, btree->root);
        // Update the tree's root pointer to the new root.
        btree->root = new_root;
        // Report root split.
        printf("Root was full, created new root\n");
    }

    // At this point, the root is guaranteed NOT full: insert below it.
    insert_non_full(btree->root, key);
    // Report successful insertion.
    printf("Inserted %d into B-tree\n", key);
}

// ============================================================================
// inorder_traversal(node)
// Perform an in-order traversal (sorted key print) of the B-tree subtree.
// For B-trees, this yields ascending order of all stored keys.
// ============================================================================
void inorder_traversal(BTreeNode *node) {
    // If subtree empty, nothing to print.
    if (node == NULL)
        return;

    // Loop through each key in this node.
    for (int i = 0; i < node->num_keys; i++) {
        // If internal, process the child to the left of this key first.
        if (!node->is_leaf)
            inorder_traversal(node->children[i]);
        // Print this key.
        printf("%d ", node->keys[i]);
    }

    // After finishing all keys, process the final rightmost child (if internal).
    if (!node->is_leaf)
        inorder_traversal(node->children[node->num_keys]);
}

// ============================================================================
// print_tree_structure(node, level)
// Print the B-tree level by level with indentation for clarity.
// Shows node keys and whether the node is a leaf.
// ============================================================================
void print_tree_structure(BTreeNode *node, int level) {
    // If subtree empty, stop.
    if (!node)
        return;

    // Print indentation proportional to tree depth level.
    for (int i = 0; i < level; i++)
        printf("  ");

    // Print level label and opening bracket for node keys.
    printf("Level %d: [", level);
    // Print all keys in this node with commas between them.
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d", node->keys[i]);
        if (i < node->num_keys - 1)
            printf(", ");
    }
    // Close bracket and print whether this node is a leaf.
    printf("] (leaf: %s)\n", node->is_leaf ? "yes" : "no");

    // If internal node, recursively print each child subtree one level deeper.
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++)
            print_tree_structure(node->children[i], level + 1);
    }
}

// ============================================================================
// free_btree(node)
// Recursively free an entire B-tree subtree.
// 1. Recurse on children if internal.
// 2. Free keys array.
// 3. Free children array.
// 4. Free node itself.
// ============================================================================
void free_btree(BTreeNode *node) {
    // Nothing to free if node NULL.
    if (!node)
        return;

    // If internal, free all child subtrees first.
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++)
            free_btree(node->children[i]);
    }

    // Free the dynamically allocated keys array.
    free(node->keys);
    // Free the dynamically allocated children array.
    free(node->children);
    // Free the node structure itself.
    free(node);
}

// ============================================================================
// main()
// Demonstrate B-tree creation, insertion, printing, traversal, and cleanup.
// ============================================================================
int main(void) {
    // Create a B-tree with the configured MIN_DEGREE.
    BTree *btree = create_btree(MIN_DEGREE);
    // Check that the tree was created.
    if (!btree) {
        printf("Failed to create B-tree\n");
        return 1;
    }

    // Print some basic tree info.
    printf("=== B-Tree Demo ===\n");
    printf("Minimum degree (t): %d\n", MIN_DEGREE);
    printf("Max keys per node: %d\n", 2 * MIN_DEGREE - 1);
    printf("Min keys per *non-root* node: %d\n", MIN_DEGREE - 1);

    // Test keys to insert into the B-tree.
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17, 25, 40, 50, 60};
    // Compute how many test keys we have.
    int num_keys = (int)(sizeof(keys_to_insert) / sizeof(keys_to_insert[0]));

    // Announce insertion phase.
    printf("\n--- Inserting keys ---\n");
    // Insert each test key one by one.
    for (int i = 0; i < num_keys; i++) {
        insert(btree, keys_to_insert[i]);
    }

    // Print a structured view of the whole B-tree.
    printf("\nB-tree structure:\n");
    print_tree_structure(btree->root, 0);

    // Print in-order traversal (sorted keys).
    printf("\nIn-order traversal:\n");
    inorder_traversal(btree->root);
    printf("\n");

    // Free the entire tree memory (node subtrees then wrapper).
    free_btree(btree->root);
    free(btree);

    // Exit success.
    return 0;
}

