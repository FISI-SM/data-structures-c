#include <stdio.h>  // For input/output functions

int main() {
    int sales[5][3];     // A 2D array to store sales data
                         // 5 salesmen (rows), 3 items (columns)
    int i, j;            // Loop counters
    int total_sales = 0; // Variable to store total sales temporarily

    // INPUT DATA
    printf("\n ENTER THE DATA");
    printf("\n *****************\n");

    // Outer loop for each salesman
    for(i = 0; i < 5; i++) {
        printf("\n Enter the sales of 3 items sold by salesman %d: ", i + 1);

        // Inner loop for each of the 3 items
        for(j = 0; j < 3; j++) {
            // Read the sales of item j by salesman i
            scanf("%d", &sales[i][j]);
        }
    }

    // PRINT TOTAL SALES BY EACH SALESMAN
    printf("\n\n---- TOTAL SALES BY EACH SALESMAN ----\n");
    for(i = 0; i < 5; i++) {
        total_sales = 0;  // Reset total for each salesman

        // Sum the sales of all 3 items for salesman i
        for(j = 0; j < 3; j++) {
            total_sales += sales[i][j];
        }

        // Print the result
        printf("Total Sales by Salesman %d = %d\n", i + 1, total_sales);
    }

    // PRINT TOTAL SALES OF EACH ITEM
    printf("\n---- TOTAL SALES OF EACH ITEM ----\n");
    for(i = 0; i < 3; i++) {   // Loop over items
        total_sales = 0;       // Reset total for each item

        // Sum the sales of item i from all 5 salesmen
        for(j = 0; j < 5; j++) {
            total_sales += sales[j][i];
        }

        // Print the result
        printf("Total Sales of Item %d = %d\n", i + 1, total_sales);
    }

    // End of program
    printf("\nProgram finished. Press Enter to exit...");
    getchar(); // Capture leftover newline
    getchar(); // Wait for user to press Enter

    return 0;  // Return success
}

