#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char names[5][10];
	char temp[10];
	int i, j, n;

	system("clear");

	printf("\nEnter the number of students (max 5): ");
	scanf("%d", &n);
	getchar();  //to consume newline from scanf
	
	//read student names
	for (i = 0; i < n; i++)
	{
		printf("Enter the name of student %d: ", i + 1);
		fgets(names[i], sizeof(names[i]), stdin);

		size_t len = strlen(names[i]);
		if (names[i][len - 1] == '\n')
			names[i][len - 1] = '\0';
	}

	//sort using bubble sort (alphabetical order)
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			//compare two names, if out of order, swap them
			if (strcmp(names[j], names[j + 1]) > 0)
			{
				strcpy(temp, names[j]);
				strcpy(names[j], names[j + 1]);
				strcpy(names[j + 1], temp);
			}
		}
	}

	//display sorted names
	printf("\nNames of the students in alphabetical order:\n");
	for (i = 0; i < n; i++)
	{
		puts(names[i]);
	}

	return 0;
}
