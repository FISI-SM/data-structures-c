#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *prev;
	struct node *next;
};

struct node *start = NULL;

struct node *create_ll(struct node *start);
struct node *display(struct node *start);
struct node *insert_beg(struct node *start);
struct node *insert_end(struct node *start);
struct node *insert_before(struct node *start);
struct node *insert_after(struct node *start);
struct node *delete_beg(struct node *start);
struct node *delete_end(struct node *start);
struct node *delete_before(struct node *start);
struct node *delete_after(struct node *start);
struct node *delete_list(struct node *start);

int main()
{
	int option;

	do {
		printf("\n\n******* MAIN MENU ************");
		printf("\n1: Create a list");
		printf("\n2: Display a list");
		printf("\n3: Add a node at the beginning");
		printf("\n4: Add a node at the end");
		printf("\n5: Add a node before a given node");
		printf("\n6: Add a node after a given node");
		printf("\n7: Delete a node from the beginning");
		printf("\n8: Delete a node from the end");
		printf("\n9: Delete a node before a given node");
		printf("\n10: Delete a node after a given node");
		printf("\n11: Delete the entire list");
		printf("\n12: EXIT");
		printf("\nEnter your option: ");
		scanf("%d", &option);

		switch(option) {
			case 1:
				start = create_ll(start);
				printf("\nDoubly linked list created");
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
				start = insert_before(start);
				break;

			case 6:
				start = insert_after(start);
				break;

			case 7:
				start = delete_beg(start);
				break;

			case 8:
				start = delete_end(start);
				break;

			case 9:
				start = delete_before(start);
				break;

			case 10:
				start = delete_after(start);
				break;
				
			case 11:
				start = delete_list(start);
				printf("\nDoubly linked list deleted");
				break;

			case 12:
				printf("\nExting program....");
				break;

			defualt:
				printf("\nInvalid choice. please select from 1 to 12..");
		}
	} while (option != 12);

	return 0;
}


struct node *create_ll(struct node *start) 
{
	struct node * new_node, *ptr;
	int num;

	printf("\nEnter -1 to end\nEnter Data: ");
	scanf("%d", &num);
	getchar();

	while (num != -1) {
		new_node = malloc(sizeof(*new_node));
		new_node->data = num;
		new_node->prev = NULL;
		new_node->next = NULL;

		if (start == NULL) {
			start = new_node;
		}
		else {
			ptr = start;
			while (ptr->next != NULL) //move pointer to last node
				ptr = ptr->next;
			ptr->next = new_node;  //link last node -> new node
			new_node->prev = ptr; //link new node <- last node
		}

		printf("Enter Data: ");
		scanf("%d", &num);      //read next input
	}

	return start;   //return updated head pointer
}


struct node *display(struct node *start)
{
	struct node *ptr = start;

	printf("\nList: ");
	if (ptr == NULL) {
		printf("Empty\n");
		return start;
	}

	while (ptr != NULL) {
		printf("%d", ptr->data);
		if (ptr->next)
			printf(" <-> ");
		ptr = ptr->next;   //move to next node
	}

	printf(" -> NULL\n");
	return start;
}


struct node *insert_beg(struct node *start)
{
	struct node *new_node;
	int num;

	printf("\nEnter Data: ");
	scanf("%d", &num);

	new_node = malloc(sizeof(*new_node));
	new_node->data = num;
	new_node->prev = NULL;
	new_node->next = start; //next pointer -> old head

	if (start != NULL) //if list wasnt empty
		start->prev = new_node; //link old head  back to new node

	start = new_node;   //update head pointer
	return start;
}


struct node *insert_end(struct node *start)
{
	struct node *new_node, *ptr;
	int num;

	printf("\nEnter data: ");
	scanf("%d", &num);

	new_node = malloc(sizeof(*new_node));
	new_node->data = num;
	new_node->next = NULL;

	if (start == NULL) { //if list is empty
		new_node->prev = NULL; //no previous node either
		return new_node; //new node is now head
	}

	ptr = start;
	while (ptr->next)
		ptr = ptr->next;

	ptr->next = new_node; //link last node -> new node
	new_node->prev = ptr;  //link new node <- last node
	return start;
}


struct node *insert_before(struct node *start)
{
	struct node *new_node, *ptr;
	int num, val;

	printf("\nEnter data: ");
	scanf("%d", &num);
	getchar();
	printf("Before which value?: ");
	scanf("%d", &val);
	getchar();

	ptr = start;
	while (ptr != NULL && ptr->data != val) //find node with the value
		ptr = ptr->next;

	if (ptr == NULL) {  //if value not found
		printf("Value not found.\n");
		return start;   //no change
	}
	
	new_node = malloc(sizeof(*new_node));
	new_node->data = num;
	new_node->next = ptr;
	new_node->prev = ptr->prev;

	if (ptr->prev)
		ptr->prev->next = new_node; //link previous node -> new node
	else 
		start = new_node;  //new becomes head

	ptr->prev = new_node;
	return start;
}


struct node *insert_after(struct node *start)
{
	struct node *new_node, *ptr;
	int num, val;

	printf("\nEnter data: ");
	scanf("%d", &num);
	getchar();
	printf("After which value?: ");
	scanf("%d", &val);
	getchar();

	ptr = start;
	while (ptr != NULL && ptr->data != val)
		ptr = ptr->next;

	if (ptr == NULL) {
		printf("Value not found.\n");
		return start;
	}

	new_node = malloc(sizeof(*new_node));
	new_node->data = num;
	new_node->next = ptr->next;
	new_node->prev = ptr;

	if (ptr->next)
		ptr->next->prev = new_node;  //adjust next node's previous pointer
					     
	ptr->next = new_node;
	return start;
}


struct node *delete_beg(struct node *start)
{
	struct node *ptr = start;
	
	if (!start) return NULL;

	start = start->next;

	if (start)
		start->prev = NULL; //clear new head's prev link

	free(ptr);
	return start;
}

struct node *delete_end(struct node *start) 
{
	struct node *ptr  = start;

	if (!start) return NULL;

	while (ptr->next)
		ptr = ptr->next;

	if (ptr->prev)
		ptr->prev->next = NULL; //remove link from second last
	else
		start = NULL;  //list becomes empty

	free(ptr);
	return start;
}

struct node *delete_before(struct node *start)
{
	struct node *ptr = start, *temp;
	int val;

	printf("\nDelete before value: ");
	scanf("%d", &val);

	while (ptr && ptr->data != val) //locate the node
		ptr = ptr->next;

	if (!ptr || !ptr->prev) { //if node or predecessor missing
		printf("Nothing to delete.\n");
		return start;
	}

	temp = ptr->prev;

	if (temp->prev)
		temp->prev->next = ptr; //link predecessor to current
	else
		start = ptr;  //removed head, update start

	ptr->prev = temp->prev; //adjust ptrs prev
	free(temp);
	return start;
}


struct node *delete_after(struct node *start)
{
	struct node *ptr = start, *temp;
	int val;

	printf("\nDelete after value: ");
	scanf("%d", &val);

	while (ptr && ptr->data != val) //find node with matching data
		ptr = ptr->next;

	if (!ptr || !ptr->next) {
		printf("Nothing to delete.\n");
		return start;
	}

	temp = ptr->next;  //node to delete
	ptr->next = temp->next;  //bypass it
	
	if (temp->next)
		temp->next->prev = ptr;  //fix backward link of the next node

	free(temp);
	return start;
}

struct node *delete_list(struct node *start)
{
	while (start)
		start = delete_beg(start);

	return NULL;
}









