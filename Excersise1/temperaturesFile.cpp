#include <fstream>
#include <iostream>
using namespace std;
void read_temperatures(double temperatures[], int length);

int main() {
  // Initializing variables
  int length = 5;
  double temperatures[length];
  int tempsUnder10 = 0;
  int tempsBetween10And20 = 0;
  int tempsOver20 = 0;

  // Reads temperatures from file
  read_temperatures(temperatures, length);

  // Sorts temperatures in each category
  for (int i = 0; i < length; i++) {
    if (temperatures[i] < 10) {
      tempsUnder10++;
    } else if (10 <= temperatures[i] && temperatures[i] <= 20) {
      tempsBetween10And20++;
    } else if (temperatures[i] > 20) {
      tempsOver20++;
    }
  }

  // Prints the number of temperatures in each category
  cout << "Antall under 10 er " << tempsUnder10 << endl;
  cout << "Antall mellom 10 og 20 er " << tempsBetween10And20 << endl;
  cout << "Antall over 20 er " << tempsOver20 << endl;
}

void read_temperatures(double temperatures[], int length) {
  const char filename[] = "temperatures.dat";
  ifstream file;
  file.open(filename);
  if (!file) {
    cout << "Feil ved åpning av fil" << endl;
    exit(EXIT_FAILURE);
  }
  double temp;
  for (int i = 0; i < length; i++) {
    file >> temp;
    cout << "Temperatur nr " << i + 1 << ": " << temp << endl;
    temperatures[i] = temp;
  }
  file.close();
}
