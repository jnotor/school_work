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



enum Color {RED, BLACK};

struct node	{
	int key;
	bool color;
	node *left, *right, *parent;
	//constructor
	node(int key) {
		this->key = key;
		left = right = parent = NULL;
		this->color = false; //this was the problem; in c9, the color defaults to false, which is red. in visual, without this line, it defaults to true which is black. therefore, it never entered the while loop in the fix it function
	}
};

// This class is exported from the dll
class STRUCTBST_API BST {
public:

	//construct
	BST() {	root = NULL; }
	//insert for pointer
		node* Pinsert(struct node* node, struct node *insert);
	//insert for key/int
		void Kinsert(int key);
	//checks for violations
		void FixIt(struct node *&root, struct node *&inserted);
	//support function for fix it; rotates points to the right
		void RRotate(struct node *&root, struct node *&point);
	//support function for fix it; rotates points to the left
		void LRotate(struct node *&root, struct node *&point);
	//display tree function	
		void Display(node *root, int indent);
	//function to call Display function from exe file
		void DHelper();
	//find
		node* search(struct node* root, int key);
	//size
		int size(struct node* node);
	//get all Ascending
		int * GetAllA(struct node *root, int array[], int &index);
	//get all Descending
		int * GetAllD(struct node *root, int array[], int &index);
	//emptyT
		void deleteTree(struct node* node);
	//support function for deleteNode
		node * minValueNode(struct node* node);
	//Remove
		node* deleteNode(struct node* root, int key);
	//inorder print for visual check
		void inorder(struct node *root);
	//destruct
		~BST() {}	//deleteTree(root);	}
private: 
	node *root;
};
