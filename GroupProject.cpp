// GroupProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono> 
#include "timsort.h"

// @J'LUN INCLUDE HEADERS
#include "FastSorts.h"

// @SEAN INCLUDE HEADERS
#include "slowSorts.h"

using namespace std;
using namespace std::chrono;

const int ARRAY_SIZE = 50;

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
void runTest(int* arr, void(*fn)(int*, const int), Record &record, int test_num);
void printArray(int* arr);
void printRecords(Record r1, Record r2, Record r3, Record r4, Record r5);

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
	
	Record timsortRecord;

	// @J'LUN "SORT1"
	Record quicksortRecord;

	// @J'LUN "SORT2"
	Record heapsortRecord;
	
	// @SEAN "SORT1"
	Record bubbleRecord;

	// @SEAN "SORT2"
	Record selectionRecord;

	// Record records[] = { timsortRecord, quicksortRecord };
	
	do {
		cout << "Enter the number of times you would like to run tests: ";
		cin >> num_tests;
		cin.get();

		if (num_tests < 0) cerr << "\nERROR: Number of tests must be greater than 0. Enter 0 to exit the program\n\n"; // Error case
	} while (num_tests < 0); // Run until the number of tests is greater than or equal to zero

	// Exit the program if the user doesn't want to run any tests
	if (num_tests == 0) return 0;

	// Create arrays the size of the tests for each of the cases
	timsortRecord.sorted.tests = new int[num_tests];
	timsortRecord.random.tests = new int[num_tests];

	/* @J'LUN CREATE RECORD MEMORY */
	quicksortRecord.sorted.tests = new int[num_tests];
	quicksortRecord.random.tests = new int[num_tests];
	heapsortRecord.sorted.tests = new int[num_tests];
	heapsortRecord.random.tests = new int[num_tests];

	/* @SEAN CREATE RECORD MEMORY */
	bubbleRecord.sorted.tests = new int[num_tests];
	bubbleRecord.random.tests = new int[num_tests];
	selectionRecord.sorted.tests = new int[num_tests];
	selectionRecord.random.tests = new int[num_tests];

	// Run x number of tests for each sort on each case
	for (int i = 0; i < num_tests; i++) { 
		int* original_array = randomArray();
		
		/*----------------- Sort 1: Timsort ----------------- */
		int* timsort_array = copyArray(original_array);
		runTest(timsort_array, timSort, timsortRecord, i); // Sorts in random case and pre-sorted case
		delete[] timsort_array;

		/*----------------- Sort 2: @J'LUN "SORT1" ----------------- */
		int* quicksort_array = copyArray(original_array);
		runTest(quicksort_array, quickSort, quicksortRecord, i); // Sorts in random case and pre-sorted case
		delete[] quicksort_array;

		/*----------------- Sort 3: @J'LUN "SORT2" ----------------- */
		int* heapsort_array = copyArray(original_array);
		runTest(heapsort_array, heapSort, heapsortRecord, i); // Sorts in random case and pre-sorted case
		delete[] heapsort_array;

		/*----------------- Sort 4: @SEAN "SORT1" ----------------- */
		int* bubble_array = copyArray(original_array);
		runTest(bubble_array, bubbleSort, bubbleRecord, i); // Sorts in random case and pre-sorted case
		delete[] bubble_array;

		/*----------------- Sort 5: @SEAN "SORT2" ----------------- */
		int* selection_array = copyArray(original_array);
		runTest(selection_array, selectionSort, selectionRecord, i); // Sorts in random case and pre-sorted case
		delete[] selection_array;

	}


	// MINIMUM -------------
	timsortRecord.random.min = findMin(timsortRecord.random.tests, num_tests);
	
	/* @J'LUN FIND THE MIN */
	quicksortRecord.random.min = findMin(quicksortRecord.random.tests, num_tests);
	heapsortRecord.random.min = findMin(heapsortRecord.random.tests, num_tests);

	/* @SEAN FIND THE MIN */
	bubbleRecord.random.min = findMin(bubbleRecord.random.tests, num_tests);
	selectionRecord.random.min = findMin(selectionRecord.random.tests, num_tests);


	// MAXIMUM -------------
	timsortRecord.random.max = findMax(timsortRecord.random.tests, num_tests);
	
	/* @J'LUN */
	quicksortRecord.random.max = findMax(quicksortRecord.random.tests, num_tests);
	heapsortRecord.random.max = findMax(heapsortRecord.random.tests, num_tests);

	/* @SEAN */
	bubbleRecord.random.max = findMax(bubbleRecord.random.tests, num_tests);
	selectionRecord.random.max = findMax(selectionRecord.random.tests, num_tests);


	// UNSORTED AVERAGE -----
	timsortRecord.random.average_time = timsortRecord.random.total_time / num_tests;

	/* @J'LUN */
	quicksortRecord.random.average_time = quicksortRecord.random.total_time / num_tests;
	heapsortRecord.random.average_time = heapsortRecord.random.total_time / num_tests;

	/* @SEAN */
	bubbleRecord.random.average_time = bubbleRecord.random.total_time / num_tests;
	selectionRecord.random.average_time = selectionRecord.random.total_time / num_tests;


	// SORTED AVERAGE -------
	timsortRecord.sorted.average_time = timsortRecord.sorted.total_time / num_tests;

	/* @J'LUN */
	quicksortRecord.sorted.average_time = quicksortRecord.sorted.total_time / num_tests;
	heapsortRecord.sorted.average_time = heapsortRecord.sorted.total_time / num_tests;

	/* @SEAN */
	bubbleRecord.sorted.average_time = bubbleRecord.sorted.total_time / num_tests;
	selectionRecord.sorted.average_time = selectionRecord.sorted.total_time / num_tests;


	// Print the records @J'LUN @SEAN
	printRecords(timsortRecord, bubbleRecord, selectionRecord, quicksortRecord, heapsortRecord);


	// Clean up memory 
	delete[] timsortRecord.sorted.tests;
	delete[] timsortRecord.random.tests;

	/* @J'LUN CLEAN UP RECORD MEMORY */
	delete[] quicksortRecord.sorted.tests;
	delete[] quicksortRecord.random.tests;
	delete[] heapsortRecord.sorted.tests;
	delete[] heapsortRecord.random.tests;

	/* @SEAN CLEAN UP RECORD MEMORY */
	delete[] bubbleRecord.sorted.tests;
	delete[] bubbleRecord.random.tests;
	delete[] selectionRecord.sorted.tests;
	delete[] selectionRecord.random.tests;

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

