/* A C program to demonstrate initialisation, insertion,
 *  search for a value and delete a value in a
 *  chained hash-table */


#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
	int data;
	struct Node *next;
};

struct Node *hashTable[SIZE];

struct Node *createNode(int value)
{
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = value;
	newNode->next = NULL;
	return newNode;
}

void insert(int value)
{
	int index = value % SIZE;

	struct Node *newNode = createNode(value);

	if (hashTable[index] == NULL)
	{
		hashTable[index] = newNode;
	}

	else
	{
		struct Node *temp = hashTable[index];
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}

	printf("Inserted %d at index %d\n", value, index);
}

void search(int value)
{
	int index = value % SIZE;

	struct Node *temp = hashTable[index];
	while (temp != NULL)
	{
		if (temp->data == value)
		{
			printf("Found %d at index %d\n", value, index);
			return;
		}

		temp = temp->next;
	}

	printf("%d not found in the hash table\n", value);
}


void delete(int value)
{
	int index = value % SIZE;

	struct Node *temp = hashTable[index];
	struct Node *prev = NULL;

	while (temp != NULL)
	{
		if (temp->data == value)
		{
			if (prev == NULL)
			{
				hashTable[index] = temp->next;
			}

			else
			{
				prev->next = temp->next;
			}

			free(temp);
			printf("Deleted %d from index %d\n", value, index);
			return;
		}

		prev = temp;
		temp = temp->next;
	}

	printf("%d not found. Cannot delete.\n", value);
}


void display()
{
	for (int i = 0; i < SIZE; i++)
	{
		printf("Index %d: ", i);

		struct Node *temp = hashTable[i];
		while (temp != NULL)
		{
			printf("%d -> ", temp->data);
			temp = temp->next;
		}

		printf("NULL\n");
	}
}


int main()
{
	int choice, value;

	for (int i = 0; i < SIZE; i++)
	{
		hashTable[i] = NULL;
	}

	do {
		printf("\nMenu:\n");
		printf("1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
		printf("Enter your choice: ");

		scanf("%d", &choice);

		switch (choice)
		{
			case 1:
				printf("Enter value to insert: ");
				scanf("%d", &value);
				insert(value);
				break;
			case 2:
				printf("Enter value to search: ");
				scanf("%d", &value);
				search(value);
				break;

			case 3:
				printf("Enter value to delete: ");
				scanf("%d", &value);
				break;

			case 4:
				display();
				break;

			case 5:
				printf("Exiting...\n");
				break;
			
			default:
				printf("Invalid choice. Please try again.\n");
		}

	} while (choice != 5);

	return 0;
}


