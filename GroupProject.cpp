// GroupProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
	TODO:	
		- Remember how to format the output to make it look pretty
			- Need to make column for random sort AND pre-sorted sort
*/

#include <iostream>
#include <ctime>
#include <chrono> 
#include "timsort.h"
// @J'LUN INCLUDE HEADERS
// @SEAN INCLUDE HEADERS
using namespace std;
using namespace std::chrono;

const int ARRAY_SIZE = 50;

struct Case {
	int total_time = 0;
	double average_time = 0;
	int* tests;
	int min; // Min value of the random tests
	int max; // Max value of the random tests
};

struct Record {
	Case sorted;
	Case random;
};

int findMax(int* arr);
int findMin(int* arr);
int* randomArray();
int* copyArray(int* original_array);
void runTest(int* arr, Record record, int test_num);
void printArray(int* arr);
void printRecord(Record record);

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
	// @SEAN "SORT2"

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

	// Run x number of tests for each sort on each case
	for (int i = 0; i < num_tests; i++) { 
		int* original_array = randomArray();
		
		cout << "ORIGINAL ARRAY: " << endl;
		printArray(original_array);
		cout << endl << endl;

		/*----------------- Sort 1: Timsort ----------------- */
		int* timsort_array = copyArray(original_array);
		runTest(timsort_array, timsort, i); // Sorts in random case and pre-sorted case
		delete[] timsort_array;

		/*----------------- Sort 2: @J'LUN "SORT1" ----------------- */

		/*----------------- Sort 3: @J'LUN "SORT2" ----------------- */

		/*----------------- Sort 4: @SEAN "SORT1" ----------------- */

		/*----------------- Sort 5: @SEAN "SORT2" ----------------- */
	}

	// Find minimum for each 
	timsort.random.min = findMin(timsort.random.tests);
	
	// Find maximum for each
	timsort.random.max = findMax(timsort.random.tests);

	// Print the record
	printRecord(timsort);
	/* @J'LUN PRINT THE RECORD */
	/* @SEAN PRINT THE RECORD */

	// Clean up memory 
	delete[] timsort.sorted.tests;
	delete[] timsort.random.tests;
	/* @J'LUN CLEAN UP RECORD MEMORY */
	/* @SEAN CLEAN UP RECORD MEMORY */

	// Exit
	return 0;
}


/* ------------------------------------------------------ HELPER FUNCTIONS ------------------------------------------------------ */
int findMin(int* arr) {
	int min = arr[0];

	for (int i = 1; i < ARRAY_SIZE; i++) {
		if (arr[i] < min) min = arr[i];
	}

	return min;
}

int findMax(int* arr) {
	int max = arr[0];

	for (int i = 1; i < ARRAY_SIZE; i++) {
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

void printRecord(Record record) {

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
void runTest(int* arr, Record record, int test_num) {
	printArray(arr); // @TEST

	// Get current time
	auto start_random = high_resolution_clock::now();

	// Run function
	timSort(arr, ARRAY_SIZE);

	auto stop_random = high_resolution_clock::now();

	auto duration_random = duration_cast<microseconds>(stop_random - start_random);

	printArray(arr);  // @TEST

	cout << "\nTime is " << duration_random.count() << endl << endl;

	record.random.tests[test_num] = duration_random.count();
	record.random.total_time += duration_random.count();

	// Get current time
	auto start_sorted = high_resolution_clock::now();

	// Run function
	timSort(arr, ARRAY_SIZE);

	auto stop_sorted = high_resolution_clock::now();

	auto duration_sorted = duration_cast<microseconds>(stop_sorted - start_sorted);

	printArray(arr);  // @TEST

	cout << "\nTime is " << duration_sorted.count() << endl << endl;

	record.sorted.tests[test_num] = duration_sorted.count();
	record.sorted.total_time += duration_sorted.count();
}

