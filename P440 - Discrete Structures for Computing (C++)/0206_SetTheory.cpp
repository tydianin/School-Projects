/*
set_theory.cpp
Weston Gibson, CISP 440
6 February 2022
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// please, for the love of god, make menus start at 1
const int MENU_FIRST = 1;
const vector<string> MENU = {
    "Union of sets",      "Intersection of sets",         "Complement of a set",
    "Difference of sets", "Symmetric difference of sets", "Exit"};

// common constants
const string PROGRAM_NAME = "Set Theory Helper";
const string DUE_DATE = "6 February 2022";

// common utilities
void ClearScreen();
void Handler();
int StringtoInt(string);
void InputVoid();

// common functions
void ProgramGreeting();
int DisplayMenu(vector<string>);
void DisplaySet(vector<int>);

// program functions
vector<int> GetSet();
vector<int> Union(vector<int>, vector<int>);
vector<int> Intersection(vector<int>, vector<int>);
vector<int> Complement(vector<int>);
vector<int> Difference(vector<int>, vector<int>);
vector<int> SymmetricDifference(vector<int>, vector<int>);

int main() {
  int numChoice = 0;
  vector<int> setA;
  vector<int> setB;
  vector<int> setC;

  // startup sequence
  ClearScreen();
  ProgramGreeting();
  ClearScreen();

  // get two integer arrays
  setA = GetSet();
  setB = GetSet();

  // display menu

  // main loop
  while (numChoice != MENU.size()) {
    // display menu
    ClearScreen();

    cout << "A = { ";
    DisplaySet(setA);
    cout << " }\n" << endl;

    cout << "B = { ";
    DisplaySet(setB);
    cout << " }\n" << endl;

    numChoice = DisplayMenu(MENU);

    switch (numChoice) {
      case 1:
        setC = Union(setA, setB);
        cout << "A u B = { ";
        DisplaySet(setC);
        cout << " }\n" << endl;
        break;
      case 2:
        setC = Intersection(setA, setB);
        cout << "A n B = { ";
        DisplaySet(setC);
        cout << " }\n" << endl;
        break;
      case 3:
        setC = Complement(setA);
        cout << "A' = { ";
        DisplaySet(setC);
        cout << " }\n" << endl;
        setC = Complement(setB);
        cout << "B' = { ";
        DisplaySet(setC);
        cout << " }\n" << endl;
        break;
      case 4:
        setC = Difference(setA, setB);
        cout << "A - B = { ";
        DisplaySet(setC);
        cout << " }\n" << endl;
        break;
      case 5:
        setC = SymmetricDifference(setA, setB);
        cout << "A ^ B = { ";
        DisplaySet(setC);
        cout << " }\n" << endl;
        break;
      case 6:
        cout << "Exiting..." << endl;
        break;
      default:
        cout << "Invalid choice. Please try again.\n" << endl;
        break;
    }

    // kicks out to main loop
    if (numChoice != MENU.size())
      InputVoid();
  }
}

// common utilities
void ClearScreen() {
  cout << "\033[2J\033[1;1H";
}

void Handler() {
  ClearScreen();
  cout << "Please enter a valid option.\n" << endl;
}

void InputVoid() {
  string temp = "";
  cout << "Press ENTER to continue.";
  getline(cin, temp);
}

int StringtoInt(string a) {
  int b;
  try {
    b = stoi(a);
  } catch (...) {
    b = 0;
  }
  return b;
}

// a simple description of what the program does
void ProgramGreeting() {
  string temp = "";
  cout << "Welcome to " << PROGRAM_NAME << "!\n"
       << "This program will allow a user to perform set operations on sets.\n"
       << "\n"
       << "The user may perform the following operations:\n"
       << "  1) Union of two sets\n"
       << "  2) Intersection of two sets\n"
       << "  3) Complement of a set\n"
       << "  4) Difference of two sets\n"
       << "  5) Symmetric difference of two sets\n"
       << "\n"
       << "This assignment was due on " << DUE_DATE << ".\n"
       << endl;
  InputVoid();
}

// a simple menu display using a vector of strings
int DisplayMenu(vector<string> menu) {
  int choice = 0;
  string input = "";

  // loops until user follows directions
  while (choice < MENU_FIRST || choice > menu.size()) {
    cout << "Please select from the following options:\n\n";
    for (int i = 0; i < menu.size(); i++)
      cout << "  " << (i + 1) << ". " << menu[i] << "\n";
    cout << endl << "Enter your choice: ";

    getline(cin, input);
    choice = StringtoInt(input);

    // handle if user doesn't follow directions
    if (choice < MENU_FIRST || choice > menu.size())
      Handler();
  }
  return choice;
}

// displays a vector of integers
void DisplaySet(vector<int> set) {
  int i = 0;
  for (i = 0; i < set.size(); i++) {
    cout << set[i];
    if (i != set.size() - 1)
      cout << ", ";
  }
}

// gets an integer vector from the user
vector<int> GetSet() {
  int size = 0;
  int element = 0;
  string input = "";
  vector<int> set;

  // gets size of vector
  while (size < 1) {
    cout << "Enter the size of the set: ";
    getline(cin, input);
    size = StringtoInt(input);

    // handle if user doesn't follow directions
    if (size < 1)
      Handler();
  }

  // gets elements of vector
  for (int i = 0; i < size; i++) {
    cout << "Enter element " << (i + 1) << ": ";
    getline(cin, input);
    element = StringtoInt(input);
    set.push_back(element);
  }

  // please just use sort();
  sort(set.begin(), set.end());

  // remove duplicate elements
  for (int i = 0; i < set.size() - 1; i++) {
    if (set[i] == set[i + 1]) {
      set.erase(set.begin() + i);
      i--;
    }
  }
  return set;
}

// union of two sets
vector<int> Union(vector<int> setA, vector<int> setB) {
  vector<int> setC;

  // add elements from set A to set C
  for (int i = 0; i < setA.size(); i++)
    setC.push_back(setA[i]);

  // add elements from set B to set C
  for (int i = 0; i < setB.size(); i++) {
    // if element is not in set C, add it
    if (!(find(setC.begin(), setC.end(), setB[i]) != setC.end()))
      setC.push_back(setB[i]);
  }

  // sort set C
  sort(setC.begin(), setC.end());

  return setC;
}

// intersection of two sets
vector<int> Intersection(vector<int> setA, vector<int> setB) {
  vector<int> setC;

  // add elements from set A to set C
  for (int i = 0; i < setA.size(); i++) {
    // if element is in set B, add it
    if (find(setB.begin(), setB.end(), setA[i]) != setB.end())
      setC.push_back(setA[i]);
  }

  // sort set C
  sort(setC.begin(), setC.end());

  return setC;
}

// complement of a set
vector<int> Complement(vector<int> setX) {
  vector<int> setY;

  // add +/- 3 of each element in set X to set Y
  for (int i = 0; i < setX.size(); i++) {
    for (int j = 1; j < 4; j++) {
      setY.push_back(setX[i] - j);
      setY.push_back(setX[i] + j);
    }
  }

  // sort set Y
  sort(setY.begin(), setY.end());

  // remove duplicate elements
  for (int i = 0; i < setY.size() - 1; i++) {
    if (setY[i] == setY[i + 1]) {
      setY.erase(setY.begin() + i);
      i--;
    }
  }

  // remove elements in set X from set Y
  for (int i = 0; i < setX.size(); i++) {
    for (int j = 0; j < setY.size(); j++) {
      if (setX[i] == setY[j]) {
        setY.erase(setY.begin() + j);
        j--;
      }
    }
  }

  return setY;
}

// difference of two sets
vector<int> Difference(vector<int> setA, vector<int> setB) {
  vector<int> setC;

  // add elements from set A to set C
  for (int i = 0; i < setA.size(); i++) {
    // if element is not in set B, add it
    if (find(setB.begin(), setB.end(), setA[i]) == setB.end())
      setC.push_back(setA[i]);
  }

  // sort set C
  sort(setC.begin(), setC.end());

  return setC;
}

// symmetric difference of two sets
vector<int> SymmetricDifference(vector<int> setA, vector<int> setB) {
  vector<int> setC;

  // add elements from set A to set C
  for (int i = 0; i < setA.size(); i++) {
    // if element is not in set B, add it
    if (find(setB.begin(), setB.end(), setA[i]) == setB.end())
      setC.push_back(setA[i]);
  }

  // add elements from set B to set C
  for (int i = 0; i < setB.size(); i++) {
    // if element is not in set A, add it
    if (find(setA.begin(), setA.end(), setB[i]) == setA.end())
      setC.push_back(setB[i]);
  }

  // sort set C
  sort(setC.begin(), setC.end());

  return setC;
}