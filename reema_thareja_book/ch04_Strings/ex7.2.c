#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char text[100]; //Array to store the main text
	char str[50]; //Array to store pattern to search for
	int i = 0; //index for outer loop- where to start searching in text
	int k; //index for inner loop - character by character check
	int max; //maximum starting point to avoid going past the end
	int index = -1; //final result: position of match (-1 if not found)
	
	printf("\nEnter the main text: ");
	fgets(text, sizeof(text), stdin);

	size_t len = strlen(text);
	if (text[len - 1] == '\n') 
		text[len - 1] = '\0';

	printf("\nEnter the pattern to search: ");
	fgets(str, sizeof(str), stdin);

	len = strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';

	//step 1
	int len_text = strlen(text);
	int len_str = strlen(str);
	max = len_text - len_str + 1;

	//step 2
	while (i < max)
	{
		//step 3: checking each character for str vs text
		for (k = 0; k < len_str; k++)
		{
			//step 4: if mismatch go to step 6
			if (str[k] != text[i + k])
				break;
		}

		//step 5: if inner loop completed without break, match found
		if (k == len_str)
		{
			index = i; //set index to position where match found
			break;
		}

		//step 6: if no match, move to next starting position
		i = i + 1;
	}

	//step 7: if no match index remains -1
	
	//step 8: output the result
	if (index != -1)
		printf("Pattern found at position: %d\n", index);
	else 
		printf("Pattern not found in the text.\n");

	return 0;
}



