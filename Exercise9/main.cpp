#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

std::ostream &operator<<(std::ostream &out, const std::vector<int> &table) {
  for (auto &e : table)
    out << e << " ";
  return out;
}

template <typename Type>
void print(std::string text, Type value) {
  std::cout << text << value << std::endl;
}

int main() {

  // Defining vector v1
  std::vector<int> v1 = {3, 3, 12, 14, 17, 25, 30};
  print("v1: ", v1);

  // Iterates v1, checking for first element larger than 15
  auto pos = find_if(v1.begin(), v1.end(), [](int i) {
    if (i > 15) {
      return true;
    }
    return false;
  });

  if (pos != v1.end()) {
    print("First element in v1 that is larger than 15 is: ", v1.at(pos - v1.begin()));
  } else {
    print("Element larger than 15 is not found in v1", "");
  }

  // Defining vector v2
  std::vector<int> v2 = {2, 3, 12, 14, 24};
  print("v2: ", v2);

  // Defining roughly equal function
  auto isRoughlyEqual = [](int number1, int number2) {
    if (abs(number1 - number2) <= 2) {
      return true;
    }
    return false;
  };

  // Using equal to determine if an interval of 5 numbers in v1 is roughly (meaning no bigger difference than 2) equal to v2
  bool isEqual = equal(v1.begin(), v1.begin() + 5, v2.begin(), isRoughlyEqual);
  if (isEqual) {
    print("The first 5 numbers from v1 and v2 is roughly equal", "");
  } else {
    print("The first 5 numbers from v1 and v2 is not roughly equal", "");
  }

  // Using equal to determine if an interval of 4 numbers in v1 is roughly equal to v2
  isEqual = equal(v1.begin(), v1.begin() + 4, v2.begin(), isRoughlyEqual);
  if (isEqual) {
    print("The first 4 numbers from v1 and v2 is roughly equal", "");
  } else {
    print("The first 4 numbers from v1 and v2 is not roughly equal", "");
  }

  // Using replace_copy_if to replace odd numbers with 100 in v1
  replace_copy_if(
      v1.begin(), v1.end(), v1.begin(),
      [](int i) {if (i % 2 == 1) {return true;}return false; },
      100);
  print("Replacing odd numbers with '100' in v1: ", v1);
}
