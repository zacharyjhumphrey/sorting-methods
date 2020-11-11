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

		temp = min_idx; //Stores the minimum value into a temporary placeholder to not corrupt the original
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx]) //Checks to see if the value of our second search parameter is smaller
			{
				temp = min_idx; //Stores the newly found smaller value into the temp slot
				min_idx = j; //Replaces smaller value with new value

				arr[i] = arr[min_idx]; //Puts the value of our initial number equal to the value of the new lower number
			}
		}

		// Swap the found minimum element with the first
		swap(arr[min_idx], arr[i]);
	}
}


void bubbleSort(int arr[], int n)
{
	int i, j; //Control variables
	bool swapped; //Bool saying if the values have been swapped or not
	for (i = 0; i < n - 1; i++)
	{
		swapped = false; //Sets swapped equal to false as our anchor
		for (j = 0; j < n - i - 1; j++) //As long as the array index of j is less than the value of n-i-1 then the value of j increments
		{
			if (arr[j] > arr[j + 1]) //If the value of j is less than the value of j+1 (or i) then -> 
			{
				swap(arr[j], arr[j + 1]); // -> j and j+1 swap
				swapped = true; //swapped becomes true and when this reiterates, the swapped value breaks us out of the loop
			}
		}

		//IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
}


/* SWAP -----------------------------------------------------
	Swaps an integer in an array with another integer
---------------------------------------------------------- */
void swap(int& num1, int& num2)
{
	int temp = num1;

	num1 = num2;
	num2 = temp;
}
