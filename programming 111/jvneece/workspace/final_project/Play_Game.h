// Play_Game Class Function Declarations
// Class Description: 
	// This Class is used for the logic of the game and the actual playing of the game. This class refers to the Player class and the Deck Class
#pragma once

#include "Deck.h"
#include "Player.h"

#include <iostream>

using namespace std;

#ifndef PLAY_GAME_H
#define PLAY_GAME_H

class Play_Game {
public:
	Play_Game();
	void playGame();
	void initializeBets();
	void initializeHands();
	void insurance();
	void dealerSecond(); 
	void checkBJ();
	void gameMenu();
	void dealerTurn();
	void displayScores(int, int);
	void results();
	void postRoundInfo();
	void resets();
private:
	int funds, holdFunds, playerBet, insuranceBet, value, roundsPlayed, firstCard, secondCard, dFirstCard, dSecondCard, BJcount, menuChoice, round;
	bool validResponse, flag, flag2, aceFlag, dealerAceFlag;
	char yes_or_no;
	Player user;
	Player dealer;
	Deck gameDeck;
};

#endif

// Play_Game Class function definitions

#include "Play_Game.h"

Play_Game::Play_Game() {
	funds = 200;
	holdFunds = 0;
	playerBet = 0;
	insuranceBet = 0;
	value = 0;
	roundsPlayed = 0;
	firstCard = 0;
	secondCard = 0;
	dFirstCard = 0;
	dSecondCard = 0;
	BJcount = 0;
	menuChoice = 0;
	round = 0;
	validResponse = false;
	flag = false;
	flag2 = false;
	aceFlag = false;
	dealerAceFlag = false;
	yes_or_no = 'y';
}

void Play_Game::playGame() {
	cout << "You start with " << funds << " chips to bet with. Bets will be placed in whole numbers, rounded down." << endl << endl;
	while (funds > 0) {
		cout << "Would you like to play a round of Blackjack? (y for yes, any other character for no) " << endl;
		cin >> yes_or_no;
		if (yes_or_no == 'y') {
			gameDeck.setDeck();
			round = 4;  
			initializeBets();
			initializeHands();
			//insurance();
			dealerSecond(); //this function doesnt add to the score, except for when it randomly does...
			//checkBJ();
			displayScores(user.getScore(), dealer.getScore());
			gameMenu();
			dealerTurn();
			displayScores(user.getScore(), dealer.getScore());
			results();
			postRoundInfo();
			resets();
		}
		else {
			funds = 0;
			postRoundInfo();
			cout << funds;
		}
	}
}

void Play_Game::initializeBets() {
	cout << "Place your bet: " << endl;
	cin >> playerBet;
	while ((playerBet > user.getBet()) || (playerBet < 1)) {
		cout << "Invalid number of chips to bet. Please place a bet less than or equal to the number of chips you have." << endl;
		cin >> playerBet;
	}
	user.placeBet(playerBet);
}

void Play_Game::initializeHands() {
	cout << "Your starting hand is: " << endl;
	firstCard = gameDeck.getNextCard(0, user.getScore());
	aceFlag = gameDeck.aceChecker(firstCard);
	cout << "and ";
	secondCard = gameDeck.getNextCard(1, user.getScore());
	
	if (!aceFlag) {
		aceFlag = gameDeck.aceChecker(secondCard);
	}
	
	user.addScore(firstCard + secondCard);
	cout << endl;

	if (firstCard + secondCard == 21) {
		BJcount += 1;
	}

	// if (firstCard==secondCard)   {
	// 	cout << "You've got a pair. Want to Split? (y for yes, any other character for no)" << endl;
	// 	cin >> y_or_n2;
	// 	if (y_or_n2 = 'y')   {

	// 	}
	// 	else {

	// 	}
	// } 

	cout << "The dealer is showing a ";
	dFirstCard = gameDeck.getNextCard(2, dealer.getScore());
	dealerAceFlag = gameDeck.aceChecker(dFirstCard);
	dealer.addScore(dFirstCard);
}

