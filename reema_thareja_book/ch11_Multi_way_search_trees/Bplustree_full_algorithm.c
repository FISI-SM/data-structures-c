Complete B+ Tree Algorithms (All Functions)
(Beginner-Friendly Pseudocode and Steps)

1. Structure of a B+ Tree
Tree Node:

keys[]: array to store keys (sorted).

children[]: array of child pointers.

is_leaf: true if node is a leaf.

num_keys: current number of keys.

next: pointer to next leaf (for fast range search).

Tree:

root: pointer to root node.

order: maximum number of children a node can have.

2. Tree Creation
Function: create_bplustree(order)
Algorithm:

Allocate memory for the tree.

Set root = NULL (empty tree).

Set order as provided.

Return the tree.

3. Node Creation
Function: create_node(order, is_leaf)
Algorithm:

Allocate memory for a node.

Allocate keys array of size order - 1.

Allocate children array of size order.

Initialize:

is_leaf = is_leaf

num_keys = 0

next = NULL

Return the node.

4. Search for a Key
Function: search_key(tree, key)
Algorithm:

If root == NULL: return NOT FOUND.

Set node = root.

While node is NOT a leaf:

Find the child where key should go:

Start at index i = 0.

While i < num_keys and key >= keys[i], increment i.

Move node = node->children[i].

Now node is a leaf:

Search keys[] in the leaf for key.

If found → return FOUND; else → NOT FOUND.

5. Insertion
Function: insert_key(tree, key)
Algorithm:

If tree is empty:

Create root as a leaf node.

Insert key in root.

Done.

If root is full:

Create new root (internal).

Split root and promote separator key.

Insert key into appropriate child.

Else:

Call insert_non_full(root, key).

Helper: insert_non_full(node, key)
Algorithm:

If node is leaf:

Insert key into keys[] in sorted order.

Increment num_keys.

Else:

Find child i where key should go.

If child i is full:

Split child and update parent keys.

Decide correct child (left or right) for key.

Recurse insert_non_full(child[i], key).

Helper: split_leaf_and_get_sep(leaf)
Algorithm:

Create new_leaf.

Move half of keys from leaf to new_leaf.

Link new_leaf->next = leaf->next.

Update leaf->next = new_leaf.

Return separator key (first key of new_leaf).

Helper: split_internal_and_get_sep(node)
Algorithm:

Create new_internal.

Move half keys and children from node to new_internal.

Extract middle key as sep_key.

Return sep_key and new_internal.

Helper: insert_into_parent(parent, sep_key, new_child)
Algorithm:

Insert sep_key in parent in sorted order.

Insert new_child pointer after sep_key.

If parent is full:

Split parent and push up separator key recursively.

6. Traversal
Function: print_tree(root)
Algorithm:

If root == NULL: print empty.

For each node in level order:

Print its keys.

Add children to queue (if internal node).

7. Free the Tree
Function: free_bplustree(node)
Algorithm:

If node is NULL → return.

If node is not leaf:

Recursively free all children.

Free keys array, children array, and node itself.

8. Deletion
Function: delete_key(tree, key)
Algorithm:

If tree empty → return.

Call delete_key_recursive(&root, key).

If root has 0 keys after deletion:

If root is internal → replace root with child[0].

Else set root = NULL.

Free old root if changed.

Helper: delete_key_recursive(root_ptr, key)
Algorithm:

If *root_ptr is NULL → return false.

Descend to leaf where key should be.

If key not found → return false.

Delete key from leaf.

If leaf underflows:

Try borrow from siblings.

Else merge with sibling.

If parent underflows → fix recursively.

Return true.

Helper: delete_key_from_leaf(leaf, key)
Algorithm:

Search for key in leaf.

If found → shift keys left by 1.

Reduce num_keys.

Return true; else false.

Helper: try_fix_node_underflow(root_ptr, node, parent, index, is_leaf)
Algorithm:

If node has enough keys → return.

If left sibling exists and can lend → borrow from left.

Else if right sibling exists and can lend → borrow from right.

Else merge node with sibling.

After merge, parent loses one key → may cause parent underflow.

Fix parent recursively if needed.

Helper: borrow_from_left_leaf(node, left_sibling, parent, index)
Algorithm:

Shift node’s keys right.

Copy last key from left sibling to node’s first slot.

Update parent separator.

Adjust key counts.

Helper: borrow_from_right_leaf(node, right_sibling, parent, index)
Algorithm:

Append first key of right sibling to node.

Shift right sibling’s keys left.

Update parent separator.

Adjust key counts.

Helper: merge_leaves(parent, left_index)
Algorithm:

Append right leaf keys to left leaf.

Remove separator key in parent.

Remove right leaf pointer in parent.

Update leaf links.

Free right leaf.

Helper: borrow_from_left_internal(...) and borrow_from_right_internal(...)
Algorithm:

Similar to leaves but involves moving a separator key down and adjusting child pointers.

Helper: merge_internals(parent, left_index)
Algorithm:

Move parent separator key down into left node.

Append right node keys and children to left node.

Remove separator from parent.

Remove right node pointer from parent.

Free right node.

9. Helper Function
find_child_index_in_parent(parent, child)
Algorithm:

For i = 0 to parent->num_keys:

If parent->children[i] == child → return i.

Return -1 (not found)
