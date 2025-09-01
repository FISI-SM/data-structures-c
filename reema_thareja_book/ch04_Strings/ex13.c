#include <stdio.h>
#include <string.h>

int main()
{
	char str[100];
	char copy_str[100];
	char *pstr, *pcopy_str;

	printf("\nEnter the string: ");
	fgets(str, sizeof(str), stdin);

	size_t len = strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';

	pstr = str;
	pcopy_str = copy_str;

	//copy characters one by one using pointers
	while (*pstr != '\0') {
		*pcopy_str = *pstr;
		pstr++;
		pcopy_str++;
	}
	
	*pcopy_str = '\0';

	//reset pointer to beginning of copy_str for printing
	pcopy_str = copy_str;

	printf("\nThe copied text is: ");
	while (*pcopy_str != '\0') {
		printf("%c", *pcopy_str);
		pcopy_str++;
	}

	printf("\n");

	return 0;
}

