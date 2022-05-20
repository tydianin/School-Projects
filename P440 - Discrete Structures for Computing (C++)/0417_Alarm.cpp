/*
alarm.cpp
Weston Gibson, CISP 440
17 April 2022
*/

// controls the three switches of the alarm system
// two switches must be on to turn on the alarm
// program must not use if or comparison for alarm status

#include <iostream>
#include <string>

using namespace std;

void TruthTable();

int main() {
  bool site[3] = {false, false, false};
  bool alarm = false, exit = false;
  string siteText[2] = {"Off", "On"};
  string alarmText[2] = {"Disarmed", "Armed"};
  int choice;

  // main loop
  while (exit != true) {
    cout << "\n\n\n"
         << "Site 1: " << siteText[site[0]] << "\n"
         << "Site 2: " << siteText[site[1]] << "\n"
         << "Site 3: " << siteText[site[2]] << "\n"
         << "Alarm: " << alarmText[alarm] << "\n"
         << "\n"
         << "Menu:\n"
         << "1. Turn on site 1\n"
         << "2. Turn on site 2\n"
         << "3. Turn on site 3\n"
         << "4. Turn off site 1\n"
         << "5. Turn off site 2\n"
         << "6. Turn off site 3\n"
         << "7. Print truth table\n"
         << "8. Exit\n"
         << "\n"
         << "Enter your choice: ";

    cin >> choice;

    switch (choice) {
      case 1:
        site[0] = true;
        break;
      case 2:
        site[1] = true;
        break;
      case 3:
        site[2] = true;
        break;
      case 4:
        site[0] = false;
        break;
      case 5:
        site[1] = false;
        break;
      case 6:
        site[2] = false;
        break;
      case 7:
        TruthTable();
        break;
      case 8:
        exit = true;
        break;
      default:
        cout << "Invalid choice.\n";
    }

    // set alarm status
    alarm = (site[0] && (site[1] || site[2])) || (site[1] && site[2]);
  }

  return 0;
}

void TruthTable() {
  string temp = "";

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

  // print the truth table
  cout << endl
       << "p q r p&(q|r)|q&r\n"
       << "---------------------\n";
  for (int i = 0; i < 8; i++) {
    cout << p[i] << " " << q[i] << " " << r[i] << "  "
         << ((p[i] && (q[i] | r[i])) || (q[i] && r[i])) << "\n";
  }
}