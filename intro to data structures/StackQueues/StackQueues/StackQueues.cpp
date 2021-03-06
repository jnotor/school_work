// StackQueues.cpp : Defines the exported functions for the DLL application.
//

#include "header.h"
#include "StackQueues.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////STACKS
ArrayBasedStack::ArrayBasedStack() {
	//default constructor
	//need to initialize 1 stack with values in it and 2 without (2 without are in the class dec) ; no this belongs in the TOH file, for this, we only need one stack
	//tower_start[4] = { 4, 3, 2, 1 }; - can stay initialized as empty, because, for the TOH file, we can push a bunch of stuff in
}


bool ArrayBasedStack::isEmpty() const {
	//check to see if the stack is empty, which is defined as having no non-zero, positive numbers
	//for (int i = 0; i < 4; ++i) {
	//	if (tower[i] > 0) {
	//		return false;
	//	}
	//}
	if (s_count != 0) {
		return false;
	}
	return true;
}

bool ArrayBasedStack::isFull() {
	//determine if the stack is full
	if (s_count == 4) {
		return true;
	}
	return false;
}

int ArrayBasedStack::peek() //is top
//If the ADT is empty throw an exception indicating this
{
	int peekedVal = 0;

	if (this->isEmpty())
	{
		throw "ADT is emtpy";
		//return false;
	}
	else
	{
		peekedVal = tower[s_count-1];
	}
	return peekedVal;
}

bool ArrayBasedStack::push(int val) {
	//check to see if target stack is full, if not, add an item to the stack
	if (this->isFull() == true) {
		cout << "The stack is full" << endl;
		return false;
	}
	//cout << "push scount before going into tower: " << s_count << endl;
	tower[s_count] = val;
	//cout << "push scount: " << s_count << endl;
	++s_count;
	return true;
	//should we be using peek here? why for push? just to know what's on top?
}

bool ArrayBasedStack::pop() {
	//check to see if there is an item on the top of the stack, if so, display it and remove the item off the top of the stack, else show an error message
	//int poppedVal = 0;

	//this->peek();//should we be using peek here?

	if (this->isEmpty()) {
		//throw "ADT is empty";
		return false;
	}
	else {

		//poppedVal = tower[s_count];
		--s_count;
		//cout << "pop'd scount: " << s_count << endl;
		tower[s_count] = 0;
		
	}
	return true;

}

int ArrayBasedStack::length() { //size
//return number of items on the stack
	int count = 0;

	for (int i = 0; i < 4; ++i) {
		if (tower[i] > 0) {
			++count;
		}
	}
	return count;
}

void ArrayBasedStack::viewTower() { //added function to make user able to see towers in game
	for (int i = 3; i >= 0; --i) {
		cout << tower[i] << endl;
	}
}
void ArrayBasedStack::Empty() {
	//empty the stack of all contents
	for (int i = 0; i < 4; ++i) {
		tower[i] = 0;
	}
}

/*string ArrayBasedStack::toString() {
//print the stack so it can be visualized
string TowerString = to_string(tower[3]);

for (int i = 2; i >= 0; --i) {
	TowerString = TowerString + '\n' + to_string(tower[i]);
	}
return TowerString;
}*/

ArrayBasedStack::~ArrayBasedStack() {
	//default destructor
}


////////////////////////////////////////////////////////////////////////////////////////////////////QUEUES

ArrayBasedQueue::ArrayBasedQueue() {
	//todo
}

bool ArrayBasedQueue::isEmpty() const {
	if (moveCount == 0) {
		return true;
	}
	return false;
}

bool ArrayBasedQueue::enQueue(std::string val) {
	//todo input should be disk,fromcol,tocol
	if (moveCount > 99) { //returns false if the moves are full, which it should likely never be since we've given 100 moves; could make this a function, but seems redundant/pointless
		cout << "The queue is full, please deQueue some moves.";
		return false;
	}


	moveList[moveCount] = val;
	++moveCount;
	return true;
}
bool ArrayBasedQueue::deQueue() {
	//todo
	//remove something in queue based on its position
	if (this->isEmpty()) {
		return false;
	}

	for (int i = 0; i < 99; ++i) {
		moveList[i] = moveList[i+1];
	}
	--moveCount;
	return true;
}

std::string ArrayBasedQueue::peekFront()
{//If the ADT is empty throw an exception indicating this
	if (this->isEmpty())
	{
		throw "ADT is emtpy";
	}
	else
	{
		cout << "The move at the front of the list is: ";
		return moveList[0];
	}


}

void ArrayBasedQueue::toString() { 
	ofstream moves;
	moves.open("moves.txt");
	cout << "This is the list of moves: "<< endl;
	for (int i = 0; i < 100; ++i) {
		cout << moveList[i] << endl;
		moves << moveList[i] << endl;

	}
	moves.close();
}

ArrayBasedQueue::~ArrayBasedQueue() {
	//todo
}