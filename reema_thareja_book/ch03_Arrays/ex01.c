#include <stdio.h>
#include <stdlib.h>

int main()
{

	int i, n, arr[20];
	system("clear");

	printf("\n Enter the number of elements in the array : ");
	scanf("%d", &n);

	for(i=0;i<n;i++)
	{
		printf("\n arr[%d] = ", i);
		scanf("%d",&arr[i]);
	}

	printf("\n The array elements are ");
	
	for(i=0;i<n;i++)
		
	printf("\t %d", arr[i]);

	return 0;
}
