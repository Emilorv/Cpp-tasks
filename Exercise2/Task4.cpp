
int main() {
  int a = 5;
  int &b = a; // En referanse kan ikke erklæres uten en variabel å referere til. Dermed setter vi at b refererer til a.
  int *c;
  c = &b;
  a = b + *c; // a og b er ikke pekere. Dermed fjerner vi "*"
  b = 2;      // Siden b er initiert som en referanse, trenger vi ikke lengere å bruke &
}
