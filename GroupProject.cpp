// GroupProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
	TODO:	
		- Remember how to format the output to make it look pretty
			- Need to make column for random sort AND pre-sorted sort
*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono> 
#include "timsort.h"

// @J'LUN INCLUDE HEADERS
#include "slowSorts.h"

// @SEAN INCLUDE HEADERS
#include "slowSorts.h"

using namespace std;
using namespace std::chrono;

const int ARRAY_SIZE = 1000;

struct Case {
	int total_time = 0;
	double average_time = 0;
	int* tests = NULL;
	int min = 0; // Min value of the random tests
	int max = 0; // Max value of the random tests
};

struct Record {
	Case sorted;
	Case random;
};

int findMax(int arr[], int num_tests);
int findMin(int arr[], int num_tests);
int* randomArray();
int* copyArray(int* original_array);
void runTest(int* arr, Record &record, int test_num);
void printArray(int* arr);
void printRecords(Record r1, Record r2, Record r3);

/* ------------------------------------------------------ MAIN ------------------------------------------------------ */
/* DRIVER -----------------------------
	n = input(number of array to sort)
		The bigger the number, the more exact the time

	Create a randomly generated array
	Send this array into each function
	Report the amount of time it takes to sort the array (average case)

	Send the sorted array through the function again
	Report how much time it takes to sort an already sorted array (best case)

	OPTIONAL:
		Create a worse case array
		Send this array through the function
		Report how

	^^ For each case, do this n times to get the average time each method for each case
------------------------------------ */
int main()
{
	// Initializing variables
	int num_tests = 0;
	
	Record timsort;
	// @J'LUN "SORT1"
	// @J'LUN "SORT2"
	
	
	// @SEAN "SORT1"
	Record bubble;

	// @SEAN "SORT2"
	Record selection;

	do {
		cout << "Enter the number of times you would like to run tests: ";
		cin >> num_tests;
		cin.get();

		if (num_tests < 0) cerr << "\nERROR: Number of tests must be greater than 0. Enter 0 to exit the program\n\n"; // Error case
	} while (num_tests < 0); // Run until the number of tests is greater than or equal to zero

	// Exit the program if the user doesn't want to run any tests
	if (num_tests == 0) return 0;

	// Create arrays the size of the tests for each of the cases
	timsort.sorted.tests = new int[num_tests];
	timsort.random.tests = new int[num_tests];

	/* @J'LUN CREATE RECORD MEMORY */


	/* @SEAN CREATE RECORD MEMORY */
	bubble.sorted.tests = new int[num_tests];
	bubble.random.tests = new int[num_tests];
	selection.sorted.tests = new int[num_tests];
	selection.random.tests = new int[num_tests];

	// Run x number of tests for each sort on each case
	for (int i = 0; i < num_tests; i++) { 
		int* original_array = randomArray();
		
		/* @TEST
			cout << "ORIGINAL ARRAY: " << endl;
			printArray(original_array);
			cout << endl << endl;
		*/

		/*----------------- Sort 1: Timsort ----------------- */
		int* timsort_array = copyArray(original_array);
		runTest(timsort_array, timsort, i); // Sorts in random case and pre-sorted case
		delete[] timsort_array;

		/*----------------- Sort 2: @J'LUN "SORT1" ----------------- */

		/*----------------- Sort 3: @J'LUN "SORT2" ----------------- */

		/*----------------- Sort 4: @SEAN "SORT1" ----------------- */
		int* bubble_array = copyArray(original_array);
		runTest(bubble_array, bubble, i); // Sorts in random case and pre-sorted case
		delete[] bubble_array;

		/*----------------- Sort 5: @SEAN "SORT2" ----------------- */
		int* selection_array = copyArray(original_array);
		runTest(selection_array, selection, i); // Sorts in random case and pre-sorted case
		delete[] selection_array;
	}

	// Find minimum for each 
	timsort.random.min = findMin(timsort.random.tests, num_tests);
	
	/* @J'LUN FIND THE MIN */


	/* @SEAN FIND THE MIN */
	bubble.random.min = findMin(bubble.random.tests, num_tests);
	selection.random.min = findMin(selection.random.tests, num_tests);

	// Find maximum for each
	timsort.random.max = findMax(timsort.random.tests, num_tests);
	
	/* @J'LUN FIND THE MAX */


	/* @SEAN FIND THE MAX */
	bubble.random.max = findMax(bubble.random.tests, num_tests);
	selection.random.max = findMax(selection.random.tests, num_tests);

	// Find the average unsorted time for each
	timsort.random.average_time = timsort.random.total_time / num_tests;

	/* @J'LUN FIND THE MAX */


	/* @SEAN FIND THE MAX */
	bubble.random.average_time = bubble.random.total_time / num_tests;
	selection.random.average_time = selection.random.total_time / num_tests;

	// Find the average sorted time for each
	timsort.sorted.average_time = timsort.sorted.total_time / num_tests;

	/* @J'LUN FIND THE MAX */


	/* @SEAN FIND THE MAX */
	bubble.sorted.average_time = bubble.sorted.total_time / num_tests;
	selection.sorted.average_time = selection.sorted.total_time / num_tests;


	// Print the record
	printRecords(timsort, bubble, selection);

	/* @J'LUN PRINT THE RECORD */


	/* @SEAN PRINT THE RECORD */


	// Clean up memory 
	delete[] timsort.sorted.tests;
	delete[] timsort.random.tests;

	/* @J'LUN CLEAN UP RECORD MEMORY */


	/* @SEAN CLEAN UP RECORD MEMORY */
	delete[] bubble.sorted.tests;
	delete[] bubble.random.tests;
	delete[] selection.sorted.tests;
	delete[] selection.random.tests;

	// Exit
	return 0;
}


