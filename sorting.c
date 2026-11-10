// Group 5 - Programming Assignment 3

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

// Sorting thread: sorts one subarray in place using bubble sort
void *sorter(void *param)
{
    SortParams *part = (SortParams *)param;
    int i, j, temp;

    for (i = 0; i < part->count - 1; i++) {
        for (j = 0; j < part->count - 1 - i; j++) {
            if (part->start[j] > part->start[j + 1]) {
                temp = part->start[j];
                part->start[j] = part->start[j + 1];
                part->start[j + 1] = temp;
            }
        }
    }
    return NULL;
}

// Merging thread: merges the two sorted halves into the result array
void *merger(void *param)
{
    MergeParams *parts = (MergeParams *)param;
    int i = 0, j = 0, k = 0;

    while (i < parts->left.count && j < parts->right.count) {
        if (parts->left.start[i] <= parts->right.start[j]) {
            sorted[k++] = parts->left.start[i++];
        } else {
            sorted[k++] = parts->right.start[j++];
        }
    }
    while (i < parts->left.count) {
        sorted[k++] = parts->left.start[i++];
    }

    while (j < parts->right.count) {
        sorted[k++] = parts->right.start[j++];
    }

    return NULL;
}

// Creates and joins the two sorting threads, then the merging thread
int run_threads(SortParams *left, SortParams *right, MergeParams *merge_params)
{
    pthread_t sort1, sort2, merge;
    int result;

    result = pthread_create(&sort1, NULL, sorter, left);

    if (result != 0) {
        fprintf(stderr, "Error creating first sorting thread: %d\n", result);
        return 1;
    }

    result = pthread_create(&sort2, NULL, sorter, right);

    if (result != 0) {
        fprintf(stderr, "Error creating second sorting thread: %d\n", result);
        pthread_join(sort1, NULL);
        return 1;
    }

    // Wait for both sorting threads to finish
    result = pthread_join(sort1, NULL);

    if (result != 0) {
        fprintf(stderr, "Error joining first sorting thread: %d\n", result);
        pthread_join(sort2, NULL);
        return 1;
    }

    result = pthread_join(sort2, NULL);

    if (result != 0) {
        fprintf(stderr, "Error joining second sorting thread: %d\n", result);
        return 1;
    }
    result = pthread_create(&merge, NULL, merger, merge_params);

    if (result != 0) {
        fprintf(stderr, "Error creating merging thread: %d\n", result);
        return 1;
    }

    result = pthread_join(merge, NULL);

    if (result != 0) {
        fprintf(stderr, "Error joining merging thread: %d\n", result);
        return 1;
    }

    return 0;
}
int main(void)
{
    SortParams left;
    SortParams right;
    MergeParams merge_params;

    setup_parts(&left, &right);

    merge_params.left = left;
    merge_params.right = right;

    if (run_threads(&left, &right, &merge_params) != 0) {
        fprintf(stderr, "Error running threads.\n");
        return 1;
    }
    printf("Final sorted array: ");

    for (int i = 0; i < SIZE; i++) {
        printf("%d", sorted[i]);

        if (i < SIZE - 1) {
            printf(" ");
        }
    }

    printf("\n");

    return 0;
}
