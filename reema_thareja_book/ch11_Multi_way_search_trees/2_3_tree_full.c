/**************************************************************
 * two_three_tree_rebuilt.c
 * Safe 2-3 Tree (Insertion, Deletion, Search, Traversal, Menu)
 * - Extra temporary capacity (keys+1, children+1) prevents overflow segfaults.
 * - Algorithm block comment before each function.
 * - Beginner-friendly comment above every line (or logical brace).
 **************************************************************/

#include <stdio.h>      // For printf / scanf
#include <stdlib.h>     // For malloc / free / exit
#include <stdbool.h>    // For bool type

/* ---------------------------------------------------------- */
/* MAX_KEYS = 2 (a 2-3 node has at most 2 keys normally)      */
/* We add +1 temporary slot for overflow handling.            */
/* ---------------------------------------------------------- */
#define MAX_KEYS 2
/* ---------------------------------------------------------- */
/* MAX_CHILDREN = MAX_KEYS + 1 = 3 normally; need +1 overflow.*/
/* ---------------------------------------------------------- */
#define MAX_CHILDREN (MAX_KEYS + 1)

/* ---------------------------------------------------------- */
/* Forward declaration of node struct for self-references.    */
/* ---------------------------------------------------------- */
typedef struct TTNode TTNode;

/* ---------------------------------------------------------- */
/* 2-3 Tree Node Structure                                    */
/* ---------------------------------------------------------- */
struct TTNode {
    int keys[MAX_KEYS + 1];          // Keys array with +1 overflow slot (size = 3)
    TTNode *children[MAX_CHILDREN + 1]; // Child pointers with +1 overflow slot (size = 4)
    int num_keys;                    // Number of *valid* keys (0..2 normally; 3 temporary)
    bool is_leaf;                    // Leaf flag
};

/* ---------------------------------------------------------- */
/* Wrapper tree structure (just holds root pointer).          */
/* ---------------------------------------------------------- */
typedef struct TTTree {
    TTNode *root;                    // Pointer to root node (NULL if empty)
} TTTree;

/* ---------------------------------------------------------- */
/* Promotion info used when a child split occurs.             */
/* ---------------------------------------------------------- */
typedef struct PromoteInfo {
    bool has_promote;                // True if a split happened
    int promote_key;                 // Key to push upward
    TTNode *right_child;             // Right child created by split
} PromoteInfo;

/* ============================================================
   create_node(is_leaf)
   ALGORITHM:
     1. Allocate a node.
     2. If allocation fails -> return NULL.
     3. Initialize num_keys=0, set is_leaf flag.
     4. Set all child pointers to NULL.
     5. Return node pointer.
   ============================================================ */
static TTNode *create_node(bool is_leaf) {
    TTNode *n = (TTNode *)malloc(sizeof(TTNode));    // Allocate memory for node
    if (!n) {                                       // Check allocation
        printf("Memory allocation failed for node.\n"); // Report failure
        return NULL;                                // Return NULL
    }
    n->num_keys = 0;                                // Start with zero keys
    n->is_leaf = is_leaf;                           // Set leaf flag
    for (int i = 0; i < MAX_CHILDREN + 1; i++) {    // Loop through children array
        n->children[i] = NULL;                      // Initialize each child pointer
    }
    return n;                                       // Return new node
}

/* ============================================================
   create_tree()
   ALGORITHM:
     1. Allocate tree wrapper.
     2. If fail -> NULL.
     3. Set root = NULL.
     4. Return tree pointer.
   ============================================================ */
static TTTree *create_tree(void) {
    TTTree *t = (TTTree *)malloc(sizeof(TTTree));   // Allocate wrapper
    if (!t) {                                       // Check allocation
        printf("Memory allocation failed for tree.\n"); // Report failure
        return NULL;                                // Return NULL
    }
    t->root = NULL;                                 // Initialize root to NULL
    return t;                                       // Return tree
}

/* ============================================================
   promote_none()
   ALGORITHM:
     Return a PromoteInfo struct indicating no split happened.
   ============================================================ */
static PromoteInfo promote_none(void) {
    PromoteInfo p;                                  // Declare struct
    p.has_promote = false;                          // No split
    p.promote_key = 0;                              // Dummy key
    p.right_child = NULL;                           // No child
    return p;                                       // Return struct
}

/* ============================================================
   promote_make(key,right)
   ALGORITHM:
     Return a PromoteInfo struct with split info.
   ============================================================ */
