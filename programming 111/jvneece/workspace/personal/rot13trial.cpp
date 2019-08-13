//john notorgiacomo - lab 7 - programming for eece - spring 2018

#include <iostream>
#include <vector>
#include <fstream> 
#include <cmath>
#include <string>

using namespace std;

int ASCII_SUM(string key)   {
    int sum = 0;
 for (int i = 0; i <key.size(); ++i)   {
     sum = sum + key.at(i);
 }
 
    return sum;
}

int Rotatoe(string key)   {
    int rotation;
    int sum;
    
    sum = ASCII_SUM(key);
    rotation = (sum % 23) + 3;
    
    return rotation;
}

//encoder function
string eNcode(string userInput)   { ////////////////NEED TO SAVE WHERE THE CAPS ARE AND MAKE THEM CAPS AGAIN AFTER THE ROT13 PROCESS
    vector <int> capsPosition;
    string key;
    int newKey;
    int newKey2;
    
        cin >> key;
    
    newKey = Rotatoe(key);

    for (int i = 0; i < userInput.size(); ++i)   { 
        if (isalpha(userInput.at(i)))   {
            if (isupper(userInput.at(i)))   { ///CONVERTS UPPER TO LOWER
                userInput.at(i) = tolower(userInput.at(i));
                capsPosition.push_back(i); ///saves position of where the uppercase is
            }
            if (userInput.at(i) + newKey > 122)   {  
            newKey2 = 26 - newKey;
            userInput.at(i) = userInput.at(i)-newKey2;
            }
            else  {
                userInput.at(i) = userInput.at(i)+newKey;
            }
        }
        for (int j = 0; j < capsPosition.size(); ++j)   {  //we want this to remember where the uppercases are supposed to be and put them back
            if (i == capsPosition.at(j))    {                //userinput is in the position where there is an upper, which we know from capsPosition, make it an upper again
                userInput.at(i) = toupper(userInput.at(i));
            }
            }
    }
    return userInput;
}
/////////////////////////////////////////////file writer function
void write(string userInput)   {
    ifstream inFS;
    ofstream outFS;
    string toWrite;
    toWrite = eNcode(userInput);
    
    //write encoded text to a file
outFS.open("encodeText.txt"); //open file
if (!outFS.is_open())   { //check and see its open
    cout << "Not opened" << endl;
}
for (int i = 0; i < toWrite.size(); ++i)    {
        outFS << toWrite.at(i);
    }

outFS.close();
}
////////////////////////////////////////decoder function
string decode()   {
ifstream inFS;
string decodedText;
 vector <int> dCapsPosition;
 
string key;
int newKey;
int newKey2;
    
cout << "Enter your key used to encrypt original message: " << endl;
cin >> key;
    
newKey = Rotatoe(key);
  newKey2 = 26 - newKey;

inFS.open("encodeText.txt");

//check that it opened
if (!inFS.is_open())   {
    cout << "Can't open encoded Text" << endl;
}
//read in all the data into a string
while (!inFS.eof())   {
    getline(inFS, decodedText);
    for (int i = 0; i < decodedText.size(); ++i)   { 
        if (isalpha(decodedText.at(i)))   {
             if (isupper(decodedText.at(i)))   { ///CONVERTS UPPER TO LOWER
                decodedText.at(i) = tolower(decodedText.at(i));
                dCapsPosition.push_back(i); ///saves position of where the uppercase is
            }
            if (decodedText.at(i)+ newKey > 122)   {
                decodedText.at(i) = decodedText.at(i)+newKey2;
            }
            else {
                decodedText.at(i) = decodedText.at(i)+newKey2;
            }
        }
            for (int j = 0; j < dCapsPosition.size(); ++j)   {  //puts uppers back in
                if (i == dCapsPosition.at(j))    {               
                    decodedText.at(i) = toupper(decodedText.at(i));
            }
            }

    }
    inFS.close();
    return decodedText;
}
}


int main() {
 
 //////////////////////////////variable declaration
ifstream inFS;
ofstream outFS;
int i = 0;
string userInput;


//////////////////////////////setup
inFS.open("test.txt");

//check that it opened
if (!inFS.is_open())   {
    cout << "Can't open3" << endl;
    return 1;
}

while (!inFS.eof())  {
getline(inFS, userInput);       ///////////getline(input, output) - function from <string>
}

cout << "Enter your encryption string key: " << endl; //could try to do this in a way so as to only pass one thing at a time; start with a function
cout << eNcode(userInput) << endl;
write(userInput);
cout << decode() << endl;
 





    
  return 0;
}

