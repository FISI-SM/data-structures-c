#include <stdio.h>   // Standard Input Output library for printf and scanf

int main() {
    int i, j;  // Loop counters
    int mat[3][3];               // Original 3x3 matrix
    int transposed_mat[3][3];    // Transposed matrix

    // Prompt user to enter elements of the 3x3 matrix
    printf("\nEnter the elements of the 3x3 matrix:\n");
    for (i = 0; i < 3; i++) {             // Loop through rows
        for (j = 0; j < 3; j++) {         // Loop through columns
            printf("Element [%d][%d]: ", i, j);  // Ask for element at position (i,j)
            scanf("%d", &mat[i][j]);     // Read element from user input
        }
    }

    // Print the original matrix
    printf("\nThe elements of the original matrix are:\n");
    for (i = 0; i < 3; i++) {             // Loop through rows
        for (j = 0; j < 3; j++) {         // Loop through columns
            printf("\t%d", mat[i][j]);   // Print each element with tab spacing
        }
        printf("\n");                     // Newline after each row
    }

    // Transpose the matrix
    // Transpose means flipping rows and columns: new[i][j] = old[j][i]
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            transposed_mat[i][j] = mat[j][i];  // Assign transposed value
        }
    }

    // Print the transposed matrix
    printf("\nThe elements of the transposed matrix are:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("\t%d", transposed_mat[i][j]);  // Print each transposed element
        }
        printf("\n");  // Newline after each row
    }

    // Optional pause before program exits (waits for Enter key)
    printf("\nPress Enter to exit...");
    getchar(); // Consume leftover newline
    getchar(); // Wait for Enter

    return 0;  // Exit program
}

