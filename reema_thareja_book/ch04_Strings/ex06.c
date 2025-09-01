#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[100];
	char substr[100];
	int i = 0, j = 0; //loop counters i: i for original string, j for substring
	int m, n;   //m for starting position, n is the length of the substring

	system("clear");

	printf("\nEnter the main string: ");
	fgets(str, sizeof(str), stdin);

	size_t len = strlen(str);
	
	if (str[len - 1] == '\n') {
		str[len - 1] = '\0';
	}
	
	//Ask for starting position(m)
	printf("\nEnter the position from which to start the substring (0-based index): ");
	scanf("%d", &m);

	//Ask for the number of characters to extract (n)
	printf("\nEnter the length of the substring: ");
	scanf("%d", &n);

	//check if starting position and length are within bounds
	if (m < 0 || m >= strlen(str)) {
		printf("\nInvalid starting position!\n");
		return 1;
	}

	if (n < 0 || (m + n) > strlen(str)) {
		printf("\nsubstring length goes out of bounds!\n");
		return 1;
	}

	i = m; //start copying from index m
	
	while (str[i] != '\0' && n > 0)
	{
		substr[j] = str[i];
		i++;
		j++;
		n--; //decrease the number of characters left to copy
	}

	substr[j] = '\0';

	printf("\nThe substring is : ");
	puts(substr);

	getchar();
	getchar();

	return 0;
}



