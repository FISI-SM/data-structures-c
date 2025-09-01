// Include the standard I/O library for input and output
#include <stdio.h>

// Define a constant 'size' as 100 for array size
#define size 100

// Function prototype for merge() which merges two sorted subarrays
void merge(int a[], int beg, int mid, int end);

// Function prototype for merge_sort() which recursively divides and sorts
void merge_sort(int a[], int beg, int end);

// Start of the main function
int main()
{
    // Declare array of max size, loop counter, and number of elements
    int arr[size], i, n;

    // Ask the user how many elements they want to sort
    printf("\n Enter the number of elements in the array : ");
    scanf("%d", &n);

    // Ask the user to input those elements
    printf("\n Enter the elements of the array: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]); // Read each element into array
    }

    // Call merge_sort on the full array (from index 0 to n-1)
    merge_sort(arr, 0, n - 1);

    // Print the sorted array
    printf("\n The sorted array is: \n");
    for(i = 0; i < n; i++)
        printf(" %d\t", arr[i]);

    // Return 0 to signal successful execution
    return 0;
}

// This function merges two sorted halves of the array
void merge(int arr[], int beg, int mid, int end)
{
    // i = start of first half, j = start of second half, index = temp array index
    int i = beg, j = mid + 1, index = beg, temp[size], k;

    // Compare elements of both halves and put the smaller one into temp[]
    while(i <= mid && j <= end)
    {
        if(arr[i] < arr[j]) // If element in left half is smaller
        {
            temp[index] = arr[i]; // Store it in temp array
            i++; // Move left pointer forward
        }
        else
        {
            temp[index] = arr[j]; // Store right half element
            j++; // Move right pointer forward
        }
        index++; // Move to next position in temp[]
    }

    // If right half finished first, copy remaining left half
    if(i <= mid)
    {
        while(i <= mid)
        {
            temp[index] = arr[i];
            i++;
            index++;
        }
    }
    // If left half finished first, copy remaining right half
    else
    {
        while(j <= end)
        {
            temp[index] = arr[j];
            j++;
            index++;
        }
    }

    // Copy the sorted temp[] back to original array arr[]
    for(k = beg; k < index; k++)
        arr[k] = temp[k];
}

// This function recursively divides and sorts the array
void merge_sort(int arr[], int beg, int end)
{
    int mid;

    // Only continue if the current subarray has more than 1 element
    if(beg < end)
    {
        // Find the middle index to divide the array
        mid = (beg + end) / 2;

        // Recursively sort the first half
        merge_sort(arr, beg, mid);

        // Recursively sort the second half
        merge_sort(arr, mid + 1, end);

        // Merge the two sorted halves
        merge(arr, beg, mid, end);
    }
}

