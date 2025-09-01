#include <stdio.h>
#include <stdlib.h>

typedef struct distance {
	int kms;
	int meters;
} DISTANCE;

DISTANCE add_distance(DISTANCE, DISTANCE);
DISTANCE subtract_distance(DISTANCE, DISTANCE);

DISTANCE d1, d2, d3, d4;

int main()
{
	int option;

	do {
		printf("\n********* MAIN MENU *************");
		printf("\n1. Read the distances");
		printf("\n2. Display the distances");
		printf("\n3. Add the distances");
		printf("\n4. Subtract the distances");
		printf("\n5. EXIT");

		printf("\nEnter your option: ");
		scanf("%d", &option);

		switch(option) {
			case 1:
				printf("\nEnter the first distance (kms meters): ");
				scanf("%d %d", &d1.kms, &d1.meters);

				printf("Enter the second distance (kms meters): ");
				scanf("%d %d", &d2.kms, &d2.meters);
				break;

			case 2:
				printf("\nThe first distance is: %d kms %d meters", d1.kms, d1.meters);
				printf("\nThe second distance is: %d kms %d meters", d2.kms, d2.meters);
				break;

			case 3:
				d3 = add_distance(d1, d2);
				printf("\nThe sum of two distances is: %d kms %d meters", d3.kms, d3.meters);
				break;

			case 4:
				d4 = subtract_distance(d1, d2);
				printf("\nThe difference between two distances is: %d kms %d meters", d4.kms, d4.meters);			       			break;

			case 5:
				printf("\nExiting the program...\n");
				break;

			default:
				printf("\nInvalid option. Please try again.\n");
		} 
	} while (option != 5);


	return 0;
}


DISTANCE add_distance(DISTANCE d1, DISTANCE d2) {
	DISTANCE sum;

	sum.meters = d1.meters + d2.meters;
	sum.kms = d1.kms + d2.kms;

	if (sum.meters >= 1000) {
		sum.kms += sum.meters / 1000;
		sum.meters = sum.meters % 1000;
	}

	return sum;
}

DISTANCE subtract_distance(DISTANCE d1, DISTANCE d2) {
	DISTANCE sub;

	int total1 = d1.kms * 1000 + d1.meters;
	int total2 = d2.kms * 1000 + d2.meters;

	int diff = total1 - total2;
	
	//Always take absolute value to avoid negative results
	if (diff < 0) {
		diff = -diff;
	}

	//convert result back to kms and meters
	sub.kms = diff / 1000;
	sub.meters = diff % 1000;

	return sub;
}



		
	

