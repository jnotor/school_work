// 
// Caleb Cargill, John Notorgiacomo
// C++ Programming, Final Project: BlackJack
//

// Main Function

#include "Player.h"
#include "Deck.h"

void gameMenu(Player, Player, Deck);	// Declaration of gameMenu function

int main()
{
	Player user;
	Player dealer;
	Deck gameDeck;
	
	gameMenu(user, dealer, gameDeck);

    return 0;
}

void gameMenu(Player user, Player dealer, Deck gameDeck) {			// Definition of gameMenu Function
	char yes_or_no; 
	cout << "Would you like to play the game of Blackjack? (y for yes, any other character for no) " << endl;
	cin >> yes_or_no; 
	if (yes_or_no == 'y') {
		gameDeck.setDeck();
		bool flag = true;
		bool validResponse;
		int value = 0;
		//variables used to check for black jack
		int firstCard = 0;
		int secondCard = 0;
		int dfirstCard = 0;
		int dsecondCard = 0;
		int BJcount = 0;
		
		int round = 4; //starting round at 3 so we can deal 2 cards face up to the user and 1 card face down to the dealer. the dealer's fourth card will be dealt to him later in our game, but is only revealed at the end of the game in a real game
								//note: if dealer has a natural black jack, they would terminate the game, winning automatically unless user has a natural blackjack as well. need to fix
		//intialize hands
		cout << "Your starting hand is: "  << endl;
		firstCard = gameDeck.getNextCard(0, user.getScore());
		cout << "and ";
		secondCard = gameDeck.getNextCard(1, user.getScore());
		user.addScore(firstCard+secondCard);
		cout << endl;
		if (firstCard+secondCard == 21) {
		BJcount += 1;
		}
		
		cout << "The dealer is showing a ";
		dfirstCard = gameDeck.getNextCard(2, dealer.getScore());
		dealer.addScore(dfirstCard);
		dsecondCard = rand() % 13;
		if (dfirstCard + dsecondCard == 21)   {	//currently reports dealer's hidden card
			BJcount += 10;
		}
		
		if (BJcount == 1)   {													//player wins
			cout << "Black Jack! You Win!" << endl;
			flag = false;
		}
		else if (BJcount == 10)   {												//dealer wins
			cout << "Dealer has Black Jack! You Lose!" << endl;
			flag = false;
		}
		else if (BJcount == 11)   {												//both black jack
			cout << "Push! You and the Dealer both have Black Jack!" << endl;
			flag = false;
		}
		
		//begin choices
		while (flag) {
			// User's Turn
			validResponse = false;
			while (!validResponse) { 														
				cout << endl << "Your Score: " << user.getScore() << endl;
				cout << "Known Dealer Score: " << dealer.getScore() << endl;
				cout << endl << "What would you like to do? " << endl;
				cout << "	1 = Hit " << endl;
				cout << "	2 = Stand " << endl;
				cout << "	3 = Quit Game " << endl;
				int menuChoice;
				cin >> menuChoice;
				switch (menuChoice) {
				case 1:
					cout << "You Drew: " << endl;											
					value = gameDeck.getNextCard(round, user.getScore());
					user.addScore(value);
					validResponse = false;													//once they draw, they need to go back to the choice menu and decide to either draw again or stand. 
					round += 1;
					// Check Score
					if (user.getScore() > 21) {
					cout << "Bust! You Lose! " << endl;
					validResponse = true;		//makes sure they can't keep going
					flag = false;				//terminates game
					}
					break;
				case 2: 
					validResponse = true;
					break;
				case 3:
				//	cout << "Thanks for playing, goodbye! " << endl; redundant with endline code
					validResponse = true;
					flag = false;
					break;
				default:
					cout << "Invalid input, please enter a valid input. " << endl;
					validResponse = false;
				}
			//else if (user.getScore() == 21) {
			//	cout << "You Win! " << endl;
			//	flag = false;																	//got rid of this condition so that the game continues once the player is ready to stand
			//}
			}
			// cout << endl << "1Your Score: " << user.getScore() << endl;
			// cout << "1Dealer Score: " << dealer.getScore() << endl;									//don't think we need this line. if they hit, they get updated already. if they stand, they just made that choice, no need to remind them
			
			// Dealer's Turn
			if (flag) {
				dealer.addScore(dsecondCard); //reveals hidden card
				cout << "Dealer flips card and his score is now: " << dealer.getScore();
				while (dealer.getScore() < 17) {
					cout << endl << "Dealer Drew: " << endl;
					value = gameDeck.getNextCard(round, dealer.getScore());
					dealer.addScore(value);
					round += 1;
					cout << endl;
				}
				if (dealer.getScore() < 22) {
				cout << "Dealer can no longer draw: " << dealer.getScore() << endl;
				}
				else   {
					cout << dealer.getScore() << ": Dealer Busts!" << endl;
				}
			// Check Score
			if (dealer.getScore() > 21) {
				cout << "You Win! " << endl;
				//flag = false;
			}
			else if (dealer.getScore() == 21) {												 //few rare situations where this is not true: dealer has a natural black jack, dealer draws up to 21 (and you don't have a natural black jack)
				cout << "You Lose! " << endl;
				//flag = false;
			}
			else if (dealer.getScore() > user.getScore())   {
				cout << "You Lose! " << endl;
				//flag = false;
			}
			else if (dealer.getScore() == user.getScore())   {
				cout << "Push! " << endl;
				//flag = false;
			}
			else   {
				cout << "You Win! " << endl;
				flag = false;	
			}
			flag = false;
			}
		}
	}
	else {
		cout << "Goodbye!" << endl;
	}
	cout << "Thanks for playing!" << endl;
}
