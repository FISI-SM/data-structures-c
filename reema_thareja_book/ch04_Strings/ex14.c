#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char str1[100];
	char str2[100];
	char copy_str[200]; //combined string after concatenation
	
	char *pstr1, *pstr2, *pcopy_str; //pointers for traversing strings
	
	system("clear");

	printf("Enter the first string: ");
	fgets(str1, sizeof(str1), stdin);

	size_t len = strlen(str1);
	if (str1[len - 1] == '\n')
		str1[len - 1] = '\0';

	printf("Enter the second string: ");
	fgets(str2, sizeof(str2), stdin);

	len = strlen(str2);
	if (str2[len - 1] == '\n')
		str2[len - 1] = '\0';

	pstr1 = str1;
	pstr2 = str2;
	pcopy_str = copy_str;

	//copy characters from str1 to copy_str
	while (*pstr1 != '\0') {
		*pcopy_str = *pstr1;
		pcopy_str++;
		pstr1++;
	}

	//copy characters from str2 to copy_str
	while (*pstr2 != '\0') {
		*pcopy_str = *pstr2;
		pcopy_str++;
		pstr2++;
	}

	*pcopy_str = '\0';  //null terminate the final string
	
	//reset pointer to beginning of copy_str to print
	pcopy_str = copy_str;

	printf("\nThe concatenated text is: ");
	while (*pcopy_str != '\0') {
		printf("%c", *pcopy_str);
		pcopy_str++;
	}
	printf("\n");

	return 0;
}
