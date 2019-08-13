// 
// Caleb Cargill, John Notorgiacomo
// C++ Programming, Final Project: BlackJack
//

// Main Function

#include "Play_Game_SlowExport.h"

int main()
{
	Play_Game_SlowExport game;
	
	game.playGame();

    return 0;
}

/////////////////error list
//cant exit game without playing - fixed
//dealer never draws second card, sometimes?
//exits code after one iteration
//surrender command executes double down?
//double down math somehow betting negative chips?
    //but when i double down the dealer now has a second card lol wtf
//double down actually does double down, but now dealer doesnt draw again...
    //double down not awarding correct amount of chips (only awarding original)
//winning with black jack doesnt end the game
//dealer has a joker some how
//gained chips on surrender because our score was still higher than the dealer... but how? cause they had 11
//known score is showing total of both scores; aka we know their hidden card