#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[100];
	int i = 0, j; //i for start of string, j for end
	int length = 0;  //to store string length
	int is_palindrome = 1; //flag 1 means palindrome, 0 means not
	
	system("clear");

	//input the string
	printf("Enter the string: ");
	fgets(str, sizeof(str), stdin);
	size_t len = strlen(str);
	if (str[len - 1] == '\n')
		str[len -1] = '\0';

	//find the length of the string
	while (str[length] != '\0') {
		length++;
	}

	//set j to last character index
	j = length - 1;
	i = 0;

	//compare characters from both ends
	while (i < j)
	{
		if (str[i] != str[j]) {
			is_palindrome = 0;
			break;
		}
		i++;
		j--;
	}

	if (is_palindrome)
		printf("\nPALINDROME\n");

	else
		printf("\nNOT A PALINDROME\n");

	return 0;
}

