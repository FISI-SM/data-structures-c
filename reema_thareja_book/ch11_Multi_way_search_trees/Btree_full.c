// Include standard I/O for printing and reading user input.
#include <stdio.h>
// Include stdlib for malloc, free, exit codes.
#include <stdlib.h>
// Include stdbool for bool, true, false.
#include <stdbool.h>

// -----------------------------------------------------------------------------
// Set the B-Tree minimum degree (a.k.a. 't' in most textbooks).
// Change this value to experiment with node capacity.
// -----------------------------------------------------------------------------
#define MIN_DEGREE 3

// -----------------------------------------------------------------------------
// Forward-declare BTreeNode so we can reference it in the struct.
// -----------------------------------------------------------------------------
typedef struct BTreeNode BTreeNode;

// -----------------------------------------------------------------------------
// Define the BTreeNode structure representing a single node in the tree.
// -----------------------------------------------------------------------------
struct BTreeNode {
    // Pointer to dynamically allocated array of keys (size = 2*t - 1).
    int *keys;
    // Pointer to dynamically allocated array of child pointers (size = 2*t).
    BTreeNode **children;
    // Current number of keys stored in this node.
    int num_keys;
    // True if node is a leaf; false if internal.
    bool is_leaf;
    // Store this node's copy of the tree's min_degree (t).
    int min_degree;
};

// -----------------------------------------------------------------------------
// Define the BTree wrapper containing the root pointer and global degree.
// -----------------------------------------------------------------------------
typedef struct BTree {
    // Pointer to root node (NULL when empty).
    BTreeNode *root;
    // Global min_degree (t) used by all nodes.
    int min_degree;
} BTree;

/* ============================================================================
 *  FUNCTION PROTOTYPES
 * ==========================================================================*/
static BTreeNode *create_node(int min_degree, bool is_leaf);
static BTree *create_btree(int min_degree);
static BTreeNode *search_node(BTreeNode *node, int key, int *pos_out);
static bool search_key(BTree *tree, int key);
static void split_child(BTreeNode *parent, int index, BTreeNode *full_child);
static bool insert_unique(BTree *tree, int key); /* returns false if duplicate */
static void insert_non_full(BTreeNode *node, int key);
static void insert(BTree *btree, int key);
static int get_predecessor(BTreeNode *node, int idx);
static int get_successor(BTreeNode *node, int idx);
static void borrow_from_prev(BTreeNode *node, int idx);
static void borrow_from_next(BTreeNode *node, int idx);
static void merge_children(BTreeNode *node, int idx);
static void fill_child(BTreeNode *node, int idx);
static void delete_from_node(BTreeNode *node, int key);
static void delete_key(BTree *tree, int key);
static void inorder_traversal(BTreeNode *node);
static void print_tree_structure(BTreeNode *node, int level);
static void free_btree_nodes(BTreeNode *node);
static void free_btree(BTree *tree);
static void menu_loop(BTree *tree);

/* ============================================================================
 *  create_node(min_degree, is_leaf)
 *  ALGORITHM:
 *    1. Allocate node struct.
 *    2. Allocate keys array size = 2*t - 1.
 *    3. Allocate children array size = 2*t.
 *    4. Initialize counters + leaf flag + children NULL.
 *    5. Return node or NULL on failure.
 * ==========================================================================*/
