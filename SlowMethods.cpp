#include <iostream>
#include <iomanip>
using namespace std;

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;

		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx])
			{
				min_idx = j;
			}
		}
		// Swap the found minimum element with the first


		swap(arr[min_idx], arr[i]);
	}
}


void bubbleSort(int arr[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}

		//IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
}


/*Swap Function provided by https://www.geeksforgeeks.org/selection-sort/ */
void swap(int* arr, int* arr2)
{
	int temp;

	temp = *arr;
	*arr = *arr2;
	*arr2 = temp;

}
