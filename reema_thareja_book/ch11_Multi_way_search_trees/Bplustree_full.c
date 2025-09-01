/**********************************************************************
 * FULL B+ TREE IMPLEMENTATION (INSERT + DELETE + SEARCH + PRINT + FREE)
 * --------------------------------------------------------------------
 * - Classic B+ Tree: all data keys live in LEAVES.
 * - Internal nodes store SEPARATOR KEYS = first key in right child.
 * - Leaves linked via ->next for range scans.
 * - Supports: insert, delete (borrow/merge), search, structure print,
 *   leaf print, range print, free.
 * - Beginner-friendly: algorithm block above each function + per-line
 *   comments immediately above lines of code.
 * - Kali Linux terminal friendly.
 *********************************************************************/

#include <stdio.h>      /* printf, scanf */
#include <stdlib.h>     /* malloc, free, exit */
#include <stdbool.h>    /* bool, true, false */

/* ------------------------------------------------------------------ */
/* B+ TREE ORDER CONFIGURATION                                        */
/* ------------------------------------------------------------------ */
/* ORDER = maximum number of child pointers in an internal node.      */
#define ORDER 4

/* Derived size helpers */
#define MAX_KEYS        (ORDER - 1)                /* max keys in any node */
#define MIN_CHILDREN    ((ORDER + 1) / 2)          /* ceil(ORDER/2) children */
#define MIN_INTERNAL_KEYS (MIN_CHILDREN - 1)       /* min keys in internal */
#define MIN_LEAF_KEYS   ((MAX_KEYS + 1) / 2)       /* ceil(max_keys/2) keys */


/* ------------------------------------------------------------------ */
/* FORWARD DECLARATIONS (structs)                                      */
/* ------------------------------------------------------------------ */
struct BPlusNode;

/* ------------------------------------------------------------------ */
/* NODE STRUCT                                                         */
/* ------------------------------------------------------------------ */
typedef struct BPlusNode {
    /* Pointer array of keys (dynamic alloc). */
    int *keys;
    /* Pointer array of child pointers (dynamic alloc). */
    struct BPlusNode **children;
    /* Number of valid keys currently stored. */
    int num_keys;
    /* True if this node is a leaf. */
    bool is_leaf;
    /* Leaf chain pointer to next leaf (NULL if last). */
    struct BPlusNode *next;
} BPlusNode;


/* ------------------------------------------------------------------ */
/* TREE WRAPPER STRUCT                                                 */
/* ------------------------------------------------------------------ */
typedef struct BPlusTree {
    /* Root pointer (NULL when tree empty). */
    BPlusNode *root;
} BPlusTree;


/* ================================================================== */
/*  create_node(is_leaf)                                              */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Allocate memory for a node.                                    */
/*  2. Allocate keys array of length MAX_KEYS.                        */
/*  3. Allocate children array of length ORDER.                       */
/*  4. Initialize num_keys=0, is_leaf, next=NULL.                     */
/*  5. Set all children[i]=NULL.                                      */
/*  6. Return node pointer (NULL on failure).                         */
/* ================================================================== */
static BPlusNode *create_node(bool is_leaf)
{
    /* Allocate space for node struct. */
    BPlusNode *node = (BPlusNode *)malloc(sizeof(BPlusNode));
    /* Check allocation success. */
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed for node\n");
        return NULL;
    }

    /* Allocate keys array. */
    node->keys = (int *)malloc(MAX_KEYS * sizeof(int));
    /* Check keys allocation. */
    if (node->keys == NULL) {
        fprintf(stderr, "Memory allocation failed for node->keys\n");
        free(node);
        return NULL;
    }

    /* Allocate children pointer array. */
    node->children = (BPlusNode **)malloc(ORDER * sizeof(BPlusNode *));
    /* Check children allocation. */
    if (node->children == NULL) {
        fprintf(stderr, "Memory allocation failed for node->children\n");
        free(node->keys);
        free(node);
        return NULL;
    }

    /* Initialize child pointers to NULL. */
    for (int i = 0; i < ORDER; i++) {
        node->children[i] = NULL;
    }

    /* Start with 0 keys. */
    node->num_keys = 0;
    /* Record leaf status passed in. */
    node->is_leaf = is_leaf;
    /* No neighbor yet in leaf chain. */
    node->next = NULL;

    /* Return the ready node. */
    return node;
}


/* ================================================================== */
/*  create_bplustree()                                                */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Allocate tree wrapper.                                         */
/*  2. Set root=NULL (empty tree).                                    */
/*  3. Return tree pointer (NULL on failure).                         */
/* ================================================================== */
static BPlusTree *create_bplustree(void)
{
    /* Allocate tree wrapper struct. */
    BPlusTree *tree = (BPlusTree *)malloc(sizeof(BPlusTree));
    /* Check allocation. */
    if (tree == NULL) {
        fprintf(stderr, "Memory allocation failed for BPlusTree\n");
        return NULL;
    }
    /* Empty tree begins with no root. */
    tree->root = NULL;
    /* Return the new tree. */
    return tree;
}


