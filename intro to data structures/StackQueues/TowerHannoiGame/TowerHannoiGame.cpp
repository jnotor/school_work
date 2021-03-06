// TowerHannoiGame.cpp : Defines the entry point for the console application.

#include <StackQueues.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TowersOfHannoiGame
{
public:
	TowersOfHannoiGame() : m_GameEnded(false) {//what is this intended to do?
			//todo? ; no its just setting the variable to false
	}
	bool IsGameEnded(ArrayBasedStack Mid_stack, ArrayBasedStack R_stack) {
			if (Mid_stack.length() == 4) {
				cout << "Game won!" << endl;
				return true;
			}
			if (R_stack.length() == 4) {
				cout << "Game won!" << endl;
				return true;
			}
			//m_GameEnded = false;
		return false; 
	}
	bool moveChecker(int diskId, int fromId, int toId, int ToSL, int ToSM, int ToSR) { //check and see that the moves are viable

		//int Lstack = 1, Mstack = 2, Rstack = 3;
		//Case 1: invalid disks or poles
		if (diskId > 4 || diskId < 1) {
			//cout << "error 1";
			return false;
		}
		else if (fromId >3 || fromId < 1) {
			//cout << "error 2";
			return false;
		}
		else if (toId > 3 || toId < 1) {
			//cout << "error 3";
			return false;
		}
		//case 2: trying to move a disk not on top
		switch (fromId) {
		case 1:
			if (diskId != ToSL) {
				//cout << "error 4";
				return false;
			}
			break;
		case 2:
			if (diskId != ToSM) {
				//cout << "error 5";
				return false;
			}
			break;
		case 3:
			if (diskId != ToSR) {
				//cout << "error 6";
				return false;
			}
			break;
		default:
			//cout << "error 7";
			cout << "You've entered a non-existent pole, please try again using only poles 1-3" << endl;
			return false;
		}
		//case 3: trying to put a bigger disk on top of a smaller disk
		switch (toId) {
		case 1: 
			if (diskId > ToSL) {
				return false;
			}
			break;
		case 2:
			if (diskId > ToSM) {
				return false;
			}
			break;
		case 3:
			if (diskId > ToSR) {
				return false;
			}
			break;
		default:
			break;
		}
		//cout << "got to end of checker";
		return true;
	}
	void PrintTowers(ArrayBasedStack L_stack, ArrayBasedStack Mid_stack, ArrayBasedStack R_stack)   {
		L_stack.viewTower();
		cout << "----Tower 1----" << endl;;
		Mid_stack.viewTower();
		cout << "----Tower 2----" << endl;;
		R_stack.viewTower();
		cout << "----Tower 3----" << endl;;
	}
private:
	bool m_GameEnded;

};

int main()
{
	cout << "Enter in moves to make for Towers  of  Hannoi" << endl;
	cout << "Progam will exit once towers have  been successfully moved of" << endl;
	cout << "or string of -1 is entered. Moves must be entired in format of" << endl;
	cout << "<disk>,<column from>,<column to>   NOTE no spaces!!!!" << endl;

	TowersOfHannoiGame game;

	//initializing the game stacks so we have something to play on
	ArrayBasedStack L_stack;
	ArrayBasedStack Mid_stack;
	ArrayBasedStack R_stack;

	//setting up that there are four disks, in descending order on the left most stack and 
	L_stack.push(4);
	L_stack.push(3);
	L_stack.push(2);
	L_stack.push(1);
	//setting initial, placeholder values in the other stacks so we can peek at them no matter what
	//Mid_stack.push(0);
	//R_stack.push(0);
	//giving ourselves a default queue for entering moves into
	ArrayBasedQueue ToHQ;
	bool receivedEndToken = false;

	while (!receivedEndToken && !game.IsGameEnded(Mid_stack,R_stack))
	{
		std::string inputLine; 
		game.PrintTowers(L_stack, Mid_stack, R_stack);
		cout << "Enter Move " << endl;
		getline(cin, inputLine); //taking it from cin and putting it into inputline

		if (inputLine == "-1")
		{
			receivedEndToken = true;
		}
		else
		{
			std::vector<std::string> output;
			std::string::size_type prev_pos = 0, pos = 0; //size_type; undetermined type like int, float, etc
			// Snippet from https://stackoverflow.com/questions/5167625/splitting-a-c-stdstring-using-tokens-e-g
			// tokenizing a string
			while ((pos = inputLine.find(",", pos)) != std::string::npos) //what is npos? am i supposed to implement? no, its a standard, no position
			{//if no , its been entered wrong
				std::string substring(inputLine.substr(prev_pos, pos - prev_pos));
				output.push_back(substring);
				prev_pos = ++pos;
			}
			//Need to get last token
			output.push_back(inputLine.substr(prev_pos, pos - prev_pos)); // Last word

			if (output.size() != 3)
			{
				receivedEndToken = true;
				cout << "Invalid input recieved = " + inputLine << endl;
			}
			else
			{
				std::string disk = output[0];
				std::string from = output[1];
				std::string to = output[2];

				if (disk.size() == 0 || from.size() == 0 || to.size() == 0)
				{
					receivedEndToken = true;
					cout << "Invalid input recieved = " + inputLine << endl;
				}

				int diskId = atoi(disk.c_str());
				int fromId = atoi(from.c_str());
				int toId = atoi(to.c_str());
				int ToSL = 5;
				int ToSM = 5;
				int ToSR = 5;
				//checking the top of each stack so we can pass that info to the move checker
				if (!L_stack.isEmpty()) {
					ToSL = L_stack.peek(); //cant peek at an empty stack
				}
				if (!Mid_stack.isEmpty()) {
					ToSM = Mid_stack.peek(); //can't peek a char
				}
				if (!R_stack.isEmpty()) {
					ToSR = R_stack.peek();
				}
				//this is where we want to insert our move checker function
				//if any number is zero we didn't have a integer
				if (diskId == 0 || fromId == 0 || toId == 0)
				{
					receivedEndToken = true;
					cout << "Invalid input recieved = " + inputLine << endl;
				}
				
				if (!game.moveChecker(diskId, fromId, toId, ToSL, ToSM, ToSR)) {
					cout << "Invalid move, try again" << endl << endl;
				}
				else {
					cout << "Disk " << diskId << " From " << fromId << " To " << toId << endl;
					//adding the move to the queue
					ToHQ.enQueue(inputLine);
					//now we need to pop the disk off the from stack
					switch (fromId) {
					case 1:
						L_stack.pop();
						break;
					case 2:
						Mid_stack.pop();
						break;
					case 3: 
						R_stack.pop();
						break;
					default: 
						break;
					}
					switch (toId) {

					case 1: 
						L_stack.push(diskId);
						break;
					case 2: 
						//Mid_stack.pop();
						Mid_stack.push(diskId);
						break;
					case 3: 
						R_stack.push(diskId);
						break;
					default: 
						break;
					}
					//game.PrintTowers(L_stack, Mid_stack, R_stack); redundant
				}
				
				


				

			}
		}
	}
	ToHQ.toString();
    return 0;
}

