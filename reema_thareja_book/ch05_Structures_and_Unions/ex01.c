#include <stdio.h>
#include <string.h>

int main()
{
	struct student {
		int roll_no;
		char name[80];
		float fees;
		char DOB[80];
	};

	struct student stud1;

	printf("\nEnter the roll number: ");
	scanf("%d", &stud1.roll_no);

	//clear input buffer before reading strings with fgets
	while (getchar() != '\n');

	printf("Enter the name: ");
	fgets(stud1.name, sizeof(stud1.name), stdin);
	stud1.name[strcspn(stud1.name, "\n")] = '\0';

	printf("Enter the fees: ");
	scanf("%f", &stud1.fees);

	//clear input buffer again
	while (getchar() != '\n');

	printf("Enter the DOB: ");
	fgets(stud1.DOB, sizeof(stud1.DOB), stdin);
	stud1.DOB[strcspn(stud1.DOB, "\n")] = '\0';

	printf("\n************* STUDENT'S DETAILS *************\n");
	printf("ROLL No. = %d\n", stud1.roll_no);
	printf("NAME     = %s\n", stud1.name);
	printf("FEES     = %.2f\n", stud1.fees);
	printf("DOB      = %s\n", stud1.DOB);

	return 0;
}
