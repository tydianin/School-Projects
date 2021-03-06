/*
dec-to-hex.cpp
Weston Gibson, CISP 310
30 January 2022
*/

// converts a binary number to decimal, then to hexadecimal

#include <algorithm>
#include <iostream>

using namespace std;

int Power(int, int);
int Dec(string);
string Hex(int);

int main() {
  int dec = 0;
  string bin = "";
  string hex = "";

  cout << "Enter a binary number: ";
  getline(cin, bin);

  dec = Dec(bin);
  cout << "The decimal equivalent is: " << dec << endl;

  hex = Hex(dec);
  cout << "The hexadecimal equivalent is: " << hex << endl;

  return 0;
}

// raises base to exp
int Power(int base, int exp) {
  int result = 1;
  for (int i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

// converts string binary to int decimal
int Dec(string bin) {
  int dec = 0;
  for (auto &ch : bin) {
    if (bin[i] == '1')
      dec += Power(2, len - i - 1);
  }
  return dec;
}

// converts int decimal to string hex
string Hex(int dec) {
  string hex = "";
  int remainder = 0;
  while (dec > 0) {
    remainder = dec % 16;
    if (remainder < 10)
      hex += remainder + 48;
    else
      hex += remainder + 55;
    dec /= 16;
  }
  reverse(hex.begin(), hex.end());
  return hex;
}
