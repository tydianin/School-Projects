/*
pig.cpp
Weston Gibson, CISP 400
January 26, 2022
*/

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

struct Player {
  string name = "";
  int turnPoints = 0;
  int grandPoints = 0;
  int choice = 0;
};

// extra Constants
const string PROGRAM_NAME = "Pig";
const int MIN_SCORE = 1;
const int WIN_SCORE = 100;
const int COMPUTER_ROLL = 4;
const int WAIT = 1;

// Specification C1 - Fixed Seed
const int SEED = 127;

// initial menu
const int INI_MENU_MIN = 1;
const int INI_MENU_SIZE = 2;
const string INI_MENU[INI_MENU_SIZE] = {"Play Game", "Quit Game"};
const int INI_MENU_PLAY = 1;
const int INI_MENU_QUIT = 2;

// Specification C4 - Bulletproof Menu
const int MENU_MIN = 1;

// Specification C3 - Numeric Menu
const int MENU_SIZE = 3;
const string MENU[MENU_SIZE] = {"Roll", "Hold", "Quit Match"};
const int MENU_ROLL = 1;
const int MENU_HOLD = 2;
const int MENU_QUIT = 3;

// Specification B2 - Display Due Date
const string DUE_DATE = "January 30, 2022";

// Specification A3 - Protect RandomNumber() input
const int RNG_MIN = 1;
const int RNG_MAX = 100;

// common utilities
void ClearScreen();
void Handler();
int StringtoInt(string);
void ProgramGreeting();

// prototypes
int InitialMenu(int*, string*);
Player NumericMenu(Player, Player, int*, string*);
Player StudentName(Player);
Player StudentTurn(Player, Player, int*, string*);
Player ComputerTurn(Player, int*, string*);
Player Roll(Player);
Player Hold(Player);
void End(Player, int*, string*);
void HighScore(Player, int*, string*);
void DisplayHighScore(int*, string*);
int RandomNumber(int, int);
int D6();

// main
int main() {
  int coin = D6();
  string temp = "";
  string input = "";
  Player computer = {"CPU"};
  Player student;

  // Specification C1 - Fixed Seed
  srand(SEED);

  // Specification B3 - Hi Score on Heap
  int* hScore = new int;
  *hScore = 0;

  // added functionality hScorePlayer
  string* hScorePlayer = new string;
  *hScorePlayer = "Nobody";

  ClearScreen();
  ProgramGreeting();

  // main game loop
  while (InitialMenu(hScore, hScorePlayer) != INI_MENU_QUIT &&
         student.choice != MENU_QUIT) {
    // Specification C2 - Student Name
    student.choice = 0;
    student = StudentName(student);

    ClearScreen();
    // psuedo-coin flip for who goes first
    if (coin > COMPUTER_ROLL) {
      cout << student.name << " will go first.\n\n";
      student = StudentTurn(student, computer, hScore, hScorePlayer);
    } else
      cout << computer.name << " will go first.\n\n";

    // loops until someone wins or user quits
    while (student.grandPoints < WIN_SCORE &&
           computer.grandPoints < WIN_SCORE && student.choice != MENU_QUIT) {
      computer = ComputerTurn(computer, hScore, hScorePlayer);
      if (computer.grandPoints < WIN_SCORE)
        student = StudentTurn(student, computer, hScore, hScorePlayer);
    }

    // display winner/quit
    if (student.grandPoints >= WIN_SCORE)
      cout << student.name << " wins the match with " << student.grandPoints
           << " points!\n\n";
    else if (computer.grandPoints >= WIN_SCORE)
      cout << computer.name << " wins the match with " << computer.grandPoints
           << " points!\n\n";
    else
      cout << "The match was ended before a winner could be declared.\n\n";

    // kicks back out to initial menu
    cout << "Press ENTER to continue.";
    getline(cin, temp);
  }

  // cleanup
  ClearScreen();
  DisplayHighScore(hScore, hScorePlayer);
  cout << "\nThanks for playing!" << endl;
  delete hScorePlayer;
  delete hScore;
  return 0;
}

