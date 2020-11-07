#include <iostream>
using namespace std;

void selectionSort(int arr[], int n)
{
	int i, j, min_idx, temp;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;

		temp = min_idx;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx])
			{
				temp = min_idx;
				min_idx = j;
				
				arr[i] = arr[min_idx];
			}
		}
		// Swap the found minimum element with the first


		swap(&arr[min_idx], &arr[i], n);
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
				swap(&arr[j], &arr[j + 1], n);
				swapped = true;
			}
		}

		//IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
}



void swap(int arr[], int arr2[], int n)
{
	int i, min_idx, temp;

	for (i = 0; i < n - 1; i++)
	{
		temp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = temp;
	}
}
