#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free
#include <stdbool.h>  // bool, true, false

// ------------------------------------------------------------------
// MAX_KEYS: maximum keys a *single node* can hold.
// This also determines: max children = MAX_KEYS + 1.
// In this mini B+ tree, ORDER = MAX_KEYS + 1, height <= 2.
// ------------------------------------------------------------------
#define MAX_KEYS 3

// ------------------------------------------------------------------
// BPlusNode: used for BOTH leaves and internal nodes.
// - keys[] always sorted, count in num_keys.
// - children[] used ONLY when is_leaf == false.
// - next links leaves left->right for range scans / printing.
// ------------------------------------------------------------------
typedef struct BPlusNode {
    int keys[MAX_KEYS];                 // Stored keys
    struct BPlusNode *children[MAX_KEYS + 1]; // Child pointers (internal only)
    struct BPlusNode *next;             // Leaf chain pointer
    int num_keys;                       // Count of valid keys
    bool is_leaf;                       // Leaf? (true) Internal? (false)
} BPlusNode;


// ==================================================================
// create_node(is_leaf)
// Create & initialize a node (leaf or internal).
// ==================================================================
static BPlusNode *create_node(bool is_leaf)
{
    // Allocate memory for node.
    BPlusNode *node = (BPlusNode *)malloc(sizeof(BPlusNode));
    // Check allocation.
    if (!node) {
        printf("Memory allocation failed for node\n");
        return NULL;
    }
    // Start empty.
    node->num_keys = 0;
    // Record type.
    node->is_leaf = is_leaf;
    // Null all children.
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        node->children[i] = NULL;
    }
    // No next leaf yet.
    node->next = NULL;
    // Return node.
    return node;
}


// ==================================================================
// insert_in_root_after_child_split(root_ptr, old_child, new_child, sep)
// Mini helper: root is INTERNAL, and one of its CHILD LEAVES split.
// We insert separator into root and attach new_child to root.
// No root re-splitting (mini version).
// ==================================================================
static void insert_in_root_after_child_split(BPlusNode **root_ptr,
                                             BPlusNode *old_child,
                                             BPlusNode *new_child,
                                             int sep_key)
{
    // Convenience ref to root.
    BPlusNode *root = *root_ptr;

    // Sanity: root must be internal in this path.
    if (root->is_leaf) {
        printf("Internal error: expected internal root in child split.\n");
        return;
    }

    // Find index of old_child in root->children[].
    int idx = 0;
    while (idx <= root->num_keys && root->children[idx] != old_child) {
        idx++;
    }
    if (idx > root->num_keys) {
        printf("Internal error: child not found in root during split.\n");
        return;
    }

    // If root full, we cannot continue (mini version limit).
    if (root->num_keys == MAX_KEYS) {
        printf("Mini B+ Tree limit hit: root full; cannot add another child.\n");
        return;
    }

    // Shift keys to make gap at idx.
    for (int i = root->num_keys; i > idx; i--) {
        root->keys[i] = root->keys[i - 1];
    }
    // Shift children to open slot at idx+1.
    for (int i = root->num_keys + 1; i > idx + 1; i--) {
        root->children[i] = root->children[i - 1];
    }

    // Insert separator key into root.
    root->keys[idx] = sep_key;
    // Link new_child pointer at idx+1.
    root->children[idx + 1] = new_child;
    // Increment root key count.
    root->num_keys++;
}


// ==================================================================
// split_leaf_root_case(root_ptr, leaf)
// Called when the ROOT (which is a LEAF) overflows.
// We split it into two leaves and make a NEW internal root.
// ==================================================================
static void split_leaf_root_case(BPlusNode **root_ptr, BPlusNode *leaf)
{
    // Compute split position (ceil half).
    int split = (MAX_KEYS + 1) / 2;

    // Create right leaf.
    BPlusNode *new_leaf = create_node(true);
    if (!new_leaf) return;

    // Move top half keys to new_leaf.
    for (int i = split, j = 0; i < MAX_KEYS; i++, j++) {
        new_leaf->keys[j] = leaf->keys[i];
    }

    // Set counts.
    new_leaf->num_keys = MAX_KEYS - split;
    leaf->num_keys = split;

    // Link leaves.
    new_leaf->next = leaf->next;
    leaf->next = new_leaf;

    // Create new root (internal).
    BPlusNode *new_root = create_node(false);
    if (!new_root) return;

    // Promote separator (first key of new_leaf).
    new_root->keys[0] = new_leaf->keys[0];
    // Root children connect to the two leaves.
    new_root->children[0] = leaf;
    new_root->children[1] = new_leaf;
    new_root->num_keys = 1;

    // Update root pointer.
    *root_ptr = new_root;
}


