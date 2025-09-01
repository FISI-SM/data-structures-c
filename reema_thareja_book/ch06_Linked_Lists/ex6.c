#include <stdio.h>
#include <stdlib.h>

struct node {
	int num;
	int coeff;
	struct node *next;
};

struct node *start1 = NULL;
struct node *start2 = NULL;
struct node *start3 = NULL;
struct node *start4 = NULL;

struct node *create_poly(struct node *);
struct node *display_poly(struct node *);
struct node *add_poly(struct node *, struct node *, struct node *);
struct node *sub_poly(struct node *, struct node *, struct node *);
struct node *add_node(struct node *, int, int);

int main() 
{
	int option;

	do {
		printf("\n************ MAIN MENU **************");
		printf("\n 1. Enter the first polynomial");
		printf("\n 2. Display the first polynomial");
		printf("\n 3. Enter the second polynomial");
		printf("\n 4. Display the second polynomial");
		printf("\n 5. Add the polynomials");
		printf("\n 6. Display addition result");
		printf("\n 7. Subtract the polynomials");
		printf("\n 8. Display subtraction result");
		printf("\n 9. EXIT");

		printf("\n\n Enter your option: ");
		scanf("%d", &option);

		switch(option) {
			
			case 1:
				start1 = create_poly(start1);
				break;
			case 2:
				start1 = display_poly(start1);
				break;
			case 3:
				start2 = create_poly(start2);
				break;
			case 4:
				start2 = display_poly(start2);
				break;
			case 5:
				start3 = add_poly(start1, start2, start3);
				break;
			case 6:
				start3 = display_poly(start3);
				break;
			case 7:
				start4 = sub_poly(start1, start2, start4);
				break;
			case 8:
				start4 = display_poly(start4);
				break;
			case 9:
				printf("\nExiting program...\n");
				break;
			default:
				printf("\nInvalid option. Please choose 1 to 9.\n");
		}
	} while (option != 9);

	return 0;
}

struct node *create_poly(struct node *start) 
{
	int n, c;  //n = coefficient of x, c = power of x
	struct node *new_node, *ptr;

	printf("\nEnter the coefficient (enter -1 to stop): ");
	scanf("%d", &n);
	getchar();

	while (n != -1) {
		printf("Enter its power: ");
		scanf("%d", &c);
		getchar();

		new_node = (struct node *)malloc(sizeof(struct node));
		if (!new_node) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		new_node->num = n;
		new_node->coeff = c;
		new_node->next = NULL;

		if (start == NULL) {
			start = new_node;
		}
		else {
			ptr = start;
			while (ptr->next != NULL)
				ptr = ptr->next;

			ptr->next = new_node;
		}
		
		//Ask user for the next coefficent (or -1 to stop)
		printf("\nEnter the coefficient (enter -1 to stop): ");
		scanf("%d", &n);
	}

	return start;
}


struct node *display_poly(struct node *start)
{
	struct node *ptr = start;

	printf("\nPolynomial: ");

	while (ptr != NULL) {
		printf("%d x^%d", ptr->num, ptr->coeff);

		if (ptr->next != NULL)
			printf(" + ");

		ptr = ptr->next;
	}

	printf("\n");

	return start;
}


struct node *add_poly(struct node *start1, struct node *start2, struct node *start3)
{
	struct node *ptr1 = start1;
	struct node *ptr2 = start2;
	int n, c;

	while (ptr1 != NULL && ptr2 != NULL) {
		if (ptr1->coeff == ptr2->coeff) {
			n = ptr1->num + ptr2->num;
			c = ptr1->coeff;
			start3 = add_node(start3, n, c);

			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		else if (ptr1->coeff > ptr2->coeff) {
			n = ptr1->num;
			c = ptr1->coeff;
			start3 = add_node(start3, n, c);

			ptr1 = ptr1->next;
		}
		else {
			n = ptr2->num;
			c = ptr2->coeff;
			start3 = add_node(start3, n, c);

			ptr2 = ptr2->next;
		}
	}

	while (ptr1 != NULL) {
		n = ptr1->num;
		c = ptr1->coeff;
		start3 = add_node(start3, n, c);
		ptr1 = ptr1->next;
	}

	while (ptr2 != NULL) {
		n = ptr2->num;
		c = ptr2->coeff;
		start3 = add_node(start3,n, c);
		ptr2 = ptr2->next;
	}

	return start3;
}

struct node *sub_poly(struct node *start1, struct node *start2, struct node *start3)
{
	struct node *ptr1 = start1;
	struct node *ptr2 = start2;
	int n, c;

	while (ptr1 != NULL && ptr2 != NULL) {
		if (ptr1->coeff == ptr2->coeff) {
			n = ptr1->num - ptr2->num;
			c = ptr1->coeff;
			start4 = add_node(start4, n, c);

			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		else if (ptr1->coeff > ptr2->coeff) {
			n = ptr1->num;
			c = ptr1->coeff;
			start4 = add_node(start4, n, c);

			ptr1 = ptr1->next;
		}
		else {
			n = -ptr2->num;
			c = ptr2->coeff;
			start4 = add_node(start4, n, c);

			ptr2 = ptr2->next;
		}
	}

	while (ptr1 != NULL) {
		n = ptr1->num;
		c = ptr1->coeff;
		start4 = add_node(start4, n, c);
		ptr1 = ptr1->next;
	}

	while (ptr2 != NULL) {
		n = -ptr2->num;
		c = ptr2->coeff;
		start4 = add_node(start4, n, c);
		ptr2 = ptr2->next;
	}

	return start4;
}


struct node *add_node(struct node *start, int n, int c)
{
	struct node *ptr, *new_node;

	new_node = (struct node *)malloc(sizeof(struct node));
	if (!new_node) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	new_node->num = n;
	new_node ->coeff = c;
	new_node->next = NULL;

	if (start == NULL) {
		start = new_node;
	}
	else {
		ptr = start;
		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = new_node;
	}

	return start;
}
		 