static PromoteInfo promote_make(int key, TTNode *right) {
    PromoteInfo p;                                  // Declare struct
    p.has_promote = true;                           // Mark split happened
    p.promote_key = key;                            // Store key
    p.right_child = right;                          // Store right node
    return p;                                       // Return
}

/* ============================================================
   search_node(node, key)
   ALGORITHM:
     1. If node NULL -> return false.
     2. Scan keys left to right while key > keys[i].
     3. If equal -> true.
     4. If leaf -> false.
     5. Recurse into child at index i.
   ============================================================ */
static bool search_node(TTNode *node, int key) {
    if (!node)                                      // If subtree empty
        return false;                               // Not found
    int i = 0;                                      // Start at first key
    while (i < node->num_keys && key > node->keys[i]) // Move while key bigger
        i++;                                        // Advance index
    if (i < node->num_keys && key == node->keys[i]) // If key matches
        return true;                                // Found
    if (node->is_leaf)                              // If leaf and not found
        return false;                               // Not found
    return search_node(node->children[i], key);     // Recurse into proper child
}

/* ============================================================
   search(tree, key)
   ALGORITHM:
     1. If tree or root NULL -> false.
     2. Else return search_node(root,key).
   ============================================================ */
static bool search(TTTree *tree, int key) {
    if (!tree || !tree->root)                       // If tree empty
        return false;                               // Not found
    return search_node(tree->root, key);            // Delegate to helper
}

/* ============================================================
   insert_key_sorted(node, key)
   PRE: node has at most MAX_KEYS keys currently (or may have MAX_KEYS then becomes MAX_KEYS+1 temp).
   ALGORITHM:
     1. i = num_keys - 1.
     2. Shift larger keys right (uses overflow slot).
     3. If duplicate encountered -> return false.
     4. Insert key at i+1; increment num_keys; return true.
   ============================================================ */
static bool insert_key_sorted(TTNode *node, int key) {
    int i = node->num_keys - 1;                     // Start at last valid key
    while (i >= 0 && node->keys[i] > key) {         // While current key > new key
        node->keys[i + 1] = node->keys[i];          // Shift key to right
        i--;                                        // Move left
    }
    if (i >= 0 && node->keys[i] == key)             // If duplicate found
        return false;                               // Do not insert duplicates
    node->keys[i + 1] = key;                        // Place new key
    node->num_keys++;                               // Increase count
    return true;                                    // Success
}

/* ============================================================
   split_leaf(leaf)
   PRE: leaf->num_keys == 3 (temporary overflow)
   ALGORITHM:
     1. mid = 1 (keys[0], keys[1], keys[2]).
     2. Promote keys[1].
     3. Left keeps keys[0].
     4. New right leaf gets keys[2].
     5. Return promote info.
   ============================================================ */
static PromoteInfo split_leaf(TTNode *leaf) {
    TTNode *right = create_node(true);              // Create new right leaf
    if (!right) {                                   // Check allocation
        printf("Fatal: leaf split allocation failed.\n"); // Report error
        exit(EXIT_FAILURE);                         // Abort
    }
    int mid = 1;                                    // Middle index of 3 keys
    int promote_key = leaf->keys[mid];              // Key to promote up
    right->keys[0] = leaf->keys[2];                 // Right leaf keeps last key
    right->num_keys = 1;                            // Right leaf has 1 key
    leaf->num_keys = 1;                             // Left leaf now has 1 key
    return promote_make(promote_key, right);        // Return promotion info
}

/* ============================================================
   split_internal(node)
   PRE: node->num_keys == 3 (temporary overflow)
   ALGORITHM:
     1. mid = 1.
     2. Promote node->keys[1].
     3. Left (original) keeps keys[0] + children[0..1].
     4. Right new internal keeps keys[2] + children[2..3].
     5. Set both num_keys = 1.
     6. Return promote info.
   ============================================================ */
static PromoteInfo split_internal(TTNode *node) {
    TTNode *right = create_node(false);             // Create new right internal node
    if (!right) {                                   // Check allocation
        printf("Fatal: internal split allocation failed.\n"); // Report
        exit(EXIT_FAILURE);                         // Abort
    }
    int mid = 1;                                    // Middle index
    int promote_key = node->keys[mid];              // Key to promote
    right->keys[0] = node->keys[2];                 // Right node gets last key
    right->children[0] = node->children[2];         // Right child0 from old child2
    right->children[1] = node->children[3];         // Right child1 from old child3
    right->num_keys = 1;                            // Right now has 1 key
    right->is_leaf = false;                         // Mark internal
    node->num_keys = 1;                             // Left (original) keeps first key
    return promote_make(promote_key, right);        // Return promotion info
}