// ==================================================================
// split_leaf_under_root(root_ptr, leaf)
// Called when a LEAF (child of an INTERNAL ROOT) overflows.
// Splits the leaf and inserts separator into root (no re-split).
// ==================================================================
static void split_leaf_under_root(BPlusNode **root_ptr, BPlusNode *leaf)
{
    // Compute split position.
    int split = (MAX_KEYS + 1) / 2;

    // Create right leaf.
    BPlusNode *new_leaf = create_node(true);
    if (!new_leaf) return;

    // Move top half keys.
    for (int i = split, j = 0; i < MAX_KEYS; i++, j++) {
        new_leaf->keys[j] = leaf->keys[i];
    }

    // Set counts.
    new_leaf->num_keys = MAX_KEYS - split;
    leaf->num_keys = split;

    // Link leaves.
    new_leaf->next = leaf->next;
    leaf->next = new_leaf;

    // Separator = first key in right leaf.
    int sep = new_leaf->keys[0];

    // Insert separator into root & attach new child.
    insert_in_root_after_child_split(root_ptr, leaf, new_leaf, sep);
}


// ==================================================================
// insert(root_ptr, key)
// Mini insert: supports
//   - Empty tree → make root leaf.
//   - Root leaf overflow → split root -> 1-level internal root.
//   - Insert into correct leaf under root (if root internal).
//   - Leaf overflow under root → split leaf & update root.
// No multi-level internal splits.
// ==================================================================
void insert(BPlusNode **root_ptr, int key)
{
    // If tree empty, create root leaf.
    if (*root_ptr == NULL) {
        *root_ptr = create_node(true);
        if (!*root_ptr) return;
    }

    // Start at root.
    BPlusNode *node = *root_ptr;

    // Descend to leaf (in mini version this is at most 1 step).
    while (!node->is_leaf) {
        int i = 0;
        // Move to child where key belongs.
        while (i < node->num_keys && key >= node->keys[i]) {
            i++;
        }
        node = node->children[i];
    }

    // 'node' is the leaf where we insert.
    BPlusNode *leaf = node;

    // Find insertion position.
    int i = 0;
    while (i < leaf->num_keys && key > leaf->keys[i]) {
        i++;
    }

    // Shift keys right to make room.
    for (int j = leaf->num_keys; j > i; j--) {
        leaf->keys[j] = leaf->keys[j - 1];
    }

    // Insert key.
    leaf->keys[i] = key;
    // Increase key count.
    leaf->num_keys++;

    // If leaf overflowed (== MAX_KEYS), split it.
    if (leaf->num_keys == MAX_KEYS) {
        // Root leaf case vs child leaf under root.
        if (leaf == *root_ptr) {
            split_leaf_root_case(root_ptr, leaf);
        } else {
            split_leaf_under_root(root_ptr, leaf);
        }
    }
}


// ==================================================================
// search(root, key)
// Standard B+ search.
// Descend internal nodes until leaf, then scan leaf keys.
// ==================================================================
bool search(BPlusNode *root, int key)
{
    // Empty tree.
    if (root == NULL) {
        return false;
    }

    // Start at root.
    BPlusNode *node = root;

    // Descend to leaf.
    while (!node->is_leaf) {
        int i = 0;
        // Advance while key >= node->keys[i].
        while (i < node->num_keys && key >= node->keys[i]) {
            i++;
        }
        node = node->children[i];
    }

    // Scan leaf keys.
    for (int i = 0; i < node->num_keys; i++) {
        if (node->keys[i] == key) {
            return true;
        }
    }
    return false;
}


// ==================================================================
// print_leaves(root)
// Go to leftmost leaf, then follow ->next printing keys.
// ==================================================================
void print_leaves(BPlusNode *root)
{
    // Empty tree?
    if (root == NULL) {
        printf("B+ Tree leaves: (empty)\n");
        return;
    }

    // Descend to leftmost leaf.
    BPlusNode *node = root;
    while (!node->is_leaf) {
        node = node->children[0];
    }

    // Print leaf chain.
    printf("B+ Tree leaves: ");
    while (node != NULL) {
        for (int i = 0; i < node->num_keys; i++) {
            printf("%d ", node->keys[i]);
        }
        node = node->next;
    }
    printf("\n");
}


// ==================================================================
// main()
// Demonstrate mini B+ Tree insert, print, search.
// ==================================================================
int main(void)
{
    // Start with empty tree.
    BPlusNode *root = NULL;

    // Keys to insert.
    int keys[] = {10, 20, 5, 6, 12};
    int n = (int)(sizeof(keys) / sizeof(keys[0]));

    // Insert all keys.
    for (int i = 0; i < n; i++) {
        insert(&root, keys[i]);
    }

    // Show resulting leaves.
    print_leaves(root);

    // Test searches.
    int search_keys[] = {6, 15};
    for (int i = 0; i < 2; i++) {
        if (search(root, search_keys[i])) {
            printf("Key %d found!\n", search_keys[i]);
        } else {
            printf("Key %d not found!\n", search_keys[i]);
        }
    }

    // NOTE: No free() here (mini demo). Add free if needed.
    return 0;
}

