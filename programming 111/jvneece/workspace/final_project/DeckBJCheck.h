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
//new
using namespace std;

#ifndef DECKBJCHECK_H
#define DECKBJCHECK_H

class Deck {
	public:
		Deck();                                                                 // Declaration of default constructor
		void setDeck();                                                         // Declaration of setDeck function
		int getNextCard(int, int);                                              // Declaration of getNextCard function
		string getSuit();                                                       // Declaration of getSuit function
		bool BJCheck();
	private: 
		vector <int> deck[52];                                                  // Declaration of private components
		string suit;
		int faceValue;
};

Deck::Deck() {                                                                  // Definition of default constructor, sets private components initially to zero
	for (int i = 0; i < 52; i++) {
		deck->push_back(0);
	}
	suit = "Ace";
	faceValue = 0;
}

void Deck::setDeck() {                                                          // Definition of setDeck function, sets a deck of 52 random integers
	srand(time(NULL));
	for (int i = 0; i < 52; i++) {
		faceValue = rand() % 13;
		deck->at(i) = faceValue;
	}
}

bool Deck::BJCheck()   {
	int BJCount = 0;
	bool flag;
	//see if anyone has blackjack
	if (deck.faceValue.at(0)+deck.faceValue.at(1) == 21)   {
		BJCount += 1;
	}
	else if (deck.faceValue.at(2)+deck.faceValue.at(3) == 21) {
		BJCount += 10;
	}
	
	
	//determine if someone's blackjack won them the game
	if (BJCount == 11)   {
		cout << "Push! You and the Dealer both have Black Jack!" << endl;
		flag = false;
	}
	else if (BJCount == 10)   {
		cout << "Dealer Black Jack! You Lose!" << endl;
		flag = false;
	}
	else if (BJCount == 1)   {
		cout << "Black Jack! You Win!" << endl;
		flag = false;
	}
	return flag;
}


int Deck::getNextCard(int round, int score) {                                   // Definition of getNextCard function, gets and returns the face value of the card, also couts a message
	faceValue = deck->at(round);                                                // Takes int round as a parameter in order to take correct "next card" and int score as a parameter in order to 
	suit = getSuit();                                                           // check which value of ace to use 
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

string Deck::getSuit() {                                                        // Definition of getSuit function, uses a random integer from 0-3 to return a string that is a suit
	int suitVal = rand() % 4;                                                   // It is okay if the "same card" is drawn twice. Blackjack played in casinos uses anywhere from 6-8 decks, we are just 
	switch (suitVal) {                                                          // setting this as a deck of 52 cards because there is no way that more than 52 rounds would be played. 
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

#endif
