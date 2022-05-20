/*
setRelations.cpp
Weston Gibson, CISP 440
19 February 2022
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int SET_A[4] = {1, 2, 3, 4};
const char SET_B[3] = {'a', 'b', 'c'};
const vector<string> SET_R = {"(1,a)", "(2,c)", "(3,b)"};
const string S_STR = "S = { (b, a) | a % 2 = 0 }\n";
const int S_INT = 0;

int main() {
  int aRb[4][3] = {0};
  int bSa[3][4] = {0};
  int RS[4][4] = {0};
  string s = "";
  vector<string> rs_str;

  cout << "Sets\n";

  // display a
  cout << "A = { ";
  for (int i = 0; i < 4; ++i) {
    cout << SET_A[i];
    if (i != 3)
      cout << ", ";
  }
  cout << " }\n";

  // display B
  cout << "B = { ";
  for (int i = 0; i < 3; ++i) {
    cout << SET_B[i];
    if (i != 2)
      cout << ", ";
  }
  cout << " }\n";

  cout << "\nRelations\n";

  // display R
  cout << "R = { ";
  for (int i = 0; i < SET_R.size(); ++i) {
    cout << SET_R[i];
    if (i != SET_R.size() - 1)
      cout << ", ";
  }
  cout << " }\n";

  // display S
  cout << S_STR;

  // generate aRb
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      s = "(" + to_string(SET_A[i]) + "," + SET_B[j] + ")";
      if (find(SET_R.begin(), SET_R.end(), s) != SET_R.end())
        aRb[i][j] = 1;
    }
  }

  // display aRb
  cout << "\naRb =  a  b  c\n";
  for (int i = 0; i < 4; ++i) {
    cout << "    " << i + 1 << " ";
    for (int j = 0; j < 3; ++j) {
      cout << "[" << aRb[i][j] << "]";
    }
    cout << "\n";
  }

  // generate bSa
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (SET_A[j] % 2 == 0)
        bSa[i][j] = 1;
    }
  }

  // display bSa
  char c = 'a';
  cout << "\nbSa =  1  2  3  4\n";
  for (int i = 0; i < 3; ++i) {
    cout << "    " << c << " ";
    for (int j = 0; j < 4; ++j) {
      cout << "[" << bSa[i][j] << "]";
    }
    cout << "\n";
    c++;
  }

  // generate RS
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (aRb[i][j] == 1) {
        for (int k = 0; k < 4; ++k) {
          if (bSa[j][k] == 1) {
            RS[i][k] = 1;
          }
        }
      }
    }
  }

  // display RS
  cout << "\nRS =  1  2  3  4\n";
  for (int i = 0; i < 4; ++i) {
    cout << "   " << i + 1 << " ";
    for (int j = 0; j < 4; ++j) {
      cout << "[" << RS[i][j] << "]";
    }
    cout << "\n";
  }

  // generate rs_str
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (RS[i][j] == 1) {
        s = "(" + to_string(i + 1) + ", " + to_string(j + 1) + ")";
        rs_str.push_back(s);
      }
    }
  }

  // display rs_str
  cout << "\nRS = { ";
  for (int i = 0; i < rs_str.size(); ++i) {
    cout << rs_str[i];
    if (i != rs_str.size() - 1)
      cout << ", ";
  }
  cout << " }\n";

  return 0;
}