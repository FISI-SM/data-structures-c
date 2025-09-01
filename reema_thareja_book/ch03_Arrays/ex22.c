#include <stdio.h>   // Required for printf and scanf
#include <stdlib.h>  // Required for exit() function

int main() {
    int i, j;  // Loop counters

    // Variables for dimensions of the matrices
    int rows1, cols1, rows2, cols2;
    int mat1[5][5], mat2[5][5], sum[5][5];  // Matrices of max size 5x5

    // Ask user for number of rows and columns of the first matrix
    printf("\nEnter the number of rows in the first matrix (max 5): ");
    scanf("%d", &rows1);
    printf("Enter the number of columns in the first matrix (max 5): ");
    scanf("%d", &cols1);

    // Ask user for number of rows and columns of the second matrix
    printf("\nEnter the number of rows in the second matrix (max 5): ");
    scanf("%d", &rows2);
    printf("Enter the number of columns in the second matrix (max 5): ");
    scanf("%d", &cols2);

    // Check if matrix dimensions match for addition
    if (rows1 != rows2 || cols1 != cols2) {
        printf("\nError: Both matrices must have the same dimensions to be added.\n");
        exit(1);  // Exit the program with error code 1
    }

    // Input elements of the first matrix
    printf("\nEnter the elements of the first matrix:\n");
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &mat1[i][j]);
        }
    }

    // Input elements of the second matrix
    printf("\nEnter the elements of the second matrix:\n");
    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &mat2[i][j]);
        }
    }

    // Perform matrix addition
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++) {
            sum[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    // Print the result matrix
    printf("\nThe resulting matrix after addition is:\n");
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++) {
            printf("\t%d", sum[i][j]);
        }
        printf("\n");  // Move to the next line after each row
    }

    // Optional pause (Linux-safe alternative to getch)
    printf("\nPress Enter to exit...");
    getchar(); // Clear newline left in buffer
    getchar(); // Wait for Enter key

    return 0;  // Program finished successfully
}

