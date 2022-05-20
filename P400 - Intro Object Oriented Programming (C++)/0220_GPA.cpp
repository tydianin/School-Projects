/*
gpa.cpp
Weston Gibson, CISP 400
20 February 2022
*/

#include <iostream>
#include <string>

using namespace std;

// Specification A1 - Date Class
class Date {
 private:
  string _mo;
  int _da, _yr;

 public:
  // construct
  Date();
  Date(string mo, int da, int yr) {
    _mo = mo;
    _da = da;
    _yr = yr;
  };

  // get
  string GetDate() const;

  // test
  void DateConstructorTest() const;
};

string Date::GetDate() const {
  return _mo + " " + to_string(_da) + ", " + to_string(_yr);
}

// Specification A3 - Component Test Method in Date
void Date::DateConstructorTest() const {
  if (GetDate() == "June 30, 1988")
    cout << "\n\nDate Constructor Test: PASS\n";
  else
    cout << "\n\nDate Constructor Test: FAIL\n";
}

// extra constants
const bool UNIT_TEST = true;
const string PROGRAM_NAME = "GPA Calculator";
const string PROGRAM_AUTHOR = "Weston Gibson";
const int MIN_SCORE = 0;
const int MAX_SCORE = 100;

// ini menu
// prevents issues with attempting to print an empty array
// room for improvement: combine the menu functions and use struct or classes
const int INI_MENU_MAX = 2;
const string INI_MENU[2] = {"Add Grades", "Quit Program"};
const int INI_MENU_ADD = 1;
const int INI_MENU_QUIT = 2;

// main menu
const int MENU_MIN = 1;
const int MENU_SIZE = 4;
const string MENU[MENU_SIZE] = {"Add Grades", "Display All Grades",
                                "Process All Grades", "Quit Program"};
const int MENU_ADD = 1;
const int MENU_DISPLAY = 2;
const int MENU_PROCESS = 3;
const int MENU_QUIT = 4;

// common utilities
void ClearScreen() {
  cout << "\033[2J\033[1;1H";
};
void Handler() {
  ClearScreen();
  cout << "Please enter a valid option.\n";
};
int StringToInt(string s) {
  int i;
  try {
    i = stoi(s);
  } catch (...) {
    i = -1;
  }
  return i;
};
template <typename T>
T* ExpandArray(T* arr, int size) {
  // create new array with old size + 1
  size++;
  T* temp = nullptr;
  temp = new T[size];
  // copy old array elements into new array
  for (int i = 0; i < (size - 1); i++)
    temp[i] = arr[i];
  // initialize last element to 0
  temp[size - 1] = 0;
  // delete old array
  delete[] arr;
  arr = nullptr;
  // return new array
  return temp;
};

// testing
void UnitTest();
void FuncTestLetterGrade();

// prototypes
void ProgramGreeting(Date);
void IniMenu(int&);
void Menu(int&);
int* AddGrade(int*, char&, int&);
void DisplayGrades(int*, int);
char LetterGrade(int);
void ProcessGrades(int*, int);

int main() {
  if (UNIT_TEST)
    UnitTest();

  int choice = 0, count = 0;
  char grade = ' ';

  // Specification A2 - External Date Initialization
  Date date("February", 20, 2022);

  // Specification B1 - Dynamic Array
  int* grades = nullptr;
  grades = new int[0];

  ClearScreen();
  ProgramGreeting(date);

  ClearScreen();
  IniMenu(choice);
  switch (choice) {
    case INI_MENU_ADD:
      grades = AddGrade(grades, grade, count);
      break;
    case INI_MENU_QUIT:
      choice = MENU_QUIT;
      break;
    default:
      break;
  }

  while (choice != MENU_QUIT) {
    ClearScreen();
    if (choice == INI_MENU_ADD || choice == MENU_ADD)
      cout << "\nGrade Added: " << grades[count - 1] << " (" << grade
           << ")\n\n";
    choice = 0;

    Menu(choice);
    switch (choice) {
      case MENU_ADD:
        grades = AddGrade(grades, grade, count);
        break;
      case MENU_DISPLAY:
        DisplayGrades(grades, count);
        break;
      case MENU_PROCESS:
        ProcessGrades(grades, count);
        break;
      default:
        break;
    }
  }

  delete[] grades;
  grades = nullptr;
  cout << "\nThank you for using " << PROGRAM_NAME << "!\n\n";

  return 0;
}

