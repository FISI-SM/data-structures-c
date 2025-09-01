#include <stdio.h>  // Standard input-output header for printf, scanf

int main() {
    int i, j, k;  // Loop counters
    int rows1, cols1;     // Rows and columns for first matrix
    int rows2, cols2;     // Rows and columns for second matrix
    int res_rows, res_cols;  // Rows and columns for result matrix

    int mat1[5][5];  // First matrix (max size 5x5)
    int mat2[5][5];  // Second matrix (max size 5x5)
    int res[5][5];   // Result matrix to store multiplication result

    // Prompt user for dimensions of first matrix
    printf("\nEnter the number of rows in the first matrix: ");
    scanf("%d", &rows1);
    printf("Enter the number of columns in the first matrix: ");
    scanf("%d", &cols1);

    // Prompt user for dimensions of second matrix
    printf("\nEnter the number of rows in the second matrix: ");
    scanf("%d", &rows2);
    printf("Enter the number of columns in the second matrix: ");
    scanf("%d", &cols2);

    // Matrix multiplication is only possible when cols1 == rows2
    if (cols1 != rows2) {
        printf("\nError: The number of columns in the first matrix must equal the number of rows in the second matrix.\n");
        return 1;  // Exit with error code
    }

    // Store result matrix size
    res_rows = rows1;
    res_cols = cols2;

    // Input elements of first matrix
    printf("\nEnter the elements of the first matrix (%dx%d):\n", rows1, cols1);
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++) {
            printf("mat1[%d][%d]: ", i, j);
            scanf("%d", &mat1[i][j]);
        }
    }

    // Input elements of second matrix
    printf("\nEnter the elements of the second matrix (%dx%d):\n", rows2, cols2);
    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++) {
            printf("mat2[%d][%d]: ", i, j);
            scanf("%d", &mat2[i][j]);
        }
    }

    // Initialize result matrix with 0s and perform multiplication
    for (i = 0; i < res_rows; i++) {
        for (j = 0; j < res_cols; j++) {
            res[i][j] = 0;  // Initialize the cell
            for (k = 0; k < cols1; k++) {
                // Multiply and accumulate
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    // Print the result (product) matrix
    printf("\nThe elements of the product matrix (%dx%d) are:\n", res_rows, res_cols);
    for (i = 0; i < res_rows; i++) {
        for (j = 0; j < res_cols; j++) {
            printf("\t%d", res[i][j]);  // Print each value with a tab
        }
        printf("\n");  // Newline after each row
    }

    // Optional: pause before exit (waits for Enter)
    printf("\nPress Enter to exit...");
    getchar();  // To consume the leftover newline
    getchar();  // Wait for Enter
    return 0;  // Exit successfully
}

