#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

struct node *tree = NULL;

struct node *insertElement(struct node *, int);
void preorderTraversal(struct node *);
void inorderTraversal(struct node *);
void postorderTraversal(struct node *);
struct node *findSmallestElement(struct node *);
struct node *findLargestElement(struct node *);
struct node *deleteElement(struct node *, int);
struct node *mirrorImage(struct node *);
int totalNodes(struct node *);
int totalExternalNodes(struct node *);
int totalInternalNodes(struct node *);
int Height(struct node *);
struct node *deleteTree(struct node *);

int main()
{
	int option, val;
	struct node *ptr;

	do {
		printf("\n**********MAIN MENU***********\n");
		printf("1. Insert Element\n");
		printf("2. Preorder Traversal\n");
		printf("3. Inorder Traversal\n");
		printf("4. Postorder Traversal\n");
		printf("5. Find the smallest element\n");
		printf("6. Find the largest element\n");
		printf("7. Delete an element\n");
		printf("8. Count total number of nodes\n");
		printf("9. Count total of external nodes (leaves)\n");
		printf("10. Count total number of internal nodes\n");
		printf("11. Determine the height of the tree\n");
		printf("12. Get the mirror image of the tree\n");
		printf("13. Delete the tree\n");
		printf("14. Exit\n");

		printf("Enter your option: ");
		scanf("%d", &option);

		switch (option) 
		{
			case 1:
				printf("Enter value of the new node: ");
				scanf("%d", &val);
				tree = insertElement(tree, val);
				break;

			case 2:
				printf("Preorder Traversal:\n");
				preorderTraversal(tree);
				break;

			case 3:
				printf("Inorder Traversal:\n");
				inorderTraversal(tree);
				break;

			case 4:
				printf("Postorder Traversal:\n");
				postorderTraversal(tree);
				break;

			case 5:
				ptr = findSmallestElement(tree);
				if (ptr)
					printf("Smallest element: %d\n", ptr->data);
				break;

			case 6:
				ptr = findLargestElement(tree);
				if (ptr)
					printf("Largest element: %d\n", ptr->data);
				break;

			case 7:
				printf("Enter the element to delete: ");
				scanf("%d", &val);
				tree = deleteElement(tree, val);
				break;

			case 8:
				printf("Total number of nodes: %d\n", totalNodes(tree));
				break;

			case 9:
				printf("Total number of external nodes (leaves): %d\n", totalExternalNodes(tree));
				break;

			case 10:
				printf("Total number of internal nodes: %d\n", totalInternalNodes(tree));
				break;

			case 11:
				printf("Height of the tree: %d\n", Height(tree));
				break;

			case 12:
				tree = mirrorImage(tree);
				printf("Mirror image created.\n");
				break;

			case 13:
				tree = deleteTree(tree);
				printf("Tree deleted successfully.\n");
				break;

			case 14:
				printf("Exiting program.\n");
				break;

			default:
				printf("Invalid option. Try again.\n");

			}
	} while (option != 14);

	return 0;
}


struct node *insertElement(struct node *tree, int val)
{
	struct node *ptr , *nodeptr, *parentptr;

	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = val;
	ptr->left = NULL;
	ptr->right = NULL;

	if (tree == NULL)
	{
		tree = ptr;
	}
	else 
	{
		parentptr = NULL;
		nodeptr = tree;

		while (nodeptr != NULL)
		{
			parentptr = nodeptr;
			if (val < nodeptr->data)
				nodeptr = nodeptr->left;
			else
				nodeptr = nodeptr->right;
		}

		if (val < parentptr->data)
			parentptr->left = ptr;
		else
			parentptr->right = ptr;
	}

	return tree;
}

void preorderTraversal(struct node *tree)
{
	if (tree != NULL)
	{
		printf("%d\t", tree->data);

		preorderTraversal(tree->left);

		preorderTraversal(tree->right);
	}
}

void inorderTraversal(struct node *tree)
{
	if (tree != NULL)
	{
		inorderTraversal(tree->left);

		printf("%d\t", tree->data);

		inorderTraversal(tree->right);
	}
}

void postorderTraversal(struct node *tree)
{
	if (tree != NULL)
	{
		postorderTraversal(tree->left);

		postorderTraversal(tree->right);

		printf("%d\t", tree->data);
	}
}


struct node *findSmallestElement(struct node *tree)
{
	if ((tree == NULL) || (tree->left == NULL))
	
		return tree;
	else
		return findSmallestElement(tree->left);
}

struct node *findLargestElement(struct node *tree)
{
	if ((tree == NULL) || (tree->right == NULL))
		return tree;
	else
		return findLargestElement(tree->right);
}

struct node *deleteElement(struct node *tree, int val)
{
	struct node *cur, *parent, *suc, *psuc, *ptr;

	if (tree == NULL)
	{
		printf("\n The tree is empty ");
		return tree;
	}

	parent = NULL;
	cur = tree;

	while (cur != NULL && val != cur->data)
	{
		parent = cur;

		if (val < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}

	if (cur == NULL)
	{
		printf("\n The value to be deleted is not present in the tree");
		return tree;
	}

	if (cur->left == NULL)
	{
		ptr = cur->right;
	}

	else if (cur->right == NULL)
	{
		ptr = cur->left;
	}

	else
	{
		psuc = cur;
		suc = cur->right;

		while (suc->left != NULL)
		{
			psuc = suc;
			suc = suc->left;
		}

		if (psuc == cur)
		{
			suc->left = cur->left;
		}
	        else
		{
			psuc->left = suc->right;
			suc->left = cur->left;
			suc->right = cur->right;
		}

		ptr = suc;
	}

	if (parent == NULL)
	{
		tree = ptr;
	}
	else if (cur == parent->left)
	{
		parent->left = ptr;
	}
	else
	{
		parent->right = ptr;
	}

	free(cur);

	return tree;
}

struct node *mirrorImage(struct node *tree)
{
	struct node *ptr;

	if (tree != NULL)
	{
		mirrorImage(tree->left);

		mirrorImage(tree->right);

		ptr = tree->left;

		tree->left = tree->right;

		tree->right = ptr;
	}

	return tree;
}


int totalNodes(struct node *tree)
{
	if (tree == NULL)
		return 0;

	else
		return (totalNodes(tree->left) + totalNodes(tree->right) + 1);
}

int totalExternalNodes(struct node *tree)
{
	if (tree == NULL)
		return 0;

	else if (tree->left == NULL && tree->right == NULL)
		return 1;

	else 
		return totalExternalNodes(tree->left) + totalExternalNodes(tree->right);
}

int totalInternalNodes(struct node *tree)
{
	if (tree == NULL)
		return 0;

	else if (tree->left == NULL && tree->right == NULL)
		return 0;

	else
		return (totalInternalNodes(tree->left) + totalInternalNodes(tree->right) + 1);
}
				

int Height(struct node *tree)
{
	int leftheight, rightheight;

	if (tree == NULL)
		return 0;

	else 
	{
		leftheight = Height(tree->left);

		rightheight = Height(tree->right);

		if (leftheight > rightheight)
			return (leftheight + 1);
		else
			return (rightheight + 1);
	}
}

struct node *deleteTree(struct node *tree)
{
	if (tree != NULL)
	{
		deleteTree(tree->left);

		deleteTree(tree->right);

		free(tree);
	}

	return NULL;
}
