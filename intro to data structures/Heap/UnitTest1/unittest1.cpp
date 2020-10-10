#include "stdafx.h"
#include "CppUnitTest.h"
#include "Heap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(InsertTest)
		{
			int A[] = { 1, 54, 333, 21, 623};
			Heap tHeap(5); //capacity is 5; we always want to keep this 1 greater than the position number of last data in array
			Assert::IsTrue(tHeap.Insert(A, 666));
		}

	};
}