/* ================================================================== */
/*  find_leaf(node, key)                                              */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If node NULL → return NULL.                                    */
/*  2. While node not leaf:                                           */
/*     a. Find first key >= key; use index i.                         */
/*     b. Descend to children[i].                                     */
/*  3. Return leaf node reached.                                      */
/* ================================================================== */
static BPlusNode *find_leaf(BPlusNode *node, int key)
{
    /* Return NULL if subtree empty. */
    if (node == NULL) {
        return NULL;
    }

    /* Keep going down until we reach a leaf. */
    while (!node->is_leaf) {
        /* Start index scan at 0. */
        int i = 0;
        /* Move right while key >= node->keys[i]. */
        while (i < node->num_keys && key >= node->keys[i]) {
            i++;
        }
        /* Descend into the chosen child. */
        node = node->children[i];
    }

    /* node is now leaf; return it. */
    return node;
}


/* ================================================================== */
/*  search_exact(tree, key)                                           */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If tree empty → NOT FOUND.                                     */
/*  2. leaf = find_leaf(root, key).                                   */
/*  3. Scan leaf keys for key.                                        */
/*  4. If found → true else false.                                    */
/* ================================================================== */
static bool search_exact(BPlusTree *tree, int key)
{
    /* If tree or root missing, fail. */
    if (tree == NULL || tree->root == NULL) {
        return false;
    }

    /* Find leaf where key would be. */
    BPlusNode *leaf = find_leaf(tree->root, key);
    /* If no leaf found, not in tree. */
    if (leaf == NULL) {
        return false;
    }

    /* Scan keys in leaf. */
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            return true;
        }
    }
    /* Not found. */
    return false;
}


/* ================================================================== */
/*  search_range(tree, low, high)                                     */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If tree empty → print empty.                                   */
/*  2. leaf = find_leaf(root, low).                                   */
/*  3. From that leaf forward (using ->next):                         */
/*     - Print keys within [low,high].                                */
/*     - Stop when key>high or no more leaves.                        */
/* ================================================================== */
static void search_range(BPlusTree *tree, int low, int high)
{
    /* If tree empty, print and return. */
    if (tree == NULL || tree->root == NULL) {
        printf("(empty)\n");
        return;
    }

    /* Find starting leaf for low. */
    BPlusNode *leaf = find_leaf(tree->root, low);
    /* If none, done. */
    if (leaf == NULL) {
        printf("(empty)\n");
        return;
    }

    /* Print label. */
    printf("Range [%d..%d]: ", low, high);

    /* Walk leaves while keys exist. */
    while (leaf != NULL) {
        /* Scan keys in this leaf. */
        for (int i = 0; i < leaf->num_keys; i++) {
            /* If within range, print. */
            if (leaf->keys[i] >= low && leaf->keys[i] <= high) {
                printf("%d ", leaf->keys[i]);
            }
            /* If we passed high, stop early. */
            else if (leaf->keys[i] > high) {
                printf("\n");
                return;
            }
        }
        /* Move to next leaf. */
        leaf = leaf->next;
    }

    /* End line. */
    printf("\n");
}


/* ================================================================== */
/*  insert_into_leaf_sorted(leaf, key)                                */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Find correct index (shift while larger).                        */
/*  2. Check duplicate: if equal, ignore & return 0.                   */
/*  3. Insert key at gap.                                              */
/*  4. ++num_keys.                                                     */
/*  5. Return 1 if inserted, 0 if duplicate.                           */
/* ================================================================== */
static int insert_into_leaf_sorted(BPlusNode *leaf, int key)
{
    /* Start from last key. */
    int i = leaf->num_keys - 1;
    /* Shift keys right while new key smaller. */
    while (i >= 0 && key < leaf->keys[i]) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    /* Duplicate check (if i>=0 and same). */
    if (i >= 0 && leaf->keys[i] == key) {
        /* Do not insert duplicates. */
        return 0;
    }
    /* Insert new key at i+1. */
    leaf->keys[i + 1] = key;
    /* Increase count. */
    leaf->num_keys++;
    /* Success. */
    return 1;
}


/* ================================================================== */
/*  insert_into_internal_shifted(internal, pos, key, right_child)     */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Shift keys right from end down to pos.                         */
/*  2. Shift children right from end down to pos+1.                   */
/*  3. Write key at pos.                                              */
/*  4. Write right_child at pos+1.                                    */
/*  5. ++num_keys.                                                    */
/* ================================================================== */
static void insert_into_internal_shifted(BPlusNode *internal,
                                         int pos,
                                         int key,
                                         BPlusNode *right_child)
{
    /* Shift keys right. */
    for (int i = internal->num_keys - 1; i >= pos; i--) {
        internal->keys[i + 1] = internal->keys[i];
    }
    /* Shift children right. */
    for (int i = internal->num_keys; i >= pos + 1; i--) {
        internal->children[i + 1] = internal->children[i];
    }
    /* Insert new key. */
    internal->keys[pos] = key;
    /* Insert new child pointer. */
    internal->children[pos + 1] = right_child;
    /* Increase key count. */
    internal->num_keys++;
}


