#include <stdio.h>

int main()
{
	char str[] = "Hello";
	char *ptrstr;
	ptrstr = str;

	printf("The string is: ");
	while (*ptrstr != '\0') {
		printf("%c", *ptrstr);
		ptrstr++;
	}

	return 0;
}
