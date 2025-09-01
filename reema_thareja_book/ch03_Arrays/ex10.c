// Include the standard input/output header for using printf, scanf, etc.
#include <stdio.h>

// Include standard library for system("clear") function
#include <stdlib.h>

// Main function — where the program starts running
int main()
{
    // Declare variables
    int i, j;           // loop counters
    int n;              // number of elements in the array
    int num;            // number to be deleted
    int arr[10];        // array with a maximum of 10 elements
    int found = 0;      // flag to check if number was found

    // Clear the terminal screen (works in Kali/Linux)
    system("clear");

    // Ask user for the number of elements
    printf("\n Enter the number of elements in the array (max 10): ");
    scanf("%d", &n);

    // Check for valid input
    if(n > 10 || n < 1) {
        printf("\n Please enter a valid number between 1 and 10.\n");
        return 1; // Exit the program with error code
    }

    // Input the elements of the array
    for(i = 0; i < n; i++) {
        printf(" arr[%d] = ", i);  // Prompt user
        scanf("%d", &arr[i]);      // Store the input
    }

    // Ask user for the number to delete
    printf("\n Enter the number to be deleted: ");
    scanf("%d", &num);

    // Loop through array to find and delete the number
    for(i = 0; i < n; i++) {
        if(arr[i] == num) {
            found = 1; // Mark that we found the number

            // Shift all elements after this index one position left
            for(j = i; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }

            n = n - 1; // Decrease array size by 1
            i = i - 1; // Adjust index to recheck current position
        }
    }

    // Check if the number was found or not
    if(found == 0) {
        printf("\n Number %d not found in the array.\n", num);
    } else {
        // Print the updated array after deletion
        printf("\n The array after deleting %d is:\n", num);
        for(i = 0; i < n; i++) {
            printf(" arr[%d] = %d\n", i, arr[i]);
        }
    }

    // Pause to allow user to see the output
    printf("\n Press Enter to exit...");
    getchar(); // consume newline
    getchar(); // wait for user to press Enter

    return 0; // Program finished successfully
}

