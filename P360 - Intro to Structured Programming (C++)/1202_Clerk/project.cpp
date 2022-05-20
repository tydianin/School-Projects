// clerk.cpp
// Weston Gibson, CISP 360
// 2 December 2021

#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

using namespace std;

const int COUPLES = 3;

int main() {
  // object vector
  vector<Person> people;

  // variables
  string first;
  string last;

  // clear the screen
  cout << "\033[2J\033[1;1H";

  // loop to add six couples to the vector
  for (int i = 0; i < COUPLES; i++) {
    // get the groom's first and last name
    cout << "Enter the groom's first name: ";
    cin >> first;
    cout << "Enter the groom's last name: ";
    cin >> last;

    // add person to vector
    people.push_back(Person(first, last));

    // get the bride's first and last name
    cout << endl;
    cout << "Enter the bride's first name: ";
    cin >> first;
    cout << "Enter the bride's last name: ";
    cin >> last;

    // add person to vector
    people.push_back(Person(first, last));

    // spacing for next input
    cout << endl;
  }

  // clear the screen
  cout << "\033[2J\033[1;1H";

  // loop to call the operator+ function and getfullname function
  //
  // Template:
  // COUPLE 1
  //   Groom: groom first groom last
  //   Bride: bride first groom last (Maiden Name: bride first bride last)
  int counter = 1;
  for (unsigned int i = 0; i < people.size(); i++) {
    cout << "COUPLE" << counter << endl;
    cout << "  Groom: " << people[i].GetFullName() << endl;
    cout << "  Bride: " << people[i] + people[i + 1]
         << " (Maiden Name: " << people[i + 1].GetFullName() << ")" << endl;
    cout << endl;
    counter++;
    i++;
  }

  // pause to close
  cout << "Press enter to close...";
  cin.ignore();
  cin.get();

  // end of main
  return 0;
}