/* ================================================================== */
/*  split_leaf_and_get_sep(leaf, &sep)                                */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. total = leaf->num_keys (already overflowed).                    */
/*  2. split_count = total / 2 (left keeps this many).                 */
/*  3. Move remaining keys to new right leaf.                          */
/*  4. Link leaf->next to right_leaf; right_leaf->next to old next.    */
/*  5. sep = first key in right_leaf.                                  */
/*  6. return right_leaf.                                              */
/* ================================================================== */
static BPlusNode *split_leaf_and_get_sep(BPlusNode *leaf, int *sep)
{
    /* Total keys in leaf (overflow). */
    int total = leaf->num_keys;
    /* Number of keys left leaf keeps. */
    int split_count = total / 2;
    /* Number of keys moving to right leaf. */
    int right_count = total - split_count;

    /* Create new leaf node. */
    BPlusNode *right_leaf = create_node(true);
    /* Bail on alloc fail. */
    if (right_leaf == NULL) {
        fprintf(stderr, "split_leaf: alloc failed\n");
        exit(EXIT_FAILURE);
    }

    /* Copy keys to right leaf. */
    for (int i = 0; i < right_count; i++) {
        right_leaf->keys[i] = leaf->keys[split_count + i];
    }
    /* Set right leaf key count. */
    right_leaf->num_keys = right_count;
    /* Shrink left leaf count. */
    leaf->num_keys = split_count;

    /* Link leaf chain. */
    right_leaf->next = leaf->next;
    leaf->next = right_leaf;

    /* Separator is first key in right leaf. */
    *sep = right_leaf->keys[0];
    /* Return new right leaf. */
    return right_leaf;
}


/* ================================================================== */
/*  split_internal_and_get_sep(internal, &sep)                        */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. total = internal->num_keys (overflow).                          */
/*  2. mid = total / 2 (promote key at mid).                           */
/*  3. New right_internal gets keys AFTER mid.                         */
/*  4. Move corresponding children.                                    */
/*  5. internal->num_keys = mid.                                       */
/*  6. sep = internal->keys[mid].                                      */
/*  7. return right_internal.                                          */
/* ================================================================== */
static BPlusNode *split_internal_and_get_sep(BPlusNode *internal, int *sep)
{
    /* Total keys after overflow. */
    int total = internal->num_keys;
    /* Index of key to promote up. */
    int mid = total / 2;

    /* Separator is the mid key. */
    *sep = internal->keys[mid];

    /* Number of keys to move to right. */
    int right_count = total - mid - 1;

    /* Make right internal node. */
    BPlusNode *right_internal = create_node(false);
    /* Check failure. */
    if (right_internal == NULL) {
        fprintf(stderr, "split_internal: alloc failed\n");
        exit(EXIT_FAILURE);
    }

    /* Copy keys AFTER mid into right_internal. */
    for (int i = 0; i < right_count; i++) {
        right_internal->keys[i] = internal->keys[mid + 1 + i];
    }
    /* Copy children AFTER mid into right_internal. */
    for (int i = 0; i < right_count + 1; i++) {
        right_internal->children[i] = internal->children[mid + 1 + i];
    }

    /* Set right_internal key count. */
    right_internal->num_keys = right_count;
    /* Shrink original internal's key count to mid. */
    internal->num_keys = mid;

    /* Return right internal node. */
    return right_internal;
}


/* ================================================================== */
/*  insert_into_parent(root_ptr, left, sep, right)                    */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If left == root → make new root w/ sep, children[0]=left,      */
/*     children[1]=right; update *root_ptr; done.                     */
/*  2. Else: find parent by walking from root.                        */
/*  3. Find position i where parent->children[i] == left.             */
/*  4. If parent has room → insert sep at i using shift helper.       */
/*  5. Else overflow → manually insert sep+child, then split parent.  */
/*  6. Recurse upward with new separator.                             */
/* ================================================================== */
static void insert_into_parent(BPlusNode **root_ptr,
                               BPlusNode *left,
                               int sep,
                               BPlusNode *right)
{
    /* If left was root, create new root. */
    if (*root_ptr == left) {
        /* Make new root internal. */
        BPlusNode *new_root = create_node(false);
        if (new_root == NULL) {
            fprintf(stderr, "insert_into_parent: new root alloc fail\n");
            exit(EXIT_FAILURE);
        }
        /* Place sep key at index 0. */
        new_root->keys[0] = sep;
        /* Link children. */
        new_root->children[0] = left;
        new_root->children[1] = right;
        /* One key in new root. */
        new_root->num_keys = 1;
        /* Update root pointer. */
        *root_ptr = new_root;
        /* Done. */
        return;
    }

    /* Otherwise we must FIND the parent of 'left'. */
    BPlusNode *parent = *root_ptr;

    /* Descend until we locate a node whose child == left. */
    while (!parent->is_leaf) {
        /* Search children for left pointer. */
        for (int i = 0; i <= parent->num_keys; i++) {
            if (parent->children[i] == left) {
                /* If parent has space, simple insert. */
                if (parent->num_keys < MAX_KEYS) {
                    insert_into_internal_shifted(parent, i, sep, right);
                    return;
                } else {
                    /* Parent full: overflow insert at i, then split. */

                    /* Shift keys right. */
                    for (int k = parent->num_keys - 1; k >= i; k--) {
                        parent->keys[k + 1] = parent->keys[k];
                    }
                    /* Shift children right. */
                    for (int k = parent->num_keys; k >= i + 1; k--) {
                        parent->children[k + 1] = parent->children[k];
                    }
                    /* Insert sep & right child. */
                    parent->keys[i] = sep;
                    parent->children[i + 1] = right;
                    /* Increase count (overflow). */
                    parent->num_keys++;

                    /* Split internal and propagate. */
                    int up_sep;
                    BPlusNode *new_internal = split_internal_and_get_sep(parent, &up_sep);
                    insert_into_parent(root_ptr, parent, up_sep, new_internal);
                    return;
                }
            }
        }
        /* Did not find 'left' at this level; descend by sep. */
        int j = 0;
        while (j < parent->num_keys && sep >= parent->keys[j]) {
            j++;
        }
        parent = parent->children[j];
    }

    /* Should never get here if tree valid. */
    fprintf(stderr, "insert_into_parent: parent not found\n");
    exit(EXIT_FAILURE);
}


