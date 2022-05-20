/*
truthTable.cpp
Weston Gibson, CISP 440
19 March 2022
*/

// generates the truth table for p or !(q&r)

#include <iostream>

using namespace std;

int main() {

  // create 3 boolean arrays of size 8
  bool p[8], q[8], r[8];

  // initialize the arrays
  for (int i = 7; i >= 0; i--) {
    // if bit 2^2 == true, p[i] = true
    p[7 - i] = (i & 4) / 4;
    // if bit 2^1 == true, q[i] = true
    q[7 - i] = (i & 2) / 2;
    // if bit 2^0 == true, r[i] = true
    r[7 - i] = i & 1;
  }
  
  // clear the screen
  cout << "\033[2J\033[1;1H";

  // print the truth table
  cout << "p q r p|!(q&r)\n";

  for (int i = 0; i < 8; i++) {
    cout << p[i] << " ";
    cout << q[i] << " ";
    cout << r[i] << "  ";
    cout << (p[i] || !(q[i] && r[i])) << "\n";
  }

  return 0;
}