static BTreeNode *create_node(int min_degree, bool is_leaf)
{
    // Allocate memory for node structure.
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    // Check allocation success.
    if (!node) {
        // Report error.
        printf("Memory allocation failed for node\n");
        // Return NULL.
        return NULL;
    }
    // Record min_degree in node.
    node->min_degree = min_degree;
    // Record whether node is a leaf.
    node->is_leaf = is_leaf;
    // Start with 0 keys.
    node->num_keys = 0;
    // Allocate keys array (2*t - 1).
    node->keys = (int *)malloc((2 * min_degree - 1) * sizeof(int));
    // Check keys allocation.
    if (!node->keys) {
        // Report error.
        printf("Memory allocation failed for keys\n");
        // Free node structure.
        free(node);
        // Return NULL.
        return NULL;
    }
    // Allocate children pointer array (2*t).
    node->children = (BTreeNode **)malloc((2 * min_degree) * sizeof(BTreeNode *));
    // Check children allocation.
    if (!node->children) {
        // Report error.
        printf("Memory allocation failed for children\n");
        // Free keys array.
        free(node->keys);
        // Free node.
        free(node);
        // Return NULL.
        return NULL;
    }
    // Initialize all child pointers to NULL.
    for (int i = 0; i < 2 * min_degree; i++) {
        // Set child[i] = NULL.
        node->children[i] = NULL;
    }
    // Return initialized node.
    return node;
}

/* ============================================================================
 *  create_btree(min_degree)
 *  ALGORITHM:
 *    1. Allocate BTree wrapper.
 *    2. Set min_degree.
 *    3. Set root = NULL (empty tree).
 *    4. Return tree or NULL on failure.
 * ==========================================================================*/
static BTree *create_btree(int min_degree)
{
    // Allocate the tree wrapper structure.
    BTree *btree = (BTree *)malloc(sizeof(BTree));
    // Check allocation success.
    if (!btree) {
        // Report error.
        printf("Memory allocation failed for B-tree\n");
        // Return NULL.
        return NULL;
    }
    // Store the global min_degree in the tree.
    btree->min_degree = min_degree;
    // Start with an empty root.
    btree->root = NULL;
    // Return the newly allocated B-tree.
    return btree;
}

/* ============================================================================
 *  search_node(node, key, pos_out)
 *  Search within subtree rooted at node.
 *  If found: return node, set *pos_out = key index.
 *  If not found: return NULL, *pos_out undefined.
 * ==========================================================================*/
static BTreeNode *search_node(BTreeNode *node, int key, int *pos_out)
{
    // If subtree empty, not found.
    if (node == NULL)
        return NULL;
    // Start scanning keys from left.
    int i = 0;
    // Move forward while search key greater than current key.
    while (i < node->num_keys && key > node->keys[i]) {
        // Advance index.
        i++;
    }
    // If we stopped within range and found key exactly, report found.
    if (i < node->num_keys && key == node->keys[i]) {
        // Store index for caller.
        if (pos_out) *pos_out = i;
        // Return node containing key.
        return node;
    }
    // If node is leaf, key not present deeper.
    if (node->is_leaf)
        return NULL;
    // Otherwise recurse into child i.
    return search_node(node->children[i], key, pos_out);
}

/* ============================================================================
 *  search_key(tree, key)
 *  Wrapper: search from root; return true if found.
 * ==========================================================================*/
static bool search_key(BTree *tree, int key)
{
    // If tree or root empty, not found.
    if (tree == NULL || tree->root == NULL)
        return false;
    // Call recursive search.
    BTreeNode *found = search_node(tree->root, key, NULL);
    // Return true if found non-NULL.
    return (found != NULL);
}

/* ============================================================================
 *  split_child(parent, index, full_child)
 *  Split full child at parent->children[index].
 *  Pre: full_child has 2*t-1 keys.
 *  Post: two nodes w/ t-1 keys; median promoted into parent.
 * ==========================================================================*/