/* ------------------------------------------------------ HELPER FUNCTIONS ------------------------------------------------------ */
int findMin(int arr[], int num_tests) {
	int min = arr[0];

	for (int i = 1; i < num_tests; i++) {
		if (arr[i] < min) min = arr[i];
	}

	return min;
}

int findMax(int arr[], int num_tests) {
	int max = arr[0];

	for (int i = 1; i < num_tests; i++) {
		if (arr[i] > max) max = arr[i];
	}

	return max;
}

int* randomArray() {
	int* arr = new int[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++) {
		arr[i] = rand() % 100 + 1;
	}

	return arr;
}

int* copyArray(int* original_array) {
	int* temp = new int[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		temp[i] = original_array[i];
	}
	return temp;
}

/* PRINTARRAY ---------------------------------------------
	Prints array to the console
-------------------------------------------------------- */
void printArray(int* arr) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		cout << arr[i];
		if (i != ARRAY_SIZE - 1) cout << ", "; // Print this if there is another number after this one
	}
	cout << endl;
}

void printRecords(Record timsort, Record bubble, Record selection) {
	cout << setw(15) << "Sort";
	cout << setw(35) << "Min Time (Unsorted Case)";
	cout << setw(35) << "Max Time (Unsorted Case)";
	cout << setw(35) << "Avg. Time (Unsorted Case)";
	cout << setw(35) << "Avg. Time (Sorted Case)";
	cout << endl;

	cout << setw(15) << "Timsort";
	cout << setw(35) << timsort.random.min;
	cout << setw(35) << timsort.random.max;
	cout << setw(35) << timsort.random.average_time;
	cout << setw(35) << timsort.sorted.average_time;
	cout << endl;

	cout << setw(15) << "Bubble";
	cout << setw(35) << bubble.random.min;
	cout << setw(35) << bubble.random.max;
	cout << setw(35) << bubble.random.average_time;
	cout << setw(35) << bubble.sorted.average_time;
	cout << endl;

	cout << setw(15) << "Selection";
	cout << setw(35) << selection.random.min;
	cout << setw(35) << selection.random.max;
	cout << setw(35) << selection.random.average_time;
	cout << setw(35) << selection.sorted.average_time;
	cout << endl;
}

/* RUNTEST ------------------------------------------------	
	Runs a test given an array and a place to record findings
		First, tests for random case, 
		Then, it tests for pre-sorted case
		Then, it tests for completely backwards case (POSSIBLY)

	Accepts: 
		arr (int pointer): Pointer to the original, random array
		record (Test): Place to record findings
-------------------------------------------------------- */
void runTest(int* arr, Record &record, int test_num) {
	/*
		cout << "ARRAY BEFORE SORT: \n";
		printArray(arr); // @TEST
	*/

	// Get current time
	auto start_random = high_resolution_clock::now();

	// Run function
	timSort(arr, ARRAY_SIZE);

	auto stop_random = high_resolution_clock::now();

	auto duration_random = duration_cast<microseconds>(stop_random - start_random);

	/*
		cout << "ARRAY AFTER SORT: \n";
		printArray(arr); // @TEST
	*/

	// @TEST cout << "\nTime is " << duration_random.count() << endl << endl;

	record.random.tests[test_num] = duration_random.count();
	record.random.total_time += duration_random.count();

	// Get current time
	auto start_sorted = high_resolution_clock::now();

	// Run function
	timSort(arr, ARRAY_SIZE);

	auto stop_sorted = high_resolution_clock::now();

	auto duration_sorted = duration_cast<microseconds>(stop_sorted - start_sorted);

	/*
		cout << "ARRAY AFTER ANOTHER SORT: \n";
		printArray(arr); // @TEST
	*/

	// @TEST cout << "\nTime is " << duration_sorted.count() << endl << endl;

	record.sorted.tests[test_num] = duration_sorted.count();
	record.sorted.total_time += duration_sorted.count();
}

