/*
InvInq.cpp
Weston Gibson, CISP 400
13 March 2022
*/

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Specification B1 - Date Class
class Date {
 private:
  int _month, _day, _year;

 public:
  // default constructor
  Date() {
    _month = 9;
    _day = 9;
    _year = 99;
  };

  // overloaded constructor
  Date(int month, int day, int year) {
    _month = month;
    _day = day;
    _year = year;
  };

  // overloaded << operator
  friend ostream& operator<<(ostream& output, const Date& date) {
    output << date._month << "/" << date._day << "/" << date._year;
    return output;
  };

  // overloaded >> operator
  friend istream& operator>>(istream& input, Date& date) {
    input >> date._month >> date._day >> date._year;
    return input;
  };

  // overloaded = operator
  Date& operator=(const Date& date) {
    _month = date._month;
    _day = date._day;
    _year = date._year;
    return *this;
  };

  // test
  // Specification B2 - ComponentTest method in Date
  static void ClassTest() {
    Date test1;
    if (test1._month == 9 && test1._day == 9 && test1._year == 99)
      cout << "\n(Date) Default constructor working correctly. Date 1: "
           << test1;
    else
      cout << "\n(Date) Default constructor not working correctly.";

    Date test2(1, 1, 11);
    if (test2._month == 1 && test2._day == 1 && test2._year == 11)
      cout << "\n(Date) Overloaded constructor working correctly. Date 2: "
           << test2;
    else
      cout << "\n(Date) Overloaded constructor not working correctly.";

    test1 = test2;
    if (test1._month == 1 && test1._day == 1 && test1._year == 11)
      cout << "\n(Date) Overloaded = operator working correctly. Date 1: "
           << test2;
    else
      cout << "\n(Date) Overloaded = operator not working correctly.";

    cout << "\nAll three tests utilize the overloaded << operator.\n";
  };
};

// Inventory Class
class Inventory {
 private:
  int _number;
  int _quantity;
  double _wholesale;
  double _retail;
  Date _date;

 public:
  // default constructor
  Inventory() {
    _number = 0;
    _quantity = 0;
    _wholesale = 0.00;
    _retail = 0.00;
    _date = Date();
  };

  // overloaded constructor
  Inventory(int number,
            int quantity,
            double wholesale,
            double retail,
            Date date) {
    _number = number;
    _quantity = quantity;
    _wholesale = wholesale;
    _retail = wholesale * 2;
    _date = date;
  };

  // overloaded << operator
  // Specification A2 - Overload operator<<
  friend ostream& operator<<(ostream& output, const Inventory& inv) {
    output << inv._number << " " << inv._quantity << " " << inv._wholesale
           << " " << inv._retail << " " << inv._date;
    return output;
  };

  // overloaded >> operator
  // Specification A3 - Overload operator>>
  friend istream& operator>>(istream& input, Inventory& inv) {
    input >> inv._number >> inv._quantity >> inv._wholesale >> inv._retail >>
        inv._date;
    return input;
  };

  // overloaded = operator
  Inventory& operator=(const Inventory& inv) {
    _number = inv._number;
    _quantity = inv._quantity;
    _wholesale = inv._wholesale;
    _retail = inv._retail;
    _date = inv._date;
    return *this;
  };

  // test
  static void ClassTest() {
    // both tests use overloaded << operator
    Inventory test1;
    if (test1._number == 0 && test1._quantity == 0 &&
        test1._wholesale == 0.00 && test1._retail == 0.00)
      cout << "\n(Inventory) Default constructor working correctly. Item 1: "
           << test1;
    else
      cout << "\n(Inventory) Default constructor not working correctly.";

    Inventory test2(1, 1, 1.00, 2.00, Date(1, 1, 11));
    if (test2._number == 1 && test2._quantity == 1 &&
        test2._wholesale == 1.00 && test2._retail == 2.00)
      cout << "\n(Inventory) Overloaded constructor working correctly. Item 2: "
           << test2;
    else
      cout << "\n(Inventory) Overloaded constructor not working correctly.";

    test1 = test2;
    if (test1._number == 1 && test1._quantity == 1 &&
        test1._wholesale == 1.00 && test1._retail == 2.00)
      cout << "\n(Inventory) Overloaded = operator working correctly. Item 1: "
           << test2;
    else
      cout << "\n(Inventory) Overloaded = operator not working correctly.";

    cout << "\nAll three tests utilize the overloaded << operator.\n";
  };
};

// program information
const string PROGRAM_NAME = "Inventory Inquisitor";
const string PROGRAM_AUTHOR = "Weston Gibson";
const string DUE_DATE = "March 13, 2022";

// settings
const bool UNIT_TEST = true;

