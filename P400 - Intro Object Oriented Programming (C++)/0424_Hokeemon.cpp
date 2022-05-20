/*
hokeemon.cpp
Weston Gibson, CISP 400
24 April 2022
*/

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Specification C2 - Creature class
class Creature {
 protected:
  string _name;
  string _type;
  int _hunger;
  int _boredom;

 public:
  // default constructor
  Creature() {
    _name = "MissingNo.";
    _type = "Error";
    _hunger = 0;
    _boredom = 0;
  };

  // default destructor
  virtual ~Creature(){};

  // overloaded constructor
  Creature(string type) {
    _name = type;
    _type = type;
    _hunger = rand() % 6;
    _boredom = rand() % 6;
  };

  // Specification A2 - Copy Constructor
  // future feature: encounters, see UnitTest for now
  Creature(const Creature& object) {
    _name = object._type;
    _type = object._type;
    _hunger = rand() % 6;
    _boredom = rand() % 6;
  };

  // Specification B3 - Overload Assignment Operator
  Creature& operator=(const Creature& object) {
    _hunger = 20;
    _boredom = 0;
    return *this;
  };

  // Specification C4 - Overload <<
  friend ostream& operator<<(ostream& output, const Creature& object) {
    output << "\n"
           << object._name << "\n"
           << "(" << object._type << ")\n\n"
           << "  Hunger: " << to_string(object._hunger) << "\n"
           << "  Boredom: " << to_string(object._boredom) << endl;
    return output;
  };

  // Specification B4 - Overload + Operator
  string operator+(const Creature& object) {
    string parents = _name + " and " + object._name;
    return parents;
  }

  // Specification C1 - PassTime()
  void PassTime() {
    if (_hunger > 0) {
      _hunger--;
      if (_hunger == 0)
        cout << _name << " has died of starvation.\n";
      else if (_boredom < 20) {
        _boredom++;
        if (_boredom == 20)
          cout << _name << " has become bored.\n";
      } else
        cout << _name << " is bored.\n";
    } else
      cout << _name << " is dead.\n";
  }

  void Play() {
    if (_hunger > 0 && _boredom < 20)
      // -5 to compensate for PassTime()
      _boredom -= (5 + rand() % 5);
    // technically the prompt said no minimum value
  }

  void Feed() {
    if (_hunger > 0 && _boredom < 20)
      // +4 to compensate for PassTime()
      _hunger += (4 + rand() % 4);
  }

  // Specification A1 - Critter Name
  void SetName() {
    char choice = ' ';
    string input;

    // loop until the user follows directions
    while (choice == ' ') {
      cout << "Would you like to give " << _name << " a new name? (y/n) ";
      getline(cin, input);
      choice = toupper(input[0]);

      if (choice != 'Y' && choice != 'N') {
        choice = ' ';
        cout << "\033[2J\033[1;1H"
             << "Invalid choice.\n";
      }
    }

    // get new creature name from user
    if (choice == 'Y') {
      cout << "Enter a name: \n";
      getline(cin, input);
      try {
        _name = input.substr(0, 16);
      } catch (const out_of_range& oor) {
        _name = input;
      }
    }
  }

  // Specification B2 - Virtual Class Creature
  virtual void ComponentTest() = 0;
};

// Specification B1 - Child Class
class Child : virtual public Creature {
 protected:
  bool _horns;

 public:
  // default constructor
  Child() : Creature("Child") { _horns = true; }

  // copy constructor
  Child(const Creature& object) : Creature(object) { _horns = true; }

  // component test
  void ComponentTest() {
    cout << "Child Component Test\n";
    if (_horns && _type == "Child")
      cout << "Child class working correctly.\n";
    else
      cout << "Child class not working correctly.\n";

    cout << "Child object: " << *this << "\n";
  };
};

// Specification A3 - Second Child Class
class Derived : virtual public Creature {
 protected:
  bool _tail;

 public:
  // default constructor
  Derived() : Creature("Derived") { _tail = true; }

  // copy constructor
  Derived(const Creature& object) : Creature(object) { _tail = true; }

  // component test
  void ComponentTest() {
    cout << "Derived Component Test\n";
    if (_tail && _type == "Derived")
      cout << "Derived class working correctly.\n";
    else
      cout << "Derived class not working correctly.\n";

    cout << "Derived object: " << *this << "\n";
  };
};

class Spawn : public Child, public Derived {
 protected:
  string _parents;

 public:
  // overloaded constructor
  Spawn(string parents) : Creature("Spawn"), Child(), Derived() {
    _parents = parents;
    _type = "Spawn";
  }

  // copy constructor
  Spawn(const Creature& object) : Creature(object), Child(), Derived() {
    _parents = "Encountered in the Wild";
    _type = "Spawn";
  }

  // component test
  void ComponentTest() {
    cout << "Spawn Component Test\n";
    if (_type == "Spawn" && _horns && _tail && _parents == "Child and Derived")
      cout << "Spawn class working correctly.\n";
    else
      cout << "Spawn class not working correctly.\n";

    cout << "Spawn object: " << *this << "\n";
  };
};

