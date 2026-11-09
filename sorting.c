// Group 5 - Programming Assignment 3
// Sorting numbers using pthreads

#include <stdio.h>
#include <pthread.h>

#define SIZE 11

int numbers[SIZE] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int sorted[SIZE];

typedef struct {
    int *start;
    int count;
} SortParams;

typedef struct {
    SortParams left;
    SortParams right;
} MergeParams;

// Split the numbers into two halves (5 and 6)
void setup_parts(SortParams *left, SortParams *right)
{
    left->start = numbers;
    left->count = SIZE / 2;

    right->start = numbers + SIZE / 2;
    right->count = SIZE - SIZE / 2;
}

// Add the sorting thread function below
// Sorting thread: sorts one subarray in place using bubble sort
void *sorter(void *param)
{
    SortParams *part;
    int i;
    int j;
    int temp;

    // Get the subarray description passed in by main
    part = (SortParams *) param;

    // Bubble sort: make count-1 passes over the subarray
    for (i = 0; i < part->count - 1; i++) {
        // Compare each neighboring pair and swap if out of order
        for (j = 0; j < part->count - 1 - i; j++) {
            if (part->start[j] > part->start[j + 1]) {
                temp = part->start[j];
                part->start[j] = part->start[j + 1];
                part->start[j + 1] = temp;
            }
        }
    }

    // This thread is done
    pthread_exit(NULL);
}
// Add the merging thread function below

// Add the thread creation and joining code below

// Add main() below
