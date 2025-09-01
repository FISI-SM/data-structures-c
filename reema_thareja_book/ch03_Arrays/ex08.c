// Include the standard input/output library for using printf and scanf
#include <stdio.h>

// Include standard library to use system("clear") for clearing the terminal
#include <stdlib.h>

// Main function - program execution starts here
int main()
{
    // Declare variables
    int i, j;            // Loop counters
    int n;               // Number of elements in the array
    int num;             // The number to be inserted
    int arr[10];         // Declare an array of size 10

    // Clear the terminal screen (only works in Unix/Linux terminals like Kali)
    system("clear");

    // Ask the user how many elements they want to enter
    printf("\n Enter the number of elements in the array: ");
    scanf("%d", &n); // Read the value and store it in variable 'n'

    // Input array elements
    for(i = 0; i < n; i++)
    {
        printf("\n arr[%d] = ", i); // Prompt for each element
        scanf("%d", &arr[i]);       // Store user input in arr[i]
    }

    // Ask the user for the number to insert into the array
    printf("\n Enter the number to be inserted: ");
    scanf("%d", &num);

    // Find the correct position to insert 'num' so that the array remains sorted
    for(i = 0; i < n; i++)
    {
        // If current element is greater than the number to insert,
        // this is the right place to insert 'num'
        if(arr[i] > num)
        {
            // Shift elements to the right to make space for 'num'
            for(j = n - 1; j >= i; j--)
            {
                arr[j + 1] = arr[j]; // Move each element one position to the right
            }

            // Insert the new number at the correct position
            arr[i] = num;

            // Exit the loop after insertion
            break;
        }
    }

    // If number is greater than all elements, insert it at the end
    if(i == n)
    {
        arr[n] = num;
    }

    // Increase the array size by 1 after insertion
    n = n + 1;

    // Print the array after insertion
    printf("\n The array after insertion of %d is:\n", num);
    for(i = 0; i < n; i++)
    {
        printf(" arr[%d] = %d\n", i, arr[i]);
    }

    // Wait for user to press Enter before exiting (for Linux/Kali compatibility)
    printf("\nPress Enter to exit...");
    getchar(); // Consume leftover newline from previous input
    getchar(); // Wait for the user to press Enter

    return 0; // Return 0 to indicate successful execution
}

