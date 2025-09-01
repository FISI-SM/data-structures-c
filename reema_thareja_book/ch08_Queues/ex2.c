#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	struct node *next;
};

struct queue 
{
	struct node *front;
	struct node *rear;
};

struct queue *q = NULL;

struct queue *create_queue();
struct queue *insert(struct queue *, int);
struct queue *delete_element(struct queue *);
struct queue *display(struct queue *);
int peek(struct queue *);
void free_queue(struct queue *);

int main()
{
	int val, option;

	q = create_queue();

	do {
		printf("\n\n********* MAIN MENU*********\n");
		printf(" 1. INSERT\n");
		printf(" 2. DELETE\n");
		printf(" 3. PEEK\n");
		printf(" 4. DISPLAY\n");
		printf(" 5. EXIT\n");
		
		printf(" Enter your option: ");
		scanf("%d", &option);

		switch (option) 
		{
			case 1:
				printf("\n Enter the number to insert in the queue: ");
				scanf("%d", &val);
				q = insert(q, val);
				break;

			case 2:
				q = delete_element(q);
				break;

			case 3:
				val = peek(q);
				if (val != -1)
					printf("\n The value at front of queue is: %d", val);
				break;

			case 4:
				q = display(q);
				break;

			case 5:
				printf("\n Exiting program.....\n");
				break;

			default:
				printf("\n Invalid choice! Please choose 1-5");
		}
	} while (option != 5);


	return 0;
}


struct queue *create_queue()
{
	struct queue *q = (struct queue*) malloc(sizeof(struct queue));
	if (q == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}

	q->front  = NULL;
	q->rear = NULL;
	return q;
}

struct queue *insert(struct queue *q, int val)
{
	struct node *ptr = (struct node *) malloc(sizeof(struct node));
	if (ptr == NULL)
	{
		printf("Memory allocation failed.\n");
		exit(1);
	}

	ptr->data = val;
	ptr->next = NULL;

	if (q->front == NULL)
	{
		q->front = ptr;
		q->rear = ptr;
	}
	else
	{
		q->rear->next = ptr;
		q->rear = ptr;
	}

	return q;
}

struct queue *display(struct queue *q)
{
	struct node *ptr = q->front;

	if (ptr == NULL)
	{
		printf("\nQUEUE IS EMPTY\n");
	}
	else
	{
		printf("\n Queue contents: ");

		while (ptr != NULL)
		{
			printf("%d\t", ptr->data);
			ptr = ptr->next;
		}

		printf("\n");
	}

	return q;
}

struct queue *delete_element(struct queue *q)
{
	struct node *ptr = q->front;

	if (q->front == NULL)
	{
		printf("\n UNDERFLOW");
	}
	else
	{
		printf("\n The value being deleted is : %d\n", ptr->data);
		q->front = q->front->next;
		free(ptr);

		if (q->front == NULL)
			q->rear = NULL;
	}

	return q;
}


int peek(struct queue *q)
{
	if (q->front == NULL)
	{
		printf("\n QUEUE IS EMPTY\n");
		return -1;
	}
	else
	{
		return q->front->data;
	}
}


void free_queue(struct queue *q)
{
	struct node *ptr = q->front;
	struct node *temp;

	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}

	free(q);
}
