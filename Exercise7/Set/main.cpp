#include "Set.hpp"
#include <iostream>
#include <string>

void print(std::string text, Set &set) {
  std::cout << text << set << std::endl;
}

int main() {
  Set mengde1;
  Set mengde2;

  mengde1 + 1;
  mengde1 + 1;
  mengde1 + 2;
  mengde1 + 3;
  mengde2 + 3;
  mengde2 + 4;
  mengde2 + 5;

  Set mengdeUnion(mengde1, mengde2);

  print("Mengde 1: ", mengde1);
  print("Mengde 2: ", mengde2);
  print("Unionsmengde: ", mengdeUnion);

  mengde1 = mengde2;
  print("Mengde1 etter = Mengde2: ", mengde1);
}
