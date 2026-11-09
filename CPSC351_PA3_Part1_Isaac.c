/*
 * CPSC 351 - Programming Assignment 3
 * Part 1: Shared data and subarray setup
 * Isaac Parada
 *
 * Paste this section at the TOP of the team's final sorting.c.
 */

#include <stdio.h>
#include <pthread.h>

#define SIZE 11

/* Shared input and final output arrays. */
int numbers[SIZE] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int sorted[SIZE];

/* Parameters passed to each sorting thread. */
typedef struct {
    int *start;
    int count;
} SortParams;

/* Parameters passed to the merging thread. */
typedef struct {
    SortParams left;
    SortParams right;
} MergeParams;

/* Split the input into 5 items on the left and 6 on the right. */
void setup_parts(SortParams *left, SortParams *right)
{
    left->start = numbers;
    left->count = SIZE / 2;

    right->start = numbers + (SIZE / 2);
    right->count = SIZE - (SIZE / 2);
}

/* Functions to be implemented in teammates' sections. */
void *sort_thread(void *arg);
void *merge_thread(void *arg);
int run_workers(SortParams *left, SortParams *right);

/* Part 5 will add main() and display the output. */
