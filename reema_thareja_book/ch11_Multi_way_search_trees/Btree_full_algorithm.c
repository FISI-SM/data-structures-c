#define MAX_KEYS 3


typedef struct BTreeNode {
    int *keys;                  // Dynamic array to store keys
    struct BTreeNode **children; // Array of pointers to child nodes
    int num_keys;               // Current number of keys in this node
    bool is_leaf;               // True if this node has no children
    int min_degree;             // Minimum degree (t)
} BTreeNode;


typedef struct BTree {
    BTreeNode *root;   // Pointer to the root node
    int min_degree;    // Minimum degree (t) of the B-tree
} BTree;


 1. create_node(min_degree, is_leaf)
Goal: Create and initialize a B-tree node.

Algorithm:
Allocate memory for a new BTreeNode.

If allocation fails → print error and return NULL.

Store min_degree in the node.

Set is_leaf flag based on input.

Set num_keys = 0 (empty node).

Allocate an array of keys of size 2*t - 1.

Allocate an array of children pointers of size 2*t.

Initialize all child pointers to NULL.

Return the created node.

 2. create_btree(min_degree)
Goal: Create an empty B-tree with a given minimum degree.

Algorithm:
Allocate memory for a BTree object.

If allocation fails → print error and return NULL.

Store min_degree in the tree object.

Set root = NULL (empty tree).

Return the new B-tree object.

 3. search_node(node, key, pos_out)
Goal: Find a key in the subtree rooted at node.

Algorithm:
If node == NULL → return NULL (tree empty).

Set i = 0.

While i < num_keys and key > keys[i]:

Increment i.

If i < num_keys and keys[i] == key:

If pos_out is not NULL, store index i in it.

Return current node.

If is_leaf == true, return NULL (not found).

Otherwise, recursively search children[i].

 4. search_key(tree, key)
Goal: Public search wrapper.

Algorithm:
If tree == NULL or tree->root == NULL, return false.

Call search_node(root, key, NULL).

If result is not NULL → return true, else false.

 5. split_child(parent, index, full_child)
Goal: Split a full child node into two and move median to parent.

Algorithm:
Let t = min_degree.

Create new_child with same is_leaf as full_child.

Copy last t-1 keys from full_child into new_child.

If full_child is not leaf, also copy last t children to new_child.

Reduce full_child->num_keys to t-1.

Shift parent’s child pointers right from index+1 to make room.

Insert new_child at children[index+1].

Shift parent’s keys right from index to make room.

Move median key from full_child (keys[t-1]) to parent’s key slot index.

Increase parent’s num_keys.

 6. insert_non_full(node, key)
Goal: Insert a key into a non-full node.

Algorithm:
Let i = num_keys - 1.

If node is a leaf:

Shift all keys greater than key to the right.

Insert key at the correct position.

Increment num_keys.

Else (internal node):

Find child index i+1 where key should go.

If child is full:

Split the child.

If key > parent->keys[i], increment child index.

Recurse into that child.

 7. insert(btree, key)
Goal: Public insertion function.

Algorithm:
If tree is empty:

Create new root as leaf and insert key.

Return.

If root is full:

Create a new root as internal node.

Old root becomes child[0] of new root.

Split old root.

Update tree root.

Call insert_non_full(root, key).

 8. insert_unique(tree, key)
Goal: Insert key only if not already present.

Algorithm:
If tree is empty:

Call insert(tree, key) and return true.

Search tree for key.

If found:

Print “Duplicate ignored” and return false.

Else:

Call insert(tree, key) and return true.

 9. get_predecessor(node, idx)
Goal: Find the largest key in the left subtree.

Algorithm:
Start from children[idx].

While node is not leaf:

Move to its rightmost child.

Return last key in this leaf.

 10. get_successor(node, idx)
Goal: Find the smallest key in the right subtree.

Algorithm:
Start from children[idx+1].

While node is not leaf:

Move to its leftmost child.

Return first key in this leaf.

 11. borrow_from_prev(node, idx)
Goal: Borrow a key from left sibling.

Algorithm:
Shift all keys in child[idx] right by one.

If not leaf, shift children right as well.

Move parent key down to child’s first position.

Move sibling’s last child (if any) to child’s first child.

Move sibling’s last key up to parent.

Increment child’s keys count, decrement sibling’s keys count.

 12. borrow_from_next(node, idx)
Goal: Borrow a key from right sibling.

Algorithm:
Bring parent key down to child’s last slot.

If not leaf, attach sibling’s first child to child’s rightmost position.

Move sibling’s first key up to parent.

Shift sibling’s keys left.

Shift sibling’s children left if internal.

Update key counts of child and sibling.

 13. merge_children(node, idx)
Goal: Merge child[idx] and child[idx+1] with parent key.

Algorithm:
Let child = children[idx], sibling = children[idx+1].

Move parent key[idx] to child’s position after its keys.

Append all sibling keys to child.

If internal, append all sibling children to child.

Shift parent keys and children left to close gap.

Free sibling node.

 14. fill_child(node, idx)
Goal: Ensure child[idx] has at least t keys before descent.

Algorithm:
If left sibling exists and has ≥ t keys:

Borrow from left.

Else if right sibling exists and has ≥ t keys:

Borrow from right.

Else:

Merge child[idx] with one sibling.

 15. delete_from_node(node, key)
Goal: Delete key from subtree rooted at node.

Algorithm:
Find index i where key should be or is present.

If key is present:

If node is leaf:

Remove key directly by shifting.

Else:

If left child has ≥ t keys:

Replace with predecessor and recurse.

Else if right child has ≥ t keys:

Replace with successor and recurse.

Else:

Merge children and recurse into merged child.

If key is not present:

If node is leaf → nothing to do.

Else:

Determine child to descend.

If child has < t keys → fix by borrow or merge.

Recurse into appropriate child.

 16. delete_key(tree, key)
Goal: Public delete wrapper.

Algorithm:
If tree empty → return.

Call delete_from_node(root, key).

If root now has 0 keys:

If root is internal → make its first child new root.

Else free root (tree empty).

 17. inorder_traversal(node)
Goal: Print all keys in ascending order.

Algorithm:
For each key in node:

If not leaf → traverse left child.

Print key.

After loop, traverse last child if not leaf.

 18. print_tree_structure(node, level)
Goal: Print tree structure level-wise.

Algorithm:
Print indentation based on level.

Print all keys of node.

If node not leaf:

Recursively call on each child, incrementing level.

 19. free_btree_nodes(node)
Goal: Free all nodes recursively.

Algorithm:
If node is NULL → return.

If not leaf:

For each child → recursively free.

Free keys array.

Free children array.

Free node.

 20. free_btree(tree)
Goal: Free entire B-tree.

Algorithm:
Call free_btree_nodes(tree->root).

Free tree wrapper.

 21. menu_loop(tree)
Goal: Interactive menu.

Algorithm:
Loop forever:

Display options.

Read user choice.

If invalid → prompt again.

If insert:

Read key, call insert_unique.

If delete:

Read key, call delete_key.

If search:

Read key, call search_key and display result.

If print structure:

Call print_tree_structure.

If inorder:

Call inorder_traversal.

If quit:

Free tree and exit loop.

 22. main()
Goal: Entry point.

Algorithm:
Create B-tree with MIN_DEGREE.

Insert demo keys.

Print initial structure and inorder traversal.

Call menu_loop for interactive user operations.
