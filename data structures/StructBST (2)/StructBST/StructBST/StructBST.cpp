// StructBST.cpp : Defines the exported functions for the DLL application.
////https://www.tutorialspoint.com/cplusplus/cpp_return_arrays_from_functions.htm
//https://www.geeksforgeeks.org/given-linked-list-representation-of-complete-tree-convert-it-to-linked-representation/
//https://gist.github.com/harish-r/a7df7ce576dda35c9660
//https://www.geeksforgeeks.org/level-order-tree-traversal/


#include <string>
//#include<stdio.h> 
//#include<stdlib.h> 
#include <iostream>
#include <iomanip>
#include "header.h"
#include "StructBST.h"

using namespace std;

node * BST::Pinsert(node * root, node *insert)
{
	//If the tree is empty, return a new node
	if (root == NULL) {
		return insert;
	}
	//Otherwise, check tree via recursion
	//check to see if new node is less than the root	
	if (insert->key < root->key) {
		root->left = Pinsert(root->left, insert);
		root->left->parent = root;
	}
	else if (insert->key > root->key) {
		root->right = Pinsert(root->right, insert);
		root->right->parent = root;
	}
	return root;
}

void BST::Kinsert(int key)
{
	node *insert = new node(key);
	root = Pinsert(root, insert);
	FixIt(root, insert);
}

void BST::FixIt(node *&root, node *&inserted)
{
	node *iParent = NULL;
	node *iGP = NULL;

	while ((inserted != root) && (inserted->color != BLACK) &&
		(inserted->parent->color == RED))
	{

		iParent = inserted->parent;
		iGP = inserted->parent->parent;

		/* Case : A
			Parent of inserted is left child of Grand-parent of inserted */
		if (iParent == iGP->left)
		{

			node *iUncle = iGP->right;

			/* Case : 1
			The uncle of inserted is also red
			Only Recoloring required */
			if (iUncle != NULL && iUncle->color == RED)
			{
				iGP->color = RED;
				iParent->color = BLACK;
				iUncle->color = BLACK;
				inserted = iGP;
			}

			else
			{
				/* Case : 2
				inserted is right child of its parent
				Left-rotation required */
				if (inserted == iParent->right)
				{
					LRotate(root, iParent);
					inserted = iParent;
					iParent = inserted->parent;
				}

				/* Case : 3
				inserted is left child of its parent
				Right-rotation required */
				RRotate(root, iGP);
				swap(iParent->color, iGP->color);
				inserted = iParent;
			}
		}

		/* Case : B
		Parent of inserted is right child of Grand-parent of inserted */
		else
		{
			node *iUncle = iGP->left;

			/* Case : 1
				The uncle of inserted is also red
				Only Recoloring required */
			if ((iUncle != NULL) && (iUncle->color == RED))
			{
				iGP->color = RED;
				iParent->color = BLACK;
				iUncle->color = BLACK;
				inserted = iGP;
			}
			else
			{
				/* Case : 2
				inserted is left child of its parent
				Right-rotation required */
				if (inserted == iParent->left)
				{
					RRotate(root, iParent);
					inserted = iParent;
					iParent = inserted->parent;
				}

				/* Case : 3
				inserted is right child of its parent
				Left-rotation required */
				LRotate(root, iGP);
				swap(iParent->color, iGP->color);
				inserted = iParent;
			}
		}
	}

	root->color = BLACK;
}

void BST::RRotate(node *&root, node *&point) //may have a bracket error in the first if.
{
	node *pts_L = point->left; //made up node = point's current left child
	point->left = pts_L->right; //setting point's left child to be the above node's right child
	//4 cases: 
	//1)original point's left child has a right child (points grandchild)
	if (point->left != NULL) {
		point->left->parent = point;
	}
	pts_L->parent = point->parent;
	//2)original point is the root
	if (point->parent == NULL) {
		root = pts_L;//making original point's child the new root
	}
	//3)OG point is not the root; check to see which kid it is, left or right
	else if (point == point->parent->left) {
		//if its the left kid, make the OG point's kid its own new parent; opposite for right
		point->parent->left = pts_L;
	}
	else { //4)
		point->parent->right = pts_L;
	}
	//now complete the swap; set the child's right to be the OG point and the OG point's parent to the child
	pts_L->right = point;
	point->parent = pts_L;
}

