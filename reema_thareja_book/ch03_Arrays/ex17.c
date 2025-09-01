#include <stdio.h>     // For standard input/output
#include <stdlib.h>    // For system("clear") if needed

int main() {
    int arr[7][7] = {0}; // 2D array initialized with 0s to store Pascal's Triangle
    int row = 2;         // Start from row index 2 (as 0 and 1 are manually set)
    int col, i, j;

    // Manually set the first two rows of Pascal’s Triangle
    arr[0][0] = 1;       // Row 0: 1
    arr[1][0] = 1;       // Row 1: 1
    arr[1][1] = 1;       // Row 1: 1 1

    // Generate Pascal’s Triangle values starting from row 2 to 6
    while (row < 7) {  // Indexes: 0 to 6 (7 rows total)
        arr[row][0] = 1;  // First element in each row is always 1

        for (col = 1; col < row; col++) {
            // Each value is the sum of the two values above it
            arr[row][col] = arr[row - 1][col - 1] + arr[row - 1][col];
        }

        arr[row][row] = 1; // Last element in each row is always 1
        row++;             // Move to the next row
    }

    // Display the Pascal’s Triangle
    printf("Pascal's Triangle:\n");
    for (i = 0; i < 7; i++) {
        for (j = 0; j <= i; j++) {
            printf("\t%d", arr[i][j]); // Print each value with tab spacing
        }
        printf("\n"); // Newline after each row
    }

    // Optional pause for terminal output (safe)
    printf("\nPress Enter to exit...");
    getchar(); // Capture newline from previous input
    getchar(); // Wait for Enter

    return 0; // Successful program end
}

