// HeapEXE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Heap.h"
#include <chrono>

using namespace std;
typedef chrono::high_resolution_clock Clock;

int main()
{
	int test_cap = 5000;
	Heap myHeap(test_cap);
	int TestArray[5000];
	int rNum;
	float insertSum = 0;
	float removeSum = 0;
	//getting times for delete;  previously was inserting then deleteing. blew the stack when the cap was set to the max size of the array. deleting first does  not have this exception thrown
	auto t3 = Clock::now();
	for (int i = 0; i < test_cap; i++) {
		myHeap.Delete(TestArray);
	}
	auto t4 = Clock::now();
	removeSum += std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
	//getting times for insert
	auto t1 = Clock::now();
	for (int i = 0; i < test_cap; ++i) {
		rNum = rand() % (test_cap + 1);
		myHeap.Insert(TestArray, rNum);
	}
	auto t2 = Clock::now();
	insertSum += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	//printing times
	cout << "Time to insert: " << insertSum << endl;
	cout << "Time to delete: " << removeSum << endl;
	return 0;
};