// common utilities
void ClearScreen() {
  cout << "\033[2J\033[1;1H";
}

void Handler() {
  ClearScreen();
  cout << "Please enter a valid option.\n" << endl;
}

int StringtoInt(string a) {
  int b;
  try {
    b = stoi(a);
  } catch (...) {
    b = 0;
  }
  return b;
}

// a simple description of what the program does
void ProgramGreeting() {
  string temp = "";
  cout << "Welcome to " << PROGRAM_NAME << "!\n"
       << "This program will simulate a simple game called " << PROGRAM_NAME
       << ".\n"
       << "\n"
       << "Each turn, the active player faces a decision (roll or hold).\n"
       << "  Roll:\n"
       << "    If the die reads a 1, the turn ends and all of the player's "
          "turn points are lost.\n"
       << "    If the die reads any other number, the number is added to the "
          "player's turn points.\n"
       << "  Hold:\n"
       << "    The player's turn points are added to the player's grand "
          "points and the turn ends.\n"
       << "\n"
       << "The first player to 100 grand points is the winner.\n"
       << "\n"
       << "This assignment was due on " + DUE_DATE + ".\n"
       << endl
       << "Press enter to continue.";
  getline(cin, temp);
}

// initial menu
int InitialMenu(int* hScore, string* hScorePlayer) {
  int choice = 0;
  string input = "";

  ClearScreen();

  // loops until user follows directions
  while (choice < INI_MENU_MIN || choice > INI_MENU_SIZE) {
    cout << "Welcome to " << PROGRAM_NAME << "!\n\n";
    DisplayHighScore(hScore, hScorePlayer);

    // get user menu choice
    cout << "Please select from the following options:\n";
    for (int i = 0; i < INI_MENU_SIZE; i++)
      cout << "  " << (i + 1) << ". " << INI_MENU[i] << "\n";
    cout << endl << "Enter your choice: ";

    getline(cin, input);
    choice = StringtoInt(input);

    // handle if user doesn't follow directions
    if (choice < INI_MENU_MIN || choice > INI_MENU_SIZE)
      Handler();
  }
  return choice;
}

// Specification C2 - Student Name
Player StudentName(Player student) {
  string input = "";
  char yn = 'N';
  if (student.name != "")
    yn = 'X';

  // loops until user accepts their name
  while (yn != 'Y') {
    ClearScreen();
    if (yn == 'N') {
      cout << "Please enter your name: ";
      getline(cin, student.name);
      cout << endl;
    }

    // confirm name with user
    do {
      cout << "Your name is " << student.name << "." << endl
           << "Would you like to keep this name? (Y/N): ";

      getline(cin, input);

      // convert string to single char, reset if length > 1
      if (input.length() == 1)
        yn = (char)toupper(input[0]);
      else {
        yn = ' ';
        input = "";
      }

      // handle if user doesn't follow directions
      if (yn != 'Y' && yn != 'N')
        Handler();

      // loop until user follows directions
    } while (yn != 'Y' && yn != 'N');
  }
  return student;
}

// Specification C3 - Numeric Menu
Player NumericMenu(Player student,
                   Player computer,
                   int* hScore,
                   string* hScorePlayer) {
  student.choice = 0;
  string input = "";

  // loops until user follows directions
  while (student.choice < MENU_MIN || student.choice > MENU_SIZE) {
    DisplayHighScore(hScore, hScorePlayer);
    cout << student.name << " Grand Points: " << student.grandPoints << "\n"
         << computer.name << " Grand Points: " << computer.grandPoints << "\n"
         << "\nYour Turn Points: " << student.turnPoints;

    // get user menu choice
    cout << "\n\nPlease select from the following options:\n";
    for (int i = 0; i < MENU_SIZE; i++)
      cout << "  " << (i + 1) << ". " << MENU[i] << "\n";
    cout << endl << "Enter your choice: ";

    getline(cin, input);
    ClearScreen();
    student.choice = StringtoInt(input);

    // Specification C4 - Bulletproof Menu
    if (student.choice < MENU_MIN || student.choice > MENU_SIZE)
      Handler();
  }
  return student;
}

