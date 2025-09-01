#include <stdio.h>      // Required for input/output functions like printf and scanf
#include <stdlib.h>     // Required for system("clear")

// Function prototype: declares a function that will read elements into an array
void read_array(int arr[], int n);

// Function prototype: declares a function that will find the smallest element
int find_small(int arr[], int n);

int main() {
    int num[10];        // Array to store up to 10 integers
    int n;              // Number of elements the user wants to enter
    int smallest;       // To store the smallest number found

    // Clear the terminal screen (works in Kali Linux)
    system("clear");

    // Ask the user for the number of elements they want to input
    printf("Enter the size of the array (max 10): ");
    scanf("%d", &n);

    // Validate array size to avoid overflow
    if (n < 1 || n > 10) {
        printf("Invalid size! Please enter a number between 1 and 10.\n");
        return 1; // Exit with error
    }

    // Call the function to read array elements from the user
    read_array(num, n);

    // Call the function to find the smallest number and store the result
    smallest = find_small(num, n);

    // Display the smallest number
    printf("\nThe smallest number in the array is: %d\n", smallest);

    // Wait for user to press Enter before closing the program
    printf("\nPress Enter to exit...");
    getchar();  // consume leftover newline from previous input
    getchar();  // actually wait for Enter key

    return 0; // Indicate successful program end
}

// Function to read n elements into an array
void read_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("arr[%d] = ", i);  // Prompt for each array index
        scanf("%d", &arr[i]);     // Read the value into arr[i]
    }
}

// Function to find and return the smallest number in the array
int find_small(int arr[], int n) {
    int i;
    int small = arr[0]; // Assume first element is the smallest to start

    for (i = 1; i < n; i++) {
        if (arr[i] < small) {
            small = arr[i]; // Update if a smaller element is found
        }
    }

    return small; // Return the smallest number found
}

