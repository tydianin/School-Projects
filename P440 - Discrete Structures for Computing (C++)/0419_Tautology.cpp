/*
tautology.cpp
Weston Gibson, CISP 440
19 March 2022
*/

// determines if a given proposition is a tautology
// proposition: (p&q) | (!p|(p&!q))

#include <iostream>

using namespace std;

int main() {
  // create arrays
  // p q (p&q) (!p) (p&!q) (!p|(p&!q)) (p&q)|(!p|(p&!q))

  // main arrays
  bool p[4], q[4];
  
  // proposition arrays
  bool p_and_q[4], not_p[4], p_and_not_q[4];
  
  // composition arrays
  bool not_p_or_p_and_not_q[4], p_and_q_or_not_p_or_p_and_not_q[4];

  // initialize the main arrays
  for (int i = 3; i >= 0; i--) {
    // if bit 2^2 == true, p[i] = true
    p[3 - i] = (i & 2) / 2;
    // if bit 2^1 == true, q[i] = true
    q[3 - i] = i & 1;
  }

  // evaluate the proposition arrays
  for (int i = 0; i < 4; i++) {
    p_and_q[i] = p[i] && q[i];
    not_p[i] = !p[i];
    p_and_not_q[i] = p[i] && !q[i];
  }

  // determine the composition arrays
  for (int i = 0; i < 4; i++) {
    not_p_or_p_and_not_q[i] = not_p[i] || p_and_not_q[i];
    p_and_q_or_not_p_or_p_and_not_q[i] = p_and_q[i] || not_p_or_p_and_not_q[i];
  }

  // determine tautology status
  bool tautology = true;
  for (int i = 0; i < 4; i++) {
    if (p_and_q[i] == false && p_and_q_or_not_p_or_p_and_not_q[i] == false) {
      tautology = false;
    }
  }

  // determine contradiction status
  bool contradiction = true;
  for (int i = 0; i < 4; i++) {
    if (p_and_q[i] == true || p_and_q_or_not_p_or_p_and_not_q[i] == true) {
      contradiction = false;
    }
  }

  // clear the screen
  cout << "\033[2J\033[1;1H";

  // print the truth tables
  cout << "p q (p&q) (!p) (p&!q) (!p|(p&!q)) (p&q)|(!p|(p&!q))\n"
       << "---------------------------------------------------\n";
  for (int i = 0; i < 4; i++) {
    cout << p[i] << " ";
    cout << q[i] << "   ";
    cout << p_and_q[i] << "    ";
    cout << not_p[i] << "      ";
    cout << p_and_not_q[i] << "         ";
    cout << not_p_or_p_and_not_q[i] << "                ";
    cout << p_and_q_or_not_p_or_p_and_not_q[i] << "\n";
  }

  // print the result
  if (tautology)
    cout << "The proposition is a tautology.\n";
  else if (contradiction)
    cout << "The proposition is a contradiction.\n";
  else
    cout << "The proposition is neither a tautology nor a contradiction.\n";

  return 0;
}