/* ============================================================
   insert_recursive(node, key)
   ALGORITHM:
     1. If leaf:
        a. Insert key (may create 3rd key).
        b. If now <= 2 keys -> no split.
        c. If 3 keys -> split_leaf().
     2. Else internal:
        a. Find child index i such that key belongs there.
        b. If duplicate in this node -> stop (no-op).
        c. Recurse into child[i].
        d. If child split -> insert promoted key + right child pointer.
        e. If node now has 3 keys -> split_internal().
     3. Return promotion info or none.
   ============================================================ */
static PromoteInfo insert_recursive(TTNode *node, int key) {
    if (node->is_leaf) {                            // If this is a leaf
        bool ok = insert_key_sorted(node, key);     // Insert key into leaf
        if (!ok) return promote_none();             // Ignore duplicate
        if (node->num_keys <= MAX_KEYS)             // If still within capacity
            return promote_none();                  // No split required
        return split_leaf(node);                    // Split overflow leaf
    }
    int i = 0;                                      // Start scanning keys
    while (i < node->num_keys && key > node->keys[i]) // Find child index
        i++;                                        // Advance
    if (i < node->num_keys && key == node->keys[i]) // Duplicate at internal node?
        return promote_none();                      // No changes
    PromoteInfo childProm = insert_recursive(node->children[i], key); // Recurse into child
    if (!childProm.has_promote)                     // If child did not split
        return promote_none();                      // Bubble up "no split"
    for (int j = node->num_keys; j > i; j--)        // Shift keys right for new key
        node->keys[j] = node->keys[j - 1];          // Shift one position
    for (int j = node->num_keys + 1; j > i + 1; j--)// Shift children right
        node->children[j] = node->children[j - 1];  // Shift pointer
    node->keys[i] = childProm.promote_key;          // Place promoted key
    node->children[i + 1] = childProm.right_child;  // Insert new right child
    node->num_keys++;                               // Increase key count
    if (node->num_keys <= MAX_KEYS)                 // If still fits
        return promote_none();                      // Done (no split)
    return split_internal(node);                    // Split internal overflow
}

/* ============================================================
   insert(tree, key)
   ALGORITHM:
     1. If tree empty: create root leaf with key.
     2. Else call insert_recursive(root,key).
     3. If root split: create new root with promoted key + two children.
   ============================================================ */
static void insert(TTTree *tree, int key) {
    if (!tree) return;                              // No tree given
    if (!tree->root) {                              // Empty tree
        tree->root = create_node(true);             // Make new leaf root
        if (!tree->root) {                          // Check allocation
            printf("Failed to allocate root.\n");   // Report error
            return;                                 // Abort insert
        }
        tree->root->keys[0] = key;                  // Store first key
        tree->root->num_keys = 1;                   // Root has 1 key
        return;                                     // Done
    }
    PromoteInfo p = insert_recursive(tree->root, key); // Insert recursively
    if (!p.has_promote)                             // If root not split
        return;                                     // Done
    TTNode *new_root = create_node(false);          // Allocate new root
    if (!new_root) {                                // Check allocation
        printf("Failed to allocate new root.\n");   // Report error
        exit(EXIT_FAILURE);                         // Abort program
    }
    new_root->keys[0] = p.promote_key;              // Store promoted key
    new_root->children[0] = tree->root;             // Left child old root
    new_root->children[1] = p.right_child;          // Right child new node
    new_root->num_keys = 1;                         // New root has 1 key
    new_root->is_leaf = false;                      // Mark internal
    tree->root = new_root;                          // Update root pointer
}

/* ============================================================
   insert_unique(tree, key)
   ALGORITHM:
     1. If key already present -> report and return.
     2. Else call insert().
   ============================================================ */
static void insert_unique(TTTree *tree, int key) {
    if (search(tree, key)) {                        // Check for duplicate
        printf("Duplicate %d ignored.\n", key);     // Report duplicate
        return;                                     // Do not insert
    }
    insert(tree, key);                              // Perform real insertion
    printf("Inserted %d.\n", key);                  // Report success
}

