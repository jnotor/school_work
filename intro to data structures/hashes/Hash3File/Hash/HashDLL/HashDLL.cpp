// HashDLL.cpp : Defines the exported functions for the DLL application.
//

#include "header.h"
#include "HashDLL.h"
#include <iostream>
#include <cmath>
 
using namespace std;

Hashtable::Hashtable() {
	//default set to 100 in lab doc?
	/*
	max = 100;
	count = 0;
	////have to fill the vector with a number of null ptrs = max items
	for (int i = 0; i < max; i++) {
		List.push_back(nullptr);
	}
	*/
}

Hashtable::Hashtable(int maxNum) {
	max = maxNum;
	count = 0;
	////have to fill the vector with a number of null ptrs = max items
	for (int i = 0; i < max; i++) {
		List.push_back(nullptr);
	}
}

bool Hashtable::AddItem(std::string tkey, int tdata) {
	if (count == max) {
		cout << "At specified maximum capacity" << endl;
		return false;
	}
	int position;
	//create node
	Node *temp = new Node(tkey, tdata);
	//hash the node to determine where it will go
	position = Hash(temp);
	//find the spot in the list it has to go
	for (int i = 0; i <= position; i++) {
		//push a pointer to the node into the vector at that position
		if (i == position) {
			if (List.at(i) == nullptr) {
				List.at(i) = temp;
				count += 1;
				return true;
			}
			else { //if you dont find a null in the first spot, find the next sequential spot that doesnt 
				while (List.at(i) != nullptr) {
					if (List.at(i)->key == temp->key) {
						cout << "Duplicate key string. Please try again" << endl;
						return false;
					}
					i++;
					if (i == max) {
						i = 0;
					}
				}
				List.at(i) = temp;
				count += 1;
				return true;
			}
		}
	}
	//somehow didnt add; maybe full
	return false;
}

Node * Hashtable::GetItem(string key) {
	Node *temp = new Node(key);
	int position;
	//hash a temporary node with the search key
	position = Hash(temp);
	//see if the node in the list at that position has the same string key
	if (List.at(position) != nullptr) {
		if (*List.at(position) == *temp) {
			return List.at(position);
		}
		else { //no? while they dont, keep iterating the through the list til you find it or you do the whole thing once
			int i = position;
			while (*List.at(i) != *temp) {
				++i;
				//preventing infinite loop; once i == position again, give up
				if (i == position) {
					return nullptr;
				}
				//if you get to end of the list, go to the begining
				if (i == max)
				{
					i = 0;
				}
				if (List.at(i) == nullptr) {
					return nullptr;
				}
			}
			return List.at(i);
		}
	}
	else {
		return nullptr;
	}
}

int Hashtable::Hash(Node * temp) {
	int sum = 0;
	for (int i = 0; i < temp->key.size(); i++) {
		sum = temp->key.at(i) + sum;
	}
	sum = sum % max;
	return sum;
}

Hashtable::~Hashtable(){
	//pop all the items from the vector while its not empty
	while (!List.empty()) {
		List.pop_back();
	}
}
