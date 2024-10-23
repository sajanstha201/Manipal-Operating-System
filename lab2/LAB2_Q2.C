/*
 argc is 6 (one for the program name and five for the arguments).
argv is an array with:
argv[0] = "./a.out"
argv[1] = "I"
argv[2] = "AM"
argv[3] = "IN"
argv[4] = "BENGALURU"
When you call sort_strings(argv + 1, argc - 1):

argv + 1 points to argv[1], which is "I", the first argument.
argc - 1 is 5, the total number of arguments provided (excluding the program name).
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to sort strings using bubble sort (case-insensitive)
void sort_strings(char *arr[], int n) {
    char *temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcasecmp(arr[i], arr[j]) > 0) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    

    int pid = fork();

    if (pid < 0) {
        // Fork failed
        printf( "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process: Sort and display strings
        sort_strings(argv + 1, argc - 1);

        printf("Sorted strings (Child Process):\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
        exit(0); // Ensure the child process exits here
    } else {
        // Parent process: Wait for child to finish
        wait(NULL);

        // Display unsorted strings
        printf("Unsorted strings (Parent Process):\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }

    return 0;
}
