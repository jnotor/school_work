// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RBBST_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RBBST_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RBBST_EXPORTS
#define RBBST_API __declspec(dllexport)
#else
#define RBBST_API __declspec(dllimport)
#endif

enum Color { RED, BLACK };

struct Node
{
	int data;
	bool color;
	Node *left, *right, *parent;

	// Constructor 
	Node(int data)
	{
		this->data = data;
		left = right = parent = NULL;
	}
};

// This class is exported from the dll
class RBBST_API RBTree {
private:
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixViolation(Node *&, Node *&);
public:
	// Constructor 
	RBTree() { root = NULL; }
	void insert(const int &n);
	void inorder();
	void levelOrder();

};
