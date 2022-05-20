// friends.cpp
// Weston Gibson, CISP 360
// 4 November 2021

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int FRIENDS = 5;

struct Person
{
  string name;
  int age;
};

int main() {
  Person persons[5];

  string selection;

  bool isFound = false;

  // Get array contents.
  for (int i = 0; i < FRIENDS; i++) {
    cout << "Enter a name: ";
    getline(cin, persons[i].name);
    cout << "Enter " << persons[i].name << "'s age: ";
    cin >> persons[i].age;
    cout << endl;
    cin.ignore();
  }

  // Allow user to enter a person's name or part of their name.
  cout << "Enter a name or part of a name: ";
  getline(cin, selection);
  cout << endl;

  // Search for name.
  for (int i = 0; i < FRIENDS; i++) {
    if (persons[i].name.find(selection) != string::npos) {
      cout << persons[i].name << " is " << persons[i].age << " years old." << endl;
      isFound = true;
    }
  }

  // If name not found, return output.
  if (isFound == false)
    cout << selection << " not found!" << endl;

  return(0);
}