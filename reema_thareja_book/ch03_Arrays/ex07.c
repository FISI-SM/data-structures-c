// Include standard input/output library for printf, scanf, etc.
#include <stdio.h>

// Include standard library for system() function
#include <stdlib.h>

// Main function – where the program starts running
int main()
{
    // Declare variables:
    int i;           // For loop index
    int n;           // Number of elements in the array
    int num;         // The number to be inserted
    int pos;         // The position where the number should be inserted
    int arr[10];     // The array (can hold up to 10 elements)

    // Clear the terminal screen (only works on Linux/Kali)
    system("clear");

    // Ask user how many elements will be in the array
    printf("\n Enter the number of elements in the array : ");
    scanf("%d", &n); // Store the input in variable 'n'

    // Ask user to input each element of the array
    for(i = 0; i < n; i++)
    {
        // Prompt for array element at index i
        printf("\n arr[%d] = ", i);
        scanf("%d", &arr[i]); // Store input in arr[i]
    }

    // Ask for the new number to be inserted into the array
    printf("\n Enter the number to be inserted : ");
    scanf("%d", &num);

    // Ask at which position (index) to insert the new number
    printf("\n Enter the position at which the number has to be added : ");
    scanf("%d", &pos);

    // Shift elements to the right to make space for new element
    // Start from the last element and go backwards to 'pos'
    for(i = n - 1; i >= pos; i--)
    {
        arr[i + 1] = arr[i]; // Move each element one position to the right
    }

    // Insert the new number at the specified position
    arr[pos] = num;

    // Increase the number of elements in the array
    n = n + 1;

    // Print the array after insertion
    printf("\n The array after insertion of %d is : ", num);
    for(i = 0; i < n; i++)
    {
        printf("\n arr[%d] = %d", i, arr[i]);
    }

    // Wait for user to press Enter before exiting (optional)
    getchar(); // consumes leftover newline
    getchar(); // waits for user to press Enter

    // Return 0 to indicate successful execution
    return 0;
}

