/*
TODOList.cpp
Weston Gibson, CISP 400
31 March 2022
*/

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

// classes
class ToDo {
 private:
  string _date;
  int _id_number;
  string _description;
  bool _visible;

 public:
  static int _id_count;

  // default constructor
  ToDo() {
    _date = GetDate();
    _id_number = 0;
    _description = "Invalid Input";
    _visible = false;
  }

  // Specification A4 - Overload Constructor
  ToDo(string input) {
    _date = GetDate();
    _id_number = ++_id_count;
    _description = input;
    _visible = true;
  }

  // Specification A1 - Overload Copy Constructor
  ToDo(const ToDo& object) {
    _date = object._date;
    _id_number = object._id_number;
    _description = object._description;
    _visible = object._visible;
  }

  // Specification A3 - System Date
  static string GetDate() {
    time_t sysTime = time(nullptr);
    return asctime(localtime(&sysTime));
  }

  static void SetID(int number) { _id_count = number; }

  int GetID() const { return _id_number; }

  string Print() const {
    stringstream ss;
    ss << "  " << _date << "\tID: " << setw(10) << _id_number << "\t"
       << _description << "\n";
    return ss.str();
  }

  // Specification A2 - Overload Assignment Operator
  ToDo& operator=(const string& input) {
    // structured for use with csv-format file
    stringstream ss(input);
    string temp, tempDate, tempID;
    bool checkDate = true, checkID = true;

    // piece out ss into individual variables
    getline(ss, temp, ',');
    tempDate = temp;
    getline(ss, temp, ',');
    tempID = temp;
    getline(ss, temp, ',');
    _description = temp;

    // regex match Www Mmm dd hh:mm:ss yyyy (asctime)
    regex dateCheck(
        "^[A-z]{3}[ ][A-z]{3}[ ][0-9]{2}[ ][0-9]{2}:[0-9]{2}:[0-9]{2}[ "
        "][0-9]{4}$");
    smatch match;
    if (regex_match(tempDate, match, dateCheck))
      _date = tempDate;
    else
      checkDate = false;

    // check if id converts to int
    try {
      _id_number = stoi(tempID);
    } catch (...) {
      checkID = false;
      _id_number = 0;
    }

    // if either check fails, set description to invalid input
    if (checkDate == false || checkID == false) {
      _description = "Invalid Input";
      _visible = false;
    } else {
      _id_count = _id_number;
      _visible = true;
    }
    return *this;
  }

  // Specification C1 - Overload <<
  friend ostream& operator<<(ostream& output, const ToDo& object) {
    stringstream ss;
    ss << object._date << "," << object._id_number << "," << object._description
       << endl;
    if (object._description != "Invalid Input" && object._visible == true)
      output << ss.str();
    else
      output << "Invalid Input";
    return output;
  }

  // Specification C2 - Overload >>
  friend istream& operator>>(istream& input, ToDo& object) {
    input >> object._description;
    return input;
  }

  // Specification C3 - Test TODO's
  static void ClassTest() {
    // generate 5 objects
    cout << "\n\n";
    ToDo test1;
    if (test1._id_number == 0 && test1._description == "Invalid Input")
      cout << "(ToDo) Default constructor working correctly.\nObject 1: "
           << test1;
    else
      cout << "(ToDo) Default constructor not working correctly.\nObject 1: "
           << test1;

    SetID(1);
    cout << "\n\n";
    ToDo test2("Test 2");
    if (test2._id_number == 2 && test2._description == "Test 2")
      cout << "(ToDo) Overloaded constructor working correctly.\nObject 2: "
           << test2;
    else
      cout << "(ToDo) Overloaded constructor not working correctly.\nObject 2: "
           << test2;

    cout << "\n\n";
    ToDo test3(test2);
    if (test3._date == test2._date && test3._id_number == test2._id_number &&
        test3._description == test2._description &&
        test3._visible == test2._visible)
      cout << "(ToDo) Overloaded copy constructor working correctly.\nObject 3: "
           << test3;
    else
      cout << "(ToDo) Overloaded copy constructor not working correctly.\nObject 3: "
           << test3;

    SetID(3);
    cout << "\n\n";
    string input = "Sun Apr 04 15:02:30 2022,4,Test 4";
    ToDo test4;
    test4 = input;
    if (test4._date == "Sun Apr 04 15:02:30 2022" && test4._id_number == 4 &&
        test4._description == "Test 4")
      cout << "(ToDo) Overloaded = operator working correctly.\nObject 4: "
           << test4;
    else
      cout << "(ToDo) Overloaded = operator not working correctly.\nObject 4: "
           << test4;

    cout << "\n\n";
    ToDo test5;
    stringstream ss("Test 5");
    ss >> test5;
    cout << "\n";
    if (test5._description == "Test 5")
      cout << "(ToDo) Overloaded >> operator working correctly.\nObject 5: "
           << test5;
    else
      cout << "(ToDo) Overloaded >> operator not working correctly.\nObject 5: "
           << test5;

    cout << "\n\nAll tests utilize the overloaded << operator.";
  }
};

