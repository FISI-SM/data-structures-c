#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char str[100];
	char temp; // temporary variable for swapping characters
	int i = 0, j = 0; //i for start of string, j for end of string

	system("clear");

	printf("\nEnter the string: ");
	fgets(str, sizeof(str), stdin);

	//remove newline
	while (str[j] != '\0') {
		if (str[j] == '\n') {
			str[j] = '\0';
			break;
		}
		j++;
	}

	//set j to the last character index of the string
	j = strlen(str) - 1;

	//loop to reverse the string using swapping
	while (i < j)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;

		//move i forward aqand j backward
		i++;
		j--;
	}

	printf("\nThe reversed string is: ");
	puts(str);

	getchar();

	return 0;
}


