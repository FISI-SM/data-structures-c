#include <stdio.h>
#include <string.h>

int main()
{
	struct DOB {
		int day;
		int month;
		int year;
	};

	struct student {
		int roll_no;
		char name[100];
		float fees;
		struct DOB date;
	};

	struct student stud1;

	printf("\nEnter the roll number: ");
	scanf("%d", &stud1.roll_no);

	while (getchar() != '\n');

	printf("Enter the name: ");
	fgets(stud1.name, sizeof(stud1.name), stdin);
	stud1.name[strcspn(stud1.name, "\n")] = '\0';

	printf("Enter the fees: ");
	scanf("%f", &stud1.fees);

	printf("Enter the DOB (day month year): ");
	scanf("%d %d %d", &stud1.date.day, &stud1.date.month, &stud1.date.year);

	printf("\n***************STUDENT'S DETAILS *************\n");
	printf("ROLL No. = %d\n", stud1.roll_no);
	printf("NAME     = %s\n", stud1.name);
	printf("FEES     = %.2f\n", stud1.fees);
	printf("DOB      = %d-%d-%d\n", stud1.date.day, stud1.date.month, stud1.date.year);

	return 0;
}
