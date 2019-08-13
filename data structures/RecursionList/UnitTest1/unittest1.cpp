#include "stdafx.h"
#include "CppUnitTest.h"
#include "RecursionList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace UnitTest1
{		
	TEST_CLASS(UnitTestFactorial)
	{
	public:
		
		TEST_METHOD(Loop1)
		{
			FactorialByLoop calculator;

			int val = calculator.CalculateFactorial(3);

			Assert::AreEqual(6, val);

			// TODO: Your test code here
		}

		TEST_METHOD(Loop2)
		{
			FactorialByLoop calculator;

			int val = calculator.CalculateFactorial(10);

			Assert::AreEqual(3628800, val);
		}

		TEST_METHOD(Recursion1)
		{
			FactorialByRecursion calculator;

			int val = calculator.CalculateFactorial(3);

			Assert::AreEqual(6, val);
		}

		TEST_METHOD(Recursion2)
		{
			FactorialByRecursion calculator;

			int val = calculator.CalculateFactorial(10);

			Assert::AreEqual(3628800, val);

		}

		TEST_METHOD(Stack1)
		{
			FactorialByStack calculator;

			int val = calculator.CalculateFactorial(3);

			Assert::AreEqual(6, val);

		}

		TEST_METHOD(Stack2)
		{
			FactorialByStack calculator;

			int val = calculator.CalculateFactorial(10);

			Assert::AreEqual(3628800, val);


		}

		TEST_METHOD(BasicAttack)



		TEST_METHOD(UserDefinedException1)
		{

			try
			{
				SimpleExceptionMethod(1);
				//Did not throw exception
				Assert::Fail();
			}
			//TODO you will need to uncommment the catch block below to catch you exceptions
		//	catch (your Exception)
		//	{
		//		//Good 
		//	}
			catch (std::exception e)
			{
				//Bad Did not catch user defined exceptio
				Assert::Fail();
			}


			try
			{
				SimpleExceptionMethod(-1);
				//Did not throw exception
				Assert::Fail();
			}
		//	catch (your Exception)
		//	{
		//		//Good 
		//	}
			catch (std::exception e)
			{
				//Bad Did not catch user defined exception
				Assert::Fail();
			}

		}



	};
}