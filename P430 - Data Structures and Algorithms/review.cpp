/*
Assignment 1
Weston Gibson, CISP 430
25 August 2022
*/

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// compile-time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// runtime constants (this becomes an ini file)
const string FILE_IN = "test.csv";

// for input file
class Prompt {
 private:
  int index;
  string _questionOptions[3];
  char _answerKey;
  bool _goodImport = false;
  char _answerUser = ' ';

 public:
  // overloaded constructor
  Prompt(string line) {
    string word;

    stringstream str(line);
  }
};

int main() {
  // attempt to import file
  ifstream file(FILE_IN);
  if (!file) {
    cout << "Error: Test file not found. The file may be absent or corrupted.\n"
         << "Please try again.\n"
         << "Exiting program...\n";
    return 0;
  }

  // seed rng
  srand(time(0));

  // read the file into the program
  string line, word, temp;
  vector<Prompt> test;

  while (file >> temp) {
    // empty the vector just in case
    test.clear();

    // get each prompt from the document
    getline(file, line);
    test.push_back(Prompt(line));
  }
}