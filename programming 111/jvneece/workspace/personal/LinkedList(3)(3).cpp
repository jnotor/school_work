//
//  LinkedList.cpp
//  LinkedListBasic project
//
//  Created by michaelahaas on 10/2/12.
//  Copyright (c) 2012 MAH Technology Development. All rights reserved.
//

//  Implementation file

//  Creates a singly-linked list (forward links only)
//  containing links; each link contains an integer data
//  value and a pointer to the next link

#include <iostream>
#include <iomanip>
#include <string>

#include "LinkedList.h"

using namespace std;

//**********************************************************************************

LinkedList::LinkedList()                    // Constructor
{
    cout << "New Linked List Object\n" ;
    cout << "--- ------ ---- ------\n" ;
    cout << endl ;
    
    // initialize list pointers
    
    start       = NULL ;                    // pointer to start of list
    ptrnew      = NULL ;                    // pointer to new node
    ptrcurrent  = NULL ;                    // pointer to current node (tracking pointer)
    ptrprev     = NULL ;                    // pointer to previous node
    
    // debug steps; hardcode input to list (so you don't have to type)
    //    AppendNode(10);
    //    AppendNode(25);
    //    AppendNode(50);
    InsertNode(25);
    InsertNode(55);
    InsertNode(-35);
    InsertNode(0);
    InsertNode(-7);
    InsertNode(100);
    // end of debug steps
    
}   // end of LinkedList constructor

//**********************************************************************************

LinkedList::~LinkedList()                    // Destructor
{
    cout << endl;
    cout << "Linked List Object Destroyed\n" ;
    cout << "------ ---- ------ ---------\n" ;
    cout << endl ;
    
}   // end of LinkedList destructor

//**********************************************************************************

void LinkedList::AppendNode(int indata)
{
    // add the new node to the end of the linked list
    
    ptrnew = new node;                      // create a new node
    ptrnew->data = indata;                  // store the data value
    ptrnew->next = NULL;                    // pointer to next link (will be last link so NULL
    
    if( start == NULL )                     // if this is the FIRST node to be added
        start = ptrnew ;                    // set start-of-list pointer

    else                                    // NOT the first node to be added
    {
        ptrcurrent = start;                 // position tracking pointer at beginning of list
        
        // move to the end of the linked list
        while ( (ptrcurrent->next != NULL) )          // transverse the list
             ptrcurrent = ptrcurrent->next;           // current node now points to next node
        
        // now at the end of the list; ready to append the new node
        
        ptrcurrent->next = ptrnew;          // current node points to the new node
    }   // end else
    
    // debug step, uncomment next line to use
    cout << "Appended " << ptrnew->data << " to end of list." <<endl;     // debug step
    
    return;
    
}   // end Addnode function


//**********************************************************************************

void LinkedList::InsertNode(int indata)
{
    // add the new node in the linked list
    // node will be added AFTER the first node with a lower data value
    // use this function exclusively to create a sorted list, lowest to highest
    
    ptrnew = new node;                      // create a new node
    ptrnew->data = indata;                  // store the data value
    
    if( start == NULL )                     // if this is the ONLY node to be added
    {
        start = ptrnew ;                    // set start-of-list pointer
        ptrnew->next = NULL;                // also last link so NULL
        
        // debug step, uncomment next line to use
        cout << "Inserted " << ptrnew->data << " as first node. " << endl;     // debug step
    }
        
    else                                    // NOT the ONLY node to be added
    {
        ptrcurrent = start;                 // position tracking pointer at beginning of list
        ptrprev = NULL;                     // reset previous node pointer node
        
        // find the right place in the linked list, past first lower data value
        // transverse the list, skip any node with larger value
        while ( (ptrcurrent != NULL) && (ptrcurrent->data < indata) )
        {
            ptrprev = ptrcurrent;                   // record previous node pointer
            ptrcurrent = ptrcurrent->next;          // current node now points to next node
        }
        
        // now past a lower value; insert the node
        
        // if this is the FIRST NODE in the list, update start pointer
        if (ptrprev == NULL)                // no previous node so this must be the first one
        {
            start = ptrnew ;                // start now points to the new node
            ptrnew->next = ptrcurrent;      // new start node now points to previous start node
            
            // debug step, uncomment next line to use
            cout << "Inserted " << ptrnew->data << " at start, before "
                 << ptrcurrent->data << endl;     // debug step

        }   // end if
        
        // otherwise, insert new node after node with smaller value
        else
        {
            ptrprev->next = ptrnew;          // previous node points to the new node
            ptrnew->next = ptrcurrent;       // new node points to next node
            
            // debug step, uncomment next line to use
            cout << "Inserted " << ptrnew->data << " after "
            << ptrprev->data  << endl;     // debug step
        }   // end else
        
    }   // end else
    
    return;
    
}   // end Addnode function


