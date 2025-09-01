// Include the standard input/output library
#include <stdio.h>

// Include the standard library for system() function
#include <stdlib.h>

// Main function where program execution begins
int main()
{
    // Declare arrays with max size 10 for arr1 and arr2
    // arr3 is for storing the merged result (max 20 elements)
    int arr1[10], arr2[10], arr3[20];

    // Declare variables for counting and indexing
    int i;              // loop counter
    int n1, n2;         // number of elements in arr1 and arr2
    int m;              // total number of merged elements
    int index = 0;      // index to keep track of where to insert in arr3

    // Clear the terminal screen (safe in Linux/Kali)
    system("clear");

    // Get the number of elements for the first array
    printf("\n Enter the number of elements in array1 (max 10): ");
    scanf("%d", &n1);

    // Validate array size
    if (n1 < 1 || n1 > 10) {
        printf("\n Invalid size for array1. Must be between 1 and 10.\n");
        return 1;
    }

    // Get elements of the first array from user
    printf("\n Enter the elements of the first array:\n");
    for(i = 0; i < n1; i++) {
        printf(" arr1[%d] = ", i);   // Prompt for each element
        scanf("%d", &arr1[i]);       // Read value into arr1
    }

    // Get the number of elements for the second array
    printf("\n Enter the number of elements in array2 (max 10): ");
    scanf("%d", &n2);

    // Validate array size
    if (n2 < 1 || n2 > 10) {
        printf("\n Invalid size for array2. Must be between 1 and 10.\n");
        return 1;
    }

    // Get elements of the second array from user
    printf("\n Enter the elements of the second array:\n");
    for(i = 0; i < n2; i++) {
        printf(" arr2[%d] = ", i);   // Prompt for each element
        scanf("%d", &arr2[i]);       // Read value into arr2
    }

    // Calculate total number of elements after merging
    m = n1 + n2;

    // Copy elements of arr1 to arr3
    for(i = 0; i < n1; i++) {
        arr3[index] = arr1[i];  // Copy element
        index++;                // Move to next index
    }

    // Copy elements of arr2 to arr3
    for(i = 0; i < n2; i++) {
        arr3[index] = arr2[i];  // Copy element
        index++;                // Move to next index
    }

    // Print the merged array
    printf("\n The merged array is:\n");
    for(i = 0; i < m; i++) {
        printf(" arr3[%d] = %d\n", i, arr3[i]);  // Display each element
    }

    // Pause to allow user to see the output
    printf("\n Press Enter to exit...");
    getchar(); // consume leftover newline character
    getchar(); // wait for user to press Enter

    // Exit successfully
    return 0;
}

