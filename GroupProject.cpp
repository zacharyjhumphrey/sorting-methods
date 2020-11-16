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
	int num_sorts = 5;
	
	// Create records
	Record timsortRecord, quicksortRecord, heapsortRecord, bubbleRecord, selectionRecord;
	Record* records[] = { &timsortRecord, &quicksortRecord, &heapsortRecord, &bubbleRecord, &selectionRecord };
	
	// Array of sorts 
	void (*sorts[])(int*, const int) = { timSort, quickSort, heapSort, bubbleSort, selectionSort };

	do {
		cout << "Enter the number of times you would like to run tests: ";
		cin >> num_tests;
		cin.get();

		if (num_tests < 0) cerr << "\nERROR: Number of tests must be greater than 0. Enter 0 to exit the program\n\n"; // Error case
	} while (num_tests < 0); // Run until the number of tests is greater than or equal to zero

	// Exit the program if the user doesn't want to run any tests
	if (num_tests == 0) return 0;

	// INIT TEST ARRAYS -----------------
	for (int i = 0; i < num_sorts; i++) {
		records[i]->sorted.tests = new int[num_tests];
		records[i]->random.tests = new int[num_tests];
	}

	// RUN TESTS ------------------------
	for (int i = 0; i < num_tests; i++) { 
		int* original_array = randomArray();

		// Run tests for each of the sorts 
		for (int j = 0; j < num_sorts; j++) {
			int* copy_array = copyArray(original_array);
			runTest(copy_array, *sorts[j], *records[j], i);
			delete[] copy_array;
		}
	}


	// FIND MINIMUM ----------------------
	for (int i = 0; i < num_sorts; i++) {
		records[i]->random.min = findMin(records[i]->random.tests, num_tests);
	}

	// FIND MAXIMUM ----------------------
	for (int i = 0; i < num_sorts; i++) {
		records[i]->random.max = findMax(records[i]->random.tests, num_tests);
	}

	// FIND UNSORTED AVERAGE --------------
	for (int i = 0; i < num_sorts; i++) {
		records[i]->random.average_time = records[i]->random.total_time / num_tests;
	}

	// FIND SORTED AVERAGE ----------------
	for (int i = 0; i < num_sorts; i++) {
		records[i]->sorted.average_time = records[i]->sorted.total_time / num_tests;
	}

	// PRINT RECORDS ----------------------
	printRecords(timsortRecord, bubbleRecord, selectionRecord, quicksortRecord, heapsortRecord);

	// CLEAN UP MEMORY --------------------
	for (int i = 0; i < num_sorts; i++) {
		delete[] records[i]->sorted.tests;
		delete[] records[i]->random.tests;
	}

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
void runTest(int* arr, void(*fn)(int*, const int), Record& record, int test_num) {
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