/* ================================================================== */
/*  insert_key(tree, key)                                             */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If tree empty → create root leaf; insert key.                  */
/*  2. leaf = find_leaf(root, key).                                   */
/*  3. If leaf has room → insert sorted; done.                        */
/*  4. Else: overflow insert, split leaf, get sep, insert in parent.  */
/* ================================================================== */
static void insert_key(BPlusTree *tree, int key)
{
    /* Guard tree pointer. */
    if (tree == NULL) {
        fprintf(stderr, "insert_key: tree NULL\n");
        return;
    }

    /* If no root, create root leaf. */
    if (tree->root == NULL) {
        BPlusNode *root = create_node(true);
        if (root == NULL) {
            fprintf(stderr, "insert_key: root alloc fail\n");
            return;
        }
        /* Insert key into empty root. */
        root->keys[0] = key;
        root->num_keys = 1;
        tree->root = root;
        printf("Inserted %d as root.\n", key);
        return;
    }

    /* Locate leaf where key belongs. */
    BPlusNode *leaf = find_leaf(tree->root, key);
    if (leaf == NULL) {
        fprintf(stderr, "insert_key: find_leaf returned NULL\n");
        return;
    }

    /* If leaf has room, insert sorted. */
    if (leaf->num_keys < MAX_KEYS) {
        int inserted = insert_into_leaf_sorted(leaf, key);
        if (inserted) {
            printf("Inserted %d into leaf.\n", key);
        } else {
            printf("Key %d duplicate ignored.\n", key);
        }
        return;
    }

    /* Leaf full: attempt insert to overflow. */
    int inserted = insert_into_leaf_sorted(leaf, key);
    if (!inserted) {
        printf("Key %d duplicate ignored.\n", key);
        return;
    }

    /* Split leaf & promote separator. */
    int sep;
    BPlusNode *right_leaf = split_leaf_and_get_sep(leaf, &sep);

    /* Insert separator into parent. */
    insert_into_parent(&tree->root, leaf, sep, right_leaf);
    printf("Inserted %d (leaf split).\n", key);
}


/* ================================================================== */
/*  find_child_index_in_parent(parent, child)                         */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Loop i=0..parent->num_keys.                                    */
/*  2. If parent->children[i]==child → return i.                      */
/*  3. If not found → return -1.                                      */
/* ================================================================== */
static int find_child_index_in_parent(BPlusNode *parent, BPlusNode *child)
{
    /* Scan child array for match. */
    for (int i = 0; i <= parent->num_keys; i++) {
        if (parent->children[i] == child) {
            return i;
        }
    }
    /* Not found. */
    return -1;
}


/* ================================================================== */
/*  update_parent_key_after_leftmost_change(parent, child_index)      */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If child_index==0 → nothing to update.                          */
/*  2. parent->keys[child_index-1] = first key in child.               */
/* ================================================================== */
static void update_parent_key_after_leftmost_change(BPlusNode *parent,
                                                    int child_index)
{
    /* If this is leftmost child, no separator to left. */
    if (child_index == 0) {
        return;
    }
    /* Child pointer. */
    BPlusNode *child = parent->children[child_index];
    /* Update parent's separator using child's first key. */
    parent->keys[child_index - 1] = child->keys[0];
}


/* ================================================================== */
/*  borrow_from_left_leaf(node,left_sib,parent,node_index)             */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Shift node keys right by 1.                                     */
/*  2. Move left_sib last key into node->keys[0].                      */
/*  3. --left_sib->num_keys; ++node->num_keys.                         */
/*  4. Update parent separator since node's first key changed.         */
/* ================================================================== */
static void borrow_from_left_leaf(BPlusNode *node,
                                  BPlusNode *left_sib,
                                  BPlusNode *parent,
                                  int node_index)
{
    /* Shift node keys right to free index 0. */
    for (int i = node->num_keys - 1; i >= 0; i--) {
        node->keys[i + 1] = node->keys[i];
    }
    /* Copy last key from left sibling into node[0]. */
    node->keys[0] = left_sib->keys[left_sib->num_keys - 1];
    /* Increase node count. */
    node->num_keys++;
    /* Decrease left sibling count. */
    left_sib->num_keys--;
    /* Update parent separator due to changed leftmost key. */
    update_parent_key_after_leftmost_change(parent, node_index);
}


/* ================================================================== */
/*  borrow_from_right_leaf(node,right_sib,parent,node_index)           */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Append right_sib first key to node end.                         */
/*  2. Shift right_sib keys left.                                      */
/*  3. Update parent->keys[node_index] = right_sib new first key.      */
/* ================================================================== */
static void borrow_from_right_leaf(BPlusNode *node,
                                   BPlusNode *right_sib,
                                   BPlusNode *parent,
                                   int node_index)
{
    /* Copy first key of right sibling to end of node. */
    node->keys[node->num_keys] = right_sib->keys[0];
    /* Increase node count. */
    node->num_keys++;
    /* Shift right sibling keys left to fill gap. */
    for (int i = 1; i < right_sib->num_keys; i++) {
        right_sib->keys[i - 1] = right_sib->keys[i];
    }
    /* Decrease right sibling count. */
    right_sib->num_keys--;
    /* Update parent's separator slot at node_index. */
    if (right_sib->num_keys > 0) {
        parent->keys[node_index] = right_sib->keys[0];
    } else {
        /* If right sibling now empty (rare), keep last known? We'll leave as-is; parent will fix next. */
        /* In a well-balanced B+ tree, borrow shouldn't empty sibling. */
    }
}


