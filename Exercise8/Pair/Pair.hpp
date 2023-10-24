#pragma once
#include <iostream>

template <typename Type1, typename Type2>
class Pair {
public:
  Type1 first;
  Type2 second;

  Pair(Type1 first, Type2 second) : first(first), second(second) {}

  Pair operator+(const Pair &other) {
    Pair<Type1, Type2> result = Pair(first + +other.first, second + other.second);
    return result;
  }

  bool operator<(const Pair &other) const {
    if ((first + second) < (other.first + other.second)) {
      return true;
    }
    return false;
  }

  bool operator>(const Pair &other) const {
    if ((this->first + this->second) > (other.first + other.second)) {
      return true;
    }
    return false;
  }

  friend std::ostream &operator<<(std::ostream &out, const Pair<Type1, Type2> &pair) {
    out << "{" << pair.first << " , " << pair.second << "}";
    return out;
  }
};