int ToDo::_id_count = 0;

// compile time constants (programmer settings)
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";
constexpr char PROGRAM_NAME[] = "TODO List";
constexpr char PROGRAM_AUTHOR[] = "Weston Gibson";

// runtime constants (this becomes an ini file)
const bool DEBUG = true;
const bool QUICK_OPTIONS = true;
const char MENU_OPTIONS[5] = {'+', '-', '?', '~', '!'};

// programming prototypes
template <typename T>
void Test(T);
void ProgramGreeting();
void UnitTest();
void Handler();
int StringToInt(string);

// template utilities
template <typename T>
T* ImportArray(T*);
template <typename T>
void ExportArray(T*);
template <typename T>
int IDToIndex(T*, int);
template <typename T>
T* ArrayAddElement(T*, T);
template <typename T>
T* ArrayRemoveElement(T*, int);
template <typename T>
void PrintArray(T*);

// runtime prototypes
string Menu(char&);

int main() {
  ToDo::SetID(0);
  string input;
  int temp, index;
  char choice = ' ';

  // Specification C4 - TODO Array
  ToDo* toDoList = nullptr;
  toDoList = new ToDo[0];

  // start up
  ProgramGreeting();

  // setting on line 188
  if (DEBUG)
    UnitTest();

  // initialize class id and import from file
  ToDo::SetID(0);
  toDoList = ImportArray(toDoList);

  // main loop
  do {
    cout << CLEAR_SCREEN;
    input = Menu(choice);

    // Specification B1 - + Symbol
    if (choice == '+') {
      ToDo object(input);
      toDoList = ArrayAddElement(toDoList, object);
    }

    // Specification B3 - - Symbol
    else if (choice == '-') {
      temp = StringToInt(input);
      if (temp - 1 > 0) {
        index = IDToIndex(toDoList, temp);
        if (index == -1)
          cout << "Invalid ID";
        else
          toDoList = ArrayRemoveElement(toDoList, index);
      } else
        cout << "Invalid ID";
    }

    // Specification B2 - ? Symbol
    else if (choice == '?') {
      cout << "___  __  _  Date  _  __  ___|__ _  ID  _ __|__ Task\n";
      PrintArray(toDoList);
    }

    // quit with saving
    else if (choice == '~')
      ExportArray(toDoList);

  } while (choice != '~' && choice != '!');

  cout << "\n\nExiting...";
  delete[] toDoList;
  toDoList = nullptr;
  return 0;
}

// programming functions
template <typename T>
void Test(T thing) {
  cout << "\n\nTest: " << thing << "\n\n";
  string input;
  getline(cin, input);
}

void ProgramGreeting() {
  string temp = "";
  cout << endl << CLEAR_SCREEN << endl;
  cout << "Welcome to ";
  cout << PROGRAM_NAME;
  cout << "!\n\nWritten by: ";
  cout << PROGRAM_AUTHOR;
  cout << ".\n\nToday is ";
  cout << ToDo::GetDate();
  cout << "\nPress enter to continue...";
  getline(cin, temp);
}

