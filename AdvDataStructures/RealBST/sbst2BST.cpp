// sbst2BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "header.h"
#include "StructBST.h"


int main()
{
	BST T;
	struct node *root = NULL;
	int indexA = 0;
	int indexD = 0;
	std::string arrayA[5];
	std::string arrayD[5];
	root = T.insert(root, "Halloween");
	root = T.insert(root, "A Nightmare on Elm Street");
	root = T.insert(root, "Hocus Pocus");
	root = T.insert(root, "Beetlejuice");
	root = T.insert(root, "Test");
	std::cout << "Saving all pointers in ascending order in an array. Printing each stored value as we go: " << std::endl;
	T.GetAllA(root, arrayA, indexA);
	std::cout << "\nSaving all pointers in descending order in an array. Printing each stored value as we go: " << std::endl;
	T.GetAllD(root, arrayD, indexD);
	T.deleteNode(root, "Halloween");
	std::cout << "\nPrinting the tree with inorder traversal to show that requested item was deleted: Halloween" << std::endl;
	T.inorder(root);
	std::cout << "\nAttempting to search for deleted node";
	T.search(root, "Halloween");
	T.size(root);
	T.deleteTree(root);
	return 0;

}
