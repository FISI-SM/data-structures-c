#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[100];
	int i = 0;
	int length;

	system("clear");

	printf("\nEnter the string: ");

	fgets(str, sizeof(str), stdin);

	//loop through the string until null character '\0' is found
	while (str[i] != '\0')
		i++;
	//if the last character before '\0' is a newline subtract 1
	//if the second last character is a newline decrease count by 1 to remove newline from
	//length
	if (str[i - 1] == '\n')
		i--;
	
	length = i;

	printf("\nThe length of the string is : %d\n", length);

	getchar();

	return 0;
}
