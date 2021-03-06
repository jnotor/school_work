// Hash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "HashDLL.h"

using namespace std;

int main() {
	int choice, inData, hashMax = 0;
	bool done = false;
	bool check;
	string inKey;
	string searchKey;
	Node *temp = new Node("temp");
	cout << "Welcome to Hash.cpp" << endl;
	cout << "Input max size of the hashtable to create: " << endl;
	cin >> hashMax;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(10, '\n'); // not sure i need this line
		cout << "Please enter a NUMBER to define the max size of the hash table" << endl;
		cin >> hashMax;
	}
	hashMax = fabs(hashMax);
	Hashtable H(hashMax);
	//choice loop
	while (done == false)
	{
		cout << "Please choose from one of the choices below: " << endl;
		cout << "1. Find number of items in HashTable" << endl;
		cout << "2. Add an item to the table" << endl;
		cout << "3. Search for an item in the table" << endl;
		cout << "4. Quit" << endl;
		cin >> choice;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Please enter a 1,2,3 or 4 as your choice." << endl;
		}
		//choices
		switch (choice) {
		case 1: //get length
			cout << "Counting the number of items in the list..." << endl;
			cout << H.GetLength() << endl;
			break;
		case 2: //Add an item
		//add its key
			cout << "Input a String as a Key : " << endl;
			cin >> inKey; //dont think you need fail prevention here because anything can be a string, no?
			//add its data
			cout << "Input Data Value: " << endl;
			cin >> inData;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Please enter a NUMBER to define the data value" << endl;
				cin >> inData;
			}
			check = H.AddItem(inKey, inData);
			if (check)
			{
				cout << "Item has been added." << endl;

			}
			else
			{
				cout << "Item could not be added." << endl;
			}

			break;
		case 3: //search an item
			cout << "Please enter a string to try to find in the hashtable (note that it will have to be exactly the same): " << endl;
			cin >> searchKey;
			temp = H.GetItem(searchKey);
			if (temp != nullptr) {
				cout << "The Key was: " << temp->key << endl;
				cout << "It has data value: " << temp->data << endl;
			}
			else {
				cout << "Node not found please try again" << endl;
			}
			break;
		case 4: //quit
			done = true;
			cout << "Thank you for using hash.cpp. Goodbye" << endl;
			break;
		default:
			cout << "Invalud choice, please try again." << endl;
			done = false;
			break;
		}
	}
	return 0;
}