/* ================================================================== */
/*  merge_leaves(parent,left_index)                                   */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. left = parent->children[left_index]; right=...+1.               */
/*  2. Append all right keys to left.                                  */
/*  3. Fix leaf chain: left->next = right->next.                       */
/*  4. Remove separator key at left_index from parent (shift).         */
/*  5. Remove right child pointer (shift).                             */
/*  6. --parent->num_keys; free right.                                 */
/* ================================================================== */
static void merge_leaves(BPlusNode *parent, int left_index)
{
    /* Identify left & right leaves. */
    BPlusNode *left_leaf = parent->children[left_index];
    BPlusNode *right_leaf = parent->children[left_index + 1];

    /* Copy right keys to end of left. */
    for (int i = 0; i < right_leaf->num_keys; i++) {
        left_leaf->keys[left_leaf->num_keys + i] = right_leaf->keys[i];
    }
    /* Increase left key count. */
    left_leaf->num_keys += right_leaf->num_keys;

    /* Link leaf chain to skip removed right. */
    left_leaf->next = right_leaf->next;

    /* Remove parent separator at left_index (shift keys left). */
    for (int i = left_index; i < parent->num_keys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }
    /* Shift children left to remove right child pointer. */
    for (int i = left_index + 1; i <= parent->num_keys; i++) {
        parent->children[i] = parent->children[i + 1];
    }

    /* Reduce parent key count. */
    parent->num_keys--;

    /* Free right leaf. */
    free(right_leaf->keys);
    free(right_leaf->children);
    free(right_leaf);
}


