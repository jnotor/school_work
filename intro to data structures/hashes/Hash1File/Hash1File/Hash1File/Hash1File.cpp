#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Node {
public:
	string key;
	int data;
	//requested == overload
	bool operator== (const Node &n1) {
		if (this->key == n1.key) {
			return true;
		}
		return false;
	}
	//bonus overload for ease of search
	bool operator!= (const Node &n1) {
		if (this->key != n1.key) {
			return true;
		}
		return false;
	}
	//constructor for creation
	Node(string tkey, int tdata) {
		this->key = tkey;
		this->data = tdata;
	}
	//constructor for searching
	Node(string tkey) {
		this->key = tkey;
		this->data = 0;
	}

};

class Hashtable {
public:
	Hashtable();
	//overloaded below;
	Hashtable(int maxNum) {
		max = maxNum;
		count = 0;
		////have to fill the vector with a number of null ptrs = max items
		for (int i = 0; i < max; i++) {
			List.push_back(nullptr);
		}
	}
	bool AddItem(string tkey, int tdata) {
		if (count == max) {
			cout << "At specified maximum capacity" << endl;
			return false;
		}
		int position;
		//create node
		Node *temp = new Node(tkey, tdata);
		//hash the node to determine where it will go
		position = Hash(temp);
		//find the spot in the list it has to go
		for (int i = 0; i <= position; i++) {
			//push a pointer to the node into the vector at that position
			if (i == position) {
				if (List.at(i) == nullptr) {
					List.at(i) = temp;
					count += 1;
					return true;
				}
				else { //if you dont find a null in the first spot, find the next sequential spot that doesnt 
					while (List.at(i) != nullptr)
					{
						if (List.at(i)->key == temp->key) {
							cout << "Duplicate key string. Please try again" << endl;
							return false;
						}
						i++;
					}
					List.at(i) = temp;
					count += 1;
					return true;
				}
			}
		}
		//somehow didnt add; maybe full
		return false;
	}
	/* not discussed in class
	Node RemoveItem(string key) {
		Node removed;
		//call get item
		//iterate through list
		//take it out of the list
		//return the pointer
		return removed;
	}
	*/
	Node *GetItem(string key) {
		Node *temp = new Node(key);
		int position;
		//hash a temporary node with the search key
		position = Hash(temp);
		//see if the node in the list at that position has the same string key
		if (List.at(position) != nullptr) {
			if (*List.at(position) == *temp) {
				return List.at(position);
			}
			else { //no? while they dont, keep iterating the through the list til you find it or you do the whole thing once
				int i = position;
				while (*List.at(i) != *temp) {
					++i;
					//preventing infinite loop; once i == position again, give up
					if (i == position) {
						return nullptr;
					}
					//if you get to end of the list, go to the begining
					if (i == max)
					{
						i = 0;
					}
				}
				return List.at(i);
			}
		}
		else {
			return nullptr;
		}
	}

	int GetLength() {
		//count the number of items not nullptr in the list
		return count;

	}
	~Hashtable() {
		//pop all the items from the vector while its not empty

		while (!List.empty())
		{
			List.pop_back();
		}
	}
	int Hash(Node *temp) {
		int sum = 0;
		for (int i = 0; i < temp->key.size(); i++) {
			sum = temp->key.at(i) + sum;
		}
		sum = sum % max;
		return sum;
	}

private:
	int max; //limits the size of the vector
	int count; //keeps track of the number of actual nodes in the vector
	vector <Node*> List;
};

int main() {
	int choice, inData, hashMax = 0;
	bool done = false;
	bool check;
	string inKey;
	string searchKey;
	Node *temp = new Node("temp");
	cout << "Welcome to Hash.cpp" << endl;
	cout << "Input max size of the hashtable to create: " << endl;
	cin >> hashMax;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(10, '\n'); // not sure i need this line
		cout << "Please enter a NUMBER to define the max size of the hash table" << endl;
		cin >> hashMax;
	}
	hashMax = fabs(hashMax);
	Hashtable H(hashMax);
	//choice loop
	while (done == false)
	{
		cout << "Please choose from one of the choices below: " << endl;
		cout << "1. Find number of items in HashTable" << endl;
		cout << "2. Add an item to the table" << endl;
		cout << "3. Search for an item in the table" << endl;
		cout << "4. Quit" << endl;
		cin >> choice;
		while (cin.fail()) {
			cin.clear();
			cout << "Please enter a 1,2,3 or 4 as your choice." << endl;
		}
		//choices
		switch (choice) {
		case 1: //get length
			cout << "Counting the number of items in the list..." << endl;
			cout << H.GetLength() << endl;
			break;
		case 2: //Add an item
		//add its key
			cout << "Input a String as a Key : " << endl;
			cin >> inKey; //dont think you need fail prevention here because anything can be a string, no?
			//add its data
			cout << "Input Data Value: " << endl;
			cin >> inData;
			while (cin.fail()) {
				cin.clear();
				//cin.ignore() not sure i need this line
				cout << "Please enter a NUMBER to define the data value" << endl;
				cin >> inData;
			}
			check = H.AddItem(inKey, inData);
			if (check)
			{
				cout << "Item has been added." << endl;

			}
			else
			{
				cout << "Item could not be added." << endl;
			}

			break;
		case 3: //search an item
			cout << "Please enter a string to try to find in the hashtable (note that it will have to be exactly the same): " << endl;
			cin >> searchKey;
			temp = H.GetItem(searchKey);
			if (temp != nullptr) {
				cout << "The Key was: " << temp->key << endl;
				cout << "It has data value: " << temp->data << endl;
			}
			else {
				cout << "Node not found please try again" << endl;
			}
			break;
		case 4: //quit
			done = true;
			cout << "Thank you for using hash.cpp. Goodbye" << endl;
			break;
		default:
			cout << "Invalud choice, please try again." << endl;
			done = false;
			break;
		}
	}
	return 0;
};