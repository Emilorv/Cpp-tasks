#include <iostream>

using namespace std;
const int length = 5;

int main() {
  // Initializing variables
  int tempsUnder10 = 0;
  int tempsBetween10And20 = 0;
  int tempsOver20 = 0;
  double temp;

  cout << "Du skal skrive inn " << length << " temperaturer" << endl;

  // Reads input from user and adds +1 to the corresponding category
  for (int i = 0; i < length; i++) {
    cout << "Temperatur nr " << i + 1 << ":";
    cin >> temp;
    if (temp < 10) {
      tempsUnder10++;
    } else if (10 <= temp && temp <= 20) {
      tempsBetween10And20++;
    } else if (temp > 20) {
      tempsOver20++;
    }
  }

  // Prints the number of temperatures in each category
  cout << "Antall under 10 er " << tempsUnder10 << endl;
  cout << "Antall mellom 10 og 20 er " << tempsBetween10And20 << endl;
  cout << "Antall over 20 er " << tempsOver20 << endl;
}
