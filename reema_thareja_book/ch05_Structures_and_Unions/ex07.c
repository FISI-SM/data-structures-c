#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student {
	int r_no;
	char name[20];
	char course[20];
	int fees;
};

int main()
{
	struct student *ptr_stud[10]; //array of pointers to struct student
	int i, n;

	printf("Enter the number of students (max 10): ");
	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {
		//allocate memory for each student
		ptr_stud[i] = (struct student *) malloc(sizeof(struct student));
		if (ptr_stud[i] == NULL) {
			printf("Memory allocation failed!\n");
			return 1;
		}

		printf("\nEnter the data for student %d", i + 1);

		printf("\nROLL NO.: ");
		scanf("%d", &ptr_stud[i]->r_no);
		getchar();

		printf("NAME: ");
		fgets(ptr_stud[i]->name, sizeof(ptr_stud[i]->name), stdin);
		ptr_stud[i]->name[strcspn(ptr_stud[i]->name, "\n")] = '\0';

		printf("COURSE: ");
		fgets(ptr_stud[i]->course, sizeof(ptr_stud[i]->course), stdin);
		ptr_stud[i]->course[strcspn(ptr_stud[i]->course, "\n")] = '\0';

		printf("FEES: ");
		scanf("%d", &ptr_stud[i]->fees);
		getchar();
	}

	printf("\nDETAILS OF STUDENTS\n");
	for (i = 0; i < n; i++) {
		printf("\nROLL NO. = %d", ptr_stud[i]->r_no);
		printf("\nNAME = %s", ptr_stud[i]->name);
		printf("\nCOURSE = %s", ptr_stud[i]->course);
		printf("\nFEES = %d\n", ptr_stud[i]->fees);
	}

	//free the allocated memory
	for (i = 0; i < n; i++) {
		free(ptr_stud[i]);
	}

	return 0;
}
