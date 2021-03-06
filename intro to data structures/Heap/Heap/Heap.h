/* Resources: 
http://www.tech-faq.com/deleting-an-element-from-a-heap.html
https://www.geeksforgeeks.org/heap-sort/
*/
//project to create a heap  via an array
#ifdef HEAP_EXPORTS
#define HEAP_API __declspec(dllexport)
#else
#define HEAP_API __declspec(dllimport)
#endif

// This class is exported from the dll
class HEAP_API Heap {
private:
	int cap;
public:
	//constructor
	Heap(int capacity) { cap = capacity; }
	//randomizer function used in testing - removed
	bool ArrayRandomizer(int A[]);
	//insertion function; puts new value at the back and swaps
	bool Insert(int A[], int iValue);
	//deletion function; swaps back and front, excludes back
	bool Delete(int A[]);
	//helper function for primary HeapSorting Function
	void HeapStart(int A[]);
	//primary HeapSort function; uses L = P*2+1 and R = P*2+2 algorithm; starts at last possible  parent and sorts backwards
	void HeapSort(int A[], int index);
	//utility printing function
	bool Print(int A[]);
	int getCap() { return cap; }
	~Heap() {};
};