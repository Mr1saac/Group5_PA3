// Isaac - Part 1
// Setting up the arrays and splitting the numbers

#include <stdio.h>
#include <pthread.h>

#define SIZE 11

int numbers[SIZE] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int sorted[SIZE];

// Info each sorting thread needs
typedef struct {
    int *start;
    int count;
} SortParams;

// Both halves for the merge thread
typedef struct {
    SortParams left;
    SortParams right;
} MergeParams;

void setup_parts(SortParams *left, SortParams *right)
{
    // First 5 numbers
    left->start = numbers;
    left->count = SIZE / 2;

    // Last 6 numbers
    right->start = numbers + SIZE / 2;
    right->count = SIZE - SIZE / 2;
}

// These functions will be added with the other parts
void *sort_thread(void *arg);
void *merge_thread(void *arg);
int run_workers(SortParams *left, SortParams *right);
