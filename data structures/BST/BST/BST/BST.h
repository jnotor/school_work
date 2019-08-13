// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the STRUCTBST_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// STRUCTBST_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BST_EXPORTS
#define BST_API __declspec(dllexport)
#else
#define BST_API __declspec(dllimport)
#endif

#include <string>
#include<stdio.h> 
#include<stdlib.h> 
#include <iostream>


struct node
{
	int key;
	char color;
	node *left, *right, *parent;
	
	//construct for node
	node(int key) {
		this->key = key;
		left = right = parent = NULL;
		color = 'r';
	}
};

// This class is exported from the dll
class BST_API BST {
public:
		//construct
	BST() { struct node *root = NULL; struct node *succ = NULL; }
	//insert
	void insert();
	//fixing insertion
	void FixIt(node *LostBoy);
	//support function for fix it
	void LRotate(node *parent);
	//support function for fix it
	void RRotate(node *parent);
	//display tree
	void Display(node *root, int indent);
	//support function for display
	void disp();
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
	void Slide2theLeft(node *&);
	void Slide2theRight();
	
private:
	node *root = NULL;
	node *succ;
};
