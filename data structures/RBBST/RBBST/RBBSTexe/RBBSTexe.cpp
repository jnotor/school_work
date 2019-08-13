// RBBSTexe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RBBST.h"

using namespace std;

int main()
{
	RBTree tree;
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	tree.insert(8);
	tree.insert(7);
	tree.insert(6);
	tree.insert(5);
	tree.insert(4);

	cout << "\n\nTree Print\n";
	tree.levelOrder();
}
