// supermarket.cpp
// Weston Gibson, CISP 360
// 4 September 2021

#include <cmath>
#include <iostream>

using namespace std;

// Initialize sales tax rate.
const double TAX_RATE = 0.0775;

// Initialize item array.
const double ITEMS[5] = {11.85, 22.75, 16.25, 10.45, 13.35};

int main() {
  // Initialize extra variables.
  double subtotal = 0, tax = 0, total = 0;

  // Intro statement.
  cout << "Thank you for shopping at\n"
       << "hypothetical supermarket!\n"
       << "-------------------------\n"
       << "Your purchases today:\n";

  // Display each item in item array and calculate subtotal.
  for (int i = 0; i <= 4; i++) {
    cout << "Item " << i + 1;
    cout.width(7);
    cout << "    : $";
    cout.width(12);
    cout << ITEMS[i] << "\n";
    subtotal += ITEMS[i];
  };

  // Calculate tax and total.
  tax = round(subtotal * TAX_RATE * 100.0) / 100.0;
  total = subtotal + tax;

  // Display subtotal, tax rate, tax, and total.
  cout << "-------------------------\n"
       << "Subtotal  : $";
  cout.width(12);
  cout << subtotal << "\nTax ";
  cout.width(4);
  cout << TAX_RATE * 100.0 << "%"
       << " : $";
  cout.width(12);
  cout << tax << "\nTotal     : $";
  cout.width(12);
  cout << total << endl;
}
