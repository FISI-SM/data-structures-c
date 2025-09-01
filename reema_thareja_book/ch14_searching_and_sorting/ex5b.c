#include <stdio.h>    // for printf and scanf functions

// Function to perform Fibonacci Search
int fibonacciSearch(int arr[], int n, int x) {
    // Initialize the first three Fibonacci numbers
    int fib2 = 0;       // (m-2)'th Fibonacci number
    int fib1 = 1;       // (m-1)'th Fibonacci number
    int fibM = fib2 + fib1;  // m'th Fibonacci number

    // Find the smallest Fibonacci number greater than or equal to n
    while (fibM < n) {
        fib2 = fib1;         // move fib2 to fib1
        fib1 = fibM;         // move fib1 to fibM
        fibM = fib1 + fib2;  // calculate next Fibonacci number
    }

    // Marks the eliminated range from front
    int offset = -1;

    // While there are elements to be inspected
    while (fibM > 1) {
        // Calculate index to be compared
        int i = (offset + fib2 < n-1) ? offset + fib2 : n - 1;

        // If x is greater than the value at index i,
        // cut the subarray from offset to i
        if (arr[i] < x) {
            fibM = fib1;     // move 1 step down
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;      // update offset
        }

        // If x is less than the value at index i,
        // cut the subarray after i+1
        else if (arr[i] > x) {
            fibM = fib2;     // move 2 steps down
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        }

        // Element found
        else {
            return i;
        }
    }

    // If the last element is the one we're looking for
    if (fib1 && arr[offset + 1] == x) {
        return offset + 1;
    }

    // Element not found
    return -1;
}

int main() {
    int arr[100], n, i, val, pos;

    // Ask the user to enter number of elements
    printf("Enter number of elements (sorted): ");
    scanf("%d", &n);

    // Input the sorted array elements
    printf("Enter %d sorted elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Ask for the value to search
    printf("Enter value to search: ");
    scanf("%d", &val);

    // Call the Fibonacci search function
    pos = fibonacciSearch(arr, n, val);

    // Print result
    if (pos >= 0)
        printf("%d found at index %d\n", val, pos);
    else
        printf("%d not found in the array\n", val);

    return 0;
}