// student turn
Player StudentTurn(Player student,
                   Player computer,
                   int* hScore,
                   string* hScorePlayer) {
  student.turnPoints = 0;

  // what will the player do
  do {
    student = NumericMenu(student, computer, hScore, hScorePlayer);
    if (student.choice == MENU_ROLL)
      student = Roll(student);
    else if (student.choice == MENU_HOLD) {
      student = Hold(student);
    }
  } while (student.choice != MENU_HOLD && student.choice != MENU_QUIT);

  // end sequence
  End(student, hScore, hScorePlayer);
  DisplayHighScore(hScore, hScorePlayer);
  return student;
}

// computer turn
Player ComputerTurn(Player computer, int* hScore, string* hScorePlayer) {
  int old = 0;
  computer.turnPoints = 0;
  this_thread::sleep_for(chrono::seconds(WAIT));
  computer = Roll(computer);

  // the computer will roll on a 4-6
  while (computer.turnPoints >= old + COMPUTER_ROLL &&
         computer.grandPoints + computer.turnPoints < WIN_SCORE) {
    cout << "CPU will roll again.\n\n";
    old = computer.turnPoints;
    computer = Roll(computer);
  }

  // the computer will hold on a 1-3
  if (computer.turnPoints > old)
    computer = Hold(computer);

  // end sequence
  End(computer, hScore, hScorePlayer);
  return computer;
}

// general roll
Player Roll(Player player) {
  int die = D6();
  cout << player.name << " rolled a " << die << ".\n\n";
  this_thread::sleep_for(chrono::seconds(WAIT));

  // awards points if die is > MIN_SCORE
  if (die != MIN_SCORE)
    player.turnPoints += die;

  // removes them if not
  else {
    player.turnPoints = 0;
    cout << player.name << "'s turn has ended.\n\n";
    player.choice = MENU_HOLD;
  }

  return player;
}

// general hold
Player Hold(Player player) {
  cout << player.name << " will hold.\n\n";
  player.grandPoints += player.turnPoints;
  return player;
}

// general end sequence
void End(Player player, int* hScore, string* hScorePlayer) {
  this_thread::sleep_for(chrono::seconds(WAIT));
  cout << player.name << " scored " << player.turnPoints << " points.\n"
       << endl;
  this_thread::sleep_for(chrono::seconds(WAIT));
  HighScore(player, hScore, hScorePlayer);
}

// updates hScore and hScorePlayer as needed
void HighScore(Player player, int* hScore, string* hScorePlayer) {
  if (player.grandPoints > *hScore) {
    *hScore = player.grandPoints;
    *hScorePlayer = player.name;
  }
}

// Specification B4 - Display High Score
void DisplayHighScore(int* hScore, string* hScorePlayer) {
  cout << "High score: " << *hScorePlayer << " with " << *hScore << " points.\n"
       << endl;
}

// Specification A2 - RandomNumber() function
int RandomNumber(int lo, int hi) {
  int r = 0;

  // Specification A3 - Protect RandomNumber() input
  if (lo > hi || lo < RNG_MIN || hi > RNG_MAX)
    return -1;
  else
    r = (rand() % hi) + 1;

  // Specification A4 - Protect RandomNumber() output
  // lo >= RNG_MIN and hi <= RNG_MAX imply RNG_MIN <= r <= RNG_MAX
  if (r > hi || r < lo)
    return -2;
  else
    return r;
}

// Specification A1 - D6() function
int D6() {
  int die = 0;
  do {
    die = RandomNumber(1, 6);
    if (die == -1)
      cout << "Error: Invalid input to RandomNumber()." << endl;
    else if (die == -2)
      cout << "Error: Invalid output from RandomNumber()." << endl;
  } while (die < 1);
  return die;
}