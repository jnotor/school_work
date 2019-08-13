//working as intended. time to clean up and add new features

#include "PlayerDND.h"

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

int main()   {
//////////////////////////////////////////////////////////////////////////////// Player Declaration - probably will want to make these easier to call/edit across implementations; maybe take the string of their name and make the default for that string their stats
    
    PlayerDND Blug(17,98,7,12,0,true,"Blug");
    usleep(1000000);
    PlayerDND Ajax(16,69,6,15,3,true,"Ajax");
    usleep(1000000);
    PlayerDND Elsby(18,73,7,15,2,true,"Elsby");                                              //going to be underpowered until spell save can be implemented
    usleep(1000000);
    PlayerDND Ragnar(15,75,6, 14,1,true,"Ragnar");                                            //calculating if two handed for dmg
    usleep(1000000);
    PlayerDND Baylin(15,53,6,15,1,true,"Baylin");
    usleep(1000000);
/////////////////////////////////////////Bad Guys
    PlayerDND ABD(19,367,15,29,2,false,"ABD");       
    usleep(1000000);
    //PlayerDND kobold2(12,70,4,4,2,false,"kobold2");  
    //usleep(1000000);                   
    //playerdnd generic(AC, HP, tohit, avgdmg, int mod)
//////////////////////////////////////////Total Combantant Storage

vector <PlayerDND> Party = {Blug, Ajax, Elsby, Ragnar, Baylin};
vector <PlayerDND> Enemies = {ABD};                                          //,kobold2
vector <PlayerDND> eParticipants = Party;
eParticipants.insert(eParticipants.end(),Enemies.begin(),Enemies.end());

PlayerDND hold;

/////////////////////////////////////////////////////////////////////////////////roll for intiative

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

////////////////////////////////////////////////////////////////////////////////Start combat

///////////////////////////////////////////intializing health for both sides
int partyHealth = 0;   
int enemyHealth = 0;

for (int i = 0; i < Party.size(); ++i)   {
    partyHealth += Party[i].getHP();
}

for (int i = 0; i < Enemies.size(); ++i)   {
    enemyHealth += Enemies[i].getHP();
}

//////////////////////////////////////////////starting combat
int turn = 0;
int combatRoll = 0;
while ((partyHealth > 0) && (enemyHealth > 0)) {                                //keeps it going until 1 side loses
    for (int j = 0; j < eParticipants.size();++j)   {
        for (int i = 0; i < eParticipants.size(); ++i)   {                    //forgot number of attacks per turn
            if (eParticipants[j].getParty() != eParticipants[i].getParty()) { //allows for fighting only between non allies
                //attack
                //break; only want to break out of the inner for loop tho...
                if ((eParticipants[i].getHP()) > 0 && (eParticipants[j].getHP() > 0))   {
                       combatRoll = eParticipants[j].d20Roll(); 
                       usleep(1000000);
                    if (checkAC(combatRoll, eParticipants[i].getAC())==1) { //checkAC function is not working correctly
                        cout << eParticipants[j].getName() << " rolled a " << combatRoll << " and successfully attacks " << eParticipants[i].getName()<< endl;
                        eParticipants[i].loseHP(eParticipants[j].getAvgDmg());
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

//should probably cout individual health's after combat

/*assumptions:
   -whoever is attacking is always in range
   -enemies are always intelligently, so that they avoid aoe damage
   -no one ever makes a move that would cause an opportunity attack
   -it is always a fight to one side's death
*/
    
    
    return 0;
}

