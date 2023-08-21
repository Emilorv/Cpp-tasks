#include <iostream>

using namespace std;
int main() {
  double number = 0;
  double *pointer = &number;
  double &reference = number;

  cout << "Initial value of number: " << number << endl;
  cout << "Three ways to assign a value to number:" << endl;

  // 1 By using number
  number = 1;
  cout << number << endl;

  // 2 By using the value of the pointed variable
  *pointer = 2;
  cout << number << endl;

  // 3 By using the reference
  reference = 3;
  cout << number << endl;
}
