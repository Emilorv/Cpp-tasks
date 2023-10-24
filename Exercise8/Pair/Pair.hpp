#pragma once
#include <iostream>
template <typename Type1, typename Type2>
class Pair {
public:
  Pair(Type1 first, Type2 second);
  Type1 first;
  Type2 second;
  Pair operator+(const Pair &other);
  Pair operator<(const Pair &other);
  Pair operator>(const Pair &other);

  friend std::ostream &operator<<(std::ostream &os, const Pair &pair);
};
