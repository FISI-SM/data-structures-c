#include <stdio.h>      // For printf, scanf
#include <stdlib.h>     // For system("clear")

int main() {
    // Arrays to hold input and merged values
    int arr1[10], arr2[10], arr3[20];

    // Counters and indices
    int i;                   // General loop counter
    int n1, n2;              // Sizes of arr1 and arr2
    int m;                   // Total size of merged array
    int index = 0;           // Index for arr3
    int index_first = 0;     // Current position in arr1
    int index_second = 0;    // Current position in arr2

    // Clear the terminal screen (works in Kali Linux)
    system("clear");

    // Prompt for number of elements in arr1
    printf("Enter the number of elements in array1 (max 10): ");
    scanf("%d", &n1);

    // Input validation
    if (n1 < 1 || n1 > 10) {
        printf("Invalid size for array1. Please enter between 1 and 10.\n");
        return 1;
    }

    // Input elements for array1
    printf("\nEnter the elements of the first array (in sorted order):\n");
    for(i = 0; i < n1; i++) {
        printf("arr1[%d] = ", i);
        scanf("%d", &arr1[i]);
    }

    // Prompt for number of elements in arr2
    printf("\nEnter the number of elements in array2 (max 10): ");
    scanf("%d", &n2);

    // Input validation
    if (n2 < 1 || n2 > 10) {
        printf("Invalid size for array2. Please enter between 1 and 10.\n");
        return 1;
    }

    // Input elements for array2
    printf("\nEnter the elements of the second array (in sorted order):\n");
    for(i = 0; i < n2; i++) {
        printf("arr2[%d] = ", i);
        scanf("%d", &arr2[i]);
    }

    // Total elements to be merged
    m = n1 + n2;

    // Merge both arrays into arr3 in sorted order
    while(index_first < n1 && index_second < n2) {
        if(arr1[index_first] < arr2[index_second]) {
            arr3[index] = arr1[index_first];
            index_first++;
        } else {
            arr3[index] = arr2[index_second];
            index_second++;
        }
        index++;
    }

    // If all elements from arr1 are used, but arr2 still has some
    while(index_second < n2) {
        arr3[index] = arr2[index_second];
        index_second++;
        index++;
    }

    // If all elements from arr2 are used, but arr1 still has some
    while(index_first < n1) {
        arr3[index] = arr1[index_first];
        index_first++;
        index++;
    }

    // Print the merged array
    printf("\n\nThe merged sorted array is:\n");
    for(i = 0; i < m; i++) {
        printf("arr3[%d] = %d\n", i, arr3[i]);
    }

    // Pause to allow the user to see the output
    printf("\nPress Enter to exit...");
    getchar();  // To catch leftover newline
    getchar();  // Wait for user input

    return 0;   // Program ends successfully
}