static void split_child(BTreeNode *parent, int index, BTreeNode *full_child)
{
    // Store degree t for convenience.
    int t = full_child->min_degree;
    // Create new sibling node w/ same leaf flag.
    BTreeNode *new_child = create_node(t, full_child->is_leaf);
    // Copy t-1 keys from full_child into new_child.
    new_child->num_keys = t - 1;
    // For each key to move...
    for (int i = 0; i < t - 1; i++) {
        // Copy key from full_child position i+t into new_child position i.
        new_child->keys[i] = full_child->keys[i + t];
    }
    // If not leaf, move t children pointers.
    if (!full_child->is_leaf) {
        // Copy each child pointer.
        for (int i = 0; i < t; i++) {
            // Move child pointer from offset i+t.
            new_child->children[i] = full_child->children[i + t];
        }
    }
    // Reduce full_child key count to t-1 keys kept.
    full_child->num_keys = t - 1;
    // Shift parent's child pointers right to open slot at index+1.
    for (int i = parent->num_keys; i >= index + 1; i--) {
        // Move child pointer right one slot.
        parent->children[i + 1] = parent->children[i];
    }
    // Link new_child as parent's child at index+1.
    parent->children[index + 1] = new_child;
    // Shift parent's keys right to open slot at index.
    for (int i = parent->num_keys - 1; i >= index; i--) {
        // Move key right one slot.
        parent->keys[i + 1] = parent->keys[i];
    }
    // Promote full_child median key into parent slot index.
    parent->keys[index] = full_child->keys[t - 1];
    // Increase parent's key count by one.
    parent->num_keys++;
}

/* ============================================================================
 *  insert_non_full(node, key)
 *  Assumes node is NOT full.
 *  If leaf: insert key in sorted order (check duplicate).
 *  If internal: locate child; if child full => split; descend correct child.
 * ==========================================================================*/
static void insert_non_full(BTreeNode *node, int key)
{
    // Start at last key index.
    int i = node->num_keys - 1;
    // If node is a leaf...
    if (node->is_leaf) {
        // Move keys greater than key one step to the right.
        while (i >= 0 && node->keys[i] > key) {
            // Shift key to the right.
            node->keys[i + 1] = node->keys[i];
            // Decrement i.
            i--;
        }
        // If i >=0 and equal key found, duplicate -> ignore.
        if (i >= 0 && node->keys[i] == key) {
            // Report duplicate.
            printf("Duplicate %d ignored (already present).\n", key);
            // Return without inserting duplicate.
            return;
        }
        // Insert new key at gap (i+1).
        node->keys[i + 1] = key;
        // Increase key count.
        node->num_keys++;
    } else {
        // Internal node: move i down past keys > key.
        while (i >= 0 && node->keys[i] > key) {
            // Decrement index left.
            i--;
        }
        // Child index to descend is i+1.
        i++;
        // Safety: ensure child exists.
        if (node->children[i] == NULL) {
            // Report missing child (corrupt tree).
            printf("Error: child[%d] is NULL in insert_non_full.\n", i);
            // Abort insert path.
            return;
        }
        // If child is full, we must split before descending.
        if (node->children[i]->num_keys == 2 * node->min_degree - 1) {
            // Split child at position i.
            split_child(node, i, node->children[i]);
            // After split, if key > promoted key, descend into right child.
            if (node->keys[i] < key)
                i++;
        }
        // Recurse into chosen child (now safe non-full).
        insert_non_full(node->children[i], key);
    }
}

/* ============================================================================
 *  insert(btree, key)
 *  Public insertion wrapper.
 *  Handles empty tree and root split before delegating to insert_non_full.
 * ==========================================================================*/
static void insert(BTree *btree, int key)
{
    // If no root exists, create a new leaf root.
    if (btree->root == NULL) {
        // Create root node (leaf).
        btree->root = create_node(btree->min_degree, true);
        // Check creation success.
        if (!btree->root) {
            // Report failure.
            printf("Failed to create root node\n");
            // Abort.
            return;
        }
        // Insert key in empty root.
        btree->root->keys[0] = key;
        // Root now has one key.
        btree->root->num_keys = 1;
        // Report insertion event.
        printf("Inserted %d as root.\n", key);
        // Done.
        return;
    }

    // If root is full, we must grow tree height by one.
    if (btree->root->num_keys == 2 * btree->min_degree - 1) {
        // Create a new internal root.
        BTreeNode *new_root = create_node(btree->min_degree, false);
        // Check allocation success.
        if (!new_root) {
            // Report error.
            printf("Failed to create new root during split.\n");
            // Abort insert.
            return;
        }
        // Old root becomes child[0] of new root.
        new_root->children[0] = btree->root;
        // Split old root.
        split_child(new_root, 0, btree->root);
        // Update tree root pointer.
        btree->root = new_root;
        // Report root split.
        printf("Root was full; split performed.\n");
    }

    // Now root is guaranteed non-full: insert below it.
    insert_non_full(btree->root, key);
    // Report insertion result (message may not appear on duplicate).
    printf("Inserted %d (if not duplicate).\n", key);
}

