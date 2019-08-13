
// combat functions
// Class Description:

#pragma once																	// This command is designed to cause the current source file to be included only once in a single compilation

#include <iostream> 
#include <string> 
#include "PlayerDND.h"

using namespace std;

#ifndef COMBAT_H
#define COMBAT_H

class Combat {
public:
	//Combat();																	//turning off default for now
	Combat(PlayerDND, PlayerDND);
	void playGame();
	// void initializeBets();
	// void initializeHands();
	// void insurance();
	// void dealerSecond(); 
	// void checkBJ();
	// void gameMenu();
	// void dealerTurn();
	// void displayScores(int, int);
	// void results();
	// void postRoundInfo();
	// void resets();
private:
	// int funds, holdfunds, playerBet, insuranceBet, value, count, firstCard, secondCard, dfirstCard, dsecondCard, BJcount, menuChoice, round;
	// bool validResponse, flag, flag2, aceFlag, dealerAceFlag;
	int turn;
	// char yes_or_no, y_or_n;
	PlayerDND kobold(12,5,4,4);
	PlayerDND Blug(17,98,7,12);													//avgdmg calculated without smite; with a smite (level 2, of 3) would be 25
	//Deck gameDeck;
};

#endif

// Play_Game Class function  below

////////////////////////////////////////////////////////////////////////////////Constructor			dont think i need to make a constructor, as the compiler will auto make a default and the players are already declared in the private

// Combat::Combat(PlayerDND P1, PlayerDND P2) {
// 	PlayerDND

// }

////////////////////////////////////////////////////////////////////////////////Start

