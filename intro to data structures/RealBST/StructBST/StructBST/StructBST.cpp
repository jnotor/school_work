// StructBST.cpp : Defines the exported functions for the DLL application.
////https://www.tutorialspoint.com/cplusplus/cpp_return_arrays_from_functions.htm
//https://www.geeksforgeeks.org/given-linked-list-representation-of-complete-tree-convert-it-to-linked-representation/
//https://gist.github.com/harish-r/a7df7ce576dda35c9660

#include "header.h"
#include "StructBST.h"
#include <string>
#include<stdio.h> 
#include<stdlib.h> 
#include <iostream>

using namespace std;

/* //vestigal code  from old method
node * BST::newNode(std::string item)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
*/

node * BST::insert(node * node, std::string key)
{
	//If the tree is empty, return a new node
	if (node == NULL) {
		//return newNode(key);
		node = new struct node;
		node->key = key;
		node->left = node->right = NULL;
	}

	//Otherwise, recur down the tree
	if (key < node->key) {
		node->left = insert(node->left, key);
	}
	else if (key > node->key) {
		node->right = insert(node->right, key);
	}

	// return the (unchanged) node pointer
	return node;
}

node * BST::search(node * root, std::string key)
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

std::string * BST::GetAllA(node * root, std::string array[], int & index)
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

std::string * BST::GetAllD(node * root, std::string array[], int & index)
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

node * BST::deleteNode(node * root, std::string key)
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