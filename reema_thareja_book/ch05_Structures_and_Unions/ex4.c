#include <stdio.h>
#include <string.h>

int main()
{
	struct student {
		int roll_no;
		char name[80];
		int fees;
		char DOB[80];
	};

	struct student stud[50];

	int n, i;  //n for size, i for loop
	int num;  //index of srudent to edit
	int new_rollno, new_fees;
	char new_name[80], new_DOB[80];

	printf("Enter the number of students: ");
	scanf("%d", &n);
	while (getchar() != '\n'); //clear newline from buffer
	
	for (i = 0; i < n; i++) {
		printf("\nEnter the roll number of student %d: ", i + 1);
		scanf("%d", &stud[i].roll_no);
		while(getchar() != '\n');

		printf("Enter the name of student %d: ", i + 1);
		fgets(stud[i].name, sizeof(stud[i].name), stdin);
		stud[i].name[strcspn(stud[i].name, "\n")] = '\0';

		printf("Enter the fees of student %d: ", i + 1);
		scanf("%d", &stud[i].fees);
		while (getchar() != '\n');

		printf("Enter the DOB of student %d: ", i + 1);
		fgets(stud[i].DOB, sizeof(stud[i].DOB), stdin);
		stud[i].DOB[strcspn(stud[i].DOB, "\n")] = '\0';
	}

		//Display original student records
	for (i = 0; i < n; i++) {
		printf("\n************* DETAILS OF STUDENT %d ***********", i + 1);
		printf("\nROLL No. = %d", stud[i].roll_no);
		printf("\nNAME     = %s", stud[i].name);
		printf("\nFEES     = %d", stud[i].fees);
		printf("\nDOB      = %s\n", stud[i].DOB);
	}

	//Ask which student's record to edit
	printf("\nEnter the student number (1 to %d) to edit: ", n);
	scanf("%d", &num);
	num = num - 1; //convert to 0 based index
	while (getchar() != '\n');

	//Read new values
	printf("Enter the new roll number: ");
	scanf("%d", &new_rollno);
	while (getchar() != '\n');

	printf("Enter the new name: ");
	fgets(new_name, sizeof(new_name), stdin);
	new_name[strcspn(new_name, "\n")] = '\0';

	printf("Enter the new fees: ");
	scanf("%d", &new_fees);
	while (getchar() != '\n');

	printf("Enter the new DOB: ");
	fgets(new_DOB, sizeof(new_DOB), stdin);
	new_DOB[strcspn(new_DOB, "\n")] = '\0';

	//Update student's record
	stud[num].roll_no = new_rollno;
	strcpy(stud[num].name, new_name);
	stud[num].fees = new_fees;
	strcpy(stud[num].DOB, new_DOB);

	//Display updated Records
	for (i = 0; i < n; i++) {
		printf("\n***************** UPDATED DETAILS OF STUDENT %d ********", i + 1);
		printf("\nROLL No. = %d", stud[i].roll_no);
		printf("\nNAME     = %s", stud[i].name);
		printf("\nFEES     = %d", stud[i].fees);
		printf("\nDOB      = %s\n", stud[i].DOB);
	}


	return 0;
}

	
	




