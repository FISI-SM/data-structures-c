#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	int r_no;
	char name[20];
	char course[20];
	int fees;
};

void display(struct student *ptr);

int main() 
{
	struct student *ptr;
	
	//allocate memory for one student using malloc
	ptr = (struct student *)malloc(sizeof(struct student));
	if (ptr == NULL) {
		printf("Memory allocation failed!\n");
		return 1;
	}

	printf("\nEnter the data for the student: ");
	
	printf("\nROLL NO.: ");
	scanf("%d", &ptr->r_no);
	getchar();

	printf("NAME: ");
	fgets(ptr->name, sizeof(ptr->name), stdin);
	ptr->name[strcspn(ptr->name, "\n")] = '\0';

	printf("COURSE: ");
	fgets(ptr->course, sizeof(ptr->course), stdin);
	ptr->course[strcspn(ptr->course, "\n")] = '\0';

	printf("FEES: ");
	scanf("%d", &ptr->fees);

	display(ptr);

	free(ptr);

	return 0;
}

void display(struct student *ptr) {
	printf("\nDETAILS OF STUDENT\n");
	printf("\nROLL NO. = %d", ptr->r_no);
	printf("\nNAME = %s", ptr->name);
	printf("\nCOURSE = %s", ptr->course);
	printf("\nFEES = %d\n", ptr->fees);
}
	