void printRecords(Record timsort, Record bubble, Record selection, Record quicksort, Record heapsort) {
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

	cout << setw(15) << "Quicksort";
	cout << setw(35) << quicksort.random.min;
	cout << setw(35) << quicksort.random.max;
	cout << setw(35) << quicksort.random.average_time;
	cout << setw(35) << quicksort.sorted.average_time;
	cout << endl;

	cout << setw(15) << "Heapsort";
	cout << setw(35) << heapsort.random.min;
	cout << setw(35) << heapsort.random.max;
	cout << setw(35) << heapsort.random.average_time;
	cout << setw(35) << heapsort.sorted.average_time;
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
void runTest(int* arr, void(*fn)(int*, const int), Record &record, int test_num) {
	// Get current time
	auto start_random = high_resolution_clock::now();

	// Run function
	fn(arr, ARRAY_SIZE);

	auto stop_random = high_resolution_clock::now();

	auto duration_random = duration_cast<microseconds>(stop_random - start_random);

	record.random.tests[test_num] = duration_random.count();
	record.random.total_time += duration_random.count();

	// Get current time
	auto start_sorted = high_resolution_clock::now();

	// Run function
	fn(arr, ARRAY_SIZE);

	auto stop_sorted = high_resolution_clock::now();

	auto duration_sorted = duration_cast<microseconds>(stop_sorted - start_sorted);

	record.sorted.tests[test_num] = duration_sorted.count();
	record.sorted.total_time += duration_sorted.count();
}

