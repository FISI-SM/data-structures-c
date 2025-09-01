#include <stdio.h>  // For input and output

#define MAX 10  // Maximum number of elements the heap can hold

// This function moves a value up the heap to maintain max-heap property
void RestoreHeapUp(int *Heap, int index);

// This function moves a value down the heap to maintain max-heap property
void RestoreHeapDown(int *Heap, int index, int n);

int main() {
    int Heap[MAX];  // Array to store the heap
    int n, i, j;

    // Ask the user how many numbers they want to sort
    printf("\nEnter the number of elements: ");
    scanf("%d", &n);

    // Ask the user to enter the numbers
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &Heap[i]);      // Store input at position i
        RestoreHeapUp(Heap, i);     // Fix the heap going upward after insertion
    }

    j = n;  // Store the original number of elements for final printing

    // Perform heap sort
    for (i = j - 1; i >= 1; i--) {
        int temp;

        // Swap the largest value (at index 0) with the last value in the heap
        temp = Heap[0];
        Heap[0] = Heap[i];
        Heap[i] = temp;

        // Heap size is now one less, fix heap from the top
        RestoreHeapDown(Heap, 0, i - 1);
    }

    // Print the sorted array (now from smallest to largest)
    printf("\nThe sorted elements are:\n");
    for (i = 0; i < j; i++) {
        printf("%4d", Heap[i]);
    }

    printf("\n");
    return 0;
}

// -----------------------------
// Fix the heap upwards from a new element
void RestoreHeapUp(int *Heap, int index) {
    int val = Heap[index];           // Value to be adjusted
    int parent = (index - 1) / 2;    // Find its parent index

    // Keep swapping with parent while value is bigger
    while (index > 0 && Heap[parent] < val) {
        Heap[index] = Heap[parent];  // Move parent down
        index = parent;              // Move index up
        parent = (index - 1) / 2;    // Update parent index
    }

    Heap[index] = val;  // Put the value in the correct spot
}

// -----------------------------
// Fix the heap downwards after removal or swap
void RestoreHeapDown(int *Heap, int index, int n) {
    int val = Heap[index];           // Value at current index
    int child = 2 * index + 1;       // Start with left child

    // Keep going until we're outside the heap
    while (child <= n) {
        // If right child exists and is bigger, move to right child
        if (child + 1 <= n && Heap[child] < Heap[child + 1]) {
            child = child + 1;
        }

        // If current value is already bigger than the largest child, stop
        if (val >= Heap[child]) {
            break;
        }

        // Move the child up
        Heap[index] = Heap[child];

        // Move down to child's position
        index = child;
        child = 2 * index + 1;  // Recalculate left child index
    }

    Heap[index] = val;  // Put the original value in its right place
}

