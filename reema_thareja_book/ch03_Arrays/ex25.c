#include <stdio.h>  // Required for printf and scanf

// Function declaration to display a 3x3 matrix using a pointer to a 1D array of 3 integers
void display(int (*mat)[3]);

int main() {
    int i, j;              // Loop counters
    int mat[3][3];         // 3x3 matrix to store user input

    // Prompt the user to enter 9 elements
    printf("\nEnter the elements of the 3x3 matrix:\n");

    // Loop through each row
    for (i = 0; i < 3; i++) {
        // Loop through each column
        for (j = 0; j < 3; j++) {
            printf("Element [%d][%d]: ", i, j);  // Show position for clarity
            scanf("%d", &mat[i][j]);            // Read matrix element
        }
    }

    // Call the display function to print the matrix
    display(mat);

    return 0;  // Exit the program successfully
}

// Function to display a 3x3 matrix using pointer notation
void display(int (*mat)[3]) {
    int i, j;  // Loop counters

    printf("\nThe elements of the matrix are:\n");

    // Loop through each row
    for (i = 0; i < 3; i++) {
        // Loop through each column
        for (j = 0; j < 3; j++) {
            // Access the matrix element using pointer notation:
            // *(*(mat + i) + j) is the same as mat[i][j]
            printf("\t%d", *(*(mat + i) + j));
        }
        printf("\n");  // New line after each row
    }
}

