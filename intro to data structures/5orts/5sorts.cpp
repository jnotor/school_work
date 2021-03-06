// 5sorts.cpp : Defines the exported functions for the DLL application.
/* references 
https://www.geeksforgeeks.org/bubble-sort/

*/

#include "header.h"
#include "5sorts.h"
#include <iostream>
#include <chrono>
#include <iostream>
#include <stdlib.h> 
#include<stdio.h> 
#include <vector>
#include <cmath>

typedef std::chrono::high_resolution_clock Clock;

void CMy5sorts::mergeKid(int A[], int l, int m, int r)
{

	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	std::vector<int> L(n1);
	std::vector<int> R(n2);

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L.at(i) = A[l + i];
	for (j = 0; j < n2; j++)
		R.at(j) = A[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L.at(i) <= R.at(j))
		{
			A[k] = L.at(i);
			i++;
		}
		else
		{
			A[k] = R.at(j);
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		A[k] = L.at(i);
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		A[k] = R.at(j);
		j++;
		k++;
	}
}

void CMy5sorts::mergeParent(int A[], int start, int end)
{
	auto t1 = Clock::now();
	int dT = 0;
	if (start < end)
	{
		auto t2 = Clock::now();
		dT = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		if (dT > 3000000000000) {
			std::cout << "exceeds time limit" << std::endl;
			abort();
		}
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = start + (end - start) / 2;

		// Sort first and second halves 
		mergeParent(A, start, m);
		mergeParent(A, m + 1, end);

		mergeKid(A, start, m, end);
	}
	std::cout << "Delta t2-t1: " << dT << " nanoseconds" << std::endl;
}

int CMy5sorts::partition(int A[], int low, int high)
{
	int pivot = A[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; ++j) {
		if (A[j] <= pivot) {
			++i;
			swap(&A[i], &A[j]);
		}
	}
	swap(&A[i + 1], &A[high]);
	return (i + 1);
}

void CMy5sorts::QuickSort(int A[], int low, int high)
{
	auto t1 = Clock::now();
	int dT = 0;
	if (low < high) {
		auto t2 = Clock::now();
		 dT = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		if (dT > 3000000000000) {
			std::cout << "exceeds time limit" << std::endl;
			abort();
		}
		int partIndex = partition(A, low, high);
		QuickSort(A, low, partIndex - 1);
		QuickSort(A, partIndex + 1, high);
	}
	std::cout << "Delta t2-t1: " << dT << " nanoseconds" << std::endl;
}

int CMy5sorts::getMax(int A[], int n)
{
	int max = 0;
	for (int i = 1; i < n; ++i) {
		if (A[i] > max) {
			max = A[i];
		}
	}
	return max;
}

