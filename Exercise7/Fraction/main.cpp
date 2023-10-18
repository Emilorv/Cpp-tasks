#include "fraction.hpp"
#include <iostream>
#include <string>

using namespace std;

void print(const string &text, const Fraction &broek) {
  cout << text << broek.numerator << " / " << broek.denominator << endl;
}

int main() {
  Fraction fraction1(1, 2);
  Fraction fraction2(3, 4);

  print("fraction1 = ", fraction1);
  print("fraction2 = ", fraction2);

  print("fraction1-5 = ", fraction1 - 5);
  print("5 - fraction2 = ", 5 - fraction2);

  print("5-3-fraction1-7-fraction2 = ", 5 - 3 - fraction1 - 7 - fraction2);
  // Tolkes som (((5-3)-fraction1)-7)-fraction2) = (((2-(1/2))-7)-(3/4)) = 6/4-28/4-3/4 = -25/4
  // Både (integer - fraction), (fraction - integer) og (fraction - fraction) versjonene av operator- blir brukt.
}
