// Player Class Function Declarations
// Class Description:
	// This class will be accessed in order to handle both players and monsters' stats: HP, AC, to hit, avg dmg on hit
	//maybe priority? maybe spell slots, maybe spell save dc and other stats to allow it to spell save
	
#pragma once																	// This command is designed to cause the current source file to be included only once in a single compilation

#include <iostream> 
#include <string> 
#include <ctime>

using namespace std;

#ifndef PLAYERDND2_H
#define PLAYERDND2_H

class PlayerDND2 {
	public:
		PlayerDND2();																// Declaration of Player Class Default Constructor
		PlayerDND2(int, int, int, int,int, bool,string);												//dec of player with passed base stats
		//void addHP(int);														probably wont need for simulation
		void loseHP(int);														//dec creature takes damage function
		int getHP() {
			return HP;
		}															//dec of function that returns current health
		int getAC() {
			return AC;
		}															//dec of function that returns current AC
		int getToHit() {
			return toHit;
		}															//dec of function that returns toHit
		int getAvgDmg() {
			return avgDmg;
		}														//dec of function that returns avg dmg on hit
		int getInt()   {
			return intiative;
		}
		int d20Roll() { //could 
			int dieRoll;
			srand(time(0));
    		dieRoll = rand() %20 + 1;
    		//cout << "Die Roll before Mod: " << dieRoll << endl;
    		//dieRoll = dieRoll + getToHit();
    		return dieRoll;
		}
		bool getParty()   {
			return party;
		}
		string getName()   {
			return name;
		}
		// PlayerDND operator=(const PlayerDND& rhs)   {
		// 	return (AC = rhs.AC & HP = rhs.HP & toHit = rhs.toHit & avgDmg = rhs.avgDmg & intiative = rhs.intiative);
		// }
	private:
		int AC, HP, toHit, avgDmg, intiative, intMod;												// Integer stats
		bool party;
		string name;
};

#endif

PlayerDND2::PlayerDND2() {																// Default constructor of the Player Class, sets initial score as 0 and initial chips as 200

	AC = 1;
	HP = 1;
	toHit = 0;
	avgDmg = 1;
	intiative = 1;
	intMod = 0;
	party = false;
}

PlayerDND2::PlayerDND2(int iAC, int iHP, int itoHit, int iavgDmg, int iIntMod, bool iParty, string iName)   {								//defined player being passed its base stats
	
	AC = iAC;
	HP = iHP;
	toHit = itoHit;
	avgDmg = iavgDmg;
	intMod = iIntMod;
	//int determine
		srand(time(0));
    	intiative = rand() %20 + 1;
    	intiative = intiative + intMod;
    party = iParty;
    name = iName;
	
}

void PlayerDND2::loseHP(int dmg) {
	HP -= dmg;
	return;
}