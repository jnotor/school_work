// Deck Class Function Declarations
// Class Description: 
	// This class creates a deck (a vector) for the game, and includes a faceValue, suit, and face 
	// for each next "on top" card in the deck. When a player decides to hit, that "on top" card is "drawn" and values are 
	// added to the player's score (using Player Class)
	
#pragma once																	

#include <iostream>
#include <string> 
#include <vector>
#include <ctime>

using namespace std;

#ifndef DECK_H
#define DECK_H



class Deck {
	public:
		Deck();																	// Declaration of Deck Default Constructor
		void setDeck();															// Declaration of function that would set a deck of 52 cards
		int getNextCard(int, int);												// Declaration of function that would return next card in deck
		string getSuit();														// Declaration of function that would return a suit for the card
		bool aceChecker(int);													// Declaration of function that checks a card to determine if it is an ace
		int cinFailCheck();														//Dec. of function to check for betting type input failure
		bool splitChecker(int, int, int, int);													//Dec of a function to check and see if a split is available
	private: 
		vector <int> deck[52];													// Vector that would act as a deck for the game
		string suit;															// String that would store the suit of the card drawn
		int faceValue;															// Integer that would contain the value of the card drawn
};

#endif

Deck::Deck() {																	// Default Constructor Defintion, sets all cards in the deck as 0

	for (int i = 0; i < 52; i++) {												// Sets faceValue as 0
		deck->push_back(0);														// Sets suit as Spades
	}
	faceValue = 0;
	suit = "Spades";
}

void Deck::setDeck() {															// Function that sets a deck of 52 random integers ranging from 0-12
	
	srand(time(NULL));															// Uses time() function to ensure better sudo random results each game
	for (int i = 0; i < 52; i++) {												// Each integer (0-12) corresponds with a card in the deck
		faceValue = rand() % 13;
		deck->at(i) = faceValue;
	}
}

int Deck::getNextCard(int round, int score) {									// Function that gets the next card in the deck, returns the facevalue of the next card
	
	faceValue = deck->at(round);												// Takes in two integers as parameters, round to ensure correct card is drawn, score to do initial Ace checking
	suit = getSuit();
	switch (faceValue) {
		case 0:
			cout << "Ace of " << suit << endl;
			if (score <= 10) {
				faceValue = 11;
			}
			else {
				faceValue = 1;
			}
			break;
		case 1:
			cout << "2 of " << suit << endl;
			faceValue = 2;
			break;
		case 2:
			cout << "3 of " << suit << endl;
			faceValue = 3;
			break;
		case 3:
			cout << "4 of " << suit <<  endl;
			faceValue = 4;
			break;
		case 4:
			cout << "5 of " << suit << endl;
			faceValue = 5;
			break;
		case 5:
			cout << "6 of " << suit << endl;
			faceValue = 6;
			break;
		case 6:
			cout << "7 of " << suit << endl;
			faceValue = 7;
			break;
		case 7:
			cout << "8 of " << suit << endl;
			faceValue = 8;
			break;
		case 8: 
			cout << "9 of " << suit << endl;
			faceValue = 9;
			break;
		case 9: 
			cout << "10 of " << suit << endl;
			faceValue = 10;
			break;
		case 10:
			cout << "Jack of " << suit << endl;
			faceValue = 10;
			break;
		case 11:
			cout << "Queen of " << suit << endl;
			faceValue = 10;
			break;
		case 12:
			cout << "King of " << suit << endl;
			faceValue = 10;
			break;
	}
	return faceValue;
}

string Deck::getSuit() {														// Function that finds a random integer (0-3) and uses this to determine the suit of the card

	int suitVal = rand() % 4;													// In Blackjack in casinos, 7-8 decks of cards are used, so we do not need to ensure that 
	switch (suitVal) {															// the "same card" is not drawn twice. 52 is used as deck size just for simplicity. 
	case 0:
		suit = "Hearts";
		break;
	case 1:
		suit = "Spades";
		break;
	case 2:
		suit = "Diamonds";
		break;
	case 3:
		suit = "Clubs";
		break;
	}
	return suit;
}

bool Deck::aceChecker(int card) {												// Function that checks the value of a card drawn and determines if it is an Ace
	
	bool aceFlag = false;
	if (card == 11) {
		aceFlag = true;
	}
	return aceFlag;
}

int Deck::cinFailCheck()   {													//preventing infinite loop due to wrong input type
	
	int playerBet;
	cin >> playerBet;
	while (cin.fail())   { 
		cin.clear();
		cin.ignore(200,'\n');
		cout << "Are you sure you meant to enter that? Please enter a real number, using digits." << endl; 
		cin >> playerBet;
	}
	return playerBet;
}