#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

////////////////////////////////////////////////////////////////////////////////pointer magic

// int main() {
// 	int x = 2, y = 3, t = 9;
// 	int *xp = &x;
// 	int *yp = &y;
// 	int *rp;

// 	rp = yp;
// *xp = t;  
// *yp = 11;
	
// 	cout << *xp << "," << y << "," << *yp << "," << x << endl; //x is printing 9 now, presumably because the pointer's value was changed and its tied to the pointer
// }

////////////////////////////////////////////////////////////////////////////////Void Trick
// class Circle{
//   public:
//   Circle(){
//      radius = 5;
//   }

//   void setRadius(double radius_temp){ //doesnt return anything and isnt passing by reference
//      double radius = radius_temp;
//      //radius = radius_temp; //if we wanted it to work, we'd have to write it this way. the above doesnt work because its redeclared the variable, radius, and thus isnt updating the previous variable
//   }

//   double getRadius() const{
//      return radius;
//   }
//   double radius;
// };

// int main(){
//   Circle bob;

//   cout << bob.getRadius() << ",";
   
// 		bob.setRadius(10); //doens't change radius, see above
   
//   cout << bob.getRadius() << ",";
   
// 		bob.radius = 20;
   
//   cout << bob.getRadius() << ",";
//   cout << bob.radius;

//   return 0;
// }

////////////////////////////////////////////////////////////////////////////////Pointer and PBR

// void X(int a, int &b, int *c)
// {
// b = *c + a;
// 	*c = b*a;
// }

// int main()
// {
// int x = 2, y = 3, t = 9;

// X(x, y, &t);

// cout << x << y << t << endl;
// }

////////////////////////////////////////////////////////////////////////////////2D array

// int main()   {
	  
// 	  int g2dArray[5][3];

// for(int row = 0; row < 5; row++) {
// 	for(int col = 0; col < 3; col++) {
// 		g2dArray[row][col] = col;
// 	}
// }

//  cout << g2dArray[2][2]  << endl; 
//  cout << g2dArray[3][2] << endl;

// }

////////////////////////////////////////////////////////////////////////////////more pointer stuff


// int w = 99;

// int f(int &w, int x, int *z){
//   static int g = 1;  
  
//   if (w < *z){
//     int t = *z;
//     *z = w;
//     w = t;
//   }else{
// 	g++;
//   }
//   x = 1;
//   return (*z);
//   *z = 13;
// }
 
// int main(){
//   int a = 5;
//   int b = 10;
//   int t = 20;
//   int d = 30;
//   int w = 100;
 
//   w = f(a, b, &t);
//   cout << a << "," << b << "," << t << "," << d << "," << w << endl; 

//   return 0;
// }

////////////////////////////////////////////////////////////////////////////////class example

// class C {
// 	public:
// 		C() { 
// 			cout << "Object C Instantiated" << endl;
// 		}
// 		C(int input) {
// 			cout << "Object has value of " << input << endl; 

// 		}
// 		C(double input) {
// 			cout << "Object has value of "  << input << endl; 

// 		}
// 		~C() {
// 			cout << "Object C destroyed" << endl; //auto destroys class objects once no longer in use.
// 		}

// };

// int main() {
// 	C X;
// 	C X1(3);
// 	C X2(3.5);
// 	return 0;
// }

// int * myFunction (int a [ ], int size){
// 	int * temp = new int [size];
//   	for (int i = 0; i < size; i++)   {
// 		temp[i] = 2 * a[i];
//   	}
//   	return temp;
// }

// int main() {
// 	int a[] = {1, 2, 3, 4, 5};
// 	int *b;
// 	b = myFunction (a, 5);
// 	cout << *b << endl; //prints only the first element of the array. see below for printing the rest. 
	
// 	// for (int i = 0; i <5; ++i)   {
// 	// cout << b[i] << endl;
// 	// }
//  }

// struct Node {
//     int x;
//     Node* next;
// };

// class S {
//     public:
//         int size();
//         S() { head = NULL;}
//     private: 
//         Node* head;
// };

// int S::size()   {
//     int count = 0;
//     if (head == NULL) {
//         return 0;
//     }
//     Node* ptr = head;
//     while (ptr != NULL)   {
//         ptr = ptr->next;
//         count++;
//     }
//     return count;
// }

// int main ()   {
//     S trial;
//     int count = trial.size();
//     cout << count;
//     return 0;
// }
////////////////////////////////////////////////////////////////////////////////obj bool

// class myclass{
// public:
// int x;
// int a[4];
// myclass(){
// x = 4;
// for (int i = 0; i < 4; i++){
// a[i] = i;
// }
// }
// myclass(int i, int z[]){
// x = i;
// for (int j = 0; j < 4; j++){
// a[j] = z[j];
// }
// }
// };
// bool operator>(const myclass left, const myclass right){
// for (int i = 0; i < 4; i++){
// if (left.a[i] < right.a[i])
// return false;
// }
// return true;
// }
// int main(){
//     int i = 0;
// int x[4] = {0,1,2,5};
// myclass obj1;
// myclass obj2(3,x);
// cout << bool(obj2 > obj1);

// return 0;
// }

// int * reverse (int const *list, const int size)
// {
//     int result [6];
//     for (int i = 0; i < size; i++)
//     {
//         result [i] = list [i];
//     }
//     return result;
// }

// int main()
// {
//     int list [] = {1, 2, 3, 4, 5, 6};
//     int *pList = reverse(list, 6);
//     for (int i = 0; i < size; i++)                                           //size not declared in the main; would yield a compiler error. if size was or if 6 was put there, it would yield the intended first outcome and then random numbers, as result is a local variable in that function
//       cout << pList[i] << endl;
//     return 0;
// } 
