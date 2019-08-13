/*assumptions:
   -whoever is attacking is always in range
   -enemies are always intelligently, so that they avoid aoe damage
   -no one ever makes a move that would cause an opportunity attack
   -it is always a fight to one side's death
   -the only way someone is removed from combat is death; once below zero they stay down
*/

//when i hard set the combat roll to 20, it went into an infinite loop

#include "PlayerDND2.h"
//#include "Combat.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <unistd.h>

using namespace std;

bool checkAC(int dRoll, int eAC)  {
    if (dRoll >= eAC) return true;
    return false;
}

void establishOrder(vector <PlayerDND2> &eParticipants) {
   PlayerDND2 hold;
   
    cout << "Int rolls are: " << endl;
    
    for (int i = 0; i < eParticipants.size(); ++i)   {                              
        cout << eParticipants[i].getName() << " rolled a " << eParticipants[i].getInt() << endl;                      //rolls are not random right now...
    }

//////////////////sorting for intiative                                         //is working

    for (int j = 0; j < eParticipants.size(); ++j)   {
        for (int i = 0; i < eParticipants.size()-1; ++i)   {
            if (eParticipants[i].getInt() < eParticipants[i+1].getInt())   {
                hold = eParticipants.at(i);
                eParticipants.at(i) = eParticipants.at(i+1);
                eParticipants.at(i+1) = hold;
            }
        }
    }

    cout << endl << "combat order: " << endl;
    for (int i = 0; i < eParticipants.size(); ++i)   {
        cout << eParticipants[i].getName() << endl;
    }
}

void startingHealth(vector <PlayerDND2> Party,vector <PlayerDND2>  Enemies,int &partyHealth, int &enemyHealth) {

for (int i = 0; i < Party.size(); ++i)   {
    partyHealth += Party[i].getHP();
}

for (int i = 0; i < Enemies.size(); ++i)   {
    enemyHealth += Enemies[i].getHP();
}
}

void combat(int partyHealth, int enemyHealth,vector <PlayerDND2> &eParticipants) {
    int combatRoll = 0;
    int turn = 0;
    int dmgDealt = 0;
    while ((partyHealth > 0) && (enemyHealth > 0)) {                                //keeps it going until 1 side loses
        for (int j = 0; j < eParticipants.size();++j)   {
            for (int i = 0; i < eParticipants.size(); ++i)   {                    //forgot number of attacks per turn
                if (eParticipants[j].getParty() != eParticipants[i].getParty()) { //allows for fighting only between non allies
                    if ((eParticipants[i].getHP()) > 0 && (eParticipants[j].getHP() > 0))   {
                        combatRoll = 20;//eParticipants[j].d20Roll();
                        usleep(1000000);
                        dmgDealt = eParticipants[j].getAvgDmg();
                        if (combatRoll >= 20)   {
                            dmgDealt = dmgDealt * 2;
                            cout << "Critical Hit!" << endl;
                        }
                        combatRoll = 20;//[j].d20Roll() + eParticipants[j].getToHit(); 
                        usleep(1000000);
                        if (checkAC(combatRoll, eParticipants[i].getAC())==1) { 
                            cout << eParticipants[j].getName() << " rolled a " << combatRoll << " and successfully attacks " << eParticipants[i].getName()<< endl;
                            eParticipants[i].loseHP(dmgDealt);
                            cout << eParticipants[i].getName() << "'s health is now: " << eParticipants[i].getHP() << endl << endl;
                            if (eParticipants[i].getParty())   {
                                partyHealth -= eParticipants[j].getAvgDmg();
                            }
                            else if (!eParticipants[i].getParty())   {
                                enemyHealth -= eParticipants[j].getAvgDmg();
                            }
                        }
                        else {
                            cout << eParticipants[j].getName() << " poop rolled a " << combatRoll << endl;
                            cout << "Fail to attack!" <<endl << endl;
                        }
                        break;
                    }
                }
            }
        }
        cout << "party health is: " <<partyHealth << endl;
        cout << "enemy party health is: " << enemyHealth << endl;
        ++turn;
        cout << "End of Round: " << turn << endl;
    }
}

void howAreWeFeeling(vector <PlayerDND2> eParticipants)   {
    for (int i = 0; i <eParticipants.size(); ++i)   {
        cout << eParticipants[i].getName() << " is at " << eParticipants[i].getHP() << " health" << endl;
    }
}

int main()   {
//////////////////////////////////////////////////////////////////////////////// Player Declaration - probably will want to make these easier to call/edit across implementations; maybe take the string of their name and make the default for that string their stats
    
    PlayerDND2 Blug(17,98,7,12,0,true,"Blug");
    usleep(1000000);
    PlayerDND2 Ajax(16,69,6,15,3,true,"Ajax");
    usleep(1000000);
    PlayerDND2 Elsby(18,73,7,15,2,true,"Elsby");                                              //going to be underpowered until spell save can be implemented
    usleep(1000000);
    PlayerDND2 Ragnar(15,75,6, 14,1,true,"Ragnar");                                            //calculating if two handed for dmg
    usleep(1000000);
    PlayerDND2 Baylin(15,53,6,15,1,true,"Baylin");
    usleep(1000000);
/////////////////////////////////////////Bad Guys
    PlayerDND2 zElite(17,42,6,9,3,false,"Zealous Elite");                       //criticals not implemented at all yet      
    usleep(1000000);
    PlayerDND2 fElite(18,42,6,9,3,false,"Fervent Elite");                       //doesnt have his recharge move
    usleep(1000000);
    PlayerDND2 gElite(19,42,6,7,3,false,"Zealous Elite");                       //grivious wounds and will of the emperor not implemented yet
    usleep(1000000);
    //usleep(1000000);                   

//////////////////////////////////////////Total Combantant Storage

    vector <PlayerDND2> Party = {Blug, Ajax, Elsby, Ragnar, Baylin};
    vector <PlayerDND2> Enemies = {zElite, fElite, gElite};                     
    vector <PlayerDND2> eParticipants = Party;
    eParticipants.insert(eParticipants.end(),Enemies.begin(),Enemies.end());
    
    int partyHealth = 0;   
    int enemyHealth = 0;

    establishOrder(eParticipants);
    
    startingHealth(Party, Enemies, partyHealth, enemyHealth);
    
    combat(partyHealth, enemyHealth, eParticipants);

    howAreWeFeeling(eParticipants);

    return 0;
}

/*so, what's missing
-critical hit (wont implement crit fails)
-number of attacks
-spell saves and thus the 6 stats from which to pull them - have to differentiate between attack types then, at least whether its against AC or a DC spell save, somehow maybe like  mage flag?
-recharge moves
-support spells and the decision to use one instead of attack... not sure it will be implemented
-(dis)advantage

////////////////may be impossible
-legendary actions
-lair actions
-movement
-control spells
*/

