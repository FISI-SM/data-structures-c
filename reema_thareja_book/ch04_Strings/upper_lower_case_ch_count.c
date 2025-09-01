#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[100];
	char *pstr;
	int upper = 0;
	int lower = 0;

	printf("\nEnter the string: ");
	fgets(str, sizeof(str), stdin);

	size_t len = strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
	
	pstr = str;

	while (*pstr != '\0')
	{
		//if character is uppercase
		if (*pstr >= 'A' && *pstr <= 'Z')
			upper++;
		
		//if character is lowercase
		else if (*pstr >= 'a' && *pstr <= 'z')
			lower++;
		pstr++;
	}

	printf("\nTotal number of uppercase characters: %d", upper);
	printf("\nTotal number of lowercase characters: %d", lower);

	return 0;
}


