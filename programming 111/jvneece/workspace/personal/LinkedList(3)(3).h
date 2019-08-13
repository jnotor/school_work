//
//  LinkedList.h
//  LinkedListBasic project
//
//  Created by michaelahaas on 10/2/12.
//  Copyright (c) 2012 MAH Technology Development. All rights reserved.
//

#ifndef __LinkedListBasic__LinkedList__
#define __LinkedListBasic__LinkedList__

//  Creates a singly-linked list (forward links only)
//  Each link contains an integer data
//  value and a pointer to the next link

//  Header file


// Creating a class called LinkedList
class LinkedList
{
    
private:
    //   Creating a NODE Structure (a node is a link in the list)
    struct node
    {
        int data;               // data held in the linked list
        node *next;             // pointer to next node (NULL if last node)
    };

    // private attributes (properties)
    node *start;        // pointer to start of list
    node *ptrnew;       // pointer to new node
    node *ptrcurrent;   // pointer to current node (while transversing)
    node *ptrprev;      // pointer to previous node

    int inputdata;      // data entered by user
    
    // private methods
    void AppendNode(int indata);      // add new link to list
    void InsertNode(int indata);      // insert a link (sorted low-to-high
    bool Continue();                  // function to prompt user to continue (or not)
    
public:
     
    // methods
    LinkedList();                       // constructor
    ~LinkedList();                      // destructor
    
    void DeleteList();                  // delete the entire list
    void GetInteger();                  // prompts user for data (one link)
    void ShowList();                    // display all the values in the list
    
};

#endif /* defined(__LinkedListBasic__LinkedList__) */
