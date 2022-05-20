// groceries.cpp
// Weston Gibson, CISP 360
// 12 September 2021

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// Initialize constants that should be set before execution.
// Initialize number of categories.
const int CATS = 3;

// Initialize discount categories.
const string CAT[CATS] = {"Groceries", "Gas, Air Travel", "Online Purchases"};

// Initialize discount amounts.
const float CAT_DISC[CATS] = {0.01f, 0.02f, 0.03f};

// Initialize printspace characteristics.
const int PRINT_WIDTH = 48, COL_1_WIDTH = 16, COL_2_WIDTH = 14,
          COL_3_WIDTH = 18, MAX_DIGITS = 8;

const char BREAK_LINE = '-';

// For loop used to requesting input from the user.
float prompt(int i) {
  float amount = 0.0f;
  cout << "How much did you spend on " << CAT[i] << "?\n"
       << R"(Please enter a number, then press "Enter": )";
  cin >> amount;
  return amount;
}

// For loop used to print the break line with variables from above.
int break_line() {
  for (int i = 0; i < PRINT_WIDTH; i++) {
    cout << BREAK_LINE;
  }
  return 0;
}

int main() {
  // Initialize logic arrays and variables.
  float cats[CATS], catDisc[CATS], total = 0.0f, totalDisc = 0.0f;

  // Set fixed to 2.
  cout << fixed << setprecision(2);

  // Obtain category 1 spending from user and calculate discount.
  // Calculate total and total discount.
  for (int i = 0; i < CATS; i++) {
    cats[i] = prompt(i);
    catDisc[i] = round(CAT_DISC[i] * cats[i] * 100.0f) / 100.0f;
    total += cats[i];
    totalDisc += catDisc[i];
  }

  // Display table format to user.
  cout << setw(COL_1_WIDTH) << left << "\nCategory" << setw(COL_2_WIDTH + 1)
       << right << "Amount" << setw(COL_3_WIDTH + 1) << "Discount\n";
  break_line();

  // Loop through table categories, amounts, discounts.
  for (int i = 0; i < CATS; i++) {
    cout << endl
         << setw(COL_1_WIDTH) << left << CAT[i] << setw(COL_2_WIDTH) << right
         << cats[i] << setw(COL_3_WIDTH) << catDisc[i];
  }

  // Display total and discount total.
  cout << endl;
  break_line();
  cout << endl
       << setw(COL_1_WIDTH + COL_2_WIDTH - (MAX_DIGITS)) << "$"
       << setw(MAX_DIGITS) << total << setw(COL_3_WIDTH - (MAX_DIGITS)) << "$"
       << setw(MAX_DIGITS) << totalDisc;
}