#include <stdio.h>  // Required for printf and scanf

// Function declarations
void read_matrix(int mat[5][5], int r);
void display_matrix(int mat[5][5], int r);

int main() {
    int row;              // To store the number of rows (and columns, since it's a square matrix)
    int mat1[5][5];       // Declare a 5x5 matrix (max supported size)

    // Ask user for the size of the square matrix
    printf("\nEnter the number of rows and columns of the matrix (max 5): ");
    scanf("%d", &row);

    // Call the function to fill the matrix according to specified logic
    read_matrix(mat1, row);

    // Call the function to print the matrix
    display_matrix(mat1, row);

    // Pause before exiting (optional, especially useful if run from a terminal)
    printf("\nPress Enter to exit...");
    getchar(); // Consume leftover newline
    getchar(); // Wait for user to press Enter

    return 0;  // Return success
}

// This function fills the matrix based on position:
// 0 on the diagonal, -1 below the diagonal, 1 above the diagonal
void read_matrix(int mat[5][5], int r) {
    int i, j;  // Loop variables

    // Loop through each row
    for (i = 0; i < r; i++) {
        // Loop through each column
        for (j = 0; j < r; j++) {
            if (i == j) {
                // Set diagonal elements to 0
                mat[i][j] = 0;
            } else if (i > j) {
                // Set elements below the diagonal to -1
                mat[i][j] = -1;
            } else {
                // Set elements above the diagonal to 1
                mat[i][j] = 1;
            }
        }
    }
}

// This function displays the matrix in a tabular format
void display_matrix(int mat[5][5], int r) {
    int i, j;  // Loop variables

    printf("\nThe matrix is:\n");

    // Loop through each row
    for (i = 0; i < r; i++) {
        // Start new line for each row
        for (j = 0; j < r; j++) {
            // Print each element with a tab
            printf("\t%d", mat[i][j]);
        }
        printf("\n");  // Move to next line after each row
    }
}

