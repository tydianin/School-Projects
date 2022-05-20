// phonebook.cpp
// Weston Gibson, CISP 360
// 3 November 2021
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string selection;

  int
    counter = 0,
    found = -1;

  bool isFound = false;

  vector<string> people;
  vector<string> phoneNumbers;

  cout << "Please enter a person's name or part of their name: ";
  cin >> selection;

  // sanitize input to string lower or input validation.

  for (auto i : people) {
    found = i.find(selection, 0);
    if (found != -1) {
      isFound = true;
      found = -1;
      cout << endl << people[counter] << " can be reached at " << phoneNumbers[counter] << "." << endl;
    }
    ++counter;
  }

  if (isFound == false)
    cout << endl << selection << " not found!";

  return(0);
}