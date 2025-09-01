/************ QUICK SORT *************/

// Include the standard input/output library for printf and scanf
#include <stdio.h>

// Define a constant size for the array (maximum number of elements)
#define size 100

// Declare the partition function which rearranges elements around a pivot
int partition(int a[], int beg, int end);

// Declare the quick_sort function which uses recursion to sort the array
void quick_sort(int a[], int beg, int end);

// The main function is where the program starts execution
int main()
{
    // Declare an integer array of fixed size, and variables for looping and size input
    int arr[size], i, n;

    // Ask the user to enter the number of elements they want to sort
    printf("\nEnter the number of elements in the array: ");
    scanf("%d", &n); // Read the number from user input

    // Ask the user to input each element of the array
    printf("\nEnter the elements of the array: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]); // Read each number and store it in the array
    }

    // Call the quick_sort function to sort the array from index 0 to n-1
    quick_sort(arr, 0, n - 1);

    // Print the sorted array after quick sort is completed
    printf("\nThe sorted array is:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]); // Print each sorted element with a tab space
    }

    printf("\n"); // Print a newline at the end
    return 0;     // Indicate that the program ended successfully
}

// This function rearranges elements around a pivot using the Hoare partition scheme
int partition(int a[], int beg, int end)
{
    // Declare necessary variables
    int left, right, temp, loc, flag;

    // Initialize pointers and pivot location
    loc = left = beg; // Set both loc and left to the beginning index
    right = end;      // Set right to the last index of the array
    flag = 0;         // This flag will control the while loop

    // Continue looping until partitioning is complete
    while(flag != 1)
    {
        // Move the right pointer leftward until we find an element less than the pivot
        while((a[loc] <= a[right]) && (loc != right))
        {
            right--; // Shift the right pointer left
        }

        // If the pivot meets the right pointer, we're done with this round
        if(loc == right)
        {
            flag = 1; // Set flag to break out of the loop
        }
        // Otherwise, swap the pivot and the element at the right pointer
        else if(a[loc] > a[right])
        {
            temp = a[loc];       // Store pivot value temporarily
            a[loc] = a[right];   // Move smaller element to pivot position
            a[right] = temp;     // Put pivot value in right position
            loc = right;         // Update pivot location
        }

        // Now do similar work from the left side if partitioning is not yet done
        if(flag != 1)
        {
            // Move the left pointer rightward until we find an element greater than the pivot
            while((a[loc] >= a[left]) && (loc != left))
            {
                left++; // Shift the left pointer right
            }

            // If the pivot meets the left pointer, we're done
            if(loc == left)
            {
                flag = 1; // Set flag to break out of the loop
            }
            // Otherwise, swap the pivot and the element at the left pointer
            else if(a[loc] < a[left])
            {
                temp = a[loc];     // Store pivot value temporarily
                a[loc] = a[left];  // Move larger element to pivot position
                a[left] = temp;    // Put pivot value in left position
                loc = left;        // Update pivot location
            }
        }
    }

    // Return the final index where the pivot is now placed correctly
    return loc;
}

// This is the main Quick Sort function that recursively sorts subarrays
void quick_sort(int a[], int beg, int end)
{
    int loc; // This will hold the index returned by partition

    // Only sort if the subarray has more than one element
    if(beg < end)
    {
        // Partition the array and get the pivot index
        loc = partition(a, beg, end);

        // Recursively sort the left subarray (elements before pivot)
        quick_sort(a, beg, loc - 1);

        // Recursively sort the right subarray (elements after pivot)
        quick_sort(a, loc + 1, end);
    }
}

