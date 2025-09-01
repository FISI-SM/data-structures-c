#include <stdio.h>
#include <stdlib.h>

int main()
{
	char Dest_str[100];
	char source_str[100];
	int i = 0,  j = 0;

	system("clear");

	printf("\nEnter the source string: ");
	fgets(source_str, sizeof(source_str), stdin);

	printf("\nEnter the destination string: ");
	fgets(Dest_str, sizeof(Dest_str), stdin);

	//Remove newline characters from fgets
	while (source_str[j] != '\0') {
		if (source_str[j] == '\n')
			source_str[j] = '\0';
		j++;
	}

	j = 0; //reset source index to 0 for actual appending process
	
	//move 'i' to the end of the destination string
	while (Dest_str[i] != '\0') {
		if (Dest_str[i] == '\n') {
			Dest_str[i] = '\0';
			break;
		}
		i++;
	}

	//Append characters from source_str to the end of Dest_str
	while (source_str[j] != '\0') {
		Dest_str[i] = source_str[j];
		i++;
		j++;
	}

	Dest_str[i] = '\0'; //Add null terminator to mark end of the string
	
	printf("\nAfter  appending, the destination string is:\n ");
	
	puts(Dest_str);

	getchar();

	return 0;
}
