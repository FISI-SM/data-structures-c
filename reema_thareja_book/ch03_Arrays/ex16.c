#include <stdio.h>
#include <stdlib.h>

int main()
{

	int arr[2][2] = {12, 34, 56,32};
	int i, j;
	
	system("clear");

	for(i=0;i<2;i++)
	{
		printf("\n");
		
		for(j=0;j<2;j++)
			printf("%d\t", arr[i][j]);
	}

	return 0;
}
