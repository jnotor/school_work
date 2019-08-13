//
//  SuperSimpleLinkedList.cpp
//  SuperSimpleLinkedList project
//
//  Created by Michael Haas on 1/2/13.
//  Copyright (c) 2013 Data Structures. All rights reserved.
//
//  Really, really simple linked list demo
//  First, adds two nodes directly in main()
//  Next, append two more nodes by calling a function

#include <iostream>

using namespace std;

struct Node
{int value;           // The integer value in this node
    Node *next;          // To point to the next node
};

// prototypes
void displaylist( Node * start);
void linkedListAppend(Node * & headPtr, int newItem);


int main(int argc, const char * argv[])
{
    Node *head = NULL;             // pointer to start of list
    Node *newNode = NULL;          // pointer to a new node
    Node *nodePtr;                 // pointer to previous node; use to move through the list
    
    cout << endl << endl;
    cout << "Really, really simple Linked List demo." << endl;
    cout << "---------------------------------------" << endl << endl;
    
    // Allocate three nodes and store some data there.
    
    cout << "Adding the first node from main()." << endl;
    
    newNode = new Node;             // first node
    newNode->value = 10;            // first node
    newNode->next = NULL;           // first node
    
    head = newNode;                 // start-of-list pointer
    nodePtr = head;                 // this node becomes the "previous" node
    
    cout << "Adding the second node from main()." << endl;
    
    newNode = new Node;             // second node
    nodePtr->next = newNode;        // pointer to second node
    newNode->value = 20;            // second node
    newNode->next = NULL;           // second node
    
    nodePtr = newNode;              // this node becomes the "previous" node
    
    // display original list
    displaylist( head );

    // call the linkedListInsert function to add a node
    linkedListAppend(head, 2000);
    
    // call the linkedListInsert function to add a node
    linkedListAppend(head, 3000);
    
    // display changed list
    displaylist( head );
    
    return 0;
}

void displaylist( Node * headPtr)
{
    // display the values of each node in the linked list
    // note headPtr passed in by value since it won't be changed
    
    Node * nodePtr;                 // pointer to current node
    nodePtr = headPtr;              // set pointer to start-of-list
    int nodecount = 0;              
    
    cout << endl;
    cout << "Linked List values." << endl;
    cout << "-------------------" << endl << endl;
    
    if (headPtr == NULL)              // if nothing to display
        cout << endl << "No nodes in the list" << endl;
    
    while (nodePtr != NULL)         // display the nodes' values
    {
        cout << "Node " << nodecount << " value is: " << nodePtr->value << endl;
        nodePtr = nodePtr->next;    // set current pointer to point to next node
        nodecount++;                // increment node counter
    }
    
    cout << endl;
    
}

void linkedListAppend (Node * &headPtr, int newItem)
{
    // add a node to the end of the linked list
    // note &headPtr passed in by reference; if fist node, this gets changed
    
    Node * newNode = NULL;          // pointer to a new node
    Node * nodePtr;                 // pointer to current node
    nodePtr = headPtr;              // set pointer to start-of-list
    
    // Add a new node
    newNode = new Node;             // new node
    newNode->value = newItem;       // add data
    newNode->next = NULL;           // in case it's end-of-list

    cout << endl << "Appending a node from linkedListAppend()." << endl;
    
    if (headPtr == NULL)            // first node in list
    {
        headPtr = newNode;          // set start-of-list pointer
        return;                     // nothing else to do
    }
    
    // not the first node in list, so find the end of the list
    while (nodePtr->next != NULL)   // end of list?
        nodePtr = nodePtr->next;    // set current pointer to point to next node
    
    nodePtr->next = newNode;        // previous node points to new node
    
    return;
    
}