// void Play_Game::insurance() {
// 	if (dealer.getScore() == 11) {
// 		cout << "Would you like to take insurance against the Dealer's potential Blackjack? (y for yes, any other character for no)" << endl;
// 		cin >> yes_or_no;
// 		if (yes_or_no == 'y') {
// 			cout << "Insurance against Dealer Blackjack is paid out 2:1. How much would you like to bet on Insurance? " << endl;
// 			cin >> insuranceBet;
// 			while ((insuranceBet > user.getBet()) || (insuranceBet < 1)) {
// 				cout << "Invalid number of chips to bet. Please place a bet less than or equal to the number of chips you have." << endl;
// 				cin >> insuranceBet;
// 			}
// 			user.placeBet(insuranceBet);
// 			cout << "Okay, " << insuranceBet << " chips bet as insurance." << endl;
// 		} else {
// 			cout << "Okay, no insurance it is." << endl;
// 		}
// 	}
// }

void Play_Game::dealerSecond() {
	dSecondCard = rand() % 11;
	if (dSecondCard == 1) {
		dSecondCard = 11;
	}
	if (!dealerAceFlag) {
		dealerAceFlag = gameDeck.aceChecker(dSecondCard);
	}
	//dealer.addScore(dSecondCard);
}

// void Play_Game::checkBJ() {
// 	if (dFirstCard + dSecondCard == 21) {
// 		BJcount += 10;
// 	}
// 	if (BJcount == 1) {
// 		cout << "Blackjack! You win!" << endl;
// 		playerBet = (0 - playerBet)*2.5;
// 		user.placeBet(playerBet);
// 		cout << "User chips total: " << user.getBet() << endl;
// 		flag = false;
// 	}
// 	else if (BJcount == 10) {
// 		if (yes_or_no == 'y') {
// 			cout << "Wow! Guess your insurance paid off!" << endl;
// 			insuranceBet = (0 - insuranceBet) * 2;
// 			user.placeBet(insuranceBet);
// 			cout << "User chips total: " << user.getBet() << endl;
// 		} else {
// 			cout << "Dealer has Blackjack! You Lose!" << endl;
// 			cout << "User chips left currently: " << user.getBet() << endl;
// 		}
// 		flag = false;
// 	} else if (BJcount == 11) {
// 		cout << "Push! You and the Dealer both have a Blackjack!" << endl;
// 		playerBet = (0 - playerBet);
// 		user.placeBet(playerBet);
// 		flag = false;
// 	}
// }

void Play_Game::displayScores(int userScore, int dealerScore) {
	cout << endl << "Your Score: " << userScore << endl;
	cout << "Known Dealer Score: " << dealerScore << endl;
}

void Play_Game::gameMenu() {
	validResponse = false;
	while (!validResponse) {
		cout << endl << "What would you like to do? " << endl;
		cout << "	1 = Hit" << endl;
		cout << "	2 = Stand" << endl;
		cout << "	3 = Surrender" << endl;
		cout << "	4 = Double Down" << endl;
		cin >> menuChoice;
		switch (menuChoice) {
			case 1:
				cout << "You Drew: " << endl;
				value = gameDeck.getNextCard(round, user.getScore());
				user.addScore(value);
				round += 1;
				if (!aceFlag) {	
					aceFlag = gameDeck.aceChecker(value);
				}
				if (user.getScore() > 21) {
					// if (aceFlag) {
					// 	cout << "Your Ace must be counted as a 1 in order to avoid Busting. Changing score now... " << endl;
					// 	user.addScore(0 - 10);
					// 	cout << "New Score is: " << user.getScore() << endl;
					// 	aceFlag = false;
					// }
					// else {
						cout << "Bust! You Lose!" << endl;
						cout << "User chips left currently: " << user.getBet() << endl;
						flag = false;
					}
				//}
				break;
			case 2:
				validResponse = true;
				break;
			case 3:
				playerBet = (0 - playerBet) / 2;
				user.placeBet(playerBet);
				validResponse = true;
				flag = true;
				flag2 = true;
			// case 4:
			// 	cout << "Doubling Down..." << endl;
			// 	playerBet *= 2;
			// 	cout << "Bet is now: " << playerBet << endl;
			// 	user.placeBet(playerBet);
			// 	cout << "Drawing next card..." << endl;
			// 	cout << "You Drew: " << endl;
			// 	value = gameDeck.getNextCard(round, user.getScore());
			// 	user.addScore(value);
			// 	validResponse = true;
			// 	round += 1;
			// 	if (user.getScore() > 21) {
			// 		cout << "Bust! You Lose!" << endl;
			// 		cout << "User chips left currently: " << user.getBet() << endl;
			// 		flag = false;
			// 	}
			// 	break;
			default:
				cout << "Invalid input, please enter a valid input." << endl;
		}
	}
}

