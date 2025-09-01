#include <stdio.h> // Include standard input/output library

int main() {
    int i, j;               // Loop counters
    int mat[3][3];          // Declare a 3x3 matrix (2D array)

    // Ask user to input elements for the 3x3 matrix
    printf("\n Enter the elements of the 3x3 matrix:\n");

    // Outer loop for rows
    for(i = 0; i < 3; i++) {
        // Inner loop for columns
        for(j = 0; j < 3; j++) {
            // Input each element using scanf
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    // Print the matrix
    printf("\n The elements of the matrix are:\n");

    for(i = 0; i < 3; i++) {
        // Start a new line for each row
        printf("\n");

        for(j = 0; j < 3; j++) {
            // Print each element with tab spacing
            printf("\t%d", mat[i][j]);
        }
    }

    // Optional: Wait for user to press Enter (Linux-safe alternative to getch)
    printf("\n\nPress Enter to exit...");
    getchar(); // This consumes the leftover newline from scanf
    getchar(); // This waits for the user to press Enter

    return 0; // Indicate that the program finished successfully
}