// menu
const int MENU_SIZE = 5;
const char MENU_CHOICE[MENU_SIZE] = {'A', 'R', 'E', 'D', 'Q'};
const string MENU_TEXT[MENU_SIZE] = {
    "  <A>dd Inventory", "  <R>emove Inventory", "  <E>dit Inventory",
    "  <D>isplay Inventory", "  <Q>uit"};
const int MENU_ADD_INDEX = 0;
const int MENU_QUIT_INDEX = MENU_SIZE - 1;

// common utility prototypes
template <typename T>
void Test(T);
void ClearScreen();
void ProgramGreeting();
int StringToInt(string input);
double StringToDouble(string input);
void Handler();
void UnitTest();

// program function prototypes
void Menu(char&);
Inventory Object();
int ItemNumber();
int ItemQuantity();
double ItemCost();
Date EntryDate();
int ItemIndex(int);
template <typename T>
T* ArrayPushBack(T*, T, int);
template <typename T>
T* ArrayPopBack(T*, int);
template <typename T>
T* ArrayEdit(T*, int);
template <typename T>
void DisplayArray(T*, int);

int main() {
  string temp;
  char choice = ' ';
  int size = 0;
  Inventory item;

  // Specification C2 - Dynamic Array
  Inventory* inventory = nullptr;
  inventory = new Inventory[0];

  ClearScreen();
  ProgramGreeting();

  // setting on line 53
  if (UNIT_TEST)
    // Specification A4 - UnitTest() method in main()
    UnitTest();

  do {
    ClearScreen();
    Menu(choice);
    switch (choice) {
      case 'A':
        if (size == 0)
          inventory[0] = Object();
        else
          inventory = ArrayPushBack(inventory, Object(), size);
        size++;
        break;
      case 'R':
        inventory = ArrayPopBack(inventory, size);
        size--;
        break;
      case 'E':
        inventory = ArrayEdit(inventory, size);
        break;
      case 'D':
        DisplayArray(inventory, size);
        cout << "\nPress enter to continue...";
        getline(cin, temp);
        break;
      case 'Q':
        break;
    }
  } while (choice != MENU_CHOICE[MENU_QUIT_INDEX]);

  cout << "\nThanks for trying! Please don't again!\n";

  delete[] inventory;
  inventory = nullptr;
  return 0;
}

// common utilities
// test piece
template <typename T>
void Test(T thing) {
  cout << "\n\nTest: " << thing << "\n\n";
  string input;
  getline(cin, input);
}

// uses cross-platform string to clear screen
void ClearScreen() {
  cout << "\033[2J\033[1;1H";
};

// school requirement - program greeting
void ProgramGreeting() {
  string temp = "";
  cout << "Welcome to " + PROGRAM_NAME +
              "!\n"
              "\nWritten by: " +
              PROGRAM_AUTHOR +
              ".\n"
              "\n"
              "This program was due on " +
              DUE_DATE +
              ".\n"
              "\nPress enter to continue...";
  getline(cin, temp);
}

// attempts to use std::__cxx11::stoi, returns -1 on failure
int StringToInt(string input) {
  int output;
  try {
    output = stoi(input);
  } catch (...) {
    output = -1;
  }
  return output;
};

// attempts to user std::__cxx11::stod, returns -1 on failure
double StringToDouble(string input) {
  double output;
  try {
    output = stod(input);
  } catch (...) {
    output = -1;
  }
  return output;
};

// clears the screen and tells user to follow directions
void Handler() {
  ClearScreen();
  cout << "Please enter a valid option.\n";
};

// unit test
void UnitTest() {
  string temp = "";
  cout << "\nStart Unit Testing\n";
  cout << "\nDate Class Test";
  Date::ClassTest();
  cout << "\nInventory Class Test";
  Inventory::ClassTest();
  cout << "\nPress enter to continue...";
  getline(cin, temp);
}

// Specification C1 - Alpha Menu
void Menu(char& choice) {
  string input;
  if (choice != ' ')
    choice = 'X';

  // only prints Add and Quit if there is no inventory
  while (choice == ' ') {
    cout << "Main Menu\n"
         << "---------\n"
         << MENU_TEXT[MENU_ADD_INDEX] << "\n"
         << MENU_TEXT[MENU_QUIT_INDEX] << "\n"
         << "\nEnter your choice (Ex: A): ";

    // gets only one char, dumps the rest, converts to uppercase
    getline(cin, input);
    choice = toupper(input[0]);

    // handle if user doesn't follow directions
    if (choice != MENU_CHOICE[MENU_ADD_INDEX] &&
        choice != MENU_CHOICE[MENU_QUIT_INDEX]) {
      Handler();
      choice = ' ';
    }
  }

  // prints full menu otherwise
  while (choice == 'X') {
    cout << "Main Menu\n"
         << "---------\n";
    for (int i = 0; i < MENU_SIZE; i++) {
      cout << MENU_TEXT[i] << "\n";
    }
    cout << "\nEnter your choice (Ex: A): ";

    // gets only one char, dumps the rest, converts to uppercase
    getline(cin, input);
    choice = toupper(input[0]);

    // handle if user doesn't follow directions
    // Specification B3 - Menu Input Validation
    if (!find(begin(MENU_CHOICE), end(MENU_CHOICE), choice)) {
      Handler();
      choice = 'X';
    }
  }
}

