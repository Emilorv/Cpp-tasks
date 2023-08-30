#include <iostream>
#include <vector>

int main() {
  std::vector<double> numbers;

  numbers.emplace_back(5);
  numbers.emplace_back(3);
  numbers.emplace_back(1);
  numbers.emplace_back(4);
  numbers.emplace_back(2);

  std::cout << numbers.front() << std::endl;
  std::cout << numbers.back() << std::endl;

  numbers.emplace(it, 6);
}
