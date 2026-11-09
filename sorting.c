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

// Add the merging thread function below

// Add the thread creation and joining code below

// Add main() below
