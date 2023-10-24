#include <iomanip>
#include <iostream>
#include <string>

template <typename Type>
void print(std::string text, Type value) {
  std::cout << text << value << std::endl;
}

void print(std::string text, double value, int precision) {
  std::cout << text << std::setprecision(precision) << value << std::endl;
}

template <typename Type>
bool equal(Type a, Type b) {
  if (a == b)
    return true;
  return false;
}

bool equal(double a, double b) {
  double tolerance = 0.00001;
  if (b < a - tolerance || b > a + tolerance) {
    return false;
  }
  return true;
}

int main() {
  print("Sjekk integer likhet: ", "");
  int number1 = 5;
  int number2 = 4;
  print("Tall1: ", number1);
  print("Tall2: ", number2);
  print("Like?: ", equal(number1, number2));

  std::cout << std::endl;
  print("Sjekk double likhet: ", "");
  double dnumber1 = 1.00000;
  double dnumber2 = 0.999989;
  print("Tall1: ", dnumber1, 8);
  print("Tall2: ", dnumber2, 5);
  print("Like?: ", equal(dnumber1, dnumber2));
}
