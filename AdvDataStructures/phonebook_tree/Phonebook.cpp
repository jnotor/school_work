#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>

struct Person {
    std::string firstname;
    std::string lastname;
    std::string number;
    Person* left, * right;
};

class Book {
public:
    // Constructor
    Book() { struct Person* root = NULL; }

    /**
     * Method to add a new Person node to the Book.
     *
     * param lastname: string of Person's lastname
     * param firstname: string of Person's firstname
     * param number: string of Person's number
     *
     * return Person: Person added to Book
     */
    Person* Add(struct Person* Person, std::string lastname, std::string firstname, std::string number) {
        // Base Case: empty node found
        if (Person == NULL) {
            Person = new struct Person;
            Person->firstname = firstname;
            Person->lastname = lastname;
            Person->number = number;
            Person->left = Person->right = NULL;

            return Person;
        }

        // Otherwise, recur down the tree
        if (lastname < Person->lastname) {
            Person->left = Add(Person->left, lastname, firstname, number);
        }
        else if (lastname > Person->lastname) {
            Person->right = Add(Person->right, lastname, firstname, number);
        }
        else if (firstname < Person->firstname) {
            Person->left = Add(Person->left, lastname, firstname, number);
        }
        else if (firstname > Person->firstname) {
            Person->right = Add(Person->right, lastname, firstname, number);
        }
        else {
            // User added existing Person; Notify and change
            std::cout << "\nUser entered already existed in Phonebook. Updating information" << std::endl;
            this->Change(root, lastname, firstname, number);
        }

        return Person;
    }


    /**
     * Method to update a Person node's number information
     *
     * param lastname: string of Person's lastname
     * param firstname: string of Person's firstname
     * param number: string of number to change the Person node's number value to
     *
     * return root: Person node that was updated
     */
    Person* Change(struct Person* root, std::string lastname, std::string firstname, std::string number) {
        // Find target person to change number of
        struct Person* temp = this->Find(root, lastname, firstname);

        if (temp != NULL) {
            // modify number
            temp->number = number;
        }

        return temp;
    }


    /**
     * Method to remove a Person from the Book.
     *
     * param root: starting point to look for Person to Delete
     * param lastname: string of Person's lastname
     * param firstname: string of Person's firstname
     *
     * return root: Person node that has assumed Deleted Person's position in Book
     */
    Person* Delete(struct Person* root, std::string lastname, std::string firstname) {
        // base case: couldnt find thing to delete
        if (root == NULL) {
            return root;
        }

        // If the name to be deleted is smaller than the root's name,
        // then it lies in left subtree
        if (lastname < root->lastname) {
            root->left = Delete(root->left, lastname, firstname);
        }
        else if (lastname > root->lastname) {
            root->right = Delete(root->right, lastname, firstname);
        }
        else if (firstname < root->firstname) {
            root->left = Delete(root->left, lastname, firstname);
        }
        else if (firstname > root->firstname) {
            root->right = Delete(root->right, lastname, firstname);
        }
        // We've found the person to delete
        else if (firstname == root->firstname && lastname == root->lastname) {
            if (root->left == NULL) {
                struct Person* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                struct Person* temp = root->left;
                delete root;
                return temp;
            }

            struct Person* temp = minValueNode(root->right);

            // Copy the inorder successor's content to this node
            root->lastname = temp->lastname;
            root->firstname = temp->firstname;
            root->number = temp->number;

            // Delete the inorder successor
            root->right = Delete(root->right, temp->lastname, temp->firstname);
        }

        return root;
    }


    /**
     * Method to delete whole Book to free up memory
     *
     * param Person: starting point for deletion, should be root
     */
    void DeleteBook(struct Person* Person) {

        if (Person == NULL) return;

        //first delete both subtrees
        DeleteBook(Person->left);
        DeleteBook(Person->right);

        // then delete the node
        std::cout << "Deleting node: " << Person->lastname << ", " << Person->firstname << std::endl;
        free(Person);
    }


    /**
     * Displays Phonebook contents in a Phonebook format using an inorder traversal
     *
     * param root: starting point for inorder traversal, should be root
     */
    void Display(Person* root) {
        if (root != NULL) {
            Display(root->left);
            std::cout << std::left << std::setw(20) << std::setfill(' ') << root->firstname << std::setw(20) << std::setfill(' ') << root->lastname << std::setw(20) << std::setfill(' ') << root->number << std::endl;
            Display(root->right);
        }
    }


    /**
     * Method to search through the BST, Book, until either no match is found or
     * a last and then first name match is found.
     *
     * param Person: struct Person to begin search from
     * param lastname: string of the person's lastname to search for/compare to
     *                 others
     * param firstname: string of the person's firstname to search for/compare to
     *                  others
     *
     * return ptr: returns nullptr if Person not in Book, else ptr to Person node
     */
    Person* Find(struct Person* root, std::string lastname, std::string firstname) {
        // Base Cases: root is null
        if (root == NULL) {
            std::cout << "Could not find: " << lastname << ", " << firstname << std::endl;

            return nullptr;
        }

        // Target Found
        if (root->lastname == lastname) {
            return root;
        }

        // Target not found, begin comparing last names
        if (root->lastname < lastname) {
            return Find(root->right, lastname, firstname);
        }
        else if (root->firstname > firstname) {
            return Find(root->left, lastname, firstname);
        }
        // last names same, compare first names
        else if (root->firstname < firstname) {
            return Find(root->right, lastname, firstname);
        }
        else {
            return Find(root->left, lastname, firstname);
        }
    }


