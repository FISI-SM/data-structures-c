#define MAX_KEYS 2

#define MAX_CHILDREN (MAX_KEYS + 1)

typedef struct TTNode TTNode;

struct TTNode 
{
    int keys[MAX_KEYS + 1];          
    TTNode *children[MAX_CHILDREN + 1]; 
    int num_keys;                    
    bool is_leaf;                    
};

typedef struct TTTree 
{
    	TTNode *root;  

} TTTree;

typedef struct PromoteInfo {
    bool has_promote;                
    int promote_key;                 
    TTNode *right_child;             
} PromoteInfo;

1. create_node()
Think of this like creating a new empty box that will hold 1 or 2 numbers.

First, we ask for some memory (space) to store this box.

We set its key count to 0 because the box is empty for now.

We mark whether the box will be a leaf (end of the tree) or not.

We also clear all the child pointers (connections) to make sure the new box doesn’t point to anything yet.

Finally, we return this new box so it can be used.

2. create_tree()
This is like making a new 2-3 tree, which starts empty.

We ask for memory to create a tree object.

We set the root (the top box of the tree) to be empty (NULL).

We return this new empty tree.

3. search_node()
This function looks for a number inside the tree starting from a given node.

We start at the first key of the current node.

We compare our target number with each key from left to right.

If we find a match, we say "Found!".

If we reach a key larger than our target, we stop because the number (if it exists) will be in the left subtree.

If we are at a leaf (end of tree) and didn’t find it, the number isn’t in the tree.

Otherwise, we follow the correct child pointer (like going down to the next box) and continue the search.

4. search()
This is just a wrapper that checks if the tree has a root.

If the tree is empty, the number is not found.

Otherwise, it calls search_node() starting from the root.

5. insert_key_sorted()
This function adds a key into a single node in sorted order.

We start from the largest key and shift them to the right until we find the correct spot for the new key.

If we see the key already exists, we stop and return false (we don’t allow duplicates).

Otherwise, we put the new key in its correct place and increase the number of keys in that node.

6. split_leaf()
A leaf node (box) can hold only 2 numbers, but after inserting, it might have 3 temporarily.

We fix this by splitting the box into two smaller boxes:

The middle number will be promoted to the parent node (the one above).

The left box will keep the smallest number.

The right box will keep the largest number.

We return this middle number and the new right box to the parent.

7. split_internal()
This is similar to splitting a leaf but happens for internal nodes (boxes with children).

If a node gets 3 keys, we:

Move the middle key up to the parent.

Split its children so the left group and right group go to separate boxes.

This keeps the 2-3 tree balanced.

8. insert_recursive()
We go down the tree to find where the new key should go.

If we reach a leaf, we simply insert the key into it in sorted order.

If the leaf overflows (3 keys), we split it.

If we are at an internal node:

We first figure out which child to follow.

We insert into that child.

If the child splits, we insert the promoted key into the current node and fix it if it overflows.

This recursion continues until all splits are handled.

9. insert()
If the tree is empty, we make a new root node and put the key there.

Otherwise, we call insert_recursive() on the root.

If the root itself overflows, we split it and make a new root above it.

10. insert_unique()
Before inserting, we search for the key.

If it’s already in the tree, we print a message that it’s a duplicate.

Otherwise, we insert it and show a success message.

11. find_predecessor()
When deleting a key from an internal node, we replace it with the largest key from the left child (called the predecessor).

This function moves to the left child and then keeps going right until it reaches the largest key.

12. Borrowing & Merging
Borrow from left: If a child box becomes empty, we can "borrow" a key from its left sibling through the parent.

Borrow from right: Same idea but borrowing from the right sibling.

Merge: If neither sibling can give a key, we merge two children and one parent key into a single node.

13. fix_child()
Before going down into a child, we check if it’s empty.

If it is, we try to borrow a key from a neighbor.

If borrowing isn’t possible, we merge with a sibling.

14. delete_recursive()
We look for the key in the current node.

If found in a leaf, we remove it directly.

If found in an internal node, we find its predecessor, replace the key, and delete the predecessor.

If the key is not in the current node:

We go down the correct child but first ensure it has enough keys by calling fix_child().

After returning, if the root becomes empty, we shrink the tree.

15. delete_key()
This is a wrapper that checks if the tree is empty.

It calls delete_recursive().

If the root becomes empty after deletion, we free it and set the tree as empty.

16. inorder()
This function prints all keys in sorted order.

It goes to the leftmost child first, prints keys one by one, and then continues to the right.

17. print_structure()
This shows the tree level by level.

It prints the keys in each node with indentation for clarity.

18. free_tree()
This deletes all nodes in the tree by going down to all children and freeing memory.

19. menu_loop()
This runs an interactive menu where the user can:

Insert a key.

Delete a key.

Search for a key.

Print the tree structure.

Print the sorted keys.

Exit the program.

20. main()
Creates a tree.

Inserts some demo keys.

Prints the initial structure.

Then runs the menu.
