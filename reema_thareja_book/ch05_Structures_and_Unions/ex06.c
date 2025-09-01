#include <stdio.h>
#include <string.h>

struct student {
	int r_no;
	char name[20];
	char course[20];
	int fees;
};

int main()
{
	struct student stud1;
	struct student *ptr_stud1;

	ptr_stud1 = &stud1;

	printf("\nEnter the details of the student:\n");

	printf("Enter the Roll Number: ");
	scanf("%d", &ptr_stud1->r_no);
	getchar();

	printf("Enter the name: ");
	fgets(ptr_stud1->name, sizeof(ptr_stud1->name), stdin);
	ptr_stud1->name[strcspn(ptr_stud1->name, "\n")] = '\0';

	printf("Enter the Course: ");
	fgets(ptr_stud1->course, sizeof(ptr_stud1->course), stdin);
	ptr_stud1->course[strcspn(ptr_stud1->course, "\n")] = '\0';

	printf("Enter the fees: ");
	scanf("%d", &ptr_stud1->fees);

	printf("\nDETAILS OF THE STUDENT\n");
	printf("ROLL NUMBER = %d\n", ptr_stud1->r_no);
	printf("NAME = %s\n", ptr_stud1->name);
	printf("COURSE = %s\n", ptr_stud1->course);
	printf("FEES = %d\n", ptr_stud1->fees);

	return 0;
}

