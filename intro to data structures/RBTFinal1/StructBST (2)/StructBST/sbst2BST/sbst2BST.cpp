// sbst2BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "header.h"
#include "StructBST.h"

using namespace std;

int main() {
	//variable declaration
	BST T;
	int TreeCont = 1;
	int Option;
	int Insert;
	//enter choice loop
	cout << "Welcome to Red-Black BST Creator" << endl;
	while (TreeCont == 1) {
		cout << "Please enter a number from an option below: " << endl;
		cout << "1. Enter a new integer to the tree." << endl;
		cout << "2. View the tree." << endl;
		cout << "3. Exit" << endl;
		cin >> Option;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(3, '\n');
			cout << "Please enter an integer 1,2, or 3" << endl;
			cin >> Option;
		}
		switch (Option) {
		case 1:
			cout << "Enter the number of the integer you would like to enter into the tree: " << endl;
			cin >> Insert;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Please enter an integer" << endl;
				cin >> Insert;
			}
			T.Kinsert(Insert);
			break;
		case 2:
			T.DHelper();
			break;
		case 3:
			cout << "Goodbye" << endl;
			TreeCont = 0;
			break;
		default: 
			cout << "Invalid choice, please try again." << endl;
			break;
		}
	}
	return 0;

}
