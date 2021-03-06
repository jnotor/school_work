// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the HASHDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// HASHDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HASHDLL_EXPORTS
#define HASHDLL_API __declspec(dllexport)
#else
#define HASHDLL_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

class Node {
public:
	std::string key;
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
	Node(std::string tkey, int tdata) {
		this->key = tkey;
		this->data = tdata;
	}
	//constructor for searching
	Node(std::string tkey) {
		this->key = tkey;
		this->data = 0;
	}

};

// This class is exported from the dll
class HASHDLL_API Hashtable {
public:
	Hashtable();
	Hashtable(int maxNum);
	int getMax() { return List.size(); }
	bool AddItem(std::string tkey, int tdata);
	Node *GetItem(std::string key);
	int GetLength() { return count; }
	int Hash(Node *temp);
	~Hashtable();
private:
	int max; //limits the size of the vector
	int count; //keeps track of the number of actual nodes in the vector
	std::vector <Node*> List;
};