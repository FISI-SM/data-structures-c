#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *start = NULL;

struct node *create_ll(struct node *);
struct node *display(struct node *);
struct node *insert_beg(struct node *);
struct node *insert_end(struct node *);
struct node *insert_before(struct node *);
struct node *insert_after(struct node *);
struct node *delete_beg(struct node *);
struct node *delete_end(struct node *);
struct node *delete_node(struct node *);
struct node *delete_after(struct node *);
struct node *delete_list(struct node *);
struct node *sort_list(struct node *);

int main()
{
	int option;

	do {
		printf("\n\n ****** MAIN MENU ********");
		printf("\n 1: create a list");
		printf("\n 2: Display the list");
		printf("\n 3: Add a node at the beginning");
		printf("\n 4: Add a node at the end");
		printf("\n 5: Add a node before a given node");
		printf("\n 6: Add a node after a given node");
		printf("\n 7: Delete a node from the beginning");
		printf("\n 8: Delete a node from the end");
		printf("\n 9: Delete a given node");
		printf("\n 10: Delete a node after a given node");
		printf("\n 11: Delete the entire list");
		printf("\n 12: Sort the list");
		printf("\n 13: EXIT");

		printf("\n\n Enter your option: ");
		scanf("%d", &option);
		getchar();

		switch(option) {
			case 1: start = create_ll(start);
				printf("\n LINKED LIST CREATED");
				break;

			case 2: start = display(start);
				break;

			case 3: start = insert_beg(start);
				break;

			case 4: start = insert_end(start);
				break;

			case 5: start = insert_before(start);
				break;

			case 6: start = insert_after(start);
				break;

			case 7: start = delete_beg(start);
				break;

			case 8: start = delete_end(start);
				break;

			case 9: start = delete_node(start);
				break;

			case 10: start = delete_after(start);
				 break;

			case 11: start = delete_list(start);
				 printf("\n LINKED LIST DELETED");
				 break;

			case 12: start = sort_list(start);
				 break;

			case 13: 
				 printf("\nExiting program....");
				 break;

			default:
				 printf("\nInvalid Option! (choose 1 - 13)");

		}
	} while (option != 13);

	return 0;
}





struct node *create_ll(struct node *start)
{
	struct node *new_node, *ptr;
	int num;

	printf("\n Enter -1 to end");
	printf("\n Enter the data: ");
	scanf("%d", &num);
	getchar();

	while (num != -1) {
		new_node = (struct node *)malloc(sizeof(struct node));
		new_node->data = num;
		new_node->next = NULL;

		if (start == NULL) { //if list is empty, newnode becomes first node
			start = new_node;
		}
		else {
			ptr = start;  //start from beginning
			
			while (ptr->next != NULL) //traverse to the last node
				ptr = ptr->next;
			ptr->next = new_node; //link last node to the new node
		}

		printf("\n Enter the data: ");
		scanf("%d", &num); //continue reading input
	}

	return start; //return updated list
}

struct node *display(struct node *start) 
{
	struct node *ptr = start;  //start from head
	printf("\nList: ");
	while (ptr != NULL) {
		printf("%d -> ", ptr->data);
		ptr = ptr->next;
	}

	printf("NULL\n");
	return start;
}

struct node *insert_beg(struct node *start)
{
	struct node *new_node;
	int num;
	printf("\n Enter the data: ");
	scanf("%d", &num);

	new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = num;
	new_node->next = start;
	start = new_node;

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
	new_node->next = NULL;

	ptr = start; 
	if (ptr = NULL) { //if list is empty, new node becomes first
		return new_node;
	}

	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_node; //Add new node at the end

	return start;
}

struct node *insert_before(struct node *start)
{
	struct node *new_node, *ptr, *preptr;
	int num, val;

	printf("\nEnter the data: ");
	scanf("%d", &num);
	printf("\n Enter the value before which to insert: ");
	scanf("%d", &val);

	new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = num;

	ptr = start;
	if (ptr->data == val) { //if the target is the first node
		new_node->next = start;
		return new_node;
	}

	while (ptr != NULL && ptr->data != val) { //search for value
		preptr = ptr;
		ptr = ptr->next;
	}

	if (ptr != NULL) {  //insert before found node
		preptr->next = new_node;
		new_node->next = ptr;
	}

	return start;
}

struct node *insert_after(struct node *start)
{
	struct node *new_node, *ptr;
	int num, val;

	printf("\n Enter the data: ");
	scanf("%d", &num);
	printf("\n Enter the value after which to insert: ");
	scanf("%d", &val);

	new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = num;

	ptr = start;
	while (ptr != NULL && ptr->data != val) {
		ptr = ptr->next;
	}

	if (ptr != NULL) {
		new_node->next = ptr->next;
		ptr->next = new_node;
	}

	return start;
}

struct node *delete_beg(struct node *start)
{
	struct node *ptr = start;
	if (ptr == NULL)  //empty list
		return NULL; 
	ptr = start->next; //move head to next node
	free(ptr); //free memory of old first head
	return start;
}

struct node *delete_end(struct node *start)
{
	struct node *ptr, *preptr;

	ptr = start;
	if (ptr == NULL)  //empty list
		return NULL;  

	if (ptr->next == NULL) { //only one node
		free(ptr);
		return NULL;
	}

	while (ptr->next != NULL) { //Disconnect last node
		preptr = ptr;
		ptr = ptr->next;
	}

	preptr->next = NULL;
	free(ptr);

	return start;
}

struct node *delete_node(struct node *start)
{
	struct node *ptr, *preptr;
	int val;

	printf("\n Enter the value to delete: ");
	scanf("%d", &val);

	ptr = start;
	if (ptr == NULL) return NULL; //empty list
 
	if (ptr->data = val) {  //value is in first node
		start = delete_beg(start);
		return start;
	}

	while (ptr != NULL && ptr->data != val) {
		preptr = ptr;
		ptr = ptr->next;
	}

	if (ptr != NULL) {
		preptr->next = ptr->next;
		free(ptr);
	}

	return start;
}

struct node *delete_after(struct node *start)
{
	struct node *ptr;
	int val;

	printf("\n Enter the value after which to delete: ");
	scanf("%d", &val);

	ptr = start;
	while (ptr != NULL && ptr->data != val) {
		ptr = ptr->next;
	}

	if (ptr != NULL && ptr->next != NULL) {
		struct node *temp = ptr->next;
		ptr->next = temp->next;
		free(temp);
	}

	return start;
}

struct node *delete_list(struct node *start)
{
	struct node *ptr;

	while (start != NULL) {
		ptr = start;
		printf("\nDeleting %d", ptr->data);
		start = start->next;
		free(ptr);
	}

	return NULL;
}


struct node *sort_list(struct node *start)
{
	struct node *ptr1, *ptr2;
	int temp;

	for (ptr1 = start; ptr1 != NULL; ptr1 = ptr1->next) {
		for (ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2->next) {
			if (ptr1->data > ptr2->data) {
				temp = ptr1->data;
				ptr1->data = ptr2->data;
				ptr2->data = temp;
			}
		}
	}

	return start;
}

