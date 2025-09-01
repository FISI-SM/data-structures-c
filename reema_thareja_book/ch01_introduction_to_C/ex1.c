//Write a program to calculate the area of a circle.

#include <stdio.h>
#include <stdlib.h>

int main()
{

	float radius;
	double area;
	system("clear");
	printf("\n Enter the radius of the circle : ");
	scanf("%f", &radius);
	area = 3.14 * radius * radius;
	printf(" \n Area = %.2lf", area);
	return 0;
}