/* ============================================================
   find_predecessor(node, idx)
   ALGORITHM:
     1. Go to left child at children[idx].
     2. Repeatedly follow its rightmost child until leaf.
     3. Return last key in that leaf.
   ============================================================ */
static int find_predecessor(TTNode *node, int idx) {
    TTNode *cur = node->children[idx];              // Start at left subtree
    while (cur && !cur->is_leaf)                    // While not leaf
        cur = cur->children[cur->num_keys];         // Move to rightmost child
    return cur->keys[cur->num_keys - 1];            // Return last key
}

/* ============================================================
   borrow_from_left(parent, idx)
   PRE: left sibling has 2 keys; child at idx has 0 keys.
   ALGORITHM:
     1. Shift child's keys/children right.
     2. Move parent key down into child's first slot.
     3. Move left sibling's last key up to parent.
     4. If internal, move sibling's last child pointer.
   ============================================================ */
static void borrow_from_left(TTNode *parent, int idx) {
    TTNode *child = parent->children[idx];          // Underflowing child
    TTNode *left  = parent->children[idx - 1];      // Left sibling
    for (int j = child->num_keys - 1; j >= 0; j--)  // Shift child keys right
        child->keys[j + 1] = child->keys[j];        // Shift
    if (!child->is_leaf) {                          // If internal
        for (int j = child->num_keys; j >= 0; j--)  // Shift children right
            child->children[j + 1] = child->children[j]; // Shift pointer
    }
    child->keys[0] = parent->keys[idx - 1];         // Bring parent key down
    if (!child->is_leaf)                            // If internal
        child->children[0] = left->children[left->num_keys]; // Move last child
    parent->keys[idx - 1] = left->keys[left->num_keys - 1];  // Left last key up
    child->num_keys++;                              // Child gained key
    left->num_keys--;                               // Left lost key
}

/* ============================================================
   borrow_from_right(parent, idx)
   PRE: right sibling has 2 keys.
   ALGORITHM:
     1. Move parent key down into child's end slot.
     2. Move sibling's first key up to parent.
     3. Shift sibling's keys (and children) left.
   ============================================================ */
static void borrow_from_right(TTNode *parent, int idx) {
    TTNode *child = parent->children[idx];          // Underflow child
    TTNode *right = parent->children[idx + 1];      // Right sibling
    child->keys[child->num_keys] = parent->keys[idx]; // Parent key down
    if (!child->is_leaf)                            // If internal
        child->children[child->num_keys + 1] = right->children[0]; // Adopt first child
    parent->keys[idx] = right->keys[0];             // Right first key up
    for (int j = 1; j < right->num_keys; j++)       // Shift right keys left
        right->keys[j - 1] = right->keys[j];        // Shift
    if (!right->is_leaf) {                          // If internal
        for (int j = 1; j <= right->num_keys; j++)  // Shift right children
            right->children[j - 1] = right->children[j]; // Shift pointer
    }
    child->num_keys++;                              // Child gained key
    right->num_keys--;                              // Right lost key
}

/* ============================================================
   merge_children(parent, idx)
   MERGE: child[idx] + parent key[idx] + child[idx+1]
   PRE: both children have 1 key.
   ALGORITHM (simplified):
     1. Left = child[idx], Right = child[idx+1], Sep = parent->keys[idx].
     2. Gather left.key0, sep, right.key0 -> sort -> keep first two.
     3. Attach any necessary child pointers (basic support).
     4. Remove right from parent (shift arrays).
     5. Free right.
   ============================================================ */
static void merge_children(TTNode *parent, int idx) {
    TTNode *left  = parent->children[idx];          // Left child
    TTNode *right = parent->children[idx + 1];      // Right child
    int sep = parent->keys[idx];                    // Separator key
    int tmp[3];                                     // Temp array
    int c = 0;                                      // Count
    for (int k = 0; k < left->num_keys; k++)        // Copy left keys
        tmp[c++] = left->keys[k];                   // Store
    tmp[c++] = sep;                                 // Add separator
    for (int k = 0; k < right->num_keys; k++)       // Copy right keys
        tmp[c++] = right->keys[k];                  // Store
    for (int a = 0; a < c; a++)                     // Bubble sort small array
        for (int b = a + 1; b < c; b++)             // Compare pairs
            if (tmp[b] < tmp[a]) {                  // If out of order
                int t = tmp[a]; tmp[a] = tmp[b]; tmp[b] = t; // Swap
            }
    left->keys[0] = tmp[0];                         // First key
    left->keys[1] = tmp[1];                         // Second key
    left->num_keys = 2;                             // Left now 2-key node
    if (!left->is_leaf)                             // If internal (rare path)
        left->children[2] = right->children[right->num_keys]; // Adopt rightmost child
    for (int j = idx + 1; j < parent->num_keys; j++)// Shift parent keys left
        parent->keys[j - 1] = parent->keys[j];      // Shift
    for (int j = idx + 2; j <= parent->num_keys; j++) // Shift parent children left
        parent->children[j - 1] = parent->children[j]; // Shift
    parent->num_keys--;                             // Parent lost a key
    free(right);                                    // Free right node
}

