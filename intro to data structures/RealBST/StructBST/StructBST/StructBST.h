// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the STRUCTBST_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// STRUCTBST_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STRUCTBST_EXPORTS
#define STRUCTBST_API __declspec(dllexport)
#else
#define STRUCTBST_API __declspec(dllimport)
#endif

#include <string>
#include<stdio.h> 
#include<stdlib.h> 
#include <iostream>


	struct node
	{
		std::string key;
		node *left, *right;
	};

// This class is exported from the dll
class STRUCTBST_API BST {
public:

	//construct
	BST() {		struct node *root = NULL; }
	//support function that creates a new node; used by constructor and insert
	//	node *newNode(std::string item); - // no longer being used
	//insert
		node* insert(struct node* node, std::string key);
	//find
		node* search(struct node* root, std::string key);
	//size
		int size(struct node* node);
	//get all Ascending
		std::string * GetAllA(struct node *root, std::string array[], int &index);
	//get all Descending
		std::string * GetAllD(struct node *root, std::string array[], int &index);
	//emptyT
		void deleteTree(struct node* node);
	//support function for deleteNode
		node * minValueNode(struct node* node);
	//Remove
		node* deleteNode(struct node* root, std::string key);
	//inorder print for visual check
		void inorder(struct node *root);
	//destruct
		~BST() {}	//deleteTree(root);	}
private: 
	node *root;
};
