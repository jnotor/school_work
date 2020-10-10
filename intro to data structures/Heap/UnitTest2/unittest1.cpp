#include "stdafx.h"
#include "CppUnitTest.h"
#include "Heap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ArrayRandomizerTest)
		{
			int A[5]; //array of zeros
			int B[5]; //array of zeros
			Heap tHeap(5); //capacity is 5; we always want to keep this 1 greater than the position number of last data in array
			Assert::AreEqual(B[2], A[2]);
			Assert::IsTrue(tHeap.ArrayRandomizer(A));
			Assert::AreNotEqual(B[2],A[2]); //array randomizer works by quickly setting each element in the array to a new, random number. 
		}

		TEST_METHOD(Insert) {
			int A[5]; //array of zeros
			int B[] = { 666,13,0,0,0 }; //array of zeros
			Heap tHeap(5);
			Assert::IsTrue(tHeap.Insert(A, 666));
			Assert::AreEqual(A[0], B[0]); //since we're using max heap, 666 should be first element in array after insert and sort (which gets called in insert function)
			Assert::IsTrue(tHeap.Insert(A, 13));
			Assert::AreEqual(13, A[2]);
			Assert::AreEqual(7, tHeap.getCap());//checking to see capacity was increased 2x after 2 insertions
		}

		TEST_METHOD(Delete) {
			int A[] = { 2, 35, 666 };
			Heap tHeap(3);
			Assert::IsTrue(tHeap.Delete(A));
			Assert::AreEqual(2, tHeap.getCap());
			Assert::IsTrue(tHeap.Delete(A));
			Assert::AreEqual(1, tHeap.getCap());
			Assert::IsTrue(tHeap.Delete(A));
			Assert::AreEqual(0, tHeap.getCap());
			Assert::IsFalse(tHeap.Delete(A)); //checking to make sure we cant delete something that isnt there
		}

		TEST_METHOD(Print) {
			int A[] = { 2, 35, 666 };
			Heap tHeap(3);
			Assert::IsTrue(tHeap.Print(A)); //just checking to see that the for loop was executed; pretty straight forward elsewise
		}

		TEST_METHOD(HeapSort) {
			int A[] = { 2, 35, 666 };
			Heap tHeap(3);
			tHeap.HeapStart(A); //sorting
			Assert::AreEqual(666, A[0]); //checking to see that max is top of heap
			Assert::AreEqual(3, tHeap.getCap());	//checking to see capacity wasnt changed since no insertion or deletion
			Assert::AreEqual(2, A[2]); //checking to make sure correct child was swapped
		}
	};
}