// mileage.cpp
// Weston Gibson, CISP 360
// 7 September 2021

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// Initialize standard charges.
const double FLAG_DROP = 5.70, PER_MILE = 2.65, PER_MINUTE = 0.70;

// Initialize printspace characteristics.
const int PRINT_WIDTH = 32, NUMBER_WIDTH = 23;

const char BREAK_LINE = '-';

// For loop used to print the break line with variables from above.
int break_line() {
  for (int i = 0; i < (PRINT_WIDTH); i++) {
    cout << BREAK_LINE;
  }
  return 0;
}

int main() {
  // Initialize extra variables.
  double mileage = 0, subtotalMileage = 0, minutes = 0, subtotalMinutes = 0,
         total = 0;

  // Set fixed to 2.
  cout << fixed << setprecision(2);

  // Obtain expected mileage from user and calculate cost.
  cout << "How many miles are you traveling today?\n"
       << R"(Please enter a number, then press "Enter": )";
  cin >> mileage;
  subtotalMileage = round(PER_MILE * mileage * 100) / 100;

  // Obtain expected waiting time from user and calculate cost.
  cout << "\nHow many minutes do you plan on waiting today?\n"
       << R"(Please enter a number, then press "Enter": )";
  cin >> minutes;
  subtotalMinutes = round(PER_MINUTE * minutes * 100) / 100;

  // Calculate total cost.
  total = FLAG_DROP + subtotalMileage + subtotalMinutes;

  // Display to the user.
  cout << "\nEstimated Taxi Cost\n";
  break_line();
  cout << "\nFlag Drop" << setw(NUMBER_WIDTH) << FLAG_DROP << endl
       << "Distance:" << setw(NUMBER_WIDTH) << subtotalMileage << endl
       << "  (" << subtotalMileage << " Mi @ $" << PER_MILE << ")\n"
       << "Waiting: " << setw(NUMBER_WIDTH) << subtotalMinutes << endl
       << "  (" << subtotalMinutes << " Min @ $" << PER_MINUTE << ")\n";
  break_line();
  cout << "\nTotal" << right << setw(4) << "  $ " << setw(NUMBER_WIDTH) << total
       << endl;
}