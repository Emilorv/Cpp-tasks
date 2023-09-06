#include <algorithm>
#include <iostream>
#include <vector>

bool finnesTallet(std::vector<double> numbers, double number);

int main() {
  std::vector<double> numbers;

  // Setter inn tallene fra 1 til 5
  numbers.emplace_back(5);
  numbers.emplace_back(3);
  numbers.emplace_back(1);
  numbers.emplace_back(4);
  numbers.emplace_back(2);

  // Skriver ut første og siste element i listen
  std::cout << numbers.front() << std::endl;
  std::cout << numbers.back() << std::endl;

  // Setter inn et tall etter første element og verifiserer at første element ikke har endret seg
  numbers.emplace(numbers.begin() + 1, 6);
  std::cout << numbers.front() << std::endl;

  // Bruker "finnesTallet()" for å sjekke om tallet finnes i listen
  finnesTallet(numbers, 6);
  finnesTallet(numbers, 1);
  finnesTallet(numbers, 0);
  finnesTallet(numbers, 7);
}

bool finnesTallet(std::vector<double> numbers, double number) {
  if (find(numbers.begin(), numbers.end(), number) != numbers.end()) {
    std::cout << "Tallet " << number << " finnes i listen" << std::endl;
    return true;
  }
  std::cout << "Tallet " << number << " finnes ikke i listen" << std::endl;
  return false;
}
