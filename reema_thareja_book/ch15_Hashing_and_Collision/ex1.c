/* A program to demostrate search function using closed hashing 
 * also known as open address collision resolution technique. The
 * particular technique under closed hashing used here is 
 * the Linear probing technique */

#include <stdio.h>

int ht[10];

int i, found = 0, key;

void insert_val();
void search_val();
void delete_val();
void display();

int main()
{
	int option;

	for (i = 0; i < 10; i++)
		ht[i] = -1;

	do 
	{
		printf("\n MENU \n1. Insert \n2. Search \n3. Delete \n4. Display \n5. Exit");
		
		printf("\n Enter your option: ");
		scanf("%d", &option);

		switch (option)
		{
			case 1:
				insert_val();
				break;

			case 2:
				search_val();
				break;

			case 3:
				delete_val();
				break;

			case 4:
				display();
				break;

			case 5:
				printf("\nExiting program...\n");
				break;

			default:
				printf("\nInvalid choice entry!!!\n");
				break;
		}

	} while (option != 5);

	return 0;
}

void insert_val()
{
	int val, f = 0;

	printf("\nEnter the element to be inserted: ");
	scanf("%d", &val);

	key = (val % 10);

	if (ht[key] == -1)
	{
		ht[key] = val;
	}

	else
	{
		for (i = key + 1; i < 10; i++)
		{
			if (ht[i] == -1)
			{
				ht[i] = val;
				return;
			}
		}


		for (i = 0; i < key; i++)
		{
			if (ht[i] == -1)
			{
				ht[i] = val;
				return;
			}
		}

		printf("\nHashtable is full! Cannot insert the value.\n");
	}
}


void display()
{
	for (i = 0; i < 10; i++)
		printf("\t%d", ht[i]);
	printf("\n");
}

void search_val()
{
	int val, flag = 0;

	printf("\nEnter the element to be searched: ");
	scanf("%d", &val);

	key = (val % 10);

	if (ht[key] == val)
	{
		flag = 1;
	}

	else
	{
		for (i = key; i < 10; i++)
		{
			if (ht[i] == val)
			{
				flag = 1;
				key = i;
				break;
			}
		}

		if (flag == 0)
		{
			for (i == 0; i < key; i++)
			{
				if (ht[i] == val)
				{
					flag = 1;
					key = i;
					break;
				}
			}
		}
	}

	if (flag == 1)
	{
		found = 1;
		printf("\nThe item searched was found at position %d!", key + 1);
	}

	else
	{
		key = -1;
		printf("\nThe item searched was not found in the hash table.");
	}
}


void delete_val()
{
	search_val();

	if (found == 1)
	{
		if (key != -1)
		{
			printf("\nThe element deleted is %d", ht[key]);
			ht[key] = -1;
		}

		found = 0;
	}
}