/* ============================================================
   fix_child(parent, idx)
   ALGORITHM:
     1. If child has >=1 key -> nothing.
     2. Else if left sibling has 2 -> borrow_from_left.
     3. Else if right sibling has 2 -> borrow_from_right.
     4. Else merge with left if possible else with right.
   ============================================================ */
static void fix_child(TTNode *parent, int idx) {
    TTNode *child = parent->children[idx];          // Target child
    if (child->num_keys >= 1)                       // If child is fine
        return;                                     // Nothing to do
    if (idx > 0 && parent->children[idx - 1]->num_keys == 2) { // Borrow left?
        borrow_from_left(parent, idx);              // Borrow from left sibling
        return;                                     // Done
    }
    if (idx < parent->num_keys && parent->children[idx + 1]->num_keys == 2) { // Borrow right?
        borrow_from_right(parent, idx);             // Borrow from right sibling
        return;                                     // Done
    }
    if (idx > 0)                                    // Merge preference
        merge_children(parent, idx - 1);            // Merge with left
    else
        merge_children(parent, idx);                // Merge with right
}

/* ============================================================
   delete_recursive(tree, node, key)
   ALGORITHM:
     1. Locate position i where key <= keys[i] or end.
     2. If key found:
        a. If leaf: remove key (shift left).
        b. If internal:
           i. Replace with predecessor (find_predecessor).
           ii. Recurse delete predecessor in left child.
           iii. Fix underflow in that child if needed.
     3. If key not found:
        a. If leaf: return false.
        b. Else:
           i. Fix child[i] if it has 0 keys.
           ii. Recurse into (maybe merged/borrowed) child.
           iii. Fix again if child underflowed.
     4. If root becomes empty and internal: promote only child.
     5. Return success flag.
   ============================================================ */
static bool delete_recursive(TTTree *tree, TTNode *node, int key) {
    if (!node)                                      // Empty subtree
        return false;                               // Not found
    int i = 0;                                      // Start index
    while (i < node->num_keys && key > node->keys[i]) // Find candidate slot
        i++;                                        // Advance
    if (i < node->num_keys && node->keys[i] == key) { // Key found in node
        if (node->is_leaf) {                        // Leaf case
            for (int j = i + 1; j < node->num_keys; j++) // Shift keys left
                node->keys[j - 1] = node->keys[j];  // Shift
            node->num_keys--;                       // Decrement key count
            return true;                            // Deleted
        } else {                                    // Internal case
            int pred = find_predecessor(node, i);   // Get predecessor
            node->keys[i] = pred;                   // Replace key with predecessor
            bool removed = delete_recursive(tree, node->children[i], pred); // Delete pred
            if (node->children[i]->num_keys == 0)   // If child underflowed to 0
                fix_child(node, i);                 // Repair
            if (tree->root == node && node->num_keys == 0 && !node->is_leaf) { // Empty root internal
                TTNode *old = tree->root;           // Save old root
                tree->root = old->children[0];      // Promote only child
                free(old);                          // Free old root
            }
            return removed;                         // Return status
        }
    }
    if (node->is_leaf)                              // Not found in leaf
        return false;                               // Return not found
    int idx = i;                                    // Child index to descend
    if (node->children[idx]->num_keys == 0)         // If that child is empty
        fix_child(node, idx);                       // Fix before descending
    if (idx > node->num_keys)                       // Adjust idx if merged shifted layout
        idx = node->num_keys;                       // Clamp idx
    bool removed = delete_recursive(tree, node->children[idx], key); // Recurse
    if (node->children[idx]->num_keys == 0 && !node->children[idx]->is_leaf) // Underflow again internal
        fix_child(node, idx);                       // Repair again
    if (tree->root == node && node->num_keys == 0 && !node->is_leaf) { // Root shrink
        TTNode *old = tree->root;                   // Save pointer
        tree->root = old->children[0];              // Promote child
        free(old);                                  // Free old
    }
    return removed;                                 // Return deletion result
}

