#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char text[200];
	char str[20];
	char new_text[200];

      int i = 0, j = 0, k, n = 0;//index i for text, j for str, k for matching, n for new text
       int found = 0;    //flag to mark if match was found
	
      system("clear"); 

      printf("\nEnter the main text: ");
      fgets(text, sizeof(text), stdin);
      size_t len = strlen(text);
      if (text[len - 1] == '\n')
	      text[len - 1] = '\0';

      printf("\nEnter the string to be deleted: ");
      fgets(str, sizeof(str), stdin);
      len = strlen(str);
      if (str[len - 1] == '\n')
	      str[len - 1] = '\0';


      while (text[i] != '\0')
      {
	      found = 0;
	      k = i;
	      j = 0;

	      //try to match str[] at pos i in text[]
	      while (text[k] == str[j] && str[j] != '\0') {
		      k++;
		      j++;
	      }

	      //if full match found
	      if (str[j] == '\0') {
		      found = 1;
		      i = k; //skip the matched substring in text[]
	      }

	      //if no match, copy current character to a new text
	      if (!found) {
		      new_text[n] = text[i];
		      i++;
		      n++;
	      }
      }

      new_text[n] = '\0';

      printf("\nThe new string is: ");
      puts(new_text);

      return 0;
}
	
