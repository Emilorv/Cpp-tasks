#include "Set.hpp"
#include <algorithm>

std::vector<int> list = {};

Set::Set() {
  list = {};
}

Set &Set::operator+(const int integer) {
  Set *thisSet = this;
  if (!thisSet->numberExsistsInSet(integer))
    thisSet->list.emplace_back(integer);
  return *this;
}

Set::Set(Set &set1, Set &set2) {
  list = set1.list;
  for (int number : set2.list) {
    if (!numberExsistsInSet(number))
      list.emplace_back(number);
  }
}
Set &Set::operator=(const Set &otherSet) {
  Set *thisSet = this;
  thisSet->list = otherSet.list;
  return *this;
}

std::ostream &operator<<(std::ostream &out, const Set &set) {
  out << "{";
  for (int i = 0; i < (int)set.list.size(); i++) {
    out << set.list[i];
    if (i != (int)set.list.size() - 1) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}

bool Set::numberExsistsInSet(int number) {
  if (find(list.begin(), list.end(), number) != list.end()) {
    return true;
  }
  return false;
}
