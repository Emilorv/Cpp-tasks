#include <iostream>
#include <string>

using namespace std;
int main() {
  string word1 = "";
  string word2 = "";
  string word3 = "";

  cout << "Skriv inn 3 ord: ";
  cin >> word1;
  cin >> word2;
  cin >> word3;

  // Skriver ut setningen
  string sentence = word1 + " " + word2 + " " + word3 + ".";
  cout << sentence << endl;

  // Skriver ut lengden på alle ordene og hele setningen
  cout << "Lengde første ord: " << word1.length() << endl;
  cout << "Lengde andre ord: " << word2.length() << endl;
  cout << "Lengde tredje ord: " << word3.length() << endl;
  cout << "Lengde hele setningen: " << sentence.length() << endl;

  // kopierer setningen, og sjekker at den har lengde større en 10
  // Erstatter tegn nr 10-12 (index 9-11) med X hvis setningen er lang nok
  string sentence2 = sentence;
  if (sentence2.size() >= 10) {
    for (int i = 9; i < 12 && i < (int)sentence2.length(); i++) {
      sentence2[i] = 'X';
    }
  } else {
    cout << "Setninger er ikke lang nok til å bytte tegn på plass 10-12" << endl;
  }

  // Skriver ut setningen og den modifiserte setningen
  cout << sentence << endl;
  cout << sentence2 << endl;

  // Definerer lengden på starten av setningen
  int sentence_start_length = 5;
  if ((int)sentence.size() < sentence_start_length) {
    sentence_start_length = sentence.size();
  }
  string sentence_start = sentence.substr(0, sentence_start_length);

  cout << "Start of sentence: " << sentence_start << endl;
  cout << sentence << endl;

  // Bruker find og sjekker om posisjonen til substringen "hallo" ikke er no-position
  int pos = 0;
  if ((pos = sentence.find("hallo")) != (int)string::npos) {
    cout << "Setningen inneholder 'hallo' ved posisjon " << pos << endl;
  } else {
    cout << "Setningen inneholder ikke 'hallo'" << endl;
  }

  // Bruker find med index til å finne forekomster av er, skriver ut til posisjonen blir no-position
  string find_word = "er";
  int index = 0;
  while ((index = sentence.find(find_word, index)) != (int)string::npos) {
    cout << "Det er en '" << find_word << "' ved posisjon " << index << endl;
    index += find_word.length();
  }
}