void Play_Game_QuickExport::playGame() {
	
	////////////////////////////////////////////////////////////////////////////Game with Functions in it
	
	cout << "You start with " << funds << " chips to bet with. Bets will be placed in whole numbers, rounded down." << endl << endl;
	while (funds > 0) {
		cout << "Would you like to play a round of Blackjack? (y for yes, any other character for no) " << endl;
		cin >> yes_or_no;
		
		if (yes_or_no == 'y') {
			gameDeck.setDeck();													//resetting the deck every round to mimic multiple decks
			round = 0;  
			initializeBets();
			initializeHands();
			insurance();
			dealerSecond(); 
			checkBJ();
			while (flag) {
				gameMenu();
				if (flag) {
					dealerTurn();
					results();
				}
			}
			postRoundInfo();
			resets();
		}
		
		else {
			funds = 0;
			cout << endl << "Maybe another time then :(" << endl;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////intialize Player Bet

void Play_Game_QuickExport::initializeBets() { 
	
	cout << "Place your bet: " << endl;
	playerBet = gameDeck.cinFailCheck();										//making sure input is a digit and wont cause infinite loop
	
	while ((playerBet > user.getBet()) || (playerBet < 1))   {					//disallows invalid betting due to number of chips
		cout << "Invalid number of chips to bet. Please place a bet less than or equal to the number of chips you have." << endl;
		playerBet = gameDeck.cinFailCheck();
	}
	
	user.placeBet(playerBet);
	funds = user.getBet();
	cout << "Funds left currently: " << funds << endl << endl;
}

////////////////////////////////////////////////////////////////////////////////intialize hands - draw cards 0 - 2

void Play_Game_QuickExport::initializeHands() {
	
	cout << "Your starting hand is: "  << endl;
	firstCard = gameDeck.getNextCard(round, user.getScore());
	round ++;
	aceFlag = gameDeck.aceChecker(firstCard);
	cout << "and ";
	secondCard = gameDeck.getNextCard(round, user.getScore());
	round ++;

	if (!aceFlag)   {																//making sure that if they already have 1 ace, we don't reset the ace flag if the second card is not an ace	
		aceFlag = gameDeck.aceChecker(secondCard);
	}
	
	user.addScore(firstCard+secondCard);
	cout << endl;
	
////////////////////////////////////////////////////////////////////////////////dealer first card			
			
	cout << "The dealer is showing a ";
	dfirstCard = gameDeck.getNextCard(round, dealer.getScore());
	round++;
	dealerAceFlag = gameDeck.aceChecker(dfirstCard);
	dealer.addScore(dfirstCard);
}

////////////////////////////////////////////////////////////////////////////////player insurance - only available if dealer showing an ace

void Play_Game_QuickExport::insurance() {
	
	if (dealer.getScore()==11)   {
		cout << "Would you like to take insurance against the Dealer's potential BlackJack? (y for yes, any other character for no)" << endl;
		cin >> y_or_n;
		
		if (y_or_n == 'y')   {
			cout << "Insurance against Dealer BlackJack is paid out 2:1. How much would you like to bet on Insurance?" << endl;
			
			insuranceBet = gameDeck.cinFailCheck(); //preventing infinite loop due to wrong input type
			
			while ((insuranceBet > user.getBet()) || (insuranceBet < 1))   {																
				cout << "Invalid number of chips to bet. Please place a bet less than or equal to the number of chips you have." << endl;
				insuranceBet = gameDeck.cinFailCheck();
			}
			
			user.placeBet(insuranceBet);
			cout << "Okay, " << insuranceBet << " coins bet as insurance." << endl;
		}
		
		else {
			cout << "Okay, no insurance it is." << endl;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////dealer second Card is drawn but not added to total; this is to check for blackjack but not alert player as to the dealer's second card

void Play_Game_QuickExport::dealerSecond() {
	
	do {																		//prevents dealer from drawing a zero, should the random number % return 0
	dsecondCard = rand() % 11;												
		if (dsecondCard == 1)   {												
			dsecondCard = 11;
		}
	} while (dsecondCard < 1);
	
	if (!dealerAceFlag)   {														//making sure that if dealer already has 1 ace, we don't reset the ace flag if the second card is not an ace
		dealerAceFlag = gameDeck.aceChecker(dsecondCard);
	}
}

////////////////////////////////////////////////////////////////////////////////Blackjack Checker

void Play_Game_QuickExport::checkBJ() {
		
	if (firstCard+secondCard == 21) {
		BJcount += 1;
	}
	
	if (dfirstCard + dsecondCard == 21)   {
		BJcount += 10;
	}
			
	if (BJcount == 1)   {													//player has BJ
		cout << "Blackjack! You Win!" << endl;
		playerBet = (0 - playerBet)*1.5;
		user.placeBet(playerBet);
		cout << "User chips total: " << user.getBet() << endl;
		flag = false;
	}
	
	else if (BJcount == 10)   {												//dealer has BJ
	
		if (y_or_n == 'y')   {
			cout << "Wow! Guess Your Insurance paid off!" << endl;
			insuranceBet = (0 - insuranceBet) * 2;
			user.placeBet(insuranceBet);
			cout << "User chips total: " << user.getBet() << endl;
		}
		
		else {
		cout << "Dealer has Blackjack! You Lose!" << endl;
		cout << "User chips left currently: " << user.getBet() << endl;
		}
		
		flag = false;
	}
	
	else if (BJcount == 11)   {												//both blackjack
		cout << "Push! You and the Dealer both have Blackjack!" << endl;
		
		if (y_or_n == 'y')   {
			cout << "Wow! Guess Your Insurance paid off!" << endl;
			insuranceBet = (0 - insuranceBet) * 1.5;
			user.placeBet(insuranceBet);
		}
		
		else   {
		playerBet = 0 - playerBet;
		user.placeBet(playerBet);
		}
		
		cout << "User chips left currently: " << user.getBet() << endl;
		flag = false;
	}
}

////////////////////////////////////////////////////////////////////////////////display score function

void Play_Game_QuickExport::displayScores(int userScore, int dealerScore) {
	
	cout << endl << "Your Score: " << userScore << endl;
	cout << "Known Dealer Score: " << dealerScore << endl;
}

////////////////////////////////////////////////////////////////////////////////Game Menu

void Play_Game_QuickExport::gameMenu() {
	
	validResponse = false;
	while (!validResponse) { 														
		displayScores(user.getScore(), dealer.getScore());
		cout << endl << "What would you like to do? " << endl;
		cout << "	1 = Hit " << endl;
		cout << "	2 = Stand " << endl;
		cout << "	3 = Surrender " << endl;
		cout << "	4 = Double Down " << endl;
		cin >> menuChoice;
		switch (menuChoice) {
						
////////////////////////////////Decisions, Decisions

/////////////////Hit
			case 1:
				cout << "You Drew: " << endl;											
				value = gameDeck.getNextCard(round, user.getScore());
				user.addScore(value);
				validResponse = false;													
				round++;
				
				if (!aceFlag)   {												//making sure that if they already have 1 ace, we don't reset the ace flag if the second card is not an ace
					aceFlag = gameDeck.aceChecker(value);
				}
				
				if (user.getScore() > 21) {										//checking for true bust or bust with ace = 11; altering score if the ace is being counted as an 11. same is done for dealer
				
					if (aceFlag)   {
						cout << "Your Ace must count as a 1 in order to avoid Busting. Changing Score now..." << endl;
						user.addScore(0-10);
						cout << "New Score is: " << user.getScore() << endl;
						aceFlag = false;										//changing aceFlag to false so the score - 10 only happens 1 time. all subsequent aces will be 1's anyway. same for dealer
					}
					
					else {
						cout << "Bust! You Lose! " << endl;
						cout << "User chips left currently: " << user.getBet() << endl;
						validResponse = true;		
						flag = false;				
					}
				}
				break;
				
	/////////////////Stand
			case 2: 
				validResponse = true;
				break;
				
	/////////////////Surrender
			case 3:
				playerBet = (0 - playerBet) / 2;
				user.placeBet(playerBet);
				validResponse = true;
				flag = false;
				flag2 = true;
				break;
				
	/////////////////Double Down
			case 4: 
			
				if (user.getBet()-playerBet*2 < 0)   {
					cout << "Sorry, not enough funds to Double Down. Please Select another option" << endl;
					validResponse = false;
				}
				
				else   {
					cout << "Doubling Down..." << endl;
					cout << "Bet is now: " << playerBet *2 << endl;
					user.placeBet(playerBet);
					playerBet = playerBet *2;
					cout << "Drawing next card..." << endl;
					cout << "You Drew: " << endl;											
					value = gameDeck.getNextCard(round, user.getScore());
					user.addScore(value);
					validResponse = true;													
					round++;
					if (user.getScore() > 21) {
						cout << "Bust! You Lose! " << endl;
						cout << "User chips left currently: " << user.getBet() << endl;
						validResponse = true;		
						flag = false;				
					}
				}
				break;
			default:
				cout << "Invalid input, please enter a valid input. " << endl;
				validResponse = false;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////Dealer's Turn

void Play_Game_QuickExport::dealerTurn() {
	
	dealer.addScore(dsecondCard); 
	cout << "Dealer flips 2nd card and his score is now: " << dealer.getScore() << endl;
	
	while (dealer.getScore() < 17) {
		cout << endl << "Dealer Drew: " << endl;
		value = gameDeck.getNextCard(round, dealer.getScore());
		dealer.addScore(value);
		round++;
		cout << endl;
		displayScores(user.getScore(), dealer.getScore());
		cout << endl;
	}
	
	if (dealer.getScore() < 22) {
			cout << "Dealer can no longer draw: " << dealer.getScore() << endl;
	}
	else if (dealerAceFlag)   {
			dealer.addScore(0-10);
			dealerAceFlag = false;
	}
	else  {
		cout << dealer.getScore() << ": Dealer Busts!" << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////Determine Round Winner

void Play_Game_QuickExport::results() { 

	if (dealer.getScore() == user.getScore())   {
		cout << "Push! " << endl;
		playerBet = 0 - playerBet;
		user.placeBet(playerBet);
		cout << "User chips left currently: " << user.getBet() << endl;
	}
	else if ((dealer.getScore() > 21) || (dealer.getScore() < user.getScore())) {
		cout << "You Win! " << endl;
		playerBet = (0 - playerBet)*2;
		user.placeBet(playerBet);
		cout << "User chips total: " << user.getBet() << endl;
	}
	else if ((dealer.getScore() > user.getScore()) || (flag2)) {				
		cout << "You Lose! " << endl;											//flag2 here is referring to if they surrendered
		cout << "User chips left currently: " << user.getBet() << endl;
	}
	flag = false;
}

////////////////////////////////////////////////////////////////////////////////Post Round Info

void Play_Game_QuickExport::postRoundInfo() {
	
	funds = user.getBet();
	holdfunds = funds;
	
	if (!(yes_or_no == 'y'))   {
		funds = 0;
		flag2 = true;
	}
	
	if ((!flag2) && (funds < 1))   {
	cout << "You're out of funds! Thanks for playing! Goodbye!" << endl;
	}
	else if (flag2) {															
		cout << "You have " << holdfunds << " chips. Thanks for playing!" << endl;
	}
	else {
		count += 1;
		cout << "Rounds played: "  << count << endl;
	}
	
	user.addScore(0-user.getScore());
	dealer.addScore(0 - dealer.getScore());
}

////////////////////////////////////////////////////////////////////////////////Reset anything that needs to be reset

void Play_Game_QuickExport::resets() {
	
	flag = true;
	BJcount = 0;
	y_or_n = 'n';
	
}