/* ================================================================== */
/*  borrow_from_left_internal(parent, idx, left_sib, child)            */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Shift child's keys/children right 1 slot.                       */
/*  2. Child->keys[0] = parent->keys[idx-1].                           */
/*  3. Child->children[0] = left_sib->last_child.                      */
/*  4. parent->keys[idx-1] = left_sib->last_key.                       */
/*  5. --left_sib->num_keys; ++child->num_keys.                        */
/* ================================================================== */
static void borrow_from_left_internal(BPlusNode *parent,
                                      int idx,
                                      BPlusNode *left_sib,
                                      BPlusNode *child)
{
    /* Shift child's keys right. */
    for (int i = child->num_keys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    /* Shift child's children right. */
    for (int i = child->num_keys; i >= 0; i--) {
        child->children[i + 1] = child->children[i];
    }
    /* Bring down parent's separator. */
    child->keys[0] = parent->keys[idx - 1];
    /* Bring over left_sib's last child. */
    child->children[0] = left_sib->children[left_sib->num_keys];
    /* Increase child count. */
    child->num_keys++;
    /* Move left_sib's last key up to parent slot. */
    parent->keys[idx - 1] = left_sib->keys[left_sib->num_keys - 1];
    /* Decrease left_sib count. */
    left_sib->num_keys--;
}


/* ================================================================== */
/*  borrow_from_right_internal(parent, idx, right_sib, child)          */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Append parent->keys[idx] to child tail.                         */
/*  2. Attach right_sib->children[0] to child->children[end+1].        */
/*  3. parent->keys[idx] = right_sib->keys[0].                         */
/*  4. Shift right_sib keys/children left.                             */
/*  5. --right_sib->num_keys; ++child->num_keys.                       */
/* ================================================================== */
static void borrow_from_right_internal(BPlusNode *parent,
                                       int idx,
                                       BPlusNode *right_sib,
                                       BPlusNode *child)
{
    /* Append parent's separator to child. */
    child->keys[child->num_keys] = parent->keys[idx];
    /* Attach first child of right sibling. */
    child->children[child->num_keys + 1] = right_sib->children[0];
    /* Increase child count. */
    child->num_keys++;
    /* Move right_sib's first key up into parent. */
    parent->keys[idx] = right_sib->keys[0];
    /* Shift right_sib keys left. */
    for (int i = 1; i < right_sib->num_keys; i++) {
        right_sib->keys[i - 1] = right_sib->keys[i];
    }
    /* Shift right_sib children left. */
    for (int i = 1; i <= right_sib->num_keys; i++) {
        right_sib->children[i - 1] = right_sib->children[i];
    }
    /* Reduce right_sib count. */
    right_sib->num_keys--;
}


/* ================================================================== */
/*  merge_internals(parent,left_index)                                */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. left = parent->children[left_index]; right=...+1.               */
/*  2. Bring parent->keys[left_index] down into left tail.             */
/*  3. Append all right keys & children to left.                       */
/*  4. Remove parent sep key & right child pointer (shift).            */
/*  5. --parent->num_keys; free right.                                 */
/* ================================================================== */
static void merge_internals(BPlusNode *parent, int left_index)
{
    /* Identify left & right internals. */
    BPlusNode *left = parent->children[left_index];
    BPlusNode *right = parent->children[left_index + 1];

    /* Bring separator key down into left. */
    left->keys[left->num_keys] = parent->keys[left_index];
    /* Increase left count. */
    left->num_keys++;

    /* Copy right's keys into left. */
    for (int i = 0; i < right->num_keys; i++) {
        left->keys[left->num_keys + i] = right->keys[i];
    }
    /* Copy right's children into left. */
    for (int i = 0; i <= right->num_keys; i++) {
        left->children[left->num_keys + i] = right->children[i];
    }

    /* Increase left count by right->num_keys. */
    left->num_keys += right->num_keys;

    /* Remove parent separator key (shift left). */
    for (int i = left_index; i < parent->num_keys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }
    /* Remove right child pointer from parent (shift). */
    for (int i = left_index + 1; i <= parent->num_keys; i++) {
        parent->children[i] = parent->children[i + 1];
    }
    /* Decrease parent key count. */
    parent->num_keys--;

    /* Free right internal. */
    free(right->keys);
    free(right->children);
    free(right);
}


/* ================================================================== */
/*  try_fix_node_underflow(root_ptr,node,parent,index,is_leaf)        */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If parent==NULL → node is root:                                */
/*     a. If node internal & 0 keys → promote only child as root.      */
/*     b. Else done.                                                   */
/*  2. min = is_leaf ? MIN_LEAF_KEYS : MIN_INTERNAL_KEYS.              */
/*  3. If node->num_keys >= min → just update parent sep if needed.    */
/*  4. left_sib = parent->children[index-1]; right_sib = index+1.      */
/*  5. If left_sib exists & has >min → borrow_from_left_xxx.           */
/*  6. Else if right_sib exists & has >min → borrow_from_right_xxx.    */
/*  7. Else must merge: merge with left if exists else with right.     */
/*  8. After merge, parent may underflow → recursively fix parent.     */
/* ================================================================== */
static void try_fix_node_underflow(BPlusNode **root_ptr,
                                   BPlusNode *node,
                                   BPlusNode *parent,
                                   int index,
                                   bool is_leaf)
{
    /* If node is root (no parent). */
    if (parent == NULL) {
        /* If root is internal and empty, collapse to only child. */
        if (!node->is_leaf && node->num_keys == 0) {
            BPlusNode *new_root = node->children[0];
            free(node->keys);
            free(node->children);
            free(node);
            *root_ptr = new_root;
        }
        /* Done at root. */
        return;
    }

    /* Determine min allowed keys for this node type. */
    int min_keys = is_leaf ? MIN_LEAF_KEYS : MIN_INTERNAL_KEYS;

    /* If node already at/above min, just update parent sep & return. */
    if (node->num_keys >= min_keys) {
        update_parent_key_after_leftmost_change(parent, index);
        return;
    }

    /* Identify siblings. */
    BPlusNode *left_sib  = (index > 0) ? parent->children[index - 1] : NULL;
    BPlusNode *right_sib = (index < parent->num_keys) ? parent->children[index + 1] : NULL;

    /* Try borrow from left. */
    if (left_sib != NULL) {
        if (left_sib->num_keys > min_keys) {
            if (is_leaf) {
                borrow_from_left_leaf(node, left_sib, parent, index);
            } else {
                borrow_from_left_internal(parent, index, left_sib, node);
            }
            return;
        }
    }

    /* Try borrow from right. */
    if (right_sib != NULL) {
        if (right_sib->num_keys > min_keys) {
            if (is_leaf) {
                borrow_from_right_leaf(node, right_sib, parent, index);
            } else {
                borrow_from_right_internal(parent, index, right_sib, node);
            }
            return;
        }
    }

    /* Must merge: prefer merging with left if exists. */
    if (left_sib != NULL) {
        if (is_leaf) {
            merge_leaves(parent, index - 1);
        } else {
            merge_internals(parent, index - 1);
        }
        /* After merge, parent may underflow; fix parent recursively. */
        try_fix_node_underflow(root_ptr, parent, NULL, -1, false);
        return;
    } else if (right_sib != NULL) {
        if (is_leaf) {
            merge_leaves(parent, index);
        } else {
            merge_internals(parent, index);
        }
        /* Fix parent recursively. */
        try_fix_node_underflow(root_ptr, parent, NULL, -1, false);
        return;
    }

    /* Should not reach here (node had no siblings?). */
    fprintf(stderr, "try_fix_node_underflow: no siblings\n");
}


/* ================================================================== */
/*  re_find_parent_and_fix(root_ptr,node,is_leaf)                     */
/* ================================================================== */
/*  NOTE: Called when we merged and lost the direct parent pointer.    */
/*  ALGORITHM:                                                        */
/*  1. If node==root → call try_fix_node_underflow w/ parent=NULL.     */
/*  2. Else walk from root:                                            */
/*     a. At each internal node, see if child==node; if yes → fix.     */
/*     b. Else descend based on node->keys[0].                         */
/*  3. If not found by time we hit leaf parent → error (tree corrupt). */
/* ================================================================== */
static void re_find_parent_and_fix(BPlusNode **root_ptr,
                                   BPlusNode *node,
                                   bool is_leaf)
{
    /* If node is root, fix at root and return. */
    if (*root_ptr == node) {
        try_fix_node_underflow(root_ptr, node, NULL, -1, is_leaf);
        return;
    }

    /* Start from root to find node's parent. */
    BPlusNode *parent = *root_ptr;

    /* Walk downward until found. */
    while (!parent->is_leaf) {
        /* Try exact child match. */
        int idx = find_child_index_in_parent(parent, node);
        if (idx != -1) {
            try_fix_node_underflow(root_ptr, node, parent, idx, is_leaf);
            return;
        }
        /* Not here; choose child path by comparing node's first key. */
        int k = node->keys[0];
        int j = 0;
        while (j < parent->num_keys && k >= parent->keys[j]) {
            j++;
        }
        parent = parent->children[j];
    }

    /* If we got here, something broke. */
    fprintf(stderr, "re_find_parent_and_fix: parent not found\n");
    exit(EXIT_FAILURE);
}


/* ================================================================== */
/*  delete_key_from_leaf(leaf, key)                                   */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Scan keys to find key index.                                    */
/*  2. If not found → return false.                                    */
/*  3. Shift keys left from index+1..end.                              */
/*  4. --num_keys; return true.                                        */
/* ================================================================== */
static bool delete_key_from_leaf(BPlusNode *leaf, int key)
{
    /* Find index of key in leaf. */
    int idx = -1;
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            idx = i;
            break;
        }
    }
    /* Not found -> false. */
    if (idx == -1) {
        return false;
    }
    /* Shift keys left over gap. */
    for (int i = idx + 1; i < leaf->num_keys; i++) {
        leaf->keys[i - 1] = leaf->keys[i];
    }
    /* Reduce count. */
    leaf->num_keys--;
    /* Deleted. */
    return true;
}


