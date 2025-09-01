#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[100];
	char upper_str[100];
	int i = 0;

	system("clear");

	printf("\nEnter the string: ");
	fgets(str, sizeof(str),stdin);

	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			upper_str[i] = str[i] - 32;
		else 
			upper_str[i] = str[i];
		i++;
	}
	
	upper_str[i] = '\0'; //add null terminator to mark the end of the string
	
	printf("\nThe string converted into uppercase is: ");
	puts(upper_str);

	return 0;
}