void UnitTest() {
  string temp = "";
  FuncTestLetterGrade();

  Date test("June", 30, 1988);
  test.ComponentTest();

  cout << "\nUnit test complete.\n"
       << "\nPress enter to continue...";
  getline(cin, temp);
}

// Specification A4 - Component Test Grade Conversion
void FuncTestLetterGrade() {
  char grade;
  for (int i = -1; i < 111; i += 10) {
    grade = LetterGrade(i);
    cout << "\nGrade: " << (i) << ", Letter: " << grade;
  }
}

// Specification C1 - Program Greeting Function
void ProgramGreeting(Date date) {
  string temp = "";
  cout << "Welcome to " << PROGRAM_NAME << "!\n"
       << "Written by " << PROGRAM_AUTHOR << ".\n"
       << "\n"
       << "This program will\n"
       << "  1. Add an unlimited number of grades to a list.\n"
       << "  2. Convert the number grades to a letter grade.\n"
       << "  3. Calculate the average of the list of grades.\n"
       << "\n"
       << "This program was due on " << date.GetDate() << "\n"
       << "\n"
       << "Press enter to continue...";
  getline(cin, temp);
}

void IniMenu(int& choice) {
  string input;

  // loops until the user follows directions
  while (choice < INI_MENU_MIN || choice > INI_MENU_SIZE) {
    // display menu
    for (int i = 0; i < INI_MENU_SIZE; i++) {
      cout << i + 1 << ". " << INI_MENU[i] << "\n";
    }

    // get user input
    cout << "\nEnter your choice: ";
    getline(cin, input);

    // convert string input to int choice
    choice = StringToInt(input);

    // handle if user doesn't follow directions
    if (choice < INI_MENU_MIN || choice > INI_MENU_SIZE)
      Handler();
  }
}

void Menu(int& choice) {
  string input;

  // loops until the user follows directions
  while (choice < MENU_MIN || choice > MENU_SIZE) {
    // display menu
    for (int i = 0; i < MENU_SIZE; i++) {
      cout << i + 1 << ". " << MENU[i] << "\n";
    }

    // get user input
    cout << "\nEnter your choice: ";
    getline(cin, input);

    // convert string input to int choice
    choice = StringToInt(input);

    // Specification B3 - Menu Input Validation
    if (choice < MENU_MIN || choice > MENU_SIZE)
      Handler();
  }
}

// Specification B2 - Add Elements
int* AddGrade(int* grades, char& grade, int& count) {
  string input;
  int score = -1;

  // add index to array
  grades = ExpandArray(grades, count);

  // loops until the user follows directions
  while (score < MIN_SCORE || score > MAX_SCORE) {
    // get user input
    cout << "\nEnter a grade: ";
    getline(cin, input);

    // convert string input to int grade
    score = StringToInt(input);

    // handle if user doesn't follow directions
    if (score < MIN_SCORE || score > MAX_SCORE)
      Handler();
    cout << "You must enter a number between " << MIN_SCORE << " and "
         << MAX_SCORE << ".\n";
  }

  // add grade to array, get letter grade, increment count
  grades[count] = score;
  grade = LetterGrade(score);
  count++;

  // return new array
  return grades;
}

// Speicifcation C2 - Print Scores
void DisplayGrades(int* grades, int count) {
  char letter;
  string temp;

  // loop over array and print elements
  for (int i = 0; i < count; i++) {
    letter = LetterGrade(grades[i]);
    cout << "\nGrade " << (i + 1) << ": " << grades[i] << " (" << letter << ")";
  }

  // confirm before continuing
  cout << "\n\nPress enter to continue...";
  getline(cin, temp);
}

// Specification C3 - Letter Grades
char LetterGrade(int grade) {
  char letter;
  if (grade > 100 || grade < 0) {
    letter = 'U';
    cout << "\nError: Grade must be between 0 and 100.";
  } else if (grade >= 90)
    letter = 'A';
  else if (grade >= 80)
    letter = 'B';
  else if (grade >= 70)
    letter = 'C';
  else if (grade >= 60)
    letter = 'D';
  else
    letter = 'F';
  return letter;
}

// Specification C4 - Compute GPA
void ProcessGrades(int* grades, int count) {
  int sum = 0, avg = 0;
  char letter;
  string temp;

  // calculate average
  for (int i = 0; i < count; i++) {
    sum += grades[i];
  }
  avg = sum / count;

  // Specification B4 - Print Letter Grade
  letter = LetterGrade(avg);
  cout << "\nAverage Grade: " << avg << " (" << letter << ")";

  // confirm before continuing
  cout << "\n\nPress enter to continue...";
  getline(cin, temp);
}