void BST::LRotate(node *&root, node *&point)
{
	node *pts_R = point->right;

	point->right = pts_R->left;

	if (point->right != NULL)
		point->right->parent = point;

	pts_R->parent = point->parent;

	if (point->parent == NULL)
		root = pts_R;

	else if (point == point->parent->left)
		point->parent->left = pts_R;

	else
		point->parent->right = pts_R;

	pts_R->left = point;
	point->parent = pts_R;
}

void BST::Display(node * root, int indent)
{
	if (root == NULL)
		return;
	if (root != NULL) {
		if (root->right) {
			Display(root->right, indent + 4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (root->right) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << root->key << "\n ";
		if (root->left) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			Display(root->left, indent + 4);
		}
	}
}

void BST::DHelper()
{
	Display(root, 0);
}

node * BST::search(node * root, int key)
{

	// Base Cases: root is null or key is present at root 
	if (root == NULL) {
		//	cout << "found dat root, it's: " << root->key << endl; //was just to check
		std::cout << "\nCould not find requested item, null pointer returned" << std::endl;
		return nullptr;
	}
	if (root->key == key) {
		std::cout << "\nFound requested item, pointer returned." << std::endl;
		return root;
	}
	// Key is greater than root's key 
	if (root->key < key) {

		return search(root->right, key);
	}
	else {
		// Key is smaller than root's key 

		return search(root->left, key);
	}
}

int BST::size(node * node)
{
		if (node == NULL)
			return 0;
		else
			return(size(node->left) + 1 + size(node->right));
}

int * BST::GetAllA(node * root, int array[], int & index)
{
	if (root != NULL)
	{
		//we can write this with string instead of void. declare an array of strings and return it in the end, i think. 
		GetAllA(root->left, array, index);
		array[index++] = root->key;
		cout << root->key << " ";
		GetAllA(root->right, array, index);
	}
	return array;
}

int * BST::GetAllD(node * root, int array[], int & index)
{
	if (root != NULL)
	{
		//we can write this with string instead of void. declare an array of strings and return it in the end, i think. 
		GetAllD(root->right, array, index);
		array[index++] = root->key;
		cout << root->key << " ";
		GetAllD(root->left, array, index);
	}
	return array;
}

void BST::deleteTree(node * node)
{

	if (node == NULL) return;

	//first delete both subtrees 
	deleteTree(node->left);
	deleteTree(node->right);

	// then delete the node 
	cout << "Deleting node: " << node->key << endl;
	free(node);
}

node * BST::minValueNode(node * node)
{
//Given a non-empty binary search tree, return the node with minimum
//key value found in that tree. Note that the entire tree does not
//need to be searched.
	struct node* current = node;

	//loop down to find the leftmost leaf
	while (current->left != NULL)
		current = current->left;

	return current;
}

node * BST::deleteNode(node * root, int key)
{
	// base case 
	if (root == NULL) return root;

	// If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node 
	// to be deleted 
	else
	{
		// node with only one child or no child 
		if (root->left == NULL)
		{
			struct node *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			struct node *temp = root->left;
			free(root);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		struct node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node 
		root->key = temp->key;

		// Delete the inorder successor 
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

void BST::inorder(node * root)
{	//function used to check and see if the tree is in fact being added and subctracted to and from. 
	//will have to be updated for next lab to give more structure to the print out
	if (root != NULL)
	{
		//we can write this with string instead of void. declare an array of strings and return it in the end, i think. 
		inorder(root->left);
		cout << root->key << " ";
		inorder(root->right);
	}
}


int main()
{

};