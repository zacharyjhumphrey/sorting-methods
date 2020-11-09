#ifndef TIMSORT_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TIMSORT_H

// Helper functions
int min(int x, int y);
void insertionSort(int arr[], int left, int right);
void merge(int arr[], int l, int m, int r);

// Main sorting function
void timSort(int arr[], int n);

#endif
