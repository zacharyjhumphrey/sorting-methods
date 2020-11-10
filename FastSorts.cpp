#include <iostream>
using namespace std;

//Credit to GeeksforGeeks 
//See source: https://www.geeksforgeeks.org/heap-sort/?ref=lbp
//Program to perform Heap Sort 

void swapArray(int arr[], int arr2[])
{
    //temp stores the original value 
    int i, large;
    int temp = arr[1]; //original number 
    arr[i] = arr[large]; //becomes the largest value 
    arr[large] = temp; //changes the arr[large] to equal the original number 

}

//Heapify array rooted with node
void heapify(int arr[], int n, int i)
{
    //n is the size of the heap 

    int large = i; //variable for the largest root
    int left = 2 * i + 1; //left child 
    int right = 2 * i;	//right child 

    //If left child is larger than root 
    if (left < n && arr[left] > arr[large]) //if left is size of the heap and the left child is greater than the size we are on it switches the numbers 
        large = left;


    // If right child is larger than largest so far 
    if (right < n && arr[right] > arr[large])
        large = right;

    // If largest is not root 
    if (large != i)
    {
        swapArray(arr[i], arr[large]); //swap the value we are at with the largest number

        // Recursively heapify the affected sub-tree 
        heapify(arr, n, large);
    }
}

// main function to do heap sort 
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) //int i = n/2 is the parent node
        heapify(arr, n, i); //Heapify the number, 

    // One by one extract an element from heap 
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end 
        swapArray(arr[0], arr[i]);

        // call max heapify on the reduced heap 
        heapify(arr, i, 0); //Resorts the list, puts the max number at the parent node 
    }
}

//#include "FastSorts.h
//printRecord(heapSort)
//delete[]
