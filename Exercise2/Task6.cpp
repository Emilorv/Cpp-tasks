
#include <iostream>

using namespace std;

int find_sum(const int *table, int length);

int main() {
  int table[20];

  // fill table with numbers from 1 to 20
  for (int i = 0; i < 20; i++) {
    table[i] = i + 1;
  }

  // Sum of first 10 numbers. Sum of 1 + 2 + .. 10 = 55
  cout << find_sum(table, 10) << endl;

  // Sum of next 5 numbers. Sum of 11 + 12 + .. 15 = 65
  cout << find_sum(&table[10], 5) << endl;

  // Sum of last 5 numbers. Sum of 16 + 17 + .. 20 = 90
  cout << find_sum(&table[15], 5) << endl;
}

// Uses pointer in table and count-length as arguments. For each step add the pointed variable to the total sum and increment the pointer.
int find_sum(const int *table, int length) {
  int sum = 0;
  for (int i = 0; i < length; i++) {
    sum += *table;
    table++;
  }
  return sum;
}
