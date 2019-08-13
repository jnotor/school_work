// StringSort.cpp
// Michael Haas, April 11, 2009
// Demonstrates sorting of an array of strings using C++ objects


#include <iostream>
#include <string>
using namespace std;

//prototypes
void SortUp(string oldstring[], int numelements);
void SortDown(string oldstring[], int numelements);
void SortCIUp(string oldstring[], int numelements);
void SortCIDown(string oldstring[], int numelements);
string UpperString(string mixedstring);

// **************************
//       function main
// **************************

int main () 
{
    
	string s1, s2, s3;
	
	cout << "Enter two words, separated by a space, then hit Enter." << endl;
	cin >> s1 >> s2;
	
	cout << "You entered: " << endl;
	cout << s1 << endl;
	cout << s2 << endl;
	
	// really simple sort of 2 variables
	// combine the 2 variables into a third variable
	
	if (s1 < s2)
		s3 = s1 + " " + s2;
	else
		s3 = s2 + " " + s1;
	
	cout << "Sorted Combination of 2 strings: " << s3 << endl;
	
	// Create an array of many strings
	string names[50];
	
	// Create a single variable of one string
	string inputline;
	
	// counters
	int stringcount = 0;
	int c;
	
	cout << "\n\nNow let's get and sort lots of strings: " << endl;
	
	// ignore anything still in the input stream from the stuff above
	cin.ignore(1,'\n');
	
	// prompt for strings, populating string elements 0-49
	while (stringcount < 50)
	{
		cout << "\nEnter a name or 0 to quit:" << endl;
		getline(cin, inputline);
		
		// if user enters a 0, then done getting input - break out of loop
		if (inputline == "0")
			break;
		
		// assign input string to the next element of the string array
		names[stringcount] = inputline;
		// count how many elements are in the array
		stringcount++;
		
	}	// end of while stringcount < 50  loop
	
	// display the contents of the string array
	cout << "Here is what you entered:\n";
	for (c = 0; c < stringcount; c++)
		cout << "Name " << c << " is: " << names[c] << endl;
	
	// --------------------------------------------------------------------
	// Sort the names - case sensitive so Upper Case beats lower case
	// Ascending order
	// pass the array and the current number of elements to the function
	// --------------------------------------------------------------------
	cout << "\n\nNow, let's sort the names in the array:\n";
	
	SortUp(names, stringcount);
	
	// display the contents of the sorted string array
	cout << "\nHere is the sorted array in ascending order:\n";
	for (c = 0; c < stringcount; c++)
		cout << "Name " << c << " is: " << names[c] << endl;
		
	// --------------------------------------------------------------------
	// Sort the names - case sensitive so Upper Case beats lower case
	// Descending order
	// pass the array and the current number of elements to the function
	// --------------------------------------------------------------------
	SortDown(names, stringcount);
	
	// display the contents of the sorted string array
	cout << "\nHere is the sorted array in desceding order:\n";
	for (c = 0; c < stringcount; c++)
		cout << "Name " << c << " is: " << names[c] << endl;
	
	// --------------------------------------------------------------------
	// Re-sort the names - case INSENSITIVE so Upper Case equals lower case
	// must call a different sort function that converts to upper case
	// pass the string array and number of elements to the function
	// --------------------------------------------------------------------
	cout << "\n\nNow, let's sort the names in the array with case-insensitive:\n";
	
	SortCIUp(names, stringcount);
	
	cout << "\nHere is the sorted array in ascending case-insensitive order:\n";
	for (c = 0; c < stringcount; c++)
	{
		cout << "Name " << c << " is: " << names[c] << endl;
	}
	
	// --------------------------------------------------------------------
	// Re-sort the names - case INSENSITIVE so Upper Case equals lower case
	// must call a different sort function that converts to upper case
	// pass the string array and number of elements to the function
	// --------------------------------------------------------------------
	SortCIDown(names, stringcount);
	
	cout << "\nHere is the sorted array in desceding case-insensitive order:\n";
	for (c = 0; c < stringcount; c++)
		cout << "Name " << c << " is: " << names[c] << endl;
		
	// --------------------------------------------------------------------
	// conversion from string to integer
	// --------------------------------------------------------------------
	
	string text;		//string containing the number
	int intresult;			//number which will contain the result

	cout << "\nEnter a number: ";
	cin >> text;		// notice that this is brought in as a string

	intresult = atoi(text.c_str());
	cout << "\nHere is the number as an integer + 15: " << intresult + 15;
	
	// --------------------------------------------------------------------
	// done
	// --------------------------------------------------------------------

	cout << "\nThank you.  Good bye.\n";

	return 0;
}

// *******************************************************************
// SortUp Function - sorts an array in ascending order, case sensitive
// *******************************************************************

void SortUp(string oldstring[], int count)
{
	int pass, item;
	// Have to pass through the array once for each element
	for (pass = 0 ; pass < count; pass++)
	{
		for ( item = 0; item < count - 1; item++)
		{
			// if the current element is bigger than the next element, swap them
			if (oldstring[item] > oldstring[item + 1])
				swap(oldstring[item +1], oldstring[item]);
		}	// end of item for loop
	}		// end of pass for loop
}			// end of SortUp function

// **********************************************************************
// SortDown Function - sorts an array in descending order, case sensitive
// **********************************************************************

void SortDown(string oldstring[], int count)
{
	int pass, item;
	// Have to pass through the array once for each element
	for (pass = 0 ; pass < count; pass++)
	{
		for ( item = 0; item < count - 1; item++)
		{
			// if the current element is smaller than the next element, swap them
			if (oldstring[item] < oldstring[item + 1])
				swap(oldstring[item +1], oldstring[item]);
		}	// end of item for loop
	}		// end of pass for loop
}			// end of SortDown function

// *******************************************************************
// SortUp Function - sorts an array in ascending order, case insensitive
// *******************************************************************

void SortCIUp(string oldstring[], int count)
{
	int pass, item;
	
	// Have to pass through the array once for each element
	for (pass = 0 ; pass < count; pass++)
	{
		for ( item = 0; item < count - 1; item++)
		{
			// if the current element is bigger than the next element, swap them
			// note: compare the UPPERCASE strings, but swap the unconverted strings
			if ( UpperString(oldstring[item]) > UpperString(oldstring[item + 1]) )
				swap(oldstring[item +1], oldstring[item]);
		}	// end of item for loop
	}		// end of pass for loop
}			// end of SortCIUp function

// **********************************************************************
// SortDown Function - sorts an array in descending order, case insensitive
// **********************************************************************

void SortCIDown(string oldstring[], int count)
{
	int pass, item;

	
	// Have to pass through the array once for each element
	for (pass = 0 ; pass < count; pass++)
	{
		for ( item = 0; item < count - 1; item++)
		{
			// if the current element is smaller than the next element, swap them
			if ( UpperString(oldstring[item]) < UpperString(oldstring[item + 1]) )
				swap(oldstring[item +1], oldstring[item]);
		}	// end of item for loop
	}		// end of pass for loop
}			// end of SortCIDown function

// ************************************************************************
// UpperString Function - converts every character in a string to uppercase
// ************************************************************************

string UpperString(string mixedstring)
{
	string upperstring = mixedstring;
	int stringlength = mixedstring.length();
	int x;
	
	// convert each character in the string to uppercase
	for (x = 0; x < stringlength; x++)
		upperstring[x] = toupper(mixedstring[x]);
		
	// return the upperstring version of the string
	return upperstring;
}			// end of UpperString function
