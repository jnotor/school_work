#include "stdafx.h"
#include "CppUnitTest.h"
#include "HashDLL.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Constructor_Overload) {
			Hashtable ht(100);
			//confirm the number of items in the vector is 0
			Assert::AreEqual(0, ht.GetLength());
			//confirm the max set in the constructor is == the size of the vector
			Assert::AreEqual(100, ht.getMax());
		}
		TEST_METHOD(AddItem_AsPlanned) {
			Hashtable ht(10);
			//add a couple items
			Assert::IsTrue(ht.AddItem("string", 666));
			Assert::IsTrue(ht.AddItem("key", 999));
			//make sure you can add duplicate data values but not duplicate keys
			Assert::IsTrue(ht.AddItem("dupedatatest", 666));
			//check to make sure you can add something with the same hash value;
			//this value, hash = 9, also checks to see if we can add when the last sequential
			//position,9, is taken
			Assert::IsTrue(ht.AddItem("jfy", 77)); 
			//check to see the "length" or count changed
			Assert::AreEqual(4, ht.GetLength());
			//check to see the maximum size did not change
			Assert::AreEqual(10, ht.getMax());
		}
		TEST_METHOD(AddItem_Woops) {
			Hashtable ht(3);
			//add a couple items
			Assert::IsTrue(ht.AddItem("string", 666));
			Assert::IsTrue(ht.AddItem("key", 999));
			//try to add a duplicate keys
			Assert::IsFalse(ht.AddItem("key", 999));
			Assert::IsFalse(ht.AddItem("key", 999));
			//try to add something with a neg data value
			Assert::IsTrue(ht.AddItem("test", -1));
			//try to add over the max set
			Assert::IsFalse(ht.AddItem("fail", 10));
		}
		TEST_METHOD(GetItem_AsPlanned) {
			Hashtable ht(100);
			//add a couple items
			Assert::IsTrue(ht.AddItem("string", 666));
			Assert::IsTrue(ht.AddItem("key", 999));
			//discovered isnull and isnotnull after writing all other tests lol
			Assert::IsNotNull(ht.GetItem("string"));
			Node *temp = new Node("key",999);
			Node *temp2 = new Node("string",666);
			//compare temp, which we know has key as its key, to the returned node
			//i would argue that this tests the overload function as well
			Assert::IsTrue(*temp == *ht.GetItem("key"));
			Assert::IsTrue(*temp2 == *ht.GetItem("string"));
		}
		TEST_METHOD(GetItem_Woops) {
			Hashtable ht(10);
			//add a couple items
			Assert::IsTrue(ht.AddItem("string", 666)); //position 3
			Assert::IsTrue(ht.AddItem("key", 999)); //position 9
			//try to trip the 2 null conditions of the function
			//first with a key that doesnt equal one of the above's hash
			Assert::IsTrue(ht.GetItem("eat") == nullptr);
			//then with a key who has same value but is not the same string - jfy hash == key hash
			Assert::IsTrue(ht.GetItem("jfy") == nullptr);
			//check that it is case sensitive
			Assert::IsTrue(ht.GetItem("Key") == nullptr);
			Assert::IsNull(ht.GetItem("Key"));
			//Assert::IsTrue(ht.GetItem("KEY") == nullptr);
		}
		//as getMax is a simple return of a private data member trait,
		//only one test function was felt to be necessary
		TEST_METHOD(GetMax_AsPlanned)
		{
			Hashtable EmptyHT(0);
			Hashtable ht(100);
			Hashtable neg(-1);
			Assert::AreEqual(0, EmptyHT.getMax());
			Assert::AreEqual(100, ht.getMax());
			//in the exe, negative numbers were prevented using cmath fabs
			//here it creates a vector size 0
			Assert::AreNotEqual(-1, neg.getMax());
			Assert::AreEqual(0, neg.getMax());
		}
		//as getLength is a simple return of a private data member trait,
		//only one test function was felt to be necessary
		TEST_METHOD(GetLength_AsPlanned)
		{
			Hashtable ht(100);
			Assert::AreEqual(0, ht.GetLength());
			//adding two
			Assert::IsTrue(ht.AddItem("string", 666)); //position 3
			Assert::IsTrue(ht.AddItem("key", 999)); //position 9
			Assert::AreEqual(2, ht.GetLength());
		}
		TEST_METHOD(Hash_AsPlanned)
		{	//i dont think there is ever a case where the hash can mess up
			//its just math/algorithm
			Hashtable ht(10);
			Assert::IsTrue(ht.AddItem("string", 666)); //position 3
			Assert::IsTrue(ht.AddItem("key", 999)); //position 9
			Node *temp = new Node("key", 999);
			Node *temp2 = new Node("string", 666);
			Assert::AreEqual(9, ht.Hash(temp));
			Assert::AreEqual(3, ht.Hash(temp2));
		}
		
	};
}