/* ================================================================== */
/*  delete_key_recursive(root_ptr, key)                               */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If root NULL → false.                                          */
/*  2. Descend from root to leaf, pushing (node,index) stacks.         */
/*  3. In leaf: delete_key_from_leaf.                                  */
/*  4. If leaf was root & empty → free root, set NULL → true.          */
/*  5. If leaf >= min or root → update parent sep; true.               */
/*  6. Else fix underflow (borrow/merge).                              */
/*  7. After fix, parent may underflow → re_find_parent_and_fix.       */
/* ================================================================== */
static bool delete_key_recursive(BPlusNode **root_ptr, int key)
{
    /* If tree empty, nothing to delete. */
    if (*root_ptr == NULL) {
        return false;
    }

    /* Stacks to remember path to leaf. */
    BPlusNode *stack_nodes[64];
    int stack_index[64];
    int depth = 0;

    /* Start at root. */
    BPlusNode *node = *root_ptr;

    /* Descend to leaf storing path. */
    while (!node->is_leaf) {
        /* Find child index for key. */
        int i = 0;
        while (i < node->num_keys && key >= node->keys[i]) {
            i++;
        }
        /* Push current node & child index. */
        stack_nodes[depth] = node;
        stack_index[depth] = i;
        depth++;
        /* Descend. */
        node = node->children[i];
    }

    /* Now node is leaf. Try delete. */
    bool removed = delete_key_from_leaf(node, key);
    /* If not in leaf, done (not found). */
    if (!removed) {
        return false;
    }

    /* If node is root and now empty -> free & clear root. */
    if (*root_ptr == node && node->num_keys == 0) {
        free(node->keys);
        free(node->children);
        free(node);
        *root_ptr = NULL;
        return true;
    }

    /* If leaf meets min occupancy or is root -> maybe update parent -> done. */
    if (node->num_keys >= MIN_LEAF_KEYS || *root_ptr == node) {
        /* If we have a parent, update sep if needed. */
        if (depth > 0) {
            BPlusNode *parent = stack_nodes[depth - 1];
            int idx = stack_index[depth - 1];
            update_parent_key_after_leftmost_change(parent, idx);
        }
        return true;
    }

    /* Leaf underflow; need to fix. */
    if (depth == 0) {
        /* Should not happen because root handled above. */
        return true;
    }

    /* Pop parent info. */
    depth--;
    BPlusNode *parent = stack_nodes[depth];
    int idx = stack_index[depth];

    /* Fix underflow at leaf. */
    try_fix_node_underflow(root_ptr, node, parent, idx, true);

    /* If parent was changed drastically (merge), fix ancestors. */
    if (depth > 0) {
        /* Re-find parent's parent & fix internal underflow if any. */
        re_find_parent_and_fix(root_ptr, parent, false);
    } else {
        /* Parent might be root; fix root. */
        try_fix_node_underflow(root_ptr, parent, NULL, -1, false);
    }

    /* Delete successful. */
    return true;
}


/* ================================================================== */
/*  delete_key(tree, key)                                             */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If tree NULL -> return.                                        */
/*  2. removed = delete_key_recursive(&root, key).                    */
/*  3. Print result.                                                  */
/* ================================================================== */
static void delete_key(BPlusTree *tree, int key)
{
    /* Guard. */
    if (tree == NULL) {
        fprintf(stderr, "delete_key: tree NULL\n");
        return;
    }
    /* Perform recursive delete. */
    bool removed = delete_key_recursive(&tree->root, key);
    /* Report. */
    if (removed) {
        printf("Deleted %d.\n", key);
    } else {
        printf("Key %d not found.\n", key);
    }
}


/* ================================================================== */
/*  print_tree_structure_rec(node, level)                             */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If node NULL -> return.                                        */
/*  2. Indent spaces based on level.                                  */
/*  3. Print keys with [..] and leaf/internal label.                  */
/*  4. If internal -> recurse on each child (level+1).                */
/* ================================================================== */
static void print_tree_structure_rec(BPlusNode *node, int level)
{
    /* Nothing to print if node NULL. */
    if (node == NULL) {
        return;
    }

    /* Indentation: 2 spaces per level. */
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    /* Print node header & keys. */
    printf("Level %d %s: [", level, node->is_leaf ? "leaf" : "int");
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d", node->keys[i]);
        if (i < node->num_keys - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    /* Recurse children if internal. */
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            print_tree_structure_rec(node->children[i], level + 1);
        }
    }
}


