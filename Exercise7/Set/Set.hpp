#pragma once
#include <iostream>
#include <vector>

class Set {
public:
  std::vector<int> list;

  Set();
  Set(Set &set1, Set &set2);
  Set &operator+(const int integer);
  Set &operator+(const Set &otherSet) const;
  Set &operator=(const Set &otherSet);
  friend std::ostream &operator<<(std::ostream &out, const Set &set);

  bool numberExsistsInSet(int number);
};
