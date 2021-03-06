// Stack13.cpp : Defines the exported functions for the DLL application.
//

#include "header.h"
#include "Stack13.h"
#include <iostream>
#include <stdlib.h>
//the below is from tostring
class STACK13_API Game { //game class should be doing all the news and all the deletes
public:
	Game() {
		P1 = new Player("Player1");
		P2 = new Player("Player2");
		//making a master list of cards
		for (int s = 0; s < 4; s++) {
			for (int rank = 1; rank <= 13; rank++)
				{ mCardList.push_back(new Cards(rank, (suit_t)s)); } }
		//seeding cards into the deck in a pseudo random order
		int ranNum = 0;
		for (auto it : mCardList) {
			ranNum = rand() % 100;
			if (ranNum > 42) {
				Deck.push_back(it);
			}
			else {
				Deck.push_front(it);
			}
		}
		gameWon = false;
		Player1Turn = true;
	}
	bool DoWeGetChickenDinner() { //see if there is a win state - stack size = 13
		//dont pass it anything; just call the player function, topStack and see if it's value == 13	
		return false;
	}
	void Play() {
		while (!gameWon) {
			//deal 'em in; 5 cards each
			for (int i = 0; i < 5; ++i) {
				//player 1 draw
				const Cards * cardDealt1 = Deck.front();
				Deck.pop_front();
				P1->DrawCard(cardDealt1);
				//player 2 draw
				const Cards * cardDealt2 = Deck.front();
				Deck.pop_front();
				P2->DrawCard(cardDealt2);
			}
		//check whose turn it is
			if (Player1Turn) {
				//turn start
				//determine if they would like to "mulligan" their hand
					//mulligan choice tree here
				//if no mulligan:
				P1->DrawCard(Deck.front());
				Deck.pop_front();
				//determine if the want to stack using a while loop where they can stack things until they no longer can/want to
					//have them auto draw a card upon stacking one
				//check to see if the turn is over
				//check to see if the game is won; if it is, set GameWon to be true
				//change the player1turn flag to false so we change turns
			}
			//player 2 turn
			else {
				//show them their stack, then their hand 
				//allow them to draw, place on stack and/or discard
				//passturn
			}
		}
	}
	~Game()
	{
		delete P1;
		delete P2;
		
		for (auto jk : mCardList) {
			delete jk;
		}

	}
private:
	Player * P1;
	Player * P2;
	std::list<Cards *> mCardList;
	std::list<const Cards *> Deck;
	bool gameWon;
	bool Player1Turn;
};

int main() {
	Game game;
	game.Play();
	return 0;
	}


/* the below was worked on at office hours with isha
Game::Game()
{
	Player* Player1 = new Player(); //initialize by calling the constructor
	Player* Player2 = new Player(); //star comes after the type name
	//Cards *Deck = new Cards();

	//intiialize deck
	std::queue<Cards*> Deck;
	for (int i = 1; i < 53; ++i) {
		Cards *newCard = new Cards(i);
		Deck.push(newCard);
	}
	//make it random order
	//deal cards
	for (int i = 1; i < 6; ++i) {
		Cards* temp1 = Deck.front();
		Deck.pop();
		Cards* temp2 = Deck.front();
		Deck.pop();
		(Player1->Hand)->push_back(temp1); //hand is supposed to be a list of pointers, but we've made 
		(Player2->Hand)->push_back(temp2);
	}

}

Game::~Game()
{
}

Cards::Cards(int i)
{
	cNumber = i;
}

Player::Player()
{

}
*/