// Play_Game Class Function Declarations
// Class Description: 
	// This Class is used for the logic of the game and the actual playing of the game. This class refers to the Player class and the Deck Class
#pragma once

#include "Deck.h"
#include "Player.h"

#include <iostream>

using namespace std;

#ifndef PLAY_GAME_QUICKEXPORT_H
#define PLAY_GAME_QUICKEXPORT_H

class Play_Game_QuickExport {
public:
	Play_Game_QuickExport();
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
	int funds, holdfunds, playerBet, insuranceBet, value, count, firstCard, secondCard, dfirstCard, dsecondCard, BJcount, menuChoice, round, splitCardCounter;
	bool validResponse, flag, flag2, aceFlag, dealerAceFlag, splitFlag;
	char yes_or_no, y_or_n, y_or_n2;
	Player user;
	Player dealer;
	Deck gameDeck;
};

#endif

// Play_Game Class function  below

////////////////////////////////////////////////////////////////////////////////Constructor

Play_Game_QuickExport::Play_Game_QuickExport() {
	funds = user.getBet();
	holdfunds = 0;
	playerBet = 0;
	insuranceBet = 0;
	value = 0;
	count = 0;
	firstCard = 0;
	secondCard = 0;
	dfirstCard = 0;
	dsecondCard = 0;
	splitCardCounter = 0;
	BJcount = 0;
	menuChoice = 0;
	round = 0;
	validResponse = false;
	flag = true;
	flag2 = false;
	aceFlag = false;
	dealerAceFlag = false;
	splitFlag = false;
	yes_or_no = 'y';
}

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
	playerBet = gameDeck.cinFailCheck();
	
	while ((playerBet > user.getBet()) || (playerBet < 1))   {	
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
	//cout << "Ace check result: " << aceFlag << endl; //for testing ace check
	cout << "and ";
	secondCard = gameDeck.getNextCard(round, user.getScore());
	round ++;
	//making sure that if they already have 1 ace, we don't reset the ace flag if the second card is not an ace		
	if (!aceFlag)   {													
		aceFlag = gameDeck.aceChecker(secondCard);
	}
	
	/* 
	splitFlag = gameDeck.splitChecker(firstCard, secondCard, funds, playerBet);
	if (splitFlag)   {
		Player secondHand; //intializing a 2nd "player" to be the split hand
		secondHand.addScore(firstCard); //giving it the same starting score as the other, since its a split
		round ++;
		cout << "Second card for the second hand is: ";
		secondCard = gameDeck.getNextCard(round, user.getScore()); 
		secondHand.addScore(secondCard);
		if (firstCard+secondCard == 21) { //checking for this hand's blackjack
			BJcount += 1;
		}
		cout << "We'll play out this hand before moving on to the original" << endl;
		
		
	 }
	 
	 
	 //need to add a condition to the game menu to check for hands and then have it iterate = number of hands before terminating to dealer hand
	 //bjchecker might have to change and, instead of just firing off at the end of the intial dealing phase, it will have to fire per user - changed to check for double blackjack instead
	 //else wise i think it remains the same
	 
	 //i've made the changes so far in the comments because i dont feel like changing the main file and all the class member names each time i make a new iteration
	 */
					
	user.addScore(firstCard+secondCard);
	cout << endl;
	
////////////////////////////////////////////////////////////////////////////////dealer first card			
			
	cout << "The dealer is showing a ";
	dfirstCard = gameDeck.getNextCard(round, dealer.getScore());
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
			while ((insuranceBet > user.getBet()) || (insuranceBet < 1))   {				//disallows invalid betting due to number of chips
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
	cout << "Hide dealer's second card please: " << dsecondCard << endl;			//remove later
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
		cout << "Blackjack! Your Hand Wins!" << endl;
		playerBet = (0 - playerBet)*2;
		user.placeBet(playerBet);
		cout << "User chips total: " << user.getBet() << endl;
		//if (!splitFlag)  {													//prevent the game from ending when one hand is still in competition with the dealer
		flag = false;
		//}
	}
	else if (BJcount == 2)   {
		cout << "Double Blackjack! You Win!" << endl;
		playerBet = (0 - playerBet)*4;
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
	else if (BJcount == 11)   {												//both black jack
		cout << "Push! You and the Dealer both have Black Jack!" << endl;
		if (y_or_n == 'y')   {
			cout << "Wow! Guess Your Insurance paid off!" << endl;
			insuranceBet = (0 - insuranceBet) * 2;
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
			round += 1;
			
			if (!aceFlag)   {													//making sure that if they already have 1 ace, we don't reset the ace flag if the second card is not an ace
				aceFlag = gameDeck.aceChecker(value);
			}
			//checking for true bust or bust with ace = 11
			if (user.getScore() > 21) {
				if (aceFlag)   {
					cout << "Your Ace must count as a 1 in order to avoid Busting. Changing Score now..." << endl;
					user.addScore(0-10);
					cout << "New Score is: " << user.getScore() << endl;
					aceFlag = false;
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
				round += 1;
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
		round += 1;
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

void Play_Game_QuickExport::results() { //need to figure out the sequence it should go in to rule out dealer busts
	if (dealer.getScore() == user.getScore())   {
		cout << "Push! " << endl;
		playerBet = 0 - playerBet;
		user.placeBet(playerBet);
		cout << "User chips left currently: " << user.getBet() << endl;
	}
	else if ((dealer.getScore() > 21) || (dealer.getScore() < user.getScore())) {
		cout << "You Win! " << endl;
		playerBet = (0 - playerBet)*1.5;
		user.placeBet(playerBet);
		cout << "User chips total: " << user.getBet() << endl;
	}
	else if ((dealer.getScore() > user.getScore()) || (flag2)) {				//(dealer.getScore() == 21) || removed this condition because its redundant. either dealer won due to BJ or wins due to higher score												
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
	else if (flag2) {															// && (funds < 1)
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
	y_or_n2 = 'n';
}