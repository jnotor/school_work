// StructBST.cpp : Defines the exported functions for the DLL application.
////https://www.tutorialspoint.com/cplusplus/cpp_return_arrays_from_functions.htm
//https://www.geeksforgeeks.org/given-linked-list-representation-of-complete-tree-convert-it-to-linked-representation/
//https://gist.github.com/harish-r/a7df7ce576dda35c9660

#include "header.h"
#include "BST.h"
#include <string>
#include<stdio.h> 
#include<stdlib.h> 
#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

void BST::insert()
{
	int keyChoice;
	cout << "Enter node value to add to tree: " << endl;
	cin >> keyChoice;
	node *Orphanage, *Adopter;
	node *LostBoy = new node(keyChoice);
	//setting up analagy where we find the lostboy a new parent
	Orphanage = root;
	Adopter = NULL;
	//LOGIC
	//empty tree? make LostBoy the root - analgoy doesnt really work here but so be it
	if (root == NULL) { 
		root = LostBoy;
		LostBoy->parent = NULL;
	}
	//not empty? 
	else	{
		//checking against existing nodes
		while (Orphanage != NULL) {
			//saving Orphanage as Adopter so we find where the tree ends and keep that last node for the next step in eval
			Adopter = Orphanage;
			//if Orphanage's key is less than LostBoy's, check down the rhs
			if (Orphanage->key < LostBoy->key) {
				Orphanage = Orphanage->right;
			}
			//elsewise check down the lhs
			else {
				Orphanage = Orphanage->left;
			}
		}
		//now that we've found which node in the tree it  should be the child of, determine if it should be a left or right child
		//set LostBoy's parent to be Adopter
		LostBoy->parent = Adopter;
		//if Adopter's key is less than LostBoy's key, make LostBoy be Adopter's right child
		if (Adopter->key < LostBoy->key) {
			Adopter->right = LostBoy;
		}
		//elsewise, LostBoy becomes left child
		else {
			Adopter->left = LostBoy;
		}
	}
	FixIt(LostBoy);
}

void BST::FixIt(node * LostBoy)
{
	if (root == LostBoy) {
		LostBoy->color = 'b';
		return; //since when can we use the return keyword for a void...?
	}
	node *Uncle;
	while (LostBoy->parent != NULL && LostBoy->parent->color == 'r') {
		node *Gramps = LostBoy->parent->parent;
		//looking to see if Lostboy and Gramps have a common connection on the left
		if (Gramps->left == LostBoy->parent) {
			if (Gramps->right != NULL) {				 //does gramps have 2 kids? yes:
				Uncle = Gramps->right;
				if (Uncle->color == 'r') {
					LostBoy->parent->color = 'b';
					Uncle->color = 'b';
					Gramps->color = 'r';
					LostBoy = Gramps;
				}
			}
			else {										//does gramps have 2 kids? no:
				if (LostBoy->parent->right == LostBoy) { //if lostboy's parent's right kid is the lostboy, we need to rotate  the parent
					LRotate(LostBoy->parent);			//if so, balance by rotating to the left
				}										//now we need to rotate gramps																//make sure the above line arrow continues to work
				LostBoy->parent->color = 'b'; 
				Gramps->color = 'r';
				RRotate(Gramps);
			}
		}
		else {											//looking to see if Lostboy and Gramps have a common connection on the right or none
			if (Gramps->left != NULL) {					//must be on right
				Uncle = Gramps->left;
				if (Uncle->color == 'r') {				//check to see if uncle is red
					LostBoy->parent->color = 'b';
					Uncle->color = 'b';
					Gramps->color = 'r';
					LostBoy = Gramps;
				}
			}
			else {										//check to see if LostBoy is his parent's left kid
				if (LostBoy->parent->left == LostBoy) { //if so, balance by rotating to the right
					//LostBoy = LostBoy->parent;
					RRotate(LostBoy->parent);
				}
				LostBoy->parent->color = 'b';
				Gramps->color = 'r';
				LRotate(Gramps);
			}
		}
		root->color = 'b'; //reset root color before proceeding back into loop, assuming conditions still met
	}
}

void BST::LRotate(node * PassedParent)
{
	if (PassedParent->right == NULL) { //no need to rotate
		return;
	}
	else {
		node *child = PassedParent->right;
		if (child->left != NULL) {				//if the child has a child
			PassedParent->right = child->left; //make the child's child be passed parent's right
			child->left->parent = PassedParent; //and the child's child's parent be passed parent
		}
		else {
			PassedParent->right = NULL;		//elsewise, passedparent's right points to nothing now
		}
		if (PassedParent->parent != NULL) {	//if passedparent is not the root
			child->parent = PassedParent->parent;	//make the  child's parent be the parent's parent
		}
		if (PassedParent->parent == NULL) {		//if the passed parent is the root, make the child the root
			root = child;
		}
		else {									//if the passed parent is NOT the root
			if (PassedParent == PassedParent->parent->left) {	//and it is it's parent's left child
				PassedParent->parent->left = child;				//make the child the grandparent's new left child
			}
			else {												//same thing but on the right
				PassedParent->parent->right = child;
			}
		}
		child->left = PassedParent;								//now set child's left to be the passed parent and passed parent to be the child
		PassedParent->parent = child;
	}
}

void BST::RRotate(node * PassedParent) //opposite of left
{
	if (PassedParent->left == NULL)
		return;
	else
	{
		node *child = PassedParent->left;
		if (child->right != NULL)
		{
			PassedParent->left = child->right;
			child->right->parent = PassedParent;
		}
		else
			PassedParent->left = NULL;
		if (PassedParent->parent != NULL)
			child->parent = PassedParent->parent;
		if (PassedParent->parent == NULL)
			root = child;
		else
		{
			if (PassedParent == PassedParent->parent->left)
				PassedParent->parent->left = child;
			else
				PassedParent->parent->right = child;
		}
		child->right = PassedParent;
		PassedParent->parent = child;
	}
}

void BST::Display(node * root, int indent)
{
	if (root == NULL)
	{
		cout << "\nEmpty Tree.";
		return;
	}
	if (root != NULL) {
		if (root->right) {
			Display(root->right, indent + 4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (root->right) {
			std::cout << " /\n" << std::setw(indent) << ' ';
		}
		std::cout << root->key << "\n ";
		if (root->left) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			Display(root->left, indent + 4);
		}
	}
}

void BST::disp()
{
	Display(root,0);
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