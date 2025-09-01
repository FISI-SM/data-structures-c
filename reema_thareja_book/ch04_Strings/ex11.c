#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[1000];
	int i = 0;
	int word_count = 0;
	int line_count = 1;
	int char_count = 0;

	system("clear");

	printf("\nEnter a '*' to end your input.");
	printf("\n******************************");
	printf("\nEnter the text:\n");

	//read input character by character until '*' is found
	scanf("%c", &str[i]);
	while (str[i] != '*') {
		i++;
		scanf("%c", &str[i]);
	}

	str[i] = '\0';

	//initialise for analysis
	i = 0;

	//skipping leading spaces
	while (str[i] == ' ')
		i++;

	//count characters, lines , words
	while (str[i] != '\0') {
		char_count++;
		
		//count new lines
		if (str[i] == '\n')
			line_count++;

		//count words: current is space, and next is not space/newline/end
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\n' && str[i + 1] != '\0')
			word_count++;
		i++;
	}

	//if any non-empty input , we count the first word
	if (char_count > 0 && str[0] !=  ' ')
		word_count++;

	//output results
	printf("\n\n--------Analysis Result----------\n");
	printf("Total number of words     : %d\n", word_count);
	printf("Total number of lines     : %d\n", line_count);
	printf("Total number of characters: %d\n", char_count);

	return 0;
}
