#include <stdio.h>  // For standard input/output functions

int main() {
    // Declare a 3D array of size 2x2x2
    int array[2][2][2];

    // Loop counters for each dimension
    int i, j, k;

    // Prompt the user to enter the elements
    printf("Enter the 8 elements for the 3D array (2x2x2):\n");

    // Nested loops to read input values into the 3D array
    for(i = 0; i < 2; i++) {            // Loop through "layers"
        for(j = 0; j < 2; j++) {        // Loop through "rows"
            for(k = 0; k < 2; k++) {    // Loop through "columns"
                printf("array[%d][%d][%d] = ", i, j, k);
                scanf("%d", &array[i][j][k]); // Read each element
            }
        }
    }

    // Display the elements of the 3D array
    printf("\nThe 3D matrix is:\n");

    for(i = 0; i < 2; i++) {  // Layer loop
        printf("Layer %d:\n", i);
        for(j = 0; j < 2; j++) {  // Row loop
            for(k = 0; k < 2; k++) {  // Column loop
                // Print the value along with its position
                printf("array[%d][%d][%d] = %d\n", i, j, k, array[i][j][k]);
            }
            printf("\n");  // Newline after each row
        }
        printf("----------\n"); // Separator between layers
    }

    return 0;  // Successful program termination
}