void CMy5sorts::countSort(int A[], int n, int exp)
{
	std::vector<int> output(n);
	int i;
	int count[10] = { 0 };

	// Store count of occurrences in count[] 
	for (i = 0; i < n; i++)
		count[(A[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual 
	//  position of this digit in output[] 
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array 
	for (i = n - 1; i >= 0; i--)
	{
		output.at(count[(A[i] / exp) % 10] - 1) = A[i];
		count[(A[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now 
	// contains sorted numbers according to current digit 
	for (i = 0; i < n; i++)
		A[i] = output.at(i);
}

void CMy5sorts::RadixSort(int A[], int n)
{
	// Find the maximum number to know number of digits 
	int m = getMax(A, n);
	// Do counting sort for every digit. Note that instead 
	// of passing digit number, exp is passed. exp is 10^i 
	// where i is current digit number 
	int dT = 0;
	auto t1 = Clock::now();
	while (dT < 3000000000000) {
	for (int exp = 1; m / exp > 0; exp *= 10) {
		countSort(A, n, exp);
		auto t2 = Clock::now();
		dT = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		}
	break;
	}
	std::cout << "Delta t2-t1: " << dT << " nanoseconds" << std::endl;
}

void CMy5sorts::inSert(int A[], int n)
{
	int i1, hold, i2;
	auto t1 = Clock::now();
	int dT = 0;
	while (dT < 3000000000000) {
		for (i1 = 1; i1 < n; ++i1) {
			hold = A[i1];
			i2 = i1 - 1;
			while (i2 >= 0 && A[i2] > hold) {
				A[i2 + 1] = A[i2];
				i2 = i2 - 1;
			}
			A[i2 + 1] = hold;
		}
		auto t2 = Clock::now();
		dT = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		std::cout << dT << std::endl;
		break;
	}
	std::cout << "Delta t2-t1: " << dT << " nanoseconds" << std::endl;
}

void CMy5sorts::swap(int * alpha, int * beta)
{
	int temp = *alpha;
	*alpha = *beta;
	*beta = temp;
}

void CMy5sorts::BubSort(int A[], int n)
{

	int i = 0;
	int j;
	auto t1 = Clock::now();
	int dT = 0;
	while (dT < 3000000000000) {
		for (i = 0; i < n - 1; ++i) {
			for (j = 0; j < n - i - 1; ++j) {
				if (A[j] > A[j + 1]) {
					swap(&A[j], &A[j + 1]);
				}
			}
		}
		auto t2 = Clock::now();
		dT = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		std::cout << dT << std::endl;
		break;
	}
	    std::cout << "Delta t2-t1: " << dT << " nanoseconds" << std::endl;
}

void CMy5sorts::ArrayRandomizer(int A[], int n)
{
	int rNum;
	for (int i = 0; i < n; ++i) {
		rNum = rand() % (2 * n);
		A[i] = rNum;
	}
}

void CMy5sorts::Sort()
{
	char SortChoice;
	char ArrayChoice;

	std::cout << "Welcome to 5ort. This program was made to demonstrate the time differences of different sorting algorithms." << std::endl;
	std::cout << "To get started, please select which type of sort you'd like to try first by entering the letter next to the sort type into the consol" << std::endl;
	std::cout << "a - Bubble Sort" << std::endl;
	std::cout << "b - Insertion Sort" << std::endl;
	std::cout << "c - Merge Sort" << std::endl;
	std::cout << "d - Quick Sort" << std::endl;
	std::cout << "e - Radix Sort" << std::endl;
	std::cout << "Any other charachter will exit the program" << std::endl;
	
	std::cin >> SortChoice;
	
	std::cout << "Now let's select the array size you would like to test: " << std::endl;
	std::cout << "a - 10" << std::endl;
	std::cout << "b - 100" << std::endl;
	std::cout << "c - 500" << std::endl;
	std::cout << "d - 5000" << std::endl;
	std::cout << "e - 25000" << std::endl;
	std::cout << "Any other charachter will exit the program" << std::endl;

	std::cin >> ArrayChoice;
	
	//gotta add times - we dont care about printing
	switch (SortChoice) {
	case 'A':
	case 'a': //bubble
		//SortInterfacePart2(ArrayChoice);
		switch (ArrayChoice) {
		case 'A':
		case 'a'://10
			BubSort(A10,10);
			PrintTest(A10, 10);
			break;
		case 'B':
		case 'b'://100
			BubSort(A100,100);
			break;
		case 'C':
		case 'c'://500
			BubSort(A500,500);
			break;
		case 'D':
		case 'd'://5000
			BubSort(A5k,5000);
			break;
		case 'E':
		case 'e'://25000
			BubSort(A25k,25000);
			break;
		default:
			std::cout << "Exiting. Goodbye!";
		}
		break;
	case 'B':
	case 'b'://insert
		switch (ArrayChoice) {
		case 'A':
		case 'a'://10
			inSert(A10,10);
			PrintTest(A10, 10);
			break;
		case 'B':
		case 'b'://100
			inSert(A100,100);
			break;
		case 'C':
		case 'c'://500
			inSert(A500,500);
			break;
		case 'D':
		case 'd'://5000
			inSert(A5k,5000);
			break;
		case 'E':
		case 'e'://25000
			inSert(A25k,25000);
			break;
		default:
			std::cout << "Exiting. Goodbye!";
		}
		break;
	case 'C':
	case 'c'://merge
		switch (ArrayChoice) {
		case 'A':
		case 'a'://10
			mergeParent(A10,0,9);
			PrintTest(A10, 10);
			break;
		case 'B':
		case 'b'://100
			mergeParent(A100,0,99);
			break;
		case 'C':
		case 'c'://500
			mergeParent(A500,0,499);
			break;
		case 'D':
		case 'd'://5000
			mergeParent(A5k,0,4999);
			break;
		case 'E':
		case 'e'://25000
			mergeParent(A25k,0,24999);
			break;
		default:
			std::cout << "Exiting. Goodbye!";
		}
		break;
	case 'D':
	case 'd'://quick
		switch (ArrayChoice) {
		case 'A':
		case 'a'://10
			QuickSort(A10,0,9);
			PrintTest(A10, 10);
			break;
		case 'B':
		case 'b'://100
			QuickSort(A100,0,99);
			break;
		case 'C':
		case 'c'://500
			QuickSort(A500,0,499);
			break;
		case 'D':
		case 'd'://5000
			QuickSort(A5k,0,4999);
			break;
		case 'E':
		case 'e'://25000
			QuickSort(A25k,0,24999);
			break;
		default:
			std::cout << "Exiting. Goodbye!";
		}
		break;
	case 'E':
	case 'e'://radix
		switch (ArrayChoice) {
		case 'A':
		case 'a'://10
			//small case not working...
			RadixSort(A10,10);
			PrintTest(A10, 10);
			break;
		case 'B':
		case 'b'://100
			RadixSort(A100,100);
			PrintTest(A100, 100);
			break;
		case 'C':
		case 'c'://500
			RadixSort(A500,500);
			break;
		case 'D':
		case 'd'://5000
			RadixSort(A5k,5000);
			break;
		case 'E':
		case 'e'://25000
			RadixSort(A25k,25000);
			break;
		default:
			std::cout << "Exiting. Goodbye!";
		}
		break;
	default:
		std::cout << "Exiting. Goodbye!";
	}
}

void CMy5sorts::PrintTest(int A[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		std::cout << A[i] << " ";
	}
}