/* ============================================================================
 *  insert_unique(tree, key)
 *  Convenience wrapper: checks for duplicate before calling insert().
 *  Returns:
 *    true  = inserted (key not present)
 *    false = duplicate ignored
 * ==========================================================================*/
static bool insert_unique(BTree *tree, int key)
{
    // If tree empty, just call insert (will create root).
    if (tree->root == NULL) {
        // Insert into empty tree.
        insert(tree, key);
        // Return inserted true.
        return true;
    }
    // Check for existing key first.
    BTreeNode *existing = search_node(tree->root, key, NULL);
    // If found, report duplicate and fail.
    if (existing != NULL) {
        // Print duplicate message.
        printf("Duplicate %d ignored (already in tree).\n", key);
        // Return not inserted.
        return false;
    }
    // Otherwise perform normal insert.
    insert(tree, key);
    // Return inserted true.
    return true;
}

/* ============================================================================
 *  get_predecessor(node, idx)
 *  Return the immediate predecessor key of node->keys[idx].
 *  We walk into left child then keep going rightmost until leaf.
 * ==========================================================================*/
static int get_predecessor(BTreeNode *node, int idx)
{
    // Start in left child of key idx.
    BTreeNode *cur = node->children[idx];
    // Descend until leaf found.
    while (!cur->is_leaf) {
        // Move to rightmost child (num_keys).
        cur = cur->children[cur->num_keys];
    }
    // Return last key in that leaf.
    return cur->keys[cur->num_keys - 1];
}

/* ============================================================================
 *  get_successor(node, idx)
 *  Return the immediate successor key of node->keys[idx].
 *  We walk into right child then keep going leftmost until leaf.
 * ==========================================================================*/
static int get_successor(BTreeNode *node, int idx)
{
    // Start in right child of key idx.
    BTreeNode *cur = node->children[idx + 1];
    // Descend until leaf found.
    while (!cur->is_leaf) {
        // Move to leftmost child (0).
        cur = cur->children[0];
    }
    // Return first key in that leaf.
    return cur->keys[0];
}

/* ============================================================================
 *  borrow_from_prev(node, idx)
 *  Borrow a key from left sibling of child[idx], pushing a key down.
 *  Pre: child[idx-1] has >= t keys.
 * ==========================================================================*/
static void borrow_from_prev(BTreeNode *node, int idx)
{
    // Get child we are fixing.
    BTreeNode *child = node->children[idx];
    // Get left sibling.
    BTreeNode *sibling = node->children[idx - 1];
    // Shift child's keys right one to make room at front.
    for (int i = child->num_keys - 1; i >= 0; i--) {
        // Move key to the right.
        child->keys[i + 1] = child->keys[i];
    }
    // If child not leaf, shift children pointers right too.
    if (!child->is_leaf) {
        for (int i = child->num_keys; i >= 0; i--) {
            // Move child pointer right.
            child->children[i + 1] = child->children[i];
        }
    }
    // Bring down key from parent into child's first key slot.
    child->keys[0] = node->keys[idx - 1];
    // If child internal, move sibling's last child pointer.
    if (!child->is_leaf) {
        // Attach sibling's last child at child->children[0].
        child->children[0] = sibling->children[sibling->num_keys];
    }
    // Move sibling's last key up into parent slot.
    node->keys[idx - 1] = sibling->keys[sibling->num_keys - 1];
    // Increase child's key count.
    child->num_keys++;
    // Decrease sibling's key count.
    sibling->num_keys--;
}

