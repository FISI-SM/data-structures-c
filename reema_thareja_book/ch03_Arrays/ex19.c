#include <stdio.h>  // Include standard input/output functions

int main() {
    int marks[5][3];     // 2D array to store marks of 5 students in 3 subjects
    int i, j;            // Loop counters
    int max_marks;       // To store highest marks for each subject

    // Input the marks for each student
    for(i = 0; i < 5; i++) {
        printf("\n Enter the marks obtained by student %d:\n", i + 1);

        for(j = 0; j < 3; j++) {
            printf(" marks[%d][%d] = ", i, j);  // Prompt for marks[i][j]
            scanf("%d", &marks[i][j]);         // Read the value
        }
    }

    // For each subject (column), find the highest mark
    for(j = 0; j < 3; j++) {
        max_marks = -999;  // Initialize with a very small value

        // Compare marks of all 5 students for this subject
        for(i = 0; i < 5; i++) {
            if(marks[i][j] > max_marks) {
                max_marks = marks[i][j];  // Update maximum if current is greater
            }
        }

        // Print the highest mark for subject j
        printf("\n The highest marks obtained in subject %d = %d", j + 1, max_marks);
    }

    // Optional: Wait for Enter key before exiting (Linux-safe)
    printf("\n\nPress Enter to exit...");
    getchar(); // Consume leftover newline
    getchar(); // Wait for Enter

    return 0;  // End of program
}

