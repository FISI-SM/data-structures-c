// Include the standard input/output library
#include <stdio.h>

// Include the standard library for system() function
#include <stdlib.h>

// Main function - program execution starts from here
int main()
{
    // Declare variables
    int i;           // Loop counter
    int n;           // Number of elements in the array
    int pos;         // Position from which to delete an element
    int arr[10];     // Declare an array of size 10

    // Clear the terminal screen (works in Linux)
    system("clear");

    // Ask user to enter the number of elements
    printf("\n Enter the number of elements in the array: ");
    scanf("%d", &n);  // Read number of elements

    // Input each array element from user
    for(i = 0; i < n; i++)
    {
        printf("\n arr[%d] = ", i);   // Prompt for element i
        scanf("%d", &arr[i]);         // Store it in the array
    }

    // Ask the user to enter the position for deletion
    printf("\n Enter the position from which the number has to be deleted: ");
    scanf("%d", &pos);  // Read the position

    // Validate the position
    if(pos < 0 || pos >= n)
    {
        printf("\n Invalid position! Must be between 0 and %d.\n", n-1);
    }
    else
    {
        // Shift elements to the left from the deletion point
        for(i = pos; i < n - 1; i++)
        {
            arr[i] = arr[i + 1];  // Move next element left
        }

        // Reduce array size by 1 after deletion
        n = n - 1;

        // Print the updated array
        printf("\n The array after deletion is:\n");
        for(i = 0; i < n; i++)
        {
            printf(" arr[%d] = %d\n", i, arr[i]);
        }
    }

    // Pause so user can see the output before program exits
    printf("\nPress Enter to exit...");
    getchar(); // To consume leftover newline
    getchar(); // Wait for Enter key

    return 0;  // End of program
}

