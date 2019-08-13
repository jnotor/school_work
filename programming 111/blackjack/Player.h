// Player Class Function Declarations
// Class Description:
	// This class will be accessed in order to add to the score of the player/dealer, deal with betting for the player,
	// and will be used to be returning the score of the player/dealer
#pragma once																	// This command is designed to cause the current source file to be included only once in a single compilation

#include <iostream> 
#include <string> 

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {
	public:
		Player();																// Declaration of Player Class Default Constructor
		void addScore(int);														// Declaration of the function that would add to the score of the user, takes next card value as parameter
		int getScore();															// Declaration of the function that would return the score of the player
		void placeBet(int);														// Declaration of the function that would subtract bet from total money of player
		int getBet();															// Declaration of the function that would return the total chips of the player
		bool bustChecker(int, bool, bool&, bool&);								// Declaration of the function that would determine if the player busts or not
	private:
		int score, bet;															// Integer that stores the score of the player and the bet of the player
};

#endif

Player::Player() {																// Default constructor of the Player Class, sets initial score as 0 and initial chips as 200

	score = 0;
	bet = 200;
}

void Player::addScore(int value) {												// Definition of function that would add to the score of the player, takes a card value as a parameter

	score += value;
	return;
}

int Player::getScore() {														// Definition of function that returns the score of the player

	return score;
}

void Player::placeBet(int money) {												// Definition that subtracts bet from total chips
	
	bet -= money;
}

int Player::getBet() {															// Definition of the function that would return the bet of the player

	return bet;
}

bool Player::bustChecker(int score, bool aceFlag, bool &validResponse, bool &flag) {
	
	bool busted = false;														// Definition of the function that checks to see if the player busts, based on if ace is present
	if (!aceFlag) {
		if (score > 21) {
			busted = true;
		}
	}
	return busted;
}