/* ============================================================================
 *  borrow_from_next(node, idx)
 *  Borrow a key from right sibling of child[idx].
 *  Pre: child[idx+1] has >= t keys.
 * ==========================================================================*/
static void borrow_from_next(BTreeNode *node, int idx)
{
    // Get child needing a key.
    BTreeNode *child = node->children[idx];
    // Get right sibling.
    BTreeNode *sibling = node->children[idx + 1];
    // Bring down parent key into child's last slot.
    child->keys[child->num_keys] = node->keys[idx];
    // If child internal, bring sibling's first child pointer over.
    if (!child->is_leaf) {
        // Attach sibling's first child pointer.
        child->children[child->num_keys + 1] = sibling->children[0];
    }
    // Move sibling's first key up into parent slot.
    node->keys[idx] = sibling->keys[0];
    // Shift sibling keys left to close gap.
    for (int i = 1; i < sibling->num_keys; i++) {
        // Move key left.
        sibling->keys[i - 1] = sibling->keys[i];
    }
    // If sibling internal, shift its children left too.
    if (!sibling->is_leaf) {
        for (int i = 1; i <= sibling->num_keys; i++) {
            // Move child pointer left.
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    // Increase child key count.
    child->num_keys++;
    // Decrease sibling key count.
    sibling->num_keys--;
}

/* ============================================================================
 *  merge_children(node, idx)
 *  Merge child[idx] + key[idx] + child[idx+1] into a single node at child[idx].
 *  After merge: child[idx] has 2*t-1 keys; child[idx+1] freed; key[idx] removed.
 * ==========================================================================*/
static void merge_children(BTreeNode *node, int idx)
{
    // Get degree t from node.
    int t = node->min_degree;
    // Child to left of merge point.
    BTreeNode *child = node->children[idx];
    // Child to right of merge point.
    BTreeNode *sibling = node->children[idx + 1];
    // Insert parent key[idx] into child at position t-1.
    child->keys[t - 1] = node->keys[idx];
    // Copy sibling's keys after that.
    for (int i = 0; i < sibling->num_keys; i++) {
        // Copy each key.
        child->keys[i + t] = sibling->keys[i];
    }
    // If internal, copy sibling children pointers.
    if (!child->is_leaf) {
        for (int i = 0; i <= sibling->num_keys; i++) {
            // Copy child pointer.
            child->children[i + t] = sibling->children[i];
        }
    }
    // Update key count in merged child.
    child->num_keys += sibling->num_keys + 1;
    // Shift parent's keys left to remove key[idx].
    for (int i = idx + 1; i < node->num_keys; i++) {
        // Move key left.
        node->keys[i - 1] = node->keys[i];
    }
    // Shift parent's children pointers left to remove sibling slot.
    for (int i = idx + 2; i <= node->num_keys; i++) {
        // Move child left.
        node->children[i - 1] = node->children[i];
    }
    // Decrement parent key count.
    node->num_keys--;
    // Free sibling's keys array.
    free(sibling->keys);
    // Free sibling's children array.
    free(sibling->children);
    // Free sibling node.
    free(sibling);
}

/* ============================================================================
 *  fill_child(node, idx)
 *  Ensure child[idx] has at least t-1 keys before descent.
 *  Try borrow from left; else borrow from right; else merge with sibling.
 * ==========================================================================*/
static void fill_child(BTreeNode *node, int idx)
{
    // Determine degree t.
    int t = node->min_degree;
    // If left sibling exists and has ≥ t keys, borrow left.
    if (idx != 0 && node->children[idx - 1]->num_keys >= t) {
        // Borrow from left sibling.
        borrow_from_prev(node, idx);
    }
    // Else if right sibling exists and has ≥ t keys, borrow right.
    else if (idx != node->num_keys && node->children[idx + 1]->num_keys >= t) {
        // Borrow from right sibling.
        borrow_from_next(node, idx);
    }
    // Else must merge with a sibling.
    else {
        // If idx is last child, merge with left sibling.
        if (idx == node->num_keys) {
            // Merge child[idx-1] and child[idx].
            merge_children(node, idx - 1);
        } else {
            // Merge child[idx] and child[idx+1].
            merge_children(node, idx);
        }
    }
}

/* ============================================================================
 *  delete_from_node(node, key)
 *  Delete key from subtree rooted at node.
 *  Implements CLRS B-tree deletion cases.
 * ==========================================================================*/
static void delete_from_node(BTreeNode *node, int key)
{
    // i will scan for key in this node.
    int i = 0;
    // Move i forward while key > node->keys[i].
    while (i < node->num_keys && key > node->keys[i]) {
        // Advance.
        i++;
    }
    // If key found in this node...
    if (i < node->num_keys && node->keys[i] == key) {
        // If node is leaf, delete directly.
        if (node->is_leaf) {
            // Shift keys left to remove index i.
            for (int j = i + 1; j < node->num_keys; j++) {
                // Move key left.
                node->keys[j - 1] = node->keys[j];
            }
            // Decrement key count.
            node->num_keys--;
        } else {
            // Internal node case.
            // Determine degree t.
            int t = node->min_degree;
            // If left child has ≥ t keys...
            if (node->children[i]->num_keys >= t) {
                // Get predecessor value.
                int pred = get_predecessor(node, i);
                // Replace key with predecessor.
                node->keys[i] = pred;
                // Recurse delete predecessor from left subtree.
                delete_from_node(node->children[i], pred);
            }
            // Else if right child has ≥ t keys...
            else if (node->children[i + 1]->num_keys >= t) {
                // Get successor value.
                int succ = get_successor(node, i);
                // Replace key with successor.
                node->keys[i] = succ;
                // Recurse delete successor from right subtree.
                delete_from_node(node->children[i + 1], succ);
            }
            // Else both children have t-1 keys, so merge them and delete in merged node.
            else {
                // Merge children[i] and children[i+1] around key i.
                merge_children(node, i);
                // Recurse delete key in merged child now at children[i].
                delete_from_node(node->children[i], key);
            }
        }
    }
    // Key not found in this node; must descend if not leaf.
    else {
        // If leaf, key does not exist in tree; nothing to do.
        if (node->is_leaf) {
            // Report not found (debug; comment out if noisy).
            // printf("Key %d not found (leaf reached).\n", key);
            return;
        }
        // Determine which child to descend into (i).
        // If key > all keys, i == num_keys => rightmost child.
        // Ensure child has at least t keys before descending.
        int t = node->min_degree;
        // If child i has only t-1 keys, fix it (borrow/merge).
        if (node->children[i]->num_keys < t) {
            // Call fill_child to ensure ≥ t keys on descent.
            fill_child(node, i);
        }
        // Now decide which child we actually go into:
        // If we merged child i with child i+1, and i == num_keys originally,
        // we need to descend to i-1 slot. But fill_child already handled index.
        // Re-check bounds: if i > node->num_keys, step back.
        if (i > node->num_keys)
            i = node->num_keys;
        // Recurse delete in appropriate child subtree.
        delete_from_node(node->children[i], key);
    }
}

/* ============================================================================
 *  delete_key(tree, key)
 *  Public delete wrapper:
 *    1. If tree empty -> return.
 *    2. Call delete_from_node(root, key).
 *    3. If root ends up empty and is internal -> promote child[0] as new root.
 * ==========================================================================*/
static void delete_key(BTree *tree, int key)
{
    // If tree empty, nothing to delete.
    if (tree == NULL || tree->root == NULL) {
        // Report empty.
        printf("Tree empty; cannot delete %d.\n", key);
        // Done.
        return;
    }
    // Perform recursive delete starting at root.
    delete_from_node(tree->root, key);
    // If root lost all keys...
    if (tree->root->num_keys == 0) {
        // If root is internal (non-leaf), promote its first child.
        if (!tree->root->is_leaf) {
            // Store old root pointer.
            BTreeNode *old_root = tree->root;
            // Promote its child[0] as the new root.
            tree->root = old_root->children[0];
            // Free old root's arrays.
            free(old_root->keys);
            free(old_root->children);
            free(old_root);
        } else {
            // Root is leaf and empty -> entire tree becomes empty.
            free(tree->root->keys);
            free(tree->root->children);
            free(tree->root);
            tree->root = NULL;
        }
    }
    // Report deletion done.
    printf("Delete %d completed (if existed).\n", key);
}

/* ============================================================================
 *  inorder_traversal(node)
 *  Print all keys in sorted order via in-order B-tree traversal.
 * ==========================================================================*/
static void inorder_traversal(BTreeNode *node)
{
    // If subtree empty, return.
    if (node == NULL)
        return;
    // For each key position...
    for (int i = 0; i < node->num_keys; i++) {
        // Visit left child before printing key (if internal).
        if (!node->is_leaf)
            inorder_traversal(node->children[i]);
        // Print current key.
        printf("%d ", node->keys[i]);
    }
    // Visit last right child (if internal).
    if (!node->is_leaf)
        inorder_traversal(node->children[node->num_keys]);
}

/* ============================================================================
 *  print_tree_structure(node, level)
 *  Visualize tree by levels with indentation.
 * ==========================================================================*/
static void print_tree_structure(BTreeNode *node, int level)
{
    // Stop if subtree empty.
    if (!node)
        return;
    // Indent two spaces per level.
    for (int i = 0; i < level; i++)
        printf("  ");
    // Print node info with brackets.
    printf("Level %d: [", level);
    // Print all keys separated by comma.
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d", node->keys[i]);
        if (i < node->num_keys - 1)
            printf(", ");
    }
    // Show leaf/internal label and newline.
    printf("] (%s)\n", node->is_leaf ? "leaf" : "int");
    // Recurse children if internal.
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++)
            print_tree_structure(node->children[i], level + 1);
    }
}

