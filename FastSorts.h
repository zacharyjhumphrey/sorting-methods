#pragma once
#ifndef FASTSORTS_H
#define FASTSORTS_H

int split(int arr[], int first, int last);
void quickSort(int arr[], const int n);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);

#endif 
