// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the STACK13_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// STACK13_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STACK13_EXPORTS
#define STACK13_API __declspec(dllexport)
#else
#define STACK13_API __declspec(dllimport)
#endif
#include <queue>
#include <stack>
#include <list>
#include <iostream>
#include <string>

enum suit_t { //are kind of default to integer values
	HEARTS,
	SPADES,
	DIAMONDS,
	CLUBS
};

class STACK13_API Cards {
public:
	Cards(int rank, suit_t suit) : m_rank(rank), m_suit(suit) {}
	suit_t GetSuit () const {return m_suit;}
	int GetRank() const {return m_rank;}
private: 
	int m_rank;
	suit_t m_suit;
};

class STACK13_API Player {
public: 
	Player(std::string name) :pName(name) {};
	std::string getName() const {
		return pName;
	}
	void DrawCard(const Cards * c) { 
		//count the hand size first, to make sure they can do so - probably needs to be a separate function
		//if (pHand.size() > 5) {
		//	return false;
		//}
		pHand.push_back(c);
	}
	const Cards * RemoveCardFromHand(int indexToList) {
		const Cards * retVal = nullptr;
		int i = 0;
		for (auto it = pHand.begin(); i <= indexToList; it++, i++)
		{
			if (i == indexToList)
			{
				retVal = *it;
				pHand.remove(retVal);
				return retVal;
			}
		}

		return retVal;
	} //note that this is only removing it from the hand, not adding it back into the stack
	void StackCard(const Cards * c) { 
		pStack.push_back(c);
	}
	void NewHand(std::list<const Cards*> Hand); //discard all cards, draw 5 more;end turn
	//turnender may need to be a game function...
	bool TurnEnder() { //check and see if they can place more cards on their stack and the state of their hand; force discard if card count = 6;
		//was passing std::list<const Cards*> Hand, std::stack<const Cards*> Stack before
		//think it should just use this->Hand and this->Stack respectively
		return true;
	}
	virtual ~Player() {
		std::cout << "Deleting " << pName << std::endl;
	}
//i think for the below two, i dont have to pass the hand or stack. just call them in the function
//void ViewHand(std::list<const Cards*> Hand);
//void topStack(std::stack<const Cards*> Stack);
private:
	std::string pName;
	std::list<const Cards *> pStack;
	std::list<const Cards *> pHand; //need to write get and set for hand and stack; these two should not be public, they should be private
};
