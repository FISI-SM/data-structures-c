#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char text[100]; //stores original text
	char str[20];   //stores string to be inserted
	char ins_text[200]; //stores final result after insertion
	int i = 0, j = 0, k = 0, pos;
	
	system("clear");

	printf("\nEnter the main text: ");
	fgets(text, sizeof(text), stdin);

	size_t len = strlen(text);

	if (text[len - 1] == '\n')
		text[len - 1] = '\0';

	printf("\nEnter the string to be inserted: ");
	fgets(str, sizeof(str), stdin);

	len = strlen(str);

	if (str[len - 1] == '\n')
		str[len - 1] = '\0';

	printf("\nEnter the position at which the string has to be inserted: ");
	scanf("%d", &pos);
	
	if (pos < 0 || pos > strlen(text)) {
		printf("\nInvalid position!\n");
		return 1;
	}

	//traverse the main text
	while (text[i] != '\0')
	{
		if (i == pos) //having reached the desired insert position
		{
			//insert the new string here
			while (str[k] != '\0') {
				ins_text[j] = str[k]; //copy character from inserted string
				j++;
				k++;
			}
		}

		//copy current character from main text
		ins_text[j] = text[i];
		j++;
		i++;
	}

	ins_text[j] = '\0'; //null terminate the final string
	
	printf("\nThe new string is: ");
	puts(ins_text);

	getchar();
	getchar();

	return 0;
}