void UnitTest() {
  string temp = "";
  cout << endl << CLEAR_SCREEN << endl;
  cout << "Start Unit Testing";
  cout << "\n\nTodo Class Test";
  ToDo::ClassTest();
  cout << "\n\nPress enter to continue...";
  getline(cin, temp);
}

void Handler() {
  cout << CLEAR_SCREEN;
  cout << "\n\nPlease enter a valid option.\n\n";
}

int StringToInt(string input) {
  int output;
  try {
    output = stoi(input);
  } catch (...) {
    output = -1;
  }
  return output;
}

// template utilities
template <typename T>
T* ImportArray(T* array) {
  char choice;
  string temp, fileName;

  cout << CLEAR_SCREEN;

  while (choice != 'Y' && choice != 'N') {
    cout << "Would you like to import a file? (y/n) ";
    getline(cin, temp);
    choice = toupper(temp[0]);

    if (choice != 'Y' && choice != 'N')
      Handler();    
  }

  if (choice == 'Y') {
    cout << "Please enter the file name and extension: ";
    getline(cin, fileName);
    
    ifstream inputFile(fileName);
    string input;

    if (inputFile.is_open()) {
      while (getline(inputFile, input)) {
        ToDo object(input);
        array = ArrayAddElement(array, object);
      }
      inputFile.close();
    } else {
      cout << "File not found.\n";
    }
  }
  return array;
}

// Specification B4 - Persistence
template <typename T>
void ExportArray(T* array) {
  string fileName;
  cout << "\n\nFile you would like to save to: ";
  getline(cin, fileName);

  ofstream outputFile(fileName);
  stringstream ss;
  string output;

  int size = (&array)[1] - array;
  for (int i = 0; i < size; i++) {
    ss << array[i];
    output = ss.str();
    if (output != "Invalid Input")
      outputFile << output;
  }
  outputFile.close();
}

template <typename T>
int IDToIndex(T* array, int id) {
  int size = (&array)[1] - array;
  for (int i = 0; i < size; i++) {
    if (array[i].GetID() == id)
      return i;
  }
  return -1;
}

template <typename T>
T* ArrayAddElement(T* array, T object) {
  int size = (&array)[1] - array;
  T* temp = new T[size + 1];
  for (int i = 0; i < size; i++) {
    temp[i] = array[i];
  }
  temp[size] = object;
  delete[] array;
  return temp;
}

template <typename T>
T* ArrayRemoveElement(T* array, int index) {
  int size = (&array)[1] - array;
  T* temp = new T[size - 1];

  // copy everything before index
  for (int i = 0; i < index; i++) {
    temp[i] = array[i];
  }

  // copy everything after index
  for (int i = index; i < size - 1; i++) {
    temp[i] = array[i + 1];
  }

  delete[] array;
  return temp;
}

template <typename T>
void PrintArray(T* array) {
  int size = (&array[1]) - array;
  for (int i = 0; i < size; i++) {
    array[i].Print();
  }
}

// runtime functions
string Menu(char& choice) {
  string input;
  choice = ' ';

  // prints menu and validates choice before returning
  while (choice == ' ') {
    cout << "Main Menu\n"
         << "---------\n"
         << "  (+) Use the plus sign to add a new task.\n"
         << "  (-) Use the minus sign to remove a task.\n"
         << "  (?) Use the question mark to view the list.\n"
         << "  (~) Use the tilde to save the list and exit.\n"
         << "  (!) Use the exclamation mark to exit without saving.\n"
         << "\n";

    // setting on line 189
    if (QUICK_OPTIONS)
      cout << "\nQuick options enabled. Ex: \"+ CISP 440 Midterm\"\n";

    cout << "\nEnter your choice: ";

    // gets char option
    getline(cin, input);
    choice = input[0];

    // handle if user doesn't follow directions
    if (!find(begin(MENU_OPTIONS), end(MENU_OPTIONS), choice)) {
      Handler();
      choice = ' ';
    }
  }
  return input;
}