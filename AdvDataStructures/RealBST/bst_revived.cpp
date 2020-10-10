#include <string>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>

struct node{
    std::string name;
    std::string number;
    node *left, *right;
};

// This class is exported from the dll
class BST {
    public:

    	BST() {	struct node *root = NULL; }

		node* insert(struct node* node, std::string name){
            //If the tree is empty, return a new node
            if (node == NULL) {
                node = new struct node;
                node->name = name;
                node->left = node->right = NULL;
            }

            //Otherwise, recur down the tree
            if (name < node->name) {
                node->left = insert(node->left, name);
            }
            else if (name > node->name) {
                node->right = insert(node->right, name);
            }

            return node;
        }

		node* search(struct node* root, std::string name){

            // Base Cases: root is null or name is present at root
            if (root == NULL) {
                std::cout << "\nCould not find requested item, null pointer returned" << std::endl;
                return nullptr;
            }
            if (root->name == name) {
                std::cout << "\nFound requested item: " << name << std::endl;
                return root;
            }
            // name is greater than root's name
            if (root->name < name) {

                return search(root->right, name);
            }
            else {
                // name is smaller than root's name

                return search(root->left, name);
            }
        }

		int size(struct node* node){
            if (node == NULL)
                return 0;
            else
                return(size(node->left) + 1 + size(node->right));
        }

		std::string * GetAllAscend(struct node *root, std::string array[], int &index){
            if (root != NULL)
            {
                //we can write this with string instead of void. declare an array of strings and return it in the end, i think.
                GetAllAscend(root->left, array, index);
                array[index++] = root->name;
                std::cout << root->name << " ";
                GetAllAscend(root->right, array, index);
            }
            return array;
        }

		std::string * GetAllDescend(struct node *root, std::string array[], int &index){
            if (root != NULL)
            {
                //we can write this with string instead of void. declare an array of strings and return it in the end, i think.
                GetAllDescend(root->right, array, index);
                array[index++] = root->name;
                std::cout << root->name << " ";
                GetAllDescend(root->left, array, index);
            }
            return array;
        }

		void deleteTree(struct node* node){

            if (node == NULL) return;

            //first delete both subtrees
            deleteTree(node->left);
            deleteTree(node->right);

            // then delete the node
            std::cout << "Deleting node: " << node->name << std::endl;
            free(node);
        }

        node * minValueNode(node * node){
            //Given a non-empty binary search tree, return the node with minimum
            //name value found in that tree. Note that the entire tree does not
            //need to be searched.
            struct node* current = node;

            //loop down to find the leftmost leaf
            while (current->left != NULL)
                current = current->left;

            return current;
        }

		node * deleteNode(struct node* root, std::string name){
            // base case
            if (root == NULL) return root;

            // If the name to be deleted is smaller than the root's name,
            // then it lies in left subtree
            if (name < root->name)
                root->left = deleteNode(root->left, name);

            // If the name to be deleted is greater than the root's name,
            // then it lies in right subtree
            else if (name > root->name)
                root->right = deleteNode(root->right, name);

            // if name is same as root's name, then This is the node
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
                root->name = temp->name;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->name);
            }
            return root;
        }

		void inorder(node * root){
        	//function used to check and see if the tree is in fact being added and subctracted to and from.
            //will have to be updated for next lab to give more structure to the print out
            if (root != NULL)
            {
                //we can write this with string instead of void. declare an array of strings and return it in the end, i think.
                inorder(root->left);
                std::cout << root->name << " ";
                inorder(root->right);
            }
        }

		~BST() {}	//deleteTree(root);	}
    private:
	    node *root;
    };

int main(){

    BST T;
	struct node *root = NULL;
	root = T.insert(root, "1");
	root = T.insert(root, "2");
	root = T.insert(root, "3");
	root = T.insert(root, "4");
	root = T.insert(root, "10");

    T.search(root, "3");
    // T.inorder(root);
	// T.deleteNode(root, "4");
	// T.inorder(root);
	// T.deleteTree(root);


};