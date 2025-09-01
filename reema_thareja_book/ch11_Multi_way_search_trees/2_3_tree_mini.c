// Include standard I/O for printing and reading
#include <stdio.h>
// Include standard library for memory allocation and exit
#include <stdlib.h>
// Include stdbool for the bool type
#include <stdbool.h>

// Define the maximum NORMAL number of keys a 2-3 tree node holds (1 or 2; so MAX=2)
#define TT_MAX_KEYS 2
// Define the maximum NORMAL number of children (keys + 1) = 3
#define TT_MAX_CHILDREN 3
// Define an extra slot for temporary overflow keys (during split we may have 3 keys)
#define TT_OVERFLOW_KEYS (TT_MAX_KEYS + 1)
// Define an extra slot for temporary overflow children (up to 4 children during split)
#define TT_OVERFLOW_CHILDREN (TT_MAX_CHILDREN + 1)

// Forward declare the node structure so the typedef can reference itself
typedef struct TTNode TTNode;

// Define the node structure for the 2-3 tree
struct TTNode {
    // Store keys with ONE extra slot to hold a temporary 3rd key before splitting
    int keys[TT_OVERFLOW_KEYS];
    // Store child pointers with ONE extra slot (up to 4 children temporarily)
    TTNode *children[TT_OVERFLOW_CHILDREN];
    // Store how many keys are currently valid (normally 1 or 2, briefly 3 before split)
    int num_keys;
    // Flag telling whether this node is a leaf (has no children)
    bool is_leaf;
};

// Define a wrapper structure for the whole tree
typedef struct TTTree {
    // Pointer to the root node (NULL means the tree is empty)
    TTNode *root;
} TTTree;

// Define a small structure to communicate promotions after splitting
typedef struct TTPromote {
    // Indicate whether a split happened and a key must be pushed upward
    bool has_promote;
    // The key that should move up to the parent
    int promote_key;
    // The right child created by the split (the left one remains the existing node)
    TTNode *right_child;
} TTPromote;

// Provide a helper that returns a "no promotion" result
static TTPromote tt_promote_none(void) {
    // Create a local promotion structure
    TTPromote p;
    // Indicate no split occurred
    p.has_promote = false;
    // Set a placeholder key value (not used)
    p.promote_key = 0;
    // Set the right child pointer to NULL
    p.right_child = NULL;
    // Return the result
    return p;
}

// Provide a helper that creates a promotion result with data
static TTPromote tt_promote_make(int key, TTNode *right_child) {
    // Create a local promotion structure
    TTPromote p;
    // Mark that a split occurred
    p.has_promote = true;
    // Store the key to push upward
    p.promote_key = key;
    // Store the pointer to the new right child
    p.right_child = right_child;
    // Return the promotion data
    return p;
}

// Create a new node with a given leaf flag
static TTNode *tt_create_node(bool is_leaf) {
    // Allocate memory for the node
    TTNode *node = (TTNode *)malloc(sizeof(TTNode));
    // Check if allocation failed
    if (!node) {
        // Report the failure
        printf("Memory allocation failed for TTNode.\n");
        // Return NULL to signal the error
        return NULL;
    }
    // Initialize number of keys to zero
    node->num_keys = 0;
    // Set whether this node is a leaf
    node->is_leaf = is_leaf;
    // Initialize all child pointers to NULL
    for (int i = 0; i < TT_OVERFLOW_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    // Return the new node
    return node;
}

// Create an empty tree
static TTTree *tt_create_tree(void) {
    // Allocate memory for the tree wrapper
    TTTree *tree = (TTTree *)malloc(sizeof(TTTree));
    // Check if allocation failed
    if (!tree) {
        // Report the failure
        printf("Memory allocation failed for TTTree.\n");
        // Return NULL to signal the error
        return NULL;
    }
    // Initialize the root pointer to NULL (empty tree)
    tree->root = NULL;
    // Return the new empty tree
    return tree;
}

// Search for a key starting at a given node
static bool tt_search_node(TTNode *node, int key) {
    // If the node pointer is NULL, the key cannot be here
    if (node == NULL) {
        return false;
    }
    // Start scanning keys from left to right
    int i = 0;
    // Move forward while the current key is smaller than the target
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    // If we stopped within bounds and found an exact match, return true
    if (i < node->num_keys && key == node->keys[i]) {
        return true;
    }
    // If this is a leaf and no match was found, the key is not in the tree
    if (node->is_leaf) {
        return false;
    }
    // Otherwise recurse into the appropriate child and continue searching
    return tt_search_node(node->children[i], key);
}

// Public search function starting at the root
static bool tt_search(TTTree *tree, int key) {
    // If the tree or its root is NULL, the key cannot be present
    if (tree == NULL || tree->root == NULL) {
        return false;
    }
    // Delegate to the recursive search helper
    return tt_search_node(tree->root, key);
}

// Insert a key into a single node in sorted order (no splitting here)
static bool tt_insert_key_into_node(TTNode *node, int key) {
    // Start at the last valid key index
    int i = node->num_keys - 1;
    // Shift keys to the right while they are larger than the new key
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    // Check if we found the key already (duplicate)
    if (i >= 0 && node->keys[i] == key) {
        // Return false to signal duplicate insertion attempt
        return false;
    }
    // Place the new key in the correct position
    node->keys[i + 1] = key;
    // Increase the count of keys
    node->num_keys++;
    // Indicate successful insertion
    return true;
}

// Handle insertion specifically into a leaf (including potential split)
static TTPromote tt_insert_into_leaf(TTNode *leaf, int key) {
    // Attempt to insert the key into the leaf
    bool inserted = tt_insert_key_into_node(leaf, key);
    // If not inserted (duplicate) return no promotion
    if (!inserted) {
        return tt_promote_none();
    }
    // If the leaf still has only 1 or 2 keys, no split is required
    if (leaf->num_keys <= TT_MAX_KEYS) {
        return tt_promote_none();
    }
    // Otherwise we have 3 keys and must split the leaf
    TTNode *right = tt_create_node(true);
    // Check allocation for the right leaf
    if (!right) {
        // Report fatal error and exit
        printf("Fatal: out of memory splitting leaf.\n");
        exit(EXIT_FAILURE);
    }
    // Decide the middle key index (1) because we have exactly 3 keys now
    int mid = 1;
    // The middle key is promoted upward
    int promote_key = leaf->keys[mid];
    // The right leaf will keep the last key (index 2)
    right->keys[0] = leaf->keys[2];
    // The right leaf has exactly 1 key
    right->num_keys = 1;
    // The left (original) leaf will keep only the first key
    leaf->num_keys = 1;
    // Return the promotion information to the caller
    return tt_promote_make(promote_key, right);
}

// Recursively insert a key into a subtree rooted at 'node'
static TTPromote tt_insert_recursive(TTNode *node, int key) {
    // If this node is a leaf, handle leaf insertion and possible split
    if (node->is_leaf) {
        return tt_insert_into_leaf(node, key);
    }
    // Otherwise this is an internal node; we must pick the correct child
    int i = 0;
    // Find the child index where the key should go
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    // If the key already exists in this internal node, do nothing
    if (i < node->num_keys && key == node->keys[i]) {
        return tt_promote_none();
    }
    // Recursively insert into the chosen child
    TTPromote prom = tt_insert_recursive(node->children[i], key);
    // If the child did not split, simply return no promotion
    if (!prom.has_promote) {
        return tt_promote_none();
    }
    // Otherwise we must insert the promoted key and new right child here
    for (int j = node->num_keys; j > i; j--) {
        node->keys[j] = node->keys[j - 1];
    }
    // Shift children pointers to make room for the new right child
    for (int j = node->num_keys + 1; j > i + 1; j--) {
        node->children[j] = node->children[j - 1];
    }
    // Place the promoted key into the current node
    node->keys[i] = prom.promote_key;
    // Attach the promoted right child
    node->children[i + 1] = prom.right_child;
    // Increase key count for this node
    node->num_keys++;
    // If after insertion this node still fits (<=2 keys), no split required
    if (node->num_keys <= TT_MAX_KEYS) {
        return tt_promote_none();
    }
    // Otherwise this internal node overflows (3 keys) and must split
    TTNode *right = tt_create_node(false);
    // Check allocation for right internal node
    if (!right) {
        printf("Fatal: out of memory splitting internal node.\n");
        exit(EXIT_FAILURE);
    }
    // Middle index is 1 in a 3-key temporary node
    int mid = 1;
    // Promote the middle key
    int promote_key = node->keys[mid];
    // Right internal node gets the last key
    right->keys[0] = node->keys[2];
    // Transfer the corresponding right children (child2 and child3)
    right->children[0] = node->children[2];
    right->children[1] = node->children[3];
    // Right node now has 1 key
    right->num_keys = 1;
    // Mark right as internal
    right->is_leaf = false;
    // Original node (left) keeps only the first key and its first two children
    node->num_keys = 1;
    // Return promotion info to parent
    return tt_promote_make(promote_key, right);
}

// Public insert function that manages root creation and root splitting
static void tt_insert(TTTree *tree, int key) {
    // If the tree pointer itself is NULL, do nothing
    if (tree == NULL) {
        return;
    }
    // If the tree is empty, create a root leaf and place the key there
    if (tree->root == NULL) {
        tree->root = tt_create_node(true);
        if (!tree->root) {
            printf("Failed to create 2-3 tree root.\n");
            return;
        }
        tree->root->keys[0] = key;
        tree->root->num_keys = 1;
        return;
    }
    // Otherwise perform recursive insertion starting at the root
    TTPromote prom = tt_insert_recursive(tree->root, key);
    // If no split happened at root level, we are done
    if (!prom.has_promote) {
        return;
    }
    // A split at the root produces a new root with one key and two children
    TTNode *new_root = tt_create_node(false);
    if (!new_root) {
        printf("Failed to allocate new root after split.\n");
        exit(EXIT_FAILURE);
    }
    // Place the promoted key into the new root
    new_root->keys[0] = prom.promote_key;
    // Left child is the old root
    new_root->children[0] = tree->root;
    // Right child is the newly created node from the split
    new_root->children[1] = prom.right_child;
    // New root now has exactly one key
    new_root->num_keys = 1;
    // Mark new root as internal
    new_root->is_leaf = false;
    // Update the tree's root pointer
    tree->root = new_root;
}

// Perform an in-order traversal to print keys in ascending order
static void tt_inorder(TTNode *node) {
    // If the node is NULL, there is nothing to print
    if (node == NULL) {
        return;
    }
    // Handle the case where the node has exactly 1 key
    if (node->num_keys == 1) {
        if (!node->is_leaf) {
            tt_inorder(node->children[0]);
        }
        printf("%d ", node->keys[0]);
        if (!node->is_leaf) {
            tt_inorder(node->children[1]);
        }
        return;
    }
    // Handle the case where the node has exactly 2 keys
    if (node->num_keys == 2) {
        if (!node->is_leaf) {
            tt_inorder(node->children[0]);
        }
        printf("%d ", node->keys[0]);
        if (!node->is_leaf) {
            tt_inorder(node->children[1]);
        }
        printf("%d ", node->keys[1]);
        if (!node->is_leaf) {
            tt_inorder(node->children[2]);
        }
        return;
    }
    // If a node ever has 0 keys here (only possible for a root in advanced versions) we would handle it (not needed now)
}

// Print a readable structure of the tree with indentation by level
static void tt_print_structure(TTNode *node, int level) {
    // If the node is NULL, stop
    if (node == NULL) {
        return;
    }
    // Print indentation spaces proportional to the level
    for (int i = 0; i < level; i++) {
        printf(" ");
    }
    // Begin printing this node's line
    printf("Level %d: [", level);
    // Print first key if at least one key exists
    if (node->num_keys >= 1) {
        printf("%d", node->keys[0]);
    }
    // If there is a second key, print it with a comma separator
    if (node->num_keys == 2) {
        printf(", %d", node->keys[1]);
    }
    // Close the bracket and show whether it's a leaf or internal node
    printf("] (%s)\n", node->is_leaf ? "leaf" : "int");
    // If this is an internal node, recursively print its children
    if (!node->is_leaf) {
        tt_print_structure(node->children[0], level + 1);
        tt_print_structure(node->children[1], level + 1);
        if (node->num_keys == 2) {
            tt_print_structure(node->children[2], level + 1);
        }
    }
}

// Recursively free all nodes in the subtree
static void tt_free_nodes(TTNode *node) {
    // If nothing to free, return
    if (node == NULL) {
        return;
    }
    // If internal, free all valid children
    if (!node->is_leaf) {
        tt_free_nodes(node->children[0]);
        tt_free_nodes(node->children[1]);
        if (node->num_keys == 2) {
            tt_free_nodes(node->children[2]);
        }
    }
    // Free this node itself
    free(node);
}

// Free the entire tree structure
static void tt_free_tree(TTTree *tree) {
    // If the tree pointer is NULL, nothing to free
    if (!tree) {
        return;
    }
    // Free all nodes starting from the root
    tt_free_nodes(tree->root);
    // Free the tree wrapper
    free(tree);
}

// Helper to search and print a message about a key
static void tt_search_and_print(TTTree *tree, int key) {
    // Perform the search
    bool found = tt_search(tree, key);
    // Print whether the key was found
    printf("Key %d %s.\n", key, found ? "FOUND" : "NOT FOUND");
}

// Program entry point
int main(void) {
    // Create a new empty 2-3 tree
    TTTree *tree = tt_create_tree();
    // If creation failed, exit with error code
    if (!tree) {
        return 1;
    }
    // Print a banner for the demo
    printf("===== 2-3 Tree Demo ======\n");
    // Prepare an array of keys to insert (including those causing splits)
    int keys[] = {20, 5, 1, 15, 30, 25, 40, 10, 50, 60, 2, 3};
    // Compute how many keys are in the array
    int n = (int)(sizeof(keys) / sizeof(keys[0]));
    // Insert each key into the tree
    for (int i = 0; i < n; i++) {
        tt_insert(tree, keys[i]);
    }
    // Print the tree structure after insertions
    printf("\n--- 2-3 Tree Structure ---\n");
    tt_print_structure(tree->root, 0);
    // Print an in-order traversal to show sorted order
    printf("\n--- In-order Traversal ---\n");
    tt_inorder(tree->root);
    printf("\n");
    // Demonstrate searching for several keys (existing and missing)
    printf("\n--- Search Demo ---\n");
    tt_search_and_print(tree, 15);
    tt_search_and_print(tree, 100);
    tt_search_and_print(tree, 3);
    tt_search_and_print(tree, 60);
    // Free all allocated memory
    tt_free_tree(tree);
    // Return success
    return 0;
}

