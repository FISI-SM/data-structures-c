#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char str[200]; //original input string
	char pat[20];  //pattern to search for
	char new_str[300]; //final str after replacement
	char rep_pat[100];  //replacement pattern

   int i = 0,j = 0, k, n = 0;//index: i in original str, j for pat,k for match, n for new_str
	int copy_loop; //position to start copying fro
        int match_found;  //flag to check if match occurred

	system("clear");

	printf("\nEnter the string: ");
	fgets(str, sizeof(str), stdin);
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';

	printf("\nEnter the pattern to be replaced: ");
	fgets(pat, sizeof(pat), stdin);
	if (pat[strlen(pat) - 1] == '\n')
		pat[strlen(pat) - 1] = '\0';
	
	printf("\nEnter the replacing pattern: ");
	fgets(rep_pat, sizeof(rep_pat), stdin);
	if (rep_pat[strlen(rep_pat) - 1] == '\n')
		rep_pat[strlen(rep_pat) - 1] = '\0';

	//scanning original string
	while (str[i] != '\0')
	{
		match_found = 1;
		k = i;
		j = 0;

		//try to match the pattern at current position
		while (str[k] == pat[j] && pat[j] != '\0') {
			k++;
			j++;
		}

		//if full pattern matched
		if (pat[j] == '\0')
		{
			//copy the replacement pattern into new_str
			int rep_index = 0;
			while (rep_pat[rep_index] != '\0') {
				new_str[n++] = rep_pat[rep_index++];
			}

			//skip he matched pattern in original string
			i = k;
		}
		else {
			//if no match, just copy the current character
			new_str[n++] = str[i++];
		}
	}

	new_str[n] = '\0';

	printf("\nThe new string is: ");
	puts(new_str);

	return 0;
}