/* ================================================================== */
/*  print_tree_structure(tree)                                        */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If tree empty -> print message.                                */
/*  2. Call recursive helper at level 0.                              */
/* ================================================================== */
static void print_tree_structure(BPlusTree *tree)
{
    /* Check empty tree. */
    if (tree == NULL || tree->root == NULL) {
        printf("(tree empty)\n");
        return;
    }
    /* Print from root. */
    print_tree_structure_rec(tree->root, 0);
}


/* ================================================================== */
/*  print_all_leaves(tree)                                            */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. Go to leftmost leaf by always taking child[0].                 */
/*  2. Walk leaf->next chain, printing keys in order.                 */
/* ================================================================== */
static void print_all_leaves(BPlusTree *tree)
{
    /* If tree empty -> message. */
    if (tree == NULL || tree->root == NULL) {
        printf("Leaves: (empty)\n");
        return;
    }
    /* Start at root. */
    BPlusNode *node = tree->root;
    /* Descend to leftmost leaf. */
    while (!node->is_leaf) {
        node = node->children[0];
    }
    /* Print keys across leaves. */
    printf("Leaves: ");
    while (node != NULL) {
        for (int i = 0; i < node->num_keys; i++) {
            printf("%d ", node->keys[i]);
        }
        node = node->next;
    }
    printf("\n");
}


/* ================================================================== */
/*  free_bplustree_rec(node)                                          */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If node NULL -> return.                                        */
/*  2. If internal -> free children recursively.                      */
/*  3. Free keys, children arrays, then node.                         */
/* ================================================================== */
static void free_bplustree_rec(BPlusNode *node)
{
    /* Nothing to free if NULL. */
    if (node == NULL) {
        return;
    }
    /* Recurse children first if internal. */
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            free_bplustree_rec(node->children[i]);
        }
    }
    /* Free arrays. */
    free(node->keys);
    free(node->children);
    /* Free node itself. */
    free(node);
}


/* ================================================================== */
/*  free_bplustree(tree)                                              */
/* ================================================================== */
/*  ALGORITHM:                                                        */
/*  1. If tree NULL -> return.                                        */
/*  2. Free all nodes via helper.                                     */
/*  3. Free tree wrapper.                                             */
/* ================================================================== */
static void free_bplustree(BPlusTree *tree)
{
    /* Guard. */
    if (tree == NULL) {
        return;
    }
    /* Free from root downward. */
    free_bplustree_rec(tree->root);
    /* Free wrapper. */
    free(tree);
}


/* ================================================================== */
/*  main()                                                            */
/* ================================================================== */
/*  DEMO:                                                             */
/*  1. Create tree.                                                   */
/*  2. Insert test keys.                                              */
/*  3. Print structure + leaves.                                      */
/*  4. Search sample keys.                                            */
/*  5. Delete some keys (includes misses).                            */
/*  6. Print final tree + leaves.                                     */
/*  7. Range query.                                                   */
/*  8. Free tree & exit.                                              */
/* ================================================================== */
int main(void)
{
    /* Create an empty B+ Tree. */
    BPlusTree *tree = create_bplustree();
    /* Check creation success. */
    if (tree == NULL) {
        return 1;
    }

    /* Test keys to insert. */
    int keys_to_insert[] = {10, 20, 5, 6, 12, 30, 7, 17, 25, 40, 50, 60};
    int num_keys = (int)(sizeof(keys_to_insert) / sizeof(keys_to_insert[0]));

    /* Insert each key. */
    printf("\n--- INSERTING KEYS ---\n");
    for (int i = 0; i < num_keys; i++) {
        insert_key(tree, keys_to_insert[i]);
    }

    /* Print tree structure. */
    printf("\n--- TREE STRUCTURE ---\n");
    print_tree_structure(tree);

    /* Print leaves. */
    printf("\n--- LEAVES ---\n");
    print_all_leaves(tree);

    /* Search tests. */
    printf("\n--- SEARCH TESTS ---\n");
    int search_keys[] = {6, 15, 25, 100};
    int num_search = (int)(sizeof(search_keys) / sizeof(search_keys[0]));
    for (int i = 0; i < num_search; i++) {
        bool found = search_exact(tree, search_keys[i]);
        printf("Key %d %s.\n", search_keys[i], found ? "FOUND" : "NOT found");
    }

    /* Deletion tests. */
    printf("\n--- DELETION TESTS ---\n");
    int delete_keys[] = {6, 13, 7, 12, 25, 10, 20};
    int num_delete = (int)(sizeof(delete_keys) / sizeof(delete_keys[0]));
    for (int i = 0; i < num_delete; i++) {
        printf("Delete %d:\n", delete_keys[i]);
        delete_key(tree, delete_keys[i]);
        print_tree_structure(tree);
        print_all_leaves(tree);
    }

    /* Range query demonstration. */
    printf("\n--- RANGE [8..30] ---\n");
    search_range(tree, 8, 30);

    /* Clean up memory. */
    printf("\n--- CLEANUP ---\n");
    free_bplustree(tree);

    /* Done. */
    return 0;
}