// compile time constants (programmer settings)
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";
constexpr char PROGRAM_NAME[] = "Hokeemon";
constexpr char PROGRAM_AUTHOR[] = "Weston Gibson";

// runtime constants (this becomes an ini file)
const bool DEBUG = true;
const int MENU_SIZE = 5;
const char MENU_OPTIONS[MENU_SIZE] = {'L', 'P', 'F', 'N', 'Q'};
const string MENU_TEXT[MENU_SIZE] = {"isten", "lay", "eed", "ame", "uit"};

// programming prototypes
void ProgramGreeting();
void UnitTest();

// runtime prototypes
void Menu(char&);

int main() {
  // seed rng
  srand(time(0));

  char choice = ' ';
  string input;

  // spec didn't say array so you get three objects
  Creature* childObject = nullptr;
  childObject = new Child();

  Creature* derivedObject = nullptr;
  derivedObject = new Derived();

  Creature* spawnObject = nullptr;
  // overloaded operator+ just for fun
  spawnObject = new Spawn(*childObject + *derivedObject);

  // startup sequence
  ProgramGreeting();
  if (DEBUG)
    UnitTest();
  cout << CLEAR_SCREEN;

  // main loop
  do {
    Menu(choice);
    cout << CLEAR_SCREEN;
    switch (choice) {
      case 'L':
        cout << "Creatures:\n";
        cout << *childObject;
        cout << *derivedObject;
        cout << *spawnObject;
        break;
      case 'P':
        cout << "Played with creatures\n";
        childObject->Play();
        derivedObject->Play();
        spawnObject->Play();
        childObject->PassTime();
        derivedObject->PassTime();
        spawnObject->PassTime();
        break;
      case 'F':
        cout << "Fed creatures\n";
        childObject->Feed();
        derivedObject->Feed();
        spawnObject->Feed();
        childObject->PassTime();
        derivedObject->PassTime();
        spawnObject->PassTime();
        break;
      case 'N':
        cout << "Name creatures\n";
        childObject->SetName();
        derivedObject->SetName();
        spawnObject->SetName();
        break;
      case 'Q':
        break;
      default:
        cout << CLEAR_SCREEN << "Invalid choice.\n";
    }
    cout << "\n";
  } while (choice != 'Q');

  cout << "\nThanks for playing!\n";

  // cleanup
  delete childObject;
  delete derivedObject;
  delete spawnObject;

  return 0;
}

void UnitTest() {
  string temp = "";

  cout << "\nUnit Testing...\n";

  // each class tests constructor and stream insertion
  cout << "Testing Child Class...\n";
  Creature* childTest = new Child();
  childTest->ComponentTest();

  cout << "\nTesting Derived Class...\n";
  Creature* derivedTest = new Derived();
  derivedTest->ComponentTest();

  // tests overloaded operator+
  cout << "\nTesting Spawn Class...\n";
  Creature* spawnTest = new Spawn(*childTest + *derivedTest);
  spawnTest->ComponentTest();

  // tests overloaded operator=
  cout << "\nAssignment Operator Test...\n";
  cout << "childTest = childTest\n";
  *childTest = *childTest;
  cout << *childTest;

  // tests copy constructor
  cout << "\nCopy Constructor Test...\n";
  cout << "encounterTest = new Child(childTest)\n";
  Creature* encounterTest = new Child(*childTest);
  cout << *encounterTest;

  cout << "\nUnit Testing Complete.\n";
  cout << "Press enter to continue...";
  getline(cin, temp);

  // cleanup
  delete childTest;
  delete derivedTest;
  delete spawnTest;
  delete encounterTest;
}

void ProgramGreeting() {
  string temp = "";

  // Specification A4 - Write a Lambda
  auto lambda = [](time_t a) { return asctime(localtime(&a)); };
  string date = lambda(time(nullptr));

  cout << endl << CLEAR_SCREEN << endl;
  cout << "Welcome to " << PROGRAM_NAME << "!\n\n";
  cout << "Written by: " << PROGRAM_AUTHOR << ".\n\n";
  cout << "It is currently " << date << "\n";
  cout << "Press enter to continue...";
  getline(cin, temp);
}

void Menu(char& choice) {
  choice = ' ';
  string input = "";

  // loop until user follows directions
  while (choice == ' ') {
    cout << "__Menu__\n";
    for (int i = 0; i < MENU_SIZE; i++)
      cout << "<" << MENU_OPTIONS[i] << ">" << MENU_TEXT[i] << "\n";
    cout << "\nEnter your choice: ";

    getline(cin, input);
    choice = toupper(input[0]);

    // Specification C3 - Validate Input
    for (int i = 0; i < MENU_SIZE; i++) {
      if (choice == MENU_OPTIONS[i])
        break;
      else if (i == MENU_SIZE - 1 && choice != MENU_OPTIONS[i]) {
        choice = ' ';
        cout << CLEAR_SCREEN << "Invalid choice.\n";
      }
    }
  }
}