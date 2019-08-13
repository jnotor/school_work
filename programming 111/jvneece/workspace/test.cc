//testing what happens when you cin the wrong variable type
#include <iostream>
#include <string> 
#include <vector>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <unistd.h> //need this

using namespace std;

int dieRoller(int a,int &b)   {
    // srand(time(NULL));
    // int dieRoll = rand() %20 + 1;
    int dieRoll;
    
    b = b-1;
    a = a-1;
dieRoll = a * b;
    return dieRoll;
}
int main()   {

// vector <int> trial = {7,23,2,3,9,10};
// sort(trial.begin(),trial.end());

// for (int i = 0; i < trial.size();++i)   {
//     cout << trial.at(i) << endl;
// }

    
 
    // for (int i = 0; i <10; ++i)   {
    //  cout << dieRoller() << endl;
    //  usleep(1000000); //gotta be at least a second for it to change
    // }
    
    int a = 6;
    int b = 2;
    //dieRoller(a,b);
    cout << dieRoller(a,b) << endl;
    cout << a << endl;
    cout << b << endl;
// int integer = 22;
// int *var = &integer;

// cout << *var << endl;

// cin >> integer;

// cout << integer;

// if (integer == 0)   {
//     cout << "hi";
// }
return 0;
}

//conclusion, it returns a zero, or false