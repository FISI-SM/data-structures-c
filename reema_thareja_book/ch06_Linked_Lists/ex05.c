#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *start = NULL;

struct node *create_hll(struct node *);
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
		printf("\n\n******* MAIN MENU *********");
		printf("\n 1: Create List");
		printf("\n 2: Display List");
		printf("\n 3: Insert at Beginning");
		printf("\n 4: Insert at End");
		printf("\n 5: Insert Before Value");
		printf("\n 6: Insert After Value");
		printf("\n 7: Delete from Beginning");
		printf("\n 8: Delete from End");
		printf("\n 9: Delete Specific Value");
		printf("\n 10: Delete After Value");
		printf("\n 11: Delete Entire List");
		printf("\n 12: Sort List");
		printf("\n 13: EXIT");
		printf("\n\nEnter option: ");

		scanf("%d", &option);
		getchar();

		switch(option) 
		{
			case 1:	
				start = create_hll(start);	
				printf("\nHEADER LINKED LIST CREATED\n");
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
				start = delete_node(start);	
				break;
			
			case 10:  
				start = delete_after(start);	
				break;
			
			case 11:  
				start = delete_list(start);	
				break;
			
			case 12:  
				start = sort_list(start);	
				break;
			
			case 13:  
				printf("\nExiting program..."); 
				break;
			
			default:  
				printf("\nInvalid Choice. Please 1 - 12");
		}
	} while (option != 13);


	return 0;
}


struct node *create_hll(struct node *start)
{
	int num;

	if (start == NULL) {
		start = malloc(sizeof(*start));
		start->next = NULL;
	}

	printf("\n Enter -1 to stop\n Enter data: ");
	scanf("%d", &num);
	getchar();

	while (num != -1) {
		struct node *new_node = malloc(sizeof(*new_node));
		new_node->data = num;
		new_node->next = NULL;

		if (start == NULL) {
			start = new_node;
		}
		else {
			struct node *t = start;
			while (t->next)
				t = t->next;
			t->next = new_node;
		}

		printf(" Enter data: ");
		scanf("%d", &num);
	}

	return start;
}


struct node *display(struct node *start) 
{

	if (!start) {
		printf("\nList empty");
		return start;
	}

	printf("\nList: ");
	struct node *t = start;
	while (t) {
		printf("%d ->", t->data);
		t = t->next;
	}
	printf("NULL\n");

	return start;
}

struct node *insert_beg(struct node *start) 
{
	struct node *new_node = malloc(sizeof(*new_node));
	printf("\n Enter data: ");
	scanf("%d", &new_node->data);
	getchar();
	new_node->next = start;
	return new_node;
}

struct node *insert_end(struct node *start)
{
	struct node *new_node = malloc(sizeof(*new_node));
	printf("\n Enter data: ");
	scanf("%d", &new_node->data);
	new_node->next = NULL;

	if (!start)
		return new_node;

	struct node *t = start;
	while (t->next)
		t = t->next;
	t->next = new_node;
	return start;
}

struct node *insert_before(struct node *start)
{
	int data, val;

	printf("\nEnter new data and value to insert before: ");
	scanf("%d%d", &data, &val);
	getchar();

	struct node *new_node = malloc(sizeof(*new_node));

	new_node->data = data;

	if (!start || !start->next) {
		printf("List is empty.Cannot insert before.\n");
		return start;
	}

	if (start->next->data == val) {
		new_node->next = start->next;
		start->next = new_node;
		return start;
	}

	struct node *ptr = start->next;

	while (ptr->next != NULL && ptr->next->data != val)
		ptr = ptr->next;

	if (ptr->next != NULL) {
		new_node->next = ptr->next;
		ptr->next = new_node;
	}

	return start;
}


struct node *insert_after(struct node *start)
{
	int data, val;

	printf("\nEnter new data and value to insert after: ");
	scanf("%d%d", &data, &val);
	getchar();

	struct node *new_node = malloc(sizeof(*new_node));

	new_node->data = data;

	if (!start || !start->next) {
		printf("List is empty. Cannot insert after.\n");
		return start;
	}

	struct node *ptr = start->next;

	while (ptr != NULL && ptr->data != val)
		ptr = ptr->next;

	if (ptr != NULL) {
		new_node->next = ptr->next;
		ptr->next = new_node;
	}
	else {
		printf("Value %d not found. Cannot insert.\n", val);

		free(new_node);
	}

	return start;
}

struct node *delete_beg(struct node *start)
{
	if (start == NULL || start->next == NULL) {
		printf("List is empty. Nothing to delete.\n");
		return start;
	}

	struct node *temp = start->next;
	
	start->next = temp->next;
	
	free(temp);

	return start;
}


struct node *delete_end(struct node *start)
{
	if (start == NULL || start->next == NULL) {
		printf("List is empty. Nothing to delete.\n");
		return start;
	}

	struct node *ptr = start->next;
	struct node *prev = start;

	while (ptr->next != NULL) {
		prev = ptr;
		ptr = ptr->next;
	}

	prev->next = NULL;
	free(ptr);

	return start;
}


struct node *delete_node(struct node *start)
{
	if (start == NULL || start->next == NULL) {
		printf("List is empty. Nothing to delete.\n");
		return start;
	}

	int val;

	printf("Enter the value of the node to delete: ");
	scanf("%d", &val);

	struct node *ptr = start->next;
	struct node *prev = start;

	while (ptr != NULL && ptr->data != val) {
		prev = ptr;
		ptr = ptr->next;
	}

	if (ptr == NULL) {
		printf("Value not found in the list.\n");
		return start;
	}

	prev->next = ptr->next;
	free(ptr);

	printf("Node with value %d deleted.\n", val);

	return start;
}

struct node *delete_after(struct node *start)
{
	if (start == NULL || start->next == NULL) {
		printf("List is empty. Nothing to delete.\n");
	        return start;
	}

	int val;

	printf("Enter the value of the node after which to delete: ");
	scanf("%d", &val);
	getchar();

	struct node *ptr = start->next;

	while (ptr != NULL && ptr->data != val) {
		ptr = ptr->next;
	}

	if (ptr == NULL) {
		printf("Value not found in the list.\n");
		return start;
	}

	if (ptr->next == NULL) {
		printf("There is no node after the given value to delete.\n");
		return start;
	}

	struct node *temp = ptr->next;
	ptr->next = temp->next;
	free(temp);

	printf("Node after value %d has been deleted.\n", val);

	return start;
}

struct node *delete_list(struct node *start)
{
	if (start == NULL || start->next == NULL) {
		printf("List is already empty. Nothing to delete.\n");
		return start;
	}

	struct node *ptr = start->next;
	struct node *temp;

	while (ptr != NULL) {
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}

	start->next = NULL;
	printf("All nodes have been deleted. Only header remains.\n");

	return start;
}


struct node *sort_list(struct node *start)
{
	if (start == NULL || start->next == NULL) {
		printf("List is empty or has only one node. No sorting needed.\n");
		return start;
	}

	struct node *ptr1, *ptr2;
	int temp;

	ptr1 = start->next;

	while (ptr1 != NULL) {
		ptr2 = ptr1->next;

		while(ptr2!= NULL) {
			if (ptr1->data > ptr2->data) {
				temp = ptr1->data;
				ptr1->data = ptr2->data;
				ptr2->data = temp;
			}
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}

	printf("List has been sorted in ascending order.\n");
	return start;
}



			

	

		

			
