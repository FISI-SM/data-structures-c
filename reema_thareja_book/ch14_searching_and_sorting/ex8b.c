#include <stdio.h>   // Standard input/output header
#include <stdlib.h>  // For standard functions like exit()

#define SIZE 10      // Define the maximum array size as 10

// Function to find the index of the smallest element from index 'k' to 'n-1'
int smallest(int arr[], int k, int n) {
    int pos = k;           // Start by assuming the kth element is the smallest
    int small = arr[k];    // Store the value of the current smallest

    for (int i = k + 1; i < n; i++) {
        if (arr[i] < small) {  // If we find a smaller element
            small = arr[i];    // Update the smallest value
            pos = i;           // And store its index
        }
    }

    return pos;  // Return the index of the smallest element found
}

// Function to perform selection sort
void selection_sort(int arr[], int n) {
    int k, pos, temp;

    // Loop through each position in the array
    for (k = 0; k < n; k++) {
        // Find the index of the smallest element from current position to end
        pos = smallest(arr, k, n);

        // Swap the current element with the smallest found
        temp = arr[k];
        arr[k] = arr[pos];
        arr[pos] = temp;
    }
}

// Main function - entry point of the program
int main() {
    int arr[SIZE];  // Declare array
    int n, i;

    // Ask user for number of elements
    printf("\nEnter the number of elements in the array: ");
    scanf("%d", &n);

    // Ask user to input elements
    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Call the selection sort function to sort the array
    selection_sort(arr, n);

    // Display the sorted array
    printf("\nThe sorted array is:\n");
    for (i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }

    printf("\n");  // Print newline at the end
    return 0;      // Exit the program
}

