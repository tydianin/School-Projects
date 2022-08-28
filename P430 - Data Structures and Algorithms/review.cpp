/*
Assignment 1
Weston Gibson, CISP 430
25 August 2022

Uses C++17 in accordance with GCC 12.2
*/

// C++ library headers
#include <algorithm>  // shuffle()
#include <fstream>    // ifstream, getline(), good(), is_open()
#include <iomanip>    // setprecision()
#include <iostream>   // cin, cout
#include <random>     // random_device, default_random_engine
#include <sstream>    // stringstream, getline()
#include <string>     // string, stoi
#include <vector>     // vector, begin(), end(), back(), push_back(), pop_back(), size

using namespace std;

// compile-time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// runtime constants (this becomes an ini file)
const string FILE_IN = "test.csv";

// for input file
class Prompt {
 private:
  int _index;
  string _question;
  vector<string> _options;
  char _answerKey;
  char _answerUser = ' ';
  bool _goodImport = false;

 public:
  // overloaded ctor
  Prompt(vector<string> line) {
    _index = stoi(line[0]);
    _question = line[1];

    _answerKey = line.back()[0];
    line.pop_back();

    for (int i = 2; i < line.size(); i++)
      _options.push_back(line[i]);
    _goodImport = true;
  }

  // print question and options
  void getQuestion() {
    cout << _question << "\n";
    char option = 'A';
    for (string item : _options) {
      cout << "  " << option << ") " << item << "\n";
      option++;
    }
  }

  // set answer and return grade
  int setAnswer(char choice) {
    _answerUser = choice;
    if (_answerKey == _answerUser)
      return 1;
    else
      return 0;
  }
};

ifstream importFile(string);
vector<string> importLine(string);

int main() {
  // burner string
  string line;

  // stream object for importing csv file
  ifstream file;

  // attempt to import file, catch exceptions
  try {
    file = importFile(FILE_IN);
  } catch (exception& e) {
    cout << "Standard exception caught: " << e.what()
         << "\nExiting program...\n\n";
    throw e;
  } catch (...) {
    cout << "An unknown error occured. Aborting program.\n";
    return 1;
  }

  // vector for holding prompt objects
  vector<Prompt> test;
  while (file.good()) {
    getline(file, line);
    // try block for csv errors
    test.push_back(Prompt(importLine(line)));
  }

  // randomize the prompt vector
  random_device rd;
  default_random_engine rng(rd());
  shuffle(test.begin(), test.end(), rng);

  // display each question, get each response, get grade
  int i = 0, count = 0, grade = 0;
  for (Prompt& item : test) {
    i++;
    count++;

    // cout << CLEAR_SCREEN;
    cout << "Question " << i << ": ";
    item.getQuestion();

    cout << "\nAnswer: ";
    getline(cin, line);
    grade += item.setAnswer(toupper(line[0]));
  }

  // calculate user score
  double score = (double)grade / count * 100.0;

  // inform user of their results
  // cout << CLEAR_SCREEN << "Test complete!\n"
  cout << "Test complete!\n"
       << "Your score: " << fixed << setprecision(2) << score << "%";

  // finished
  return 0;
}

ifstream importFile(string str) {
  string temp = " ";
  char choice = ' ';

  // attempts to import file
  ifstream file(str);

  // checks if file exists
  while (!file.is_open()) {
    // if not, print error and start loop
    cout << "\nError: Test file not found, may be absent or corrupted.\n";
    choice = ' ';

    while (choice == ' ') {
      // prompt user for new file or exit
      cout << "Try a different file? Y/N: ";

      // get choice from user
      getline(cin, temp);
      choice = temp[0];

      // user failed to follow directions
      if (toupper(choice) != 'Y' || toupper(choice) != 'N') {
        cout << CLEAR_SCREEN << "\nPlease use a valid option.\n\n";
        choice = ' ';
      }
    };

    // user chose to try a different file
    if (choice == 'Y') {
      cout << "\nPlease enter a new file to import. (ex: file.csv)\n"
           << "Make sure to include the file extension: ";
      getline(cin, temp);
      ifstream file(temp);
    }
  }

  // return file or return exception to be handeled in try block
  return file;
}

vector<string> importLine(string line) {
  vector<string> row;
  string word;
  stringstream s(line);

  // breaks line into individual fields
  while (getline(s, word, ',')) {
    row.push_back(word);
  }

  return row;
}