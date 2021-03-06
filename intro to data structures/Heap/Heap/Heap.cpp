// Heap.cpp : Defines the exported functions for the DLL application.
//

#include "header.h"
#include "Heap.h"
#include <iostream>
#include <climits>

using namespace std;


bool Heap::ArrayRandomizer(int A[])
{
	int rNum;
	for (int i = 0; i < cap; ++i) {
		rNum = rand() % cap;
		A[i] = rNum;
	}
	return true;
}

bool Heap::Insert(int A[], int iValue)
{
	//insert the new value at the end of the range of the array (plus 1, technically, since array starts at position 0)
	A[cap] = iValue;
	//now swap the very first value and it, to force it to bubble down into its place
	swap(A[0], A[cap]);
	//increase the capacity, since we added a new value
	cap++;
	//sort it now
	HeapStart(A);
	return true;
}

bool Heap::Delete(int A[])
{
	if (cap == 0) {
		return false;
	}
	//decrease the capacity; being kept track of as a private data member
	cap--;
	//swap the top of the heap with the bottom; we will be excluding the bottom from the new heap sort
	swap(A[0], A[cap]);
	//re-sort
	HeapStart(A);
	return true;
}

void Heap::HeapStart(int A[])
{
	for (int i = cap / 2 - 1; i >= 0; i--) {
		HeapSort(A, i);
	}
}

void Heap::HeapSort(int A[], int index)
{
	int largest = index; // Initialize largest as root 
	int LC = 2 * index + 1; // left = 2*i + 1 
	int RC = 2 * index + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (LC < cap && A[LC] > A[largest]) {
		largest = LC;
	}
	// If right child is larger than largest so far 
	if (RC < cap && A[RC] > A[largest]) {
		largest = RC;
	}
	// If largest is not root 
	if (largest != index) {
		swap(A[index], A[largest]);
		// Recursively heapify the affected sub-tree 
		HeapSort(A, largest);
	}
}

bool Heap::Print(int A[])
{
	for (int i = 0; i < cap; i++) {
		cout << A[i] << " ";
	}
	cout << " " << endl;

	return true;
}