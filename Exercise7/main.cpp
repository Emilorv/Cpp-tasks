#include "fraction.hpp"
#include <iostream>
#include <string>

using namespace std;

void print(const string &text, const Fraction &broek) {
  cout << text << broek.numerator << " / " << broek.denominator << endl;
}

int main() {
  Fraction fraction1(11, 2);
  Fraction fraction2(3, 4);

  print("fraction1 = ", fraction1);
  print("fraction2 = ", fraction2);

  fraction1 = fraction1 - 5;
}