void Play_Game::dealerTurn() {
	if (flag) {
		dealer.addScore(dSecondCard);
		cout << "Dealer flips card and his score is now: " << dealer.getScore() << endl;
		while (dealer.getScore() < 17) {
			cout << endl << "Dealer Drew: " << endl;
			value = gameDeck.getNextCard(round, dealer.getScore());
			dealer.addScore(value);
			round += 1;
			cout << endl;
		}
		if (dealer.getScore() < 22) {
			cout << "Dealer can no longer draw." << endl;
		} 
		// else if (dealerAceFlag) {
		// 	dealer.addScore(0 - 10);
		// 	dealerAceFlag = false;
		// }
		else {
			cout << "Dealer Busts! " << endl;
		}
	}
}

void Play_Game::results() {
	if (dealer.getScore() > 21) {
		cout << "You Win! " << endl;
		playerBet = (0 - playerBet) * 2;
		user.placeBet(playerBet);
		cout << "User chips total: " << user.getBet() << endl;

	} else if (dealer.getScore() == 21) {
		cout << "You Lose! " << endl;
		cout << "User chips left currently: " << user.getBet() << endl;

	} else if (dealer.getScore() > user.getScore()) {
		cout << "You Lose! " << endl;
		cout << "User chips left currently: " << user.getBet() << endl;

	} else if (dealer.getScore() == user.getScore()) {
		cout << "Push! " << endl;
		playerBet = 0 - playerBet;
		user.placeBet(playerBet);

	} else {
		cout << "You Win! " << endl;
		playerBet = (0 - playerBet) * 2;
		user.placeBet(playerBet);
		cout << "User chips total: " << user.getBet() << endl;
	}
	flag = false; //might not need
}

void Play_Game::postRoundInfo() {
	funds = user.getBet();
	holdFunds = funds;
	if (yes_or_no =~ 'y') {
		funds = 0;
		flag2 = true;
	}
	if ((!flag2) && (funds < 1)) {
		cout << "You're out of funds! Thanks for playing! Goodbye!" << endl;
	} else if (flag2) {															
		cout << "You have " << holdFunds << " chips. Thanks for playing!" << endl;
	} else {
		roundsPlayed += 1;
		cout << "Rounds played: " << roundsPlayed << endl;
	}
}

void Play_Game::resets() {
	if (!flag2) {
		funds = user.getBet();
	}
	holdFunds = 0;
	playerBet = 0;
	insuranceBet = 0;
	value = 0;
	firstCard = 0;
	secondCard = 0;
	dFirstCard = 0;
	dSecondCard = 0;
	BJcount = 0;
	menuChoice = 0;
	round = 0;
	validResponse = false;
	flag = false;
	flag2 = false;
	aceFlag = false;
	dealerAceFlag = false;
	yes_or_no = 'y';
	user.addScore(0 - user.getScore());
	dealer.addScore(0 - dealer.getScore());
}