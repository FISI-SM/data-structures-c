#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *start = NULL;

struct node *create_cll(struct node *);
struct node *display(struct node *);
struct node *insert_beg(struct node *);
struct node *insert_end(struct node *);
struct node *delete_beg(struct node *);
struct node *delete_end(struct node *);
struct node *delete_after(struct node *);
struct node *delete_list(struct node *);

int main()
{
	int option;

	do {
		printf("\n\n ******** MAIN MENU *********");
		printf("\n 1: Create a list");
		printf("\n 2: Display the list");
		printf("\n 3: Add a node at the beginning");
		printf("\n 4: Add a node at the end");
		printf("\n 5: Delete a node from the beginning");
		printf("\n 6: Delete a node from the end");
		printf("\n 7: Delete a node after a given node");
		printf("\n 8: Delte the entire list");
		printf("\n 9: EXIT");
	
		printf("\n\n Enter your option: ");
		scanf("%d", &option);
		getchar();

		switch(option) {
			case 1: 
				start = create_cll(start);
				printf("\n CIRCULAR LINKED LIST CREATED");
				break;

			case 2:
				start = display(start);
				break;
			
			case 3:
				start = insert_beg(start);
				break;

			case 4:
				start = insert_end(start);
				break;

			case 5:
				start = delete_beg(start);
				break;

			case 6:
				start = delete_end(start);
				break;

			case 7:
				start = delete_after(start);
				break;

			case 8:
				start = delete_list(start);
				printf("\n CIRCULAR LINKED LIST DELETED");
				break;

			case 9:
				printf("\n Exiting program.....");
				break;

			default:
				printf("\nInvalid choice (Enter 1 - 9)");

		}
	} while (option != 9);

	return 0;
}

struct node *create_cll(struct node *start)
{
	struct node *new_node, *ptr;
	int num;

	printf("\n Enter -1 to end");
	printf("\n Enter the data: ");
	scanf("%d", &num);
	getchar();

	while (num != -1) {
		new_node = (struct node*)malloc(sizeof(struct node));
		new_node->data = num;
		new_node->next = NULL;

		if (start == NULL) {
			//first node case: create the first node that points to itself
			new_node->next = new_node;
			start = new_node;
		}
		else {
			//add new node at the end
			ptr = start;
			while (ptr->next != start)
				ptr = ptr->next;
			
			ptr->next = new_node; //last node points to new node
			new_node->next = start;  //new node points to start (circular)
		}

		printf("\n Enter the data: ");
		scanf("%d", &num);
		getchar();
	}

	return start;
}


struct node *display(struct node *start)
{
	struct node *ptr;

	if (start == NULL) {
		printf("\n List is empty");
		return start;
	}

	ptr = start; //start from beginning
	printf("\n Circular Linked list: ");
	while (ptr->next != start) { //loop until we come back
		printf("%d -> ", ptr->data);
		ptr = ptr->next;
	}

	printf("%d -> (Back to start)", ptr->data);

	return start;
}

struct node *insert_beg(struct node *start)
{
	struct node *new_node, *ptr;
	int num;

	printf("\n Enter the data: ");
	scanf("%d", &num);

	new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = num;

	if (start == NULL) {
		new_node->next = new_node;
		start = new_node;
	}
	else {
		ptr = start;

		while (ptr->next != start) //find the last node
			ptr = ptr->next;

		ptr->next = new_node;  //last node points to new node
		new_node->next = start; //new node points to old start
		start = new_node;       //new node becomes the new start
	}

	return start;
}

struct node *insert_end(struct node *start)
{
	struct node *ptr, *new_node;
	int num;

	printf("\n Enter the data: ");
	scanf("%d", &num);

	new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = num;

	if (start == NULL) {
		new_node->next = new_node;
		return new_node;
	}

	ptr = start;
	while (ptr->next != start)
		ptr = ptr->next;
	

	ptr->next = new_node;
	new_node->next = start;

	return start;
}


struct node *delete_beg(struct node *start)
{
	struct node *ptr = start;

	if (start == NULL) return NULL;//if list is empty

	while (ptr->next != start)  //find last node
		ptr = ptr->next;

	ptr->next = start->next;  //last node points to second node
	free(start);
	start = ptr->next;

	return start;
}

struct node *delete_end(struct node *start)
{
	struct node *ptr = start, *preptr;

	if (start == NULL) return NULL;

	while (ptr->next != start) {
		preptr = ptr;
		ptr = ptr->next;
	}

	preptr->next = start;
	free(ptr);

	return start;
}

struct node *delete_after(struct node *start)
{
	struct node *ptr, *preptr;
	int val;

	printf("\n Enter the value after which the node has to be deleted: ");
	scanf("%d", &val);
	getchar();

	ptr = start;
	preptr = ptr;

	while (preptr->data != val) {
		preptr = ptr;
		ptr = ptr->next;
	}

	preptr->next = ptr->next;

	if (ptr == start)
		start = preptr->next;

	free(ptr);//free memory of deleted node

	return start;
}

struct node *delete_list(struct node *start)
{
	struct node *ptr = start;

	while (ptr->next != start) {
		start = delete_end(start);
		ptr = start;
	}

	free(start);
	return NULL;
}





