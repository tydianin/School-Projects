// d=st.cpp
// Weston Gibson, CISP 360
// 31 August 2021

#include <iostream>
#include <string>
using namespace std;

// initialize constant
const int SPEED = 57;

// initialize constant array
const int TIMES[3] = {5, 8, 12};

// distance function for calculating distance traveled
int distance(int speed, int time, string str1, string str2, string str3) {
  int result = speed * time;
  cout << str1 << time << str2 << result << str3;
  return 0;
}

int main() {
  // initialize local variables
  string str1 = "The distance the car will travel in ",
         str2 = " hours is: ", str3 = " miles.\n";

  // print intro statement
  cout << "The car is traveling at a speed of " << SPEED << " miles per hour.\n";
  cout << "-----------------------------------------------------\n";

  // calculate and print distance by times above.
  for (int i = 0; i <= 2; i++) {
    distance(SPEED, TIMES[i], str1, str2, str3);
  }
}
