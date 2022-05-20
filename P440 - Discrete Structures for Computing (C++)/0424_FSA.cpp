/*
fsa.cpp
Weston Gibson, CISP 440
24 April 2022
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;

  bool fsa1 = true, fsa2 = false;

  cout << "Please enter a word to test: ";
  getline(cin, input);

  if (toupper(input[0]) == 'A') {
    fsa1 = false;
    fsa2 = true;
  }

  for (int i = 1; i < input.length(); i++) {
    if (toupper(input[i]) == 'A') {
      fsa1 = !fsa1;
      fsa2 = false;
    }
  }

  if (fsa1)
    cout << "FSA1 accepts the word.\n";
  else
    cout << "FSA1 rejects the word.\n";

  if (fsa2)
    cout << "FSA2 accepts the word.\n";
  else
    cout << "FSA2 rejects the word.\n";

  return 0;
}