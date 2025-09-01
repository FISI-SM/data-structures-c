#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str1[50], str2[50];
	int i = 0; //used for comparison loop
	int len1 = 0, len2 = 0;
	int same = 0; // flag to check if strings are the same

	system("clear");

	printf("\nEnter the first string: ");
	fgets(str1, sizeof(str1),stdin);

	//remove newline character manually from str1  (str1[strcspn(str1, "\n")] = '\0';
	int j = 0;
	
	while (str1[j] != '\0') {     
		if (str1[j] == '\n') {
			str1[j] = '\0';
			break;
		}
		j++;
	}

	printf("\nEnter the second string: ");
	fgets(str2, sizeof(str2), stdin);

	//remove newline character manually from str2 (str2[strcspn(str2, "\n")] = '\0';
	j = 0;

	while (str2[j] != '\0') {
		if (str2[j] == '\n') {
			str2[j] = '\0';
			break;
		}
		j++;
	}


	len1 = strlen(str1);
	len2 = strlen(str2);

	if (len1 == len2)
	{
		//loop through each character and compare one by one
		while (i < len1)
		{
			if (str1[i] == str2[i])
				i++;
			else
				break;
		}

		//if all characters matched
		if (i == len1)
		{
			same = 1;
			printf("\nThe two strings are equal.\n");
		}
	}
	
	else {
		printf("\nThe two strings are not equal.\n");
	}
	
	//if not the same, determine which string is greater
	if (same == 0)
	{
		if (str1[i] > str2[i])
			printf("\nstring 1 is greater than string 2.\n");
		else if (str1[i] < str2[i])
			printf("\nString 2 is greater than string 1.\n");
		else
			printf("\nThe strings differ but neither is greater.\n");
	}

	getchar();

	return 0;
}
	

	


