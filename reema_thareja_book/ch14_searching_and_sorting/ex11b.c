#include <stdio.h>    // Standard I/O functions
#include <stdlib.h>   // Standard library for dynamic memory if needed

#define size 10       // Define constant size as 10 (used for buckets)

// Function prototype: finds and returns the largest number in the array
int largest(int arr[], int n);

// Function prototype: performs radix sort on the array
void radix_sort(int arr[], int n);

// Main function: entry point of the program
int main() {
    int arr[size];    // Declare an array to store input values
    int i, n;         // i for loop, n for number of elements

    // Prompt user for number of elements
    printf("\nEnter the number of elements in the array: ");
    scanf("%d", &n);   // Read the value of n from user

    // Prompt user to enter array elements
    printf("\nEnter the elements of the array: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);  // Read each element into array
    }

    // Call radix_sort to sort the input array
    radix_sort(arr, n);

    // Print the sorted array
    printf("\nThe sorted array is:\n");
    for (i = 0; i < n; i++) {
        printf("%d\t", arr[i]);  // Print each element
    }

    printf("\n");
    return 0;  // Return success to the OS
}

// This function returns the largest element in the array
int largest(int arr[], int n) {
    int large = arr[0];  // Assume first element is largest
    int i;

    // Compare with each element to find actual largest
    for (i = 1; i < n; i++) {
        if (arr[i] > large)
            large = arr[i];  // Update if current element is bigger
    }

    return large;  // Return the largest number found
}

// This function performs radix sort on the input array
void radix_sort(int arr[], int n) {
    int bucket[size][size];          // 2D array to hold buckets of each digit (0-9)
    int bucket_count[size];          // Stores count of elements in each bucket

    int i, j, k;                     // Loop counters
    int remainder;                   // Holds digit value at current place
    int NOP = 0;                     // Number of passes required
    int divisor = 1;                 // Divisor used to extract digit
    int large;                       // Holds largest number in array
    int pass;                        // Loop index for passes

    large = largest(arr, n);        // Find largest number to determine digit count

    // Count how many digits are in the largest number (number of passes)
    while (large > 0) {
        NOP++;                       // Increase number of passes
        large /= size;              // Move to next digit place
    }

    // Perform sorting for each digit place
    for (pass = 0; pass < NOP; pass++) {
        // Initialize bucket counts to 0 before each pass
        for (i = 0; i < size; i++) {
            bucket_count[i] = 0;
        }

        // Place each element in appropriate bucket based on current digit
        for (i = 0; i < n; i++) {
            remainder = (arr[i] / divisor) % size;  // Extract digit at current place
            bucket[remainder][bucket_count[remainder]] = arr[i];  // Place in bucket
            bucket_count[remainder]++;              // Increase count for that bucket
        }

        // Collect numbers from buckets back into the array
        i = 0;  // Reset array index
        for (k = 0; k < size; k++) {         // For each bucket (0 to 9)
            for (j = 0; j < bucket_count[k]; j++) {
                arr[i] = bucket[k][j];       // Copy back to original array
                i++;                         // Move to next position
            }
        }

        divisor *= size;  // Move to next higher digit place (units → tens → hundreds)
    }
}