/* ============================================================================
 *  free_btree_nodes(node)
 *  Recursively free all nodes below and including 'node'.
 * ==========================================================================*/
static void free_btree_nodes(BTreeNode *node)
{
    // Nothing to free if node NULL.
    if (!node)
        return;
    // If internal, free all children first.
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++)
            free_btree_nodes(node->children[i]);
    }
    // Free keys array.
    free(node->keys);
    // Free children array.
    free(node->children);
    // Free node structure.
    free(node);
}

/* ============================================================================
 *  free_btree(tree)
 *  Free entire B-tree and wrapper.
 * ==========================================================================*/
static void free_btree(BTree *tree)
{
    // If no tree, nothing to do.
    if (!tree)
        return;
    // Free node hierarchy starting at root.
    free_btree_nodes(tree->root);
    // Free wrapper struct.
    free(tree);
}

/* ============================================================================
 *  menu_loop(tree)
 *  Interactive menu for manual testing.
 *  Options: insert, delete, search, print structure, inorder, quit.
 * ==========================================================================*/
static void menu_loop(BTree *tree)
{
    // Variable to store user menu selection.
    int choice = 0;
    // Loop until quit.
    while (1) {
        // Print menu.
        printf("\n=== B-Tree Menu ===\n");
        printf("1. Insert key\n");
        printf("2. Delete key\n");
        printf("3. Search key\n");
        printf("4. Print tree structure\n");
        printf("5. In-order traversal\n");
        printf("6. Quit\n");
        printf("Enter choice: ");
        // Read menu number.
        if (scanf("%d", &choice) != 1) {
            // Clear bad input.
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            // Notify user invalid.
            printf("Invalid input. Try again.\n");
            // Continue loop.
            continue;
        }
        // Switch on user choice.
        switch (choice) {
            // Insert key case.
            case 1: {
                // Prompt user for key.
                printf("Enter key to insert: ");
                // Temporary variable to hold key.
                int k;
                // Read key.
                if (scanf("%d", &k) == 1) {
                    // Insert with duplicate check.
                    insert_unique(tree, k);
                } else {
                    // Invalid input; clear buffer.
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) { }
                    // Notify user.
                    printf("Invalid key.\n");
                }
                // Break switch.
                break;
            }
            // Delete key case.
            case 2: {
                // Ask for key to delete.
                printf("Enter key to delete: ");
                // Temporary variable.
                int k;
                // Read key.
                if (scanf("%d", &k) == 1) {
                    // Perform delete.
                    delete_key(tree, k);
                } else {
                    // Bad input flush.
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) { }
                    // Notify user.
                    printf("Invalid key.\n");
                }
                // Break switch.
                break;
            }
            // Search key case.
            case 3: {
                // Prompt for key.
                printf("Enter key to search: ");
                // Temporary variable.
                int k;
                // Read key.
                if (scanf("%d", &k) == 1) {
                    // Call search wrapper.
                    bool found = search_key(tree, k);
                    // Report result.
                    printf("Key %d %s.\n", k, found ? "FOUND" : "NOT found");
                } else {
                    // Flush bad input.
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) { }
                    // Notify user.
                    printf("Invalid key.\n");
                }
                // Break switch.
                break;
            }
            // Print structure case.
            case 4:
                // If empty tree, say so.
                if (tree->root == NULL)
                    printf("(tree empty)\n");
                else
                    print_tree_structure(tree->root, 0);
                // Break switch.
                break;
            // In-order traversal case.
            case 5:
                // Print sorted keys or empty.
                if (tree->root == NULL)
                    printf("(tree empty)\n");
                else {
                    inorder_traversal(tree->root);
                    printf("\n");
                }
                // Break switch.
                break;
            // Quit case.
            case 6:
                // Inform user we are quitting.
                printf("Exiting...\n");
                // Free entire tree.
                free_btree(tree);
                // Return to caller to end program.
                return;
            // Default: invalid menu selection.
            default:
                // Report invalid menu choice.
                printf("Invalid choice. Please select 1-6.\n");
                // Break switch.
                break;
        }
    }
}

