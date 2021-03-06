// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MY5SORTS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MY5SORTS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MY5SORTS_EXPORTS
#define MY5SORTS_API __declspec(dllexport)
#else
#define MY5SORTS_API __declspec(dllimport)
#endif

class MY5SORTS_API CMy5sorts {
public:

	CMy5sorts() {
		ArrayRandomizer(A10, 10);
		ArrayRandomizer(A100, 100);
		ArrayRandomizer(A500, 500);
		ArrayRandomizer(A5k, 5000);
		ArrayRandomizer(A25k, 25000);
	}
	////supporting merge function for merge sort
	void mergeKid(int A[], int start, int mid, int end);
	//function to implement merge sort
	void mergeParent(int A[], int start, int end);
	////utility function for quick sort
	int partition(int A[], int low, int high);
	//function to implement quick sort
	void QuickSort(int A[], int low, int high);
	////utility function for Radix sort #1
	int getMax(int A[], int n);
	////utility function for Radix sort #2
	void countSort(int A[], int n, int exp);
	//function to implement radix sort
	void RadixSort(int A[],int n);
	//function to implement insertion Sort
	void inSert(int A[], int n);
	////utility function for a few other functions
	void swap(int *alpha, int *beta);
	//function to implement Bubble Sort
	void BubSort(int A[], int n);
	//used by constructor to give us arrays to sort
	void ArrayRandomizer(int A[], int n);
	//interfaces for sorting choices
	void Sort();
	//function made to simply be able to visually test if arrays are actually being sorted
	void PrintTest(int A[], int n);
	~CMy5sorts() {	}
private:
	int A10[10];
	int A100[100];
	int A500[500];
	int A5k[5000];
	int A25k[25000];
	
};


//extern MY5SORTS_API int nMy5sorts;

//MY5SORTS_API int fnMy5sorts(void);
