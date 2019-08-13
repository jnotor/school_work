// Clean Version of 2E; only features left to implement are: Splitting and Ace fluidity
//
// Caleb Cargill, John Notorgiacomo
// C++ Programming, Final Project: BlackJack
//

// Main Function

#include "PlayerBet.h"
#include "Deck.h"

void gameMenu(Player, Player, Deck);											// Declaration of gameMenu function

int main()
{
	Player user;
	Player dealer;
	Deck gameDeck;
	
	gameMenu(user, dealer, gameDeck);

    return 0;
}

void gameMenu(Player user, Player dealer, Deck gameDeck) {						// Definition of gameMenu Function

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////variable declaration

	char yes_or_no; 
	int funds = user.getBet();
	int playerBet;
	int count = 0;
	bool flag2 = false;
	int holdfunds;
	bool flag = true;
	bool validResponse;
	int value = 0;
	char y_or_n;
	int insuranceBet;
	//variables used to check for black jack
	int firstCard = 0;
	int secondCard = 0;
	int dfirstCard = 0;
	int dsecondCard = 0;
	int BJcount = 0;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////start game

	cout << "You start with " << funds << " chips to bet with. Bets will be placed in whole numbers, rounded down." << endl << endl;
	
	while (funds > 0)   {
	
		cout << "Would you like to play a round of Blackjack? (y for yes, any other character for no) " << endl;
		cin >> yes_or_no; 
		if (yes_or_no == 'y') {
			gameDeck.setDeck();
			int round = 4; 
			
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////intialize bets
			
			cout << "Place your bet: " << endl;
			cin >> playerBet;
			
			while ((playerBet > user.getBet()) || (playerBet < 1))   {			
				cout << "Invalid number of chips to bet. Please place a bet less than or equal to the number of chips you have." << endl;
				cin >> playerBet;
			}
			
			user.placeBet(playerBet);
			
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////intialize hands

////////////////////////////////////////////////////////////////////////////////player hand			
			cout << "Your starting hand is: "  << endl;
			firstCard = gameDeck.getNextCard(0, user.getScore());
			cout << "and ";
			secondCard = gameDeck.getNextCard(1, user.getScore());
			user.addScore(firstCard+secondCard);
			cout << endl;
	
			if (firstCard+secondCard == 21) {
				BJcount += 1;
			}
////////////////////////////////////////////////////////////////////////////////dealer hand			
			cout << "The dealer is showing a ";
			dfirstCard = gameDeck.getNextCard(2, dealer.getScore());
			dealer.addScore(dfirstCard);
			
////////////////////////////////////////insurance
			if (dealer.getScore()==11)   {
				cout << "Would you like to take insurance against the Dealer's potential BlackJack? (y for yes, any other character for no)" << endl;
				cin >> y_or_n;
				if (y_or_n == 'y')   {
					cout << "Insurance against Dealer BlackJack is paid out 2:1. How much would you like to bet on Insurance?" << endl;
					cin >> insuranceBet;
					while ((insuranceBet > user.getBet()) || (insuranceBet < 1))   {				//disallows invalid betting 
						cout << "Invalid number of chips to bet. Please place a bet less than or equal to the number of chips you have." << endl;
						cin >> insuranceBet;
					}
					user.placeBet(insuranceBet);
					cout << "Okay, " << insuranceBet << " coins bet as insurance." << endl;
				}
				else {
					cout << "Okay, no insurance it is." << endl;
				}
			}
////////////////////////////////////dealer 2nd card
			
			dsecondCard = rand() % 11;												//changed from mod 13 to mod 11 for this implementation here; dealer could draw a card worth 12 or 13 before
			if (dsecondCard == 1)   {												// added this line so that the default in the deck library holds true here; will have to be edited later
				dsecondCard = 11;
			}
			cout << "Hide dealer's second card please: " << dsecondCard << endl;			//remove later
			
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////check for Black Jack
			if (dfirstCard + dsecondCard == 21)   {
				BJcount += 10;
			}
			
			if (BJcount == 1)   {													//player has BJ
				cout << "Black Jack! You Win!" << endl;
					playerBet = (0 - playerBet)*2.5;
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
				cout << "Dealer has Black Jack! You Lose!" << endl;
				cout << "User chips left currently: " << user.getBet() << endl;
				}
				flag = false;
			}
			else if (BJcount == 11)   {												//both black jack
				cout << "Push! You and the Dealer both have Black Jack!" << endl;
				playerBet = 0 - playerBet;
				user.placeBet(playerBet);
				flag = false;
			}
			
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////begin game

			while (flag) {
				
////////////////////////////////////////////////////////////////////////////////User's Turn

				validResponse = false;
				while (!validResponse) { 														
					cout << endl << "Your Score: " << user.getScore() << endl;
					cout << "Known Dealer Score: " << dealer.getScore() << endl;
					cout << endl << "What would you like to do? " << endl;
					cout << "	1 = Hit " << endl;
					cout << "	2 = Stand " << endl;
					cout << "	3 = Surrender " << endl;
					cout << "	4 = Double Down " << endl;
					int menuChoice;
					cin >> menuChoice;
					switch (menuChoice) {
						
////////////////////////////////Decisions, Decisions

					case 1:
						cout << "You Drew: " << endl;											
						value = gameDeck.getNextCard(round, user.getScore());
						user.addScore(value);
						validResponse = false;													
						round += 1;
						// if (value == 11)   {										need to give the player the option to have ace's be fluid		
						// 	cout << "You can change the value of this Ace to a 1 later in the game by..."
						// }
						// Check Score
						if (user.getScore() > 21) {
						cout << "Bust! You Lose! " << endl;
						cout << "User chips left currently: " << user.getBet() << endl;
						validResponse = true;		
						flag = false;				
						}
						break;
					case 2: 
						validResponse = true;
						break;
					case 3:
						playerBet = (0 - playerBet) / 2;
						user.placeBet(playerBet);
						validResponse = true;
						flag = false;
						flag2 = true;
						break;
					case 4: 
						cout << "Doubling Down..." << endl;
						cout << "Bet is now: " << playerBet *2 << endl;
						user.placeBet(playerBet);
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
						break;
					default:
						cout << "Invalid input, please enter a valid input. " << endl;
						validResponse = false;
					}
				}
				
//////////////////////////////////////////////////////////////////////////////// Dealer's Turn

				if (flag) {
					dealer.addScore(dsecondCard); 
					cout << "Dealer flips card and his score is now: " << dealer.getScore() << endl;
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
					
////////////////////////////////////////////////////////////////////////////////Decide who won

				if (dealer.getScore() > 21) {
					cout << "You Win! " << endl;
					playerBet = (0 - playerBet)*2;
					user.placeBet(playerBet);
					cout << "User chips total: " << user.getBet() << endl;
				
				}
				else if (dealer.getScore() == 21) {												
					cout << "You Lose! " << endl;
					cout << "User chips left currently: " << user.getBet() << endl;
			
				}
				else if (dealer.getScore() > user.getScore())   {
					cout << "You Lose! " << endl;
					cout << "User chips left currently: " << user.getBet() << endl;
				
				}
				else if (dealer.getScore() == user.getScore())   {
					cout << "Push! " << endl;
					playerBet = 0 - playerBet;
					user.placeBet(playerBet);
				
				}
				else   {
					cout << "You Win! " << endl;
					playerBet = (0 - playerBet)*2;
					user.placeBet(playerBet);
					cout << "User chips total: " << user.getBet() << endl;
				
				}
				flag = false;
				}
			}
		}
		
////////////////////////////////////////////////////////////////////////////////Post Round Info + Resets

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
	}