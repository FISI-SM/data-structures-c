/********* INSERTION SORT ALGORITHM  **********/


// Include the standard input-output header file
#include <stdio.h>

// Define the size of the array (can hold up to 5 elements)
#define size 5

// Declare the insertion sort function
void insertion_sort(int arr[], int n);

// Define the main function
int main()
{
    // Declare an integer array of size 'size' (5)
    int arr[size];

    // Declare variables to use in loops and input
    int i, n;

    // Ask the user how many elements they want to sort
    printf("\n Enter the number of elements in the array: ");
    
    // Read the number of elements from user
    scanf("%d", &n);

    // Ask the user to enter the elements of the array
    printf("\n Enter the elements of the array: ");
    
    // Use a loop to read 'n' elements into the array
    for(i = 0; i < n; i++)
    {
        // Read each element one by one
        scanf("%d", &arr[i]);
    }

    // Call the insertion sort function to sort the array
    insertion_sort(arr, n);

    // Print the sorted array
    printf("\n The sorted array is: \n");
    
    // Loop to print each sorted element
    for(i = 0; i < n; i++)
        printf(" %d\t", arr[i]);

    // Return 0 to signal successful program end
    return 0;
}

// Define the insertion sort function
void insertion_sort(int arr[], int n)
{
    // Declare temporary variables for sorting
    int i, j, temp;

    // Loop through the array starting from the second element (i=1)
    for(i = 1; i < n; i++)
    {
        // Store the current element in temp
        temp = arr[i];

        // Set j to the index before i
        j = i - 1;

        // Move elements that are greater than temp one position to the right
        while((temp < arr[j]) && (j >= 0))
        {
            // Shift element to the right
            arr[j + 1] = arr[j];

            // Move j one step back
            j--;
        }

        // Insert temp into its correct position
        arr[j + 1] = temp;
    }
}

