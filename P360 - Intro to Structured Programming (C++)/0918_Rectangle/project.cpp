// rectangle.cpp
// Weston Gibson, CISP 360
// 18 September 2021

#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Global constants.
const string PROMPT1 = "  Enter the width.: ";
const string PROMPT2 = "  Enter the length: ";
const string HEADER1 = "**************************\n";
const string HEADER2 = "*    CALCULATION MENU    *\n";
const string HEADER3 = "* 1) Area                *\n";
const string HEADER4 = "* 2) Perimeter           *\n";
const string HEADER5 = "------------------------\n";
const string RESULT1 = "  Rectangle 1 is Greater than Rectangle 2\n";
const string RESULT2 = "  Rectangle 2 is Greater than Rectangle 1\n";
const string RESULT3 = "  The Rectangles are Equal\n";

// Main function.
int main() {
  // Local variables.
  int selection = 0;

  float length[2], width[2], value[2] = {0.00f, 0.00f};

  // Getting base dimensions from the user.
  for (int i = 0; i < 2; i++) {
    cout << "Rectangle " << i << ":\n" << PROMPT1;
    cin >> width[i];
    if (cin.fail()) {
      cout << endl << "Please use rational numbers only (1.23).\n";
      return 13;
    }
    cout << PROMPT2;
    cin >> length[i];
    if (cin.fail()) {
      cout << endl << "Please use rational numbers only (1.23).\n";
      return 13;
    }
    cout << endl;
  }

  // Print menu and request a selection from user.
  cout << HEADER1 << HEADER2 << HEADER1 << HEADER3 << HEADER4 << HEADER1
       << "Enter Selection: ";
  cin >> selection;

  // Switch block for menu selection.
  switch (selection) {
    case 1:
      cout << endl << "You chose Area.\n";
      for (int i = 0; i < 2; i++) {
        value[i] = width[i] * length[i];
      }
      cout << endl << "Area of Rectangles\n";
      break;
    case 2:
      cout << endl << "You chose Perimeter.\n";
      for (int i = 0; i < 2; i++) {
        value[i] = width[i] + length[i] * 2;
      }
      cout << endl << "Perimeter of Rectangles\n";
      break;
    default:
      cout << endl << "Please choose one of the options provided.\n";
      exit(13);
  }

  // Set precision to 2.
  cout << fixed << showpoint << setprecision(2);

  // Print output.
  cout << HEADER5;
  for (int i = 0; i < 2; i++) {
    cout << "Rectangle " << i << ": " << setw(8) << right << value[i]
         << " in\n";
  }
  cout << HEADER5 << endl << "Result:\n";

  // Decision block on what is greater than what.
  if (value[0] != value[1]) {
    if (value[0] > value[1]) {
      cout << RESULT1;
    } else {
      cout << RESULT2;
    }
    return 0;
  }
  cout << RESULT3;
  return 0;
}