//
//  lindedlistclient.cpp
//  LinkedListBasic Project
//
//  Created by michaelahaas on 10/2/12.
//  Modified 1/14/2013
//  Copyright (c) 2012 MAH Technology Development. All rights reserved.
//
#include <iostream>
#include "LinkedList.h"

using namespace std;

// ***********************************************
// main - client application starts here
// tests the LinkedList class
// ***********************************************


int main(int argc, const char * argv[])
{
    // this program tests the LinkedList class
    
    cout << endl << endl << endl ;
    cout << "******************************************" << endl ;
    cout << "              Linked Lists"                 << endl ;
    cout << "******************************************" << endl ;
    cout << endl;
    
    cout << "****** Object Creation (hard-coded input) *****" << endl << endl;
   
    // create a linked list object
    LinkedList l1;
    
    cout << endl;
    cout << "********** User input Demo **********" << endl << endl;
    
    l1.GetInteger();    // get a value from the user
    
    cout << "********** Display Demo **********" << endl << endl;
    
    l1.ShowList();      // show the list
        
    cout << "********** Delete Entire List Demo **********" << endl << endl;
    
    l1.DeleteList();    // delete the list
    
    l1.ShowList();      // show the list
    
    cout << endl << "Thank you for using the Linked List Basic App.  Good-bye." << endl << endl;
    
    return 0;
}