    /**
     *  Save Phonebook contents in a Phonebook format using an preorder traversal
     *
     * param root: starting point for prerorder traversal, should be root
     * param saveloc: string holding full path of the text file that the phone book is being saved to
     */
    void SaveBook(Person* root, std::string saveloc) {
        std::ofstream outfile;

        outfile.open(saveloc, std::ios_base::app); //Open file in append mode
        outfile << std::left << std::setw(20) << std::setfill(' ') << root->lastname << std::setw(20) << std::setfill(' ') << root->firstname << std::setw(20) << std::setfill(' ') << root->number << std::endl;

        if (root->left != NULL)
            SaveBook(root->left, saveloc);
        if (root->right != NULL)
            SaveBook(root->right, saveloc);
    }


    /**
     *  Load Phonebook contents in the Phonebook tree
     *
     * param loadloc: string holding full path of the text file that the phone book is being loaded from, each lines is ordered: Last Name/First Name/Phone number
     *                A delimiter is required but the specific delimiter is irrelevent (ie. The delimiter seperating the three values can be: / , . \ ; : " " etc.)
     * return ptr: returns root node to the loaded tree
     */
    Person* LoadBook(std::string loadloc) {
        struct Person* root = NULL;
        std::string lastname;
        std::string firstname;
        std::string number;
        std::ifstream infile;

        infile.open(loadloc, std::ios::in); //open file in read mode

        while (infile >> lastname >> firstname >> number) {
            if ((lastname.find("Name") != true) || (lastname.find("Last") != true) || (firstname.find("First") != true) || (firstname.find("Name") != true) || (number.find("Phone") != true) || (number.find("Number") != true)) {
                root = Add(root, lastname, firstname, number);
            }
        }
        return root;
    }


    /**
     * Supporting function to Delete(). Finds the inorder successor, by name, of
     * node/"Person" to be deleted. Note: the entire tree does not need to be
     * searched.
     *
     * param Person: struct Person from which to begin search
     *
     * return current: Node with no left child, furthest from given Person
     */
    Person* minValueNode(Person* Person) {
        struct Person* current = Person;

        //loop down to find the leftmost leaf
        while (current->left != NULL)
            current = current->left;

        return current;
    }


    /**
     * Method returns the size of the tree a.k.a how many nodes
     *
     * param Person: Person struct to begin count from; should be root for correct size
     *
     * return int: size of Book from given Person node
     */
    int size(struct Person* Person) {
        if (Person == NULL)
            return 0;
        else
            return(size(Person->left) + 1 + size(Person->right));
    }


    ~Book() {}

private:
    Person* root;
};

class UserInterface {
public:
    UserInterface() {
        Book Phonebook;
        struct Person* root = NULL;
        bool EndInput = false;
        std::string firstname;
        std::string lastname;
        std::string number;
        struct Person* temp = NULL;
        int choice2 = 0;
        int choice = 0;

        std::cout << "Welcome to your phonebook." << std::endl;


        while (!EndInput) {
            std::cout << "Phonebook Menu" << std::endl;
            std::cout << "Type the number to choose" << std::endl;
            std::cout << "0: Load a Phonebook" << std::endl;
            std::cout << "1: Add a contact" << std::endl;
            std::cout << "2: Delete a contact" << std::endl;
            std::cout << "3: Find a contact" << std::endl;
            std::cout << "4: Change a contact" << std::endl;
            std::cout << "5: Display a contact" << std::endl;
            std::cout << "6: Quit" << std::endl;
            std::cin >> choice;


            switch (choice) {

            case 0:
                std::cout << std::endl << "Enter 1 to start a new phonebook or 2 to load a phonebook" << std::endl;
                std::cin >> choice2;
                if (choice2 == 1) {
                    root = NULL;
                }
                else if (choice2 == 2) {
                    std::string loadpath;
                    std::cout << "Enter an absolute path to where you would like to load the Phonebook: ";
                    std::cin >> loadpath;

                    // Save book out to text file
                    root = Phonebook.LoadBook(loadpath);
                }
                break;
            // Add
            case 1:
                std::cout << "Enter User firstname: \n";
                std::cin >> firstname;

                std::cout << "Enter User lastname: \n";
                std::cin >> lastname;

                std::cout << "Enter User number: \n";
                std::cin >> number;


                temp = Phonebook.Add(root, lastname, firstname, number);
                if (root == NULL) {
                    root = temp;
                }
                break;
            // Delete
            case 2:
                std::cout << "Enter User firstname: \n";
                std::cin >> firstname;

                std::cout << "Enter User lastname: \n";
                std::cin >> lastname;

                root = Phonebook.Delete(root, lastname, firstname);

                break;
            // Find
            case 3:
                std::cout << "Enter User firstname: \n";
                std::cin >> firstname;

                std::cout << "Enter User lastname: \n";
                std::cin >> lastname;

                root = Phonebook.Find(root, lastname, firstname);

                std::cout << root->firstname << "\t" << root->lastname << "\t" << root->number << std::endl;

                break;
            // Change
            case 4:
                std::cout << "Enter User firstname: \n";
                std::cin >> firstname;

                std::cout << "Enter User lastname: \n";
                std::cin >> lastname;

                std::cout << "Enter User number: \n";
                std::cin >> number;

                root = Phonebook.Change(root, lastname, firstname, number);

                break;
            // Display
            case 5:
                Phonebook.Display(root);
                break;
            // Quit and save
            case 6:
                if (root == NULL)
                {
                    EndInput = true;
                    break;
                }
                std::string path;
                std::cout << "Enter an absolute path to where you would like to save the Phonebook: ";
                std::cin >> path;

                // Save book out to text file
                Phonebook.SaveBook(root, path);
                // Free up the memory
                Phonebook.DeleteBook(root);
                EndInput = true;
                break;
            }
        }
    }
};


int main() {

    UserInterface();

};
