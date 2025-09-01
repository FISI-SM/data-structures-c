//Write a program to convert an integer into the corresponding floating point number.

#include <stdio.h>
#include <stdlib.h>

int main()
{

	float f_num;
	int i_num;
	system("clear");
	printf("\n Enter any integer: ");
	scanf("%d", &i_num);
	f_num = (float)i_num;
	printf("\n The floating point variant of %d is = %f", i_num, f_num);
	return 0;
}
