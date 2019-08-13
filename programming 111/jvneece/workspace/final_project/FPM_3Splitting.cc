// working on splitting
//
// Caleb Cargill, John Notorgiacomo
// C++ Programming, Final Project: BlackJack
//

// Main Function

#include "PlayerBet.h"
#include "DeckAceCheck.h"

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

	//"Numbers"
	int funds = user.getBet();
	int playerBet;
	int insuranceBet;
	int value = 0;
	int count = 0;
	int holdfunds;

	//"Flags"
	bool validResponse; //maintains user decision loop until they decide to stop or are forced; once true, it moves the turn to the dealer
	bool flag = true; //starts decision tree/actual game
	bool flag2 = false; //used to denote whether the user has intentionally quit the game or lost all their coins and thats why the game is ending
	bool aceFlag = false; //notes where an ace is 11 but could be a 1 for the player; is used to prevent unfair busts
	bool dealerAceFlag = false; //notes where an ace is 11 but could be a 1 for the dealer; is used to prevent unfair busts

	//"Choice inputs"
	char yes_or_no; //decision to play a round
	char y_or_n; //decision for insurance
	char y_or_n2; //decision for splitting; not yet implemented
	
	//variables used to check for black jack
		//player
			int firstCard = 0;
			int secondCard = 0;
		//dealer
			int dfirstCard = 0;
			int dsecondCard = 0;
		//used to determine if 1 or both has Blackjack
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
			aceFlag = gameDeck.aceChecker(firstCard);
																				//cout << "Ace check result: " << aceFlag << endl; for testing ace check
			cout << "and ";
			secondCard = gameDeck.getNextCard(1, user.getScore());
			
			if (!aceFlag)   {													//making sure that if they already have 1 ace, we don't reset the ace flag if the second card is not an ace
				aceFlag = gameDeck.aceChecker(secondCard);
				}
			
			user.addScore(firstCard+secondCard);
			cout << endl;
	
			if (firstCard+secondCard == 21) {
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
			
////////////////////////////////////////////////////////////////////////////////dealer hand			
			
			cout << "The dealer is showing a ";
			dfirstCard = gameDeck.getNextCard(2, dealer.getScore());
			dealerAceFlag = gameDeck.aceChecker(dfirstCard);
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
			if (dsecondCard == 1)   {												// added this line so that the default in the deck library holds true here; will have to be edited later?
				dsecondCard = 11;
			}
			if (!dealerAceFlag)   {													//making sure that if dealer already has 1 ace, we don't reset the ace flag if the second card is not an ace
				dealerAceFlag = gameDeck.aceChecker(dsecondCard);
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
					int menuChoice;												//why is this being declared here?
					cin >> menuChoice;
					switch (menuChoice) {
						
////////////////////////////////Decisions, Decisions

					case 1:
						cout << "You Drew: " << endl;											
						value = gameDeck.getNextCard(round, user.getScore());
						user.addScore(value);
						validResponse = false;													
						round += 1;
						if (!aceFlag)   {													//making sure that if they already have 1 ace, we don't reset the ace flag if the second card is not an ace
							aceFlag = gameDeck.aceChecker(value);
						}
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
