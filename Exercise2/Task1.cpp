#include <iostream>

using namespace std;
int main() {
  // Initializing variables and pointers
  int i = 3;
  int j = 5;
  int *p = &i;
  int *q = &j;

  // Does operations with pointers
  *p = 7;
  *q += 4;
  *q = *p + 1;
  p = q;

  // Writes values and addresses of variables and pointers to console
  cout << "i: " << i << " " << &i << endl;
  cout << "j: " << j << " " << &j << endl;
  cout << "*p: " << *p << " " << &p << endl;
  cout << "*q: " << *q << " " << &q << endl;
}
