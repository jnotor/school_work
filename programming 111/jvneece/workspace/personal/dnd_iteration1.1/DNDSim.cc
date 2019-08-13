#include "PlayerDND.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool checkAC(int dRoll, int eAC)  {
    if (dRoll >= eAC) return true;
    return false;
}

int main()   {
//////////////////////////////////////////////////////////////////////////////// Player Declaration - probably will want to make these easier to call/edit across implementations; maybe take the string of their name and make the default for that string their stats
    PlayerDND Blug(17,98,7,12,0,true,"Blug");
    int BlugInt = Blug.getInt();
    PlayerDND Ajax(16,69,6,15,3,true,"Ajax");
    int AjaxInt = Ajax.getInt();
    PlayerDND Elsby(18,73,7,15,2,true,"Elsby");                                              //going to be underpowered until spell save can be implemented
    int ElsbyInt = Elsby.getInt();
    PlayerDND Ragnar(13,75,6, 14,1,true,"Ragnar");                                            //calculating if two handed for dmg
    int RagnarInt = Ragnar.getInt();
    PlayerDND Baylin(12,53,6,15,1,true,"Baylin");
    int BaylinInt = Baylin.getInt();
/////////////////////////////////////////Bad Guys
    PlayerDND kobold(12,70,14,4,2,false,"kobold1");       
    int KobInt = kobold.getInt();
    PlayerDND kobold2(12,70,14,4,2,false,"kobold2");                     
    int KobInt2 = kobold2.getInt();
//////////////////////////////////////////Total Combantant Storage

vector <PlayerDND> eParticipants = {Blug, Ajax, Elsby, Ragnar, Baylin, kobold, kobold2}; //think we can add the two vectors below to make this easier fopr future use
vector <PlayerDND> Party = {Blug, Ajax, Elsby, Ragnar, Baylin};
vector <PlayerDND> Enemies = {kobold,kobold2};
int size = eParticipants.size();
PlayerDND hold;
int holdInt;
                                                                                // hold = Blug;
                                                                                // cout << hold.getAC();
vector <int> ePInt(size);

for (int i = 0; i < eParticipants.size(); ++i)   {                              //vector storing intiative rolls
    hold = eParticipants.at(i);                                                 
    //nope - have to overload the = operator so that you can actually set hold to something - no i dont. it works, see above. just not working in the below loop
    ePInt.at(i) = hold.getInt(); //dont really need this any more now that i know how to use the [] operator for vectors
    //cout << "Int rolls are: " << ePInt.at(i) << endl;                           //rolls are not random right now...
}
///////////////////sorting for intiative
//cout << "Reordering... " << endl;
for (int j = 0; j < size; ++j)   {
    for (int i = 0; i < size-1; ++i)   {
        if (ePInt.at(i) > ePInt.at(i+1))   {
            //holding temporary values of greater position
           holdInt = ePInt.at(i);
           hold = eParticipants.at(i); 
           //assigning earlier position the lesser value
           ePInt.at(i) = ePInt.at(i+1);
           eParticipants.at(i) = eParticipants.at(i+1); 
           //assigning later position the greater value, which is held by hold
           ePInt.at(i+1) = holdInt;
           eParticipants.at(i+1) = hold;
           
    }
   
}
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
while ((partyHealth > 0) && (enemyHealth > 0)) {                                //keeps it going until 1 side loses
    for (int j = 0; j < eParticipants.size();++j)   {
        for (int i = 0; i < eParticipants.size(); ++i)   {                    //forgot number of attacks per turn
            if (eParticipants[j].getParty() != eParticipants[i].getParty()) { //allows for fighting only between non allies
                //attack
                //break; only want to break out of the inner for loop tho...
                if ((eParticipants[i].getHP()) > 0 && (eParticipants[j].getHP() > 0))   {
                    if (checkAC(eParticipants[j].d20Roll(), eParticipants[i].getAC())==1) {
                        cout << eParticipants[j].getName() << " successfully attacks " << eParticipants[i].getName()<< endl;
                        eParticipants[i].loseHP(eParticipants[j].getAvgDmg());
                        cout << eParticipants[i].getName() << "'s health is now: " << eParticipants[i].getHP() << endl << endl;
                        if (eParticipants[i].getParty())   {
                            partyHealth -= eParticipants[j].getAvgDmg();
                        }
                        else if (!eParticipants[i].getParty())   {
                            enemyHealth -= eParticipants[j].getAvgDmg();
                        }
                    }
                    break;
                }
        //cout << i << endl; //trying to write condition to fight
        //cout << eParticipants[i].getAC() << "compared to " << eParticipants[i+1].getAC() << endl;
            
            }
        }
    }
    // for (int i = 0; i < Party.size(); ++i)   {
    //     partyHealth += Party[i].getHP();
    // }
    cout << "party health is: " <<partyHealth << endl;
    
    // for (int i = 0; i < Enemies.size(); ++i)   {
    //     enemyHealth += Enemies[i].getHP();
    // }
    cout << "enemy party health is: " << enemyHealth << endl;
    ++turn;
    cout << "End of Round: " << turn << endl;
}


    
    //set order of combat in terms of int - note that this only really matters if you've passed/added the intiative bonus
    //for 2 people it would be easy, just check and see which one is greater but what about for more people?
        //int may have to be a next level feature, lets decide the order ourselves for now
    
    //combat can be broken up into a series of rolls and checks in the simulator - going to assume always in range to make the attack
    //combat currently only with melee combatants
    //turn 1 - turn denotes which player is attacking
    // cout << "Blug rolled a: " <<Blug.d20Roll() << endl;
    // //cout << checkAC(Blug.d20Roll(), kobold.getAC()) << endl;
    // if (checkAC(Blug.d20Roll(), kobold.getAC())==1) {
    //     cout << "Blug successfully attacks the kobold!" << endl;
    //     kobold.loseHP(Blug.getAvgDmg());
    //     cout << "kobold health is now: " <<kobold.getHP();
    // }
        //decide who to attack (perhaps with a later feature of priority)
        //attack roll
        //check if attack roll meets enemy AC
        //if it does, apply avg dmg - roll for dmg can be later
        //change turns
    
    
    return 0;
}

