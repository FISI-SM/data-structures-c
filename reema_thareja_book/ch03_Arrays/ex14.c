#include <stdio.h>      // Standard Input/Output functions
#include <stdlib.h>     // For system("clear")

// Function Prototypes
void read_array(int my_array[], int n);                    // Reads values into the array
void display_array(int my_array[], int n);                 // Displays the array values
void interchange(int arr[], int n);                        // Swaps smallest and largest elements
int find_biggest_pos(int my_array[], int n);               // Returns index of largest element
int find_smallest_pos(int my_array[], int n);              // Returns index of smallest element

int main() {
    int arr[10];       // Array that can hold up to 10 integers
    int n;             // Actual number of elements to be used

    system("clear");   // Clear terminal screen (Kali Linux compatible)

    // Ask user for the number of elements
    printf("Enter the size of the array (max 10): ");
    scanf("%d", &n);

    // Validate input to prevent overflow
    if (n < 1 || n > 10) {
        printf("Invalid size. Please enter a number between 1 and 10.\n");
        return 1; // Exit with error code
    }

    // Read user input into the array
    read_array(arr, n);

    // Swap the smallest and largest elements
    interchange(arr, n);

    // Display the modified array
    printf("\nThe new array is:\n");
    display_array(arr, n);

    // Pause to let user read output
    printf("\n\nPress Enter to exit...");
    getchar(); // Consume leftover newline
    getchar(); // Wait for Enter

    return 0; // End program successfully
}

// Reads elements into the array from the user
void read_array(int my_array[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &my_array[i]); // Store each input into the array
    }
}

// Displays the array elements one by one
void display_array(int my_array[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, my_array[i]);
    }
}

// Finds the biggest and smallest elements and swaps them
void interchange(int my_array[], int n) {
    int temp;
    int big_pos = find_biggest_pos(my_array, n);   // Get index of largest number
    int small_pos = find_smallest_pos(my_array, n); // Get index of smallest number

    // Swap the values at big_pos and small_pos
    temp = my_array[big_pos];
    my_array[big_pos] = my_array[small_pos];
    my_array[small_pos] = temp;
}

// Finds and returns the index of the biggest element in the array
int find_biggest_pos(int my_array[], int n) {
    int i, large = my_array[0], pos = 0;

    for (i = 1; i < n; i++) {
        if (my_array[i] > large) {
            large = my_array[i];  // Update largest value
            pos = i;              // Save index of largest
        }
    }

    return pos; // Return index of largest element
}

// Finds and returns the index of the smallest element in the array
int find_smallest_pos(int my_array[], int n) {
    int i, small = my_array[0], pos = 0;

    for (i = 1; i < n; i++) {
        if (my_array[i] < small) {
            small = my_array[i]; // Update smallest value
            pos = i;             // Save index of smallest
        }
    }

    return pos; // Return index of smallest element
}

