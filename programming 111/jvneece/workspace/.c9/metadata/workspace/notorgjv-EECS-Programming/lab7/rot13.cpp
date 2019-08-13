{"changed":false,"filter":false,"title":"rot13.cpp","tooltip":"/notorgjv-EECS-Programming/lab7/rot13.cpp","value":"//john notorgiacomo - lab 7 - programming for eece - spring 2018\n\n#include <iostream>\n#include <vector>\n#include <fstream> \n#include <cmath>\n#include <string>\n\nusing namespace std;\n\n//encoder function\nstring eNcode(string userInput)   { ////////////////NEED TO SAVE WHERE THE CAPS ARE AND MAKE THEM CAPS AGAIN AFTER THE ROT13 PROCESS\n    vector <int> capsPosition;\n    for (int i = 0; i < userInput.size(); ++i)   { \n        if (isalpha(userInput.at(i)))   {\n            if (isupper(userInput.at(i)))   { ///CONVERTS UPPER TO LOWER\n                userInput.at(i) = userInput.at(i)+32;\n                capsPosition.push_back(i); ///saves position of where the uppercase is\n            }\n            if (userInput.at(i) <= 109)   {\n            userInput.at(i) = userInput.at(i)+13;\n            }\n            else  {\n                userInput.at(i) = userInput.at(i)-13;\n            }\n        }\n        for (int j = 0; j < capsPosition.size(); ++j)   {  //we want this to remember where the uppercases are supposed to be and put them back\n            if (i == capsPosition.at(j))    {                //userinput is in the position where there is an upper, which we know from capsPosition, make it an upper again\n                userInput.at(i) = userInput.at(i)-32;;\n            }\n            }\n    }\n    return userInput;\n}\n/////////////////////////////////////////////file writer function\nvoid write(string userInput)   {\n    ifstream inFS;\n    ofstream outFS;\n    string toWrite;\n    toWrite = eNcode(userInput);\n    \n    //write encoded text to a file\noutFS.open(\"encodeText.txt\"); //open file\nif (!outFS.is_open())   { //check and see its open\n    cout << \"Not opened\" << endl;\n}\nfor (int i = 0; i < toWrite.size(); ++i)    {\n        outFS << toWrite.at(i);\n    }\n\noutFS.close();\n}\n////////////////////////////////////////decoder function\nstring decode()   {\nifstream inFS;\nstring decodedText;\n vector <int> dCapsPosition;\n    \ninFS.open(\"encodeText.txt\");\n\n//check that it opened\nif (!inFS.is_open())   {\n    cout << \"Can't open2\" << endl;\n}\n//read in all the data into a string\nwhile (!inFS.eof())   {\n    getline(inFS, decodedText);\n    for (int i = 0; i < decodedText.size(); ++i)   { \n        if (isalpha(decodedText.at(i)))   {\n             if (isupper(decodedText.at(i)))   { ///CONVERTS UPPER TO LOWER\n                decodedText.at(i) = tolower(decodedText.at(i));\n                dCapsPosition.push_back(i); ///saves position of where the uppercase is\n            }\n            if (decodedText.at(i) <= 109)   {\n            decodedText.at(i) = decodedText.at(i)+13;\n            }\n            else {\n                decodedText.at(i) = decodedText.at(i)-13;\n            }\n        }\n            for (int j = 0; j < dCapsPosition.size(); ++j)   {  //we want this to remember where the uppercases are supposed to be and put them back\n                if (i == dCapsPosition.at(j))    {                //userinput is in the position where there is an upper, which we know from capsPosition, make it an upper again\n                    decodedText.at(i) = toupper(decodedText.at(i));\n            }\n            }\n\n    }\n    inFS.close();\n    return decodedText;\n}\n}\n\n\nint main() {\n//////////////////////////////variable declaration\nifstream inFS;\nofstream outFS;\nint i = 0;\nstring userInput;\n//////////////////////////////setup\ninFS.open(\"test.txt\");\n\n//check that it opened\nif (!inFS.is_open())   {\n    cout << \"Can't open3\" << endl;\n    return 1;\n}\n\nwhile (!inFS.eof())  {\ngetline(inFS, userInput);       ///////////getline(input, output) - function from <string>\n}\n\n\n///////////////////////////////testing\ncout << \"test case: The quick brown fox jumps over the moon!\" << endl;\ncout << \"should encode to: \" << endl;\ncout << \"Gur dhvpx oebja sbk whzcf bire gur zbba! = \" << eNcode(userInput) << endl;\n\nwrite(userInput);\n\ncout <<  \"should decode to the test case = \" << decode() << endl;\n\n  return 0;\n}\n\n","undoManager":{"mark":-1,"position":-1,"stack":[]},"ace":{"folds":[],"scrolltop":1320,"scrollleft":0,"selection":{"start":{"row":22,"column":19},"end":{"row":22,"column":19},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":{"row":93,"state":"start","mode":"ace/mode/c_cpp"}},"timestamp":1521587267125}