//  ************************************************************************************

void LinkedList::GetInteger()           // Get integer data from user
{
    bool more = true ;                  // continue indicator
    string inputstring;                 // string input (avoid cin problems)
    inputdata = 0;                      // default input value
     
    while( more )                       // until user is done
    {
        // get data from user
        
        cout << endl << "Enter an integer value: " ;
        getline(cin, inputstring);              // get the data as string
        inputdata = atoi(inputstring.c_str());  // convert to integer
        
        if ((inputdata == 0 ) && (inputstring != "0") )   // error check
        {
            // if user input a 0, then ok; otherwise atoi is an error
            cout << inputstring << " is invalid!  Try again." << endl;
            continue;
        }
    
        // AppendNode(inputdata);               // append the node
        InsertNode(inputdata);                  // insert the node
        
        more = Continue();                      // prompt user to continue
        
    }   // end while
    
    cout << endl ;
    
    return;
    
}   // end GetInteger function

//  ************************************************************************************

void LinkedList::ShowList()
{
    // this function displays the entire linked list (just the values)
    
    int nodecounter = 0;            // node number
    ptrcurrent = start;             // point to first node
    
    cout << fixed << left << endl;
    cout << "Node #" << "     " << "Data Value" << endl;
    cout << "---- -" << "     " << "---- -----" << endl;
    
    if ( start == NULL)
        cout << endl << "No nodes in the list." << endl;
    
    while( ptrcurrent != NULL )                                 // until no node
    {
        cout << setw(7) << nodecounter++ << "     " ;           // output node number
        cout << ptrcurrent->data << endl;                       // output data value
        ptrcurrent = ptrcurrent->next;                          // point to next node
    }
    
    cout << endl;
    
   }   // end ShowList function

//  ************************************************************************************

bool LinkedList::Continue()
{
    // this function prompts the user to continue and returns true (if Y) or false (if N)
    
    string  answer;                          // user input
    char    charanswer;
    
    do                                      // enter more nodes or done?
    {
        cout << "Enter another node? (Y/N) ==> " ;
        getline(cin, answer);
        if (answer.length() == 0)
            continue;
        charanswer = toupper(answer[0]);
    } while (charanswer != 'Y' && charanswer != 'N') ;   // must enter Y y N n
    
    if (charanswer == 'Y')
        return true;
    else
        return false;
    
}   // end Continue function

//  ************************************************************************************

void LinkedList::DeleteList()
{
    // this function deletes the entire list and de-allocates the memory
    
    int nodecounter = 0;            // node number
    ptrcurrent = start;             // point to first node
    
    while( ptrcurrent != NULL )                                 // until no node
    {
        ptrprev = ptrcurrent;                                   // copy pointer to this node
        ptrcurrent = ptrcurrent->next;                          // point to next node
        delete ptrprev;                                         // delete previous one
        nodecounter++;                                          // count
    }
    start = NULL;
    
    cout << endl << "Deleted " << nodecounter << " nodes." << endl;

}
