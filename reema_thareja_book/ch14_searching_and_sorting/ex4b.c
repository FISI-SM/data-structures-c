#include <stdio.h>
#include <math.h>

#define MAX 20

int jump_search(int a[], int low, int high, int val, int n)
{
    // Declare 'step' to hold the size of each jump (usually √n)
    int step = sqrt(n);

    // 'prev' will store the start index of the block where we are currently jumping from
    int prev = 0;

    // This loop jumps ahead block-by-block until we find a block where 'val' might exist
    // We make sure we don’t go out of bounds by using (int)fmin(step, n) - 1
    while (a[(int)fmin(step, n) - 1] < val)
    {
        // Move 'prev' to the start of the next block
        prev = step;

        // Move 'step' to the end of the next block
        step += sqrt(n);

        // If 'prev' goes beyond array size, then 'val' is not in array
        if (prev >= n)
            return -1;
    }

    // Now we are in the block where 'val' might be present
    // We perform linear search from index 'prev' to the smaller of 'step' or 'n'
    while (prev < fmin(step, n))
    {
        // If the current element matches 'val', we return its index
        if (a[prev] == val)
            return prev;

        // Move to the next index
        prev++;
    }

    // If we finish the block and didn't find the value, return -1 to indicate failure
    return -1;
}



int main()
{
    // Declare array and necessary variables
    int arr[MAX], i, n, val, pos;

    // Ask the user how many elements will be in the array
    printf("\nEnter the number of elements in the array: ");
    scanf("%d", &n);

    // Prompt the user to enter the elements (must be sorted for jump search)
    printf("\nEnter the elements in sorted order: ");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Ask the user for the value they want to search for
    printf("\nEnter the value to be searched: ");
    scanf("%d", &val);

    // Call the jump_search function to find the value
    pos = jump_search(arr, 0, n - 1, val, n);

    // Display the result
    if(pos == -1)
        printf("\n%d is not found in the array.\n", val);
    else
        // +1 to show human-readable position (starting from 1, not 0)
        printf("\n%d is found at position %d.\n", val, pos + 1);

    // Exit the program successfully
    return 0;
}
