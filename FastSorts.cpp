#include <iostream>
using namespace std;


//Credit: https://www.geeksforgeeks.org/cpp-program-for-quicksort/ (void swapQ)
//Program performs Quick Sort

void swapQ(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void split(int arr[], int first, int last)
{
    int pivot = arr[last];    //pivot (largest element)
    int i = (first - 1);  // Index of smaller element 

    //Loop checks if the index is smaller than the pivot, if it smaller the loop continues
    for (int j = first; j <= last - 1; j++)
    { 
        //If the the smaller element is smaller than or equal to the largest element
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element 
            swapQ(&arr[i], &arr[j]);
        }
    }

    //?? 
    swapQ(&arr[i + 1], &arr[last]);
    return (i + 1); //Return the i
}

void quickSort(int arr[],int first, int last)
{
    //if the first number is less than the last number 
    if (first < last)
    {
       int position = split(arr, first, last); //Puts the position index at the right place
        quickSort(arr, first, position - 1); //Sort left
        quickSort(arr, position + 1, last); //Sort right 
    }
}

//Credit to GeeksforGeeks 
//See source: https://www.geeksforgeeks.org/heap-sort/?ref=lbp
//Program to perform Heap Sort 

void swapArray(int& num1, int& num2)
{
	int temp = num1;

	num1 = num2;
	num2 = temp;
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
		swap2(arr[i], arr[large]); //swap the value we are at with the largest number

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
		swap2(arr[0], arr[i]);

        // call max heapify on the reduced heap 
        heapify(arr, i, 0); //Resorts the list, puts the max number at the parent node 
    }
}

//#include "FastSorts.h

