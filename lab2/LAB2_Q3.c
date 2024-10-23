#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Compare function for qsort
int compare(const void *a, const void *b) {
    // Cast the void pointers to char pointers, then use strcasecmp to compare them
    return strcmp(*( char **)a, *( char **)b);
}

// Bubble Sort function
void bubble_sort(char *arr[], int n) {
    char *temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                // Swap the elements
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Quick Sort function
void quick_sort(char *arr[], int n) {
    qsort(arr, n, sizeof(char *), compare);
}

// Function to print an array of strings
void prints(char *str[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", str[i]);
    }
}

int main() {
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);

    // Allocate memory for strings
    char *str[n];
    for (int i = 0; i < n; i++) {
        str[i] = (char *)malloc(100 * sizeof(char)); // Assuming maximum length of each string is 99
        printf("Enter string %d: ", i + 1);
        scanf("%s", str[i]);
    }

    int pid1 = fork();

    if (pid1 < 0) {
        printf("Error creating fork\n");
        exit(1);
    } else if (pid1 == 0) {
        // Child process 1: Perform Bubble Sort
        bubble_sort(str, n);
        printf("Sorted strings using Bubble Sort (Child 1):\n");
        prints(str, n);
        exit(0);
    }

    int pid2 = fork();

    if (pid2 < 0) {
        printf("Error creating fork\n");
        exit(1);
    } else if (pid2 == 0) {
        // Child process 2: Perform Quick Sort
        quick_sort(str, n);
        printf("Sorted strings using Quick Sort (Child 2):\n");
        prints(str, n);
        exit(0);
    }
}