// get inventory item from user
Inventory Object() {
  int number = ItemNumber();
  int quantity = ItemQuantity();
  double cost = ItemCost();
  double price = cost * 2;
  Date date = EntryDate();

  Inventory item(number, quantity, cost, price, date);
  return item;
}

// get item number from user
int ItemNumber() {
  string input;
  int temp = -1;

  // Specification B4 - Inventory Entry Input Validation
  while (temp < 0) {
    cout << "\nEnter the 5-digit item number: ";
    getline(cin, input);
    temp = StringToInt(input);

    // handle if user doesn't follow directions
    if (temp < 0 || temp > 99999) {
      Handler();
      temp = -1;
    }
  }

  return temp;
}

// get item quantity from user
int ItemQuantity() {
  string input;
  int temp = -1;

  while (temp < 0) {
    cout << "Enter the quantity: ";
    getline(cin, input);
    temp = StringToInt(input);

    // handle if user doesn't follow directions
    if (temp < 0) {
      Handler();
      temp = -1;
    }
  }

  return temp;
}

// get item cost from user
double ItemCost() {
  string input;
  double temp = -0.01;

  while (temp < 0) {
    cout << "Enter the cost (Ex: 15.00): ";
    getline(cin, input);
    temp = StringToDouble(input);

    // handle if user doesn't follow directions
    if (temp < 0) {
      Handler();
      temp = -1;
    }
  }

  return temp;
}

// get entry date from user
Date EntryDate() {
  string input;
  int month = -1;
  int day = -1;
  int year = -1;

  while (month < 1) {
    cout << "Enter the month (Ex: 12): ";
    getline(cin, input);
    month = StringToInt(input);

    // handle if user doesn't follow directions
    if (month < 1 || month > 12) {
      Handler();
      month = -1;
    }
  }

  while (day < 1) {
    cout << "Enter the day (Ex: 31): ";
    getline(cin, input);
    day = StringToInt(input);

    // handle if user doesn't follow directions
    if (day < 1 || day > 31) {
      Handler();
      day = -1;
    }
  }

  while (year < 1) {
    cout << "Enter the year (Ex: 99): ";
    getline(cin, input);
    year = StringToInt(input);

    // handle if user doesn't follow directions
    if (year < 1) {
      Handler();
      year = -1;
    }
  }

  Date temp = Date(month, day, year);
  return temp;
}

// get item index from user
int ItemIndex(int size) {
  string input;
  int temp = -1;

  while (temp < 0) {
    cout << "Enter the index of the item to edit: ";
    getline(cin, input);
    temp = StringToInt(input);

    // handle if user doesn't follow directions
    if (temp < 0 || temp > size - 1) {
      Handler();
      temp = -1;
    }
  }

  return temp;
}

// mimics vector<T>::push_back()
// Specification C3 - Resize Array - add to end
template <typename T>
T* ArrayPushBack(T* old, T element, int size) {
  // create new array with old size + 1
  T* temp = nullptr;
  temp = new T[size + 1];

  // initialize new array with old elements, then add new element
  for (int i = 0; i < size; i++)
    temp[i] = old[i];
  temp[size] = element;

  // delete old array, reset pointer, return new array pointer
  delete[] old;
  old = nullptr;
  return temp;
}

// mimic vector<T>::pop_back()
// Specification C4 - Resize Array - subtract from end
template <typename T>
T* ArrayPopBack(T* old, int size) {

  // create new array with old size - 1
  T* temp = nullptr;
  temp = new T[size - 1];

  // initialize new array with old elements, skip last element
  for (int i = 0; i < size; i++)
    temp[i] = old[i];

  // delete old array, reset pointer, return new array pointer
  delete[] old;
  old = nullptr;
  return temp;
}

// allow user to edit an existing entry
// Specification A1 - Edit Inventory
template <typename T>
T* ArrayEdit(T* old, int size) {
  int index = -1;

  // display the current array and get the index of the item to edit
  DisplayArray(old, size);
  index = ItemIndex(size);

  // get new item from user
  Inventory item = Object();

  // overwrite the previous entry and return the array
  old[index] = item;
  return old;
}

// display elements of array
template <typename T>
void DisplayArray(T* array, int size) {
  for (int i = 0; i < size; i++)
    cout << array[i] << "\n";
}