/* ============================================================
   delete_key(tree, key)
   ALGORITHM:
     1. If tree empty -> message.
     2. Else call delete_recursive on root.
     3. If root becomes empty leaf -> free it, set root NULL.
     4. Report success/failure.
   ============================================================ */
static void delete_key(TTTree *tree, int key) {
    if (!tree || !tree->root) {                     // If tree empty
        printf("Tree empty; cannot delete %d.\n", key); // Report
        return;                                     // Exit
    }
    bool removed = delete_recursive(tree, tree->root, key); // Attempt deletion
    if (tree->root && tree->root->is_leaf && tree->root->num_keys == 0) { // Empty root leaf
        free(tree->root);                           // Free root
        tree->root = NULL;                          // Tree becomes empty
    }
    if (removed)                                    // If removed
        printf("Deleted %d.\n", key);               // Report success
    else                                            // Not found
        printf("Key %d not found.\n", key);         // Report failure
}

/* ============================================================
   inorder(node)
   ALGORITHM:
     1-key node: child0, key0, child1
     2-key node: child0, key0, child1, key1, child2
     (Root with 0 keys only prints child0.)
   ============================================================ */
static void inorder(TTNode *node) {
    if (!node) return;                              // Base case
    if (node->num_keys == 1) {                      // Single key
        if (!node->is_leaf)                         // Left
            inorder(node->children[0]);             // Recurse
        printf("%d ", node->keys[0]);               // Print key
        if (!node->is_leaf)                         // Right
            inorder(node->children[1]);             // Recurse
        return;                                     // Done
    }
    if (node->num_keys == 2) {                      // Two keys
        if (!node->is_leaf)                         // Child0
            inorder(node->children[0]);             // Recurse
        printf("%d ", node->keys[0]);               // Print first key
        if (!node->is_leaf)                         // Child1
            inorder(node->children[1]);             // Recurse
        printf("%d ", node->keys[1]);               // Print second key
        if (!node->is_leaf)                         // Child2
            inorder(node->children[2]);             // Recurse
        return;                                     // Done
    }
    if (!node->is_leaf && node->num_keys == 0)      // Root can be empty internal
        inorder(node->children[0]);                 // Traverse its only child
}

/* ============================================================
   print_structure(node, level)
   ALGORITHM:
     1. Indent by level.
     2. Print keys and node type.
     3. Recurse over children (num_keys + 1).
   ============================================================ */
static void print_structure(TTNode *node, int level) {
    if (!node) return;                              // Base case
    for (int i = 0; i < level; i++)                 // Indentation loop
        printf("  ");                               // Two spaces
    if (node->num_keys == 0)                        // Empty (possible root)
        printf("Level %d: [] (%s)\n", level, node->is_leaf ? "leaf" : "int");
    else if (node->num_keys == 1)                   // One key
        printf("Level %d: [%d] (%s)\n", level, node->keys[0], node->is_leaf ? "leaf" : "int");
    else                                            // Two keys
        printf("Level %d: [%d, %d] (%s)\n", level, node->keys[0], node->keys[1], node->is_leaf ? "leaf" : "int");
    if (!node->is_leaf) {                           // If internal node
        for (int c = 0; c <= node->num_keys; c++)   // Iterate children
            print_structure(node->children[c], level + 1); // Recurse
    }
}

/* ============================================================
   free_nodes(node)
   ALGORITHM:
     1. If internal: recursively free children[0..num_keys].
     2. Free node itself.
   ============================================================ */
static void free_nodes(TTNode *node) {
    if (!node) return;                              // Base case
    if (!node->is_leaf) {                           // If internal
        for (int i = 0; i <= node->num_keys; i++)   // Loop through children
            free_nodes(node->children[i]);          // Recurse free
    }
    free(node);                                     // Free this node
}

/* ============================================================
   free_tree(tree)
   ALGORITHM:
     1. Free node hierarchy.
     2. Free tree wrapper.
   ============================================================ */
static void free_tree(TTTree *tree) {
    if (!tree) return;                              // Nothing to free
    free_nodes(tree->root);                         // Free all nodes
    free(tree);                                     // Free wrapper
}

/* ============================================================
   menu_loop(tree)
   ALGORITHM:
     Loop until user chooses quit:
       1. Show menu.
       2. Read choice.
       3. Perform action (insert/delete/search/print/inorder).
       4. On quit: free tree and return.
   ============================================================ */
static void menu_loop(TTTree *tree) {
    int choice;                                     // Menu choice
    while (1) {                                     // Infinite loop until break
        printf("\n=== 2-3 Tree Menu ===\n");        // Menu header
        printf("1. Insert key\n");                  // Option insert
        printf("2. Delete key\n");                  // Option delete
        printf("3. Search key\n");                  // Option search
        printf("4. Print structure\n");             // Option print
        printf("5. In-order traversal\n");          // Option inorder
        printf("6. Quit\n");                       // Option quit
        printf("Enter choice: ");                   // Prompt
        if (scanf("%d", &choice) != 1) {            // Read choice
            int ch;                                 // Temp var
            while ((ch = getchar()) != '\n' && ch != EOF) {} // Flush bad input
            printf("Invalid input.\n");             // Report
            continue;                               // Restart loop
        }
        if (choice == 1) {                          // Insert path
            int k;                                  // Key variable
            printf("Enter key to insert: ");        // Prompt
            if (scanf("%d", &k) == 1)               // Read key
                insert_unique(tree, k);             // Insert key
            else {                                  // Bad input
                int ch;                             // Temp
                while ((ch = getchar()) != '\n' && ch != EOF) {} // Flush
                printf("Invalid key.\n");           // Report
            }
        } else if (choice == 2) {                   // Delete path
            int k;                                  // Key variable
            printf("Enter key to delete: ");        // Prompt
            if (scanf("%d", &k) == 1)               // Read key
                delete_key(tree, k);                // Delete
            else {                                  // Bad input
                int ch;                             // Temp
                while ((ch = getchar()) != '\n' && ch != EOF) {} // Flush
                printf("Invalid key.\n");           // Report
            }
        } else if (choice == 3) {                   // Search path
            int k;                                  // Key variable
            printf("Enter key to search: ");        // Prompt
            if (scanf("%d", &k) == 1)               // Read key
                printf("Key %d %s.\n", k, search(tree, k) ? "FOUND" : "NOT found"); // Report
            else {                                  // Bad input
                int ch;                             // Temp
                while ((ch = getchar()) != '\n' && ch != EOF) {} // Flush
                printf("Invalid key.\n");           // Report
            }
        } else if (choice == 4) {                   // Print structure
            if (!tree->root)                        // If empty
                printf("(tree empty)\n");           // Report empty
            else
                print_structure(tree->root, 0);     // Print structure
        } else if (choice == 5) {                   // In-order traversal
            if (!tree->root)                        // If empty
                printf("(tree empty)\n");           // Report empty
            else {
                inorder(tree->root);                // Traverse
                printf("\n");                       // Newline
            }
        } else if (choice == 6) {                   // Quit option
            printf("Exiting...\n");                 // Message
            free_tree(tree);                        // Free memory
            return;                                 // Exit loop
        } else {                                    // Invalid menu choice
            printf("Invalid choice.\n");            // Report invalid selection
        }
    }
}

/* ============================================================
   main()
   ALGORITHM:
     1. Create tree.
     2. Insert demo keys (shows splits).
     3. Print initial structure and in-order.
     4. Enter interactive menu.
   ============================================================ */
int main(void) {
    TTTree *tree = create_tree();                   // Create a new tree
    if (!tree) return 1;                            // Exit if allocation failed
    printf("=== Rebuilt Safe 2-3 Tree Demo ===\n"); // Banner
    int demo[] = {20,5,1,15,30,25,40,10,50,60,2,3}; // Demo key array
    int dn = (int)(sizeof(demo)/sizeof(demo[0]));   // Number of demo keys
    for (int i = 0; i < dn; i++)                    // Loop over demo keys
        insert_unique(tree, demo[i]);               // Insert each
    printf("\n-- Initial Structure --\n");          // Header
    print_structure(tree->root, 0);                 // Show tree
    printf("\n-- Initial In-Order --\n");           // Header
    inorder(tree->root);                            // Print sorted keys
    printf("\n");                                   // Newline
    menu_loop(tree);                                // Start interactive menu
    return 0;                                       // Program end
}