/* ============================================================================
 *  main()
 *  Demo entry point:
 *    1. Create B-tree.
 *    2. Insert sample batch.
 *    3. Show structure + inorder.
 *    4. Enter interactive menu loop.
 * ==========================================================================*/
int main(void)
{
    // Create a new B-tree using global MIN_DEGREE.
    BTree *btree = create_btree(MIN_DEGREE);
    // Verify allocation success.
    if (!btree) {
        // Report failure.
        printf("Failed to create B-tree.\n");
        // Exit with error.
        return 1;
    }
    // Print startup banner.
    printf("=== B-Tree Interactive Demo ===\n");
    // Show degree info.
    printf("Minimum degree (t): %d | Max keys: %d | Min non-root keys: %d\n",
           MIN_DEGREE, 2 * MIN_DEGREE - 1, MIN_DEGREE - 1);

    // Preload some demo keys.
    int demo_keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 25};
    // Compute count of demo keys.
    int demo_n = (int)(sizeof(demo_keys) / sizeof(demo_keys[0]));
    // Insert demo keys.
    printf("\n-- Loading demo keys --\n");
    for (int i = 0; i < demo_n; i++) {
        // Insert each (duplicates ignored).
        insert_unique(btree, demo_keys[i]);
    }
    // Show tree structure after preload.
    printf("\n-- Initial B-tree structure --\n");
    print_tree_structure(btree->root, 0);
    // Show inorder traversal after preload.
    printf("\n-- Initial in-order traversal --\n");
    inorder_traversal(btree->root);
    printf("\n");

    // Start interactive loop for user commands.
    menu_loop(btree);

    // We never reach here because menu_loop frees tree and returns.
    return 0;
}

