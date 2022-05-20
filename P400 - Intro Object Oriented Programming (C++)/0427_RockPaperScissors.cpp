/*
rockPaperScissors.cpp
Weston Gibson, CISP 400
27 April 2022
*/

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// compile time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";
constexpr char PROGRAM_NAME[] = "Rock, Paper, Scissors";
constexpr char PROGRAM_AUTHOR[] = "Weston Gibson";

// runtime constants
const int MENU_SIZE = 4;
const char MENU_OPTIONS[MENU_SIZE] = {'R', 'P', 'S', 'Q'};
const string MENU_TEXT[MENU_SIZE] = {"Rock", "Paper", "Scissors", "Quit"};

// prototypes
void ProgramGreeting();
void Menu(char&);

int main() {
  // seed rng
  srand(time(0));
  char choice = ' ';
  int user = 0, computer = 0;
  int uScore = 0, cScore = 0, hands = 0;

  // startup sequence
  ProgramGreeting();
  cout << CLEAR_SCREEN;

  // main loop
  do {
    computer = rand() % 3;

    Menu(choice);
    cout << CLEAR_SCREEN;

    // turn user input into a number
    switch (choice) {
      case 'R':
        cout << "You chose Rock.\n";
        user = 0;
        hands += 1;
        break;
      case 'P':
        cout << "You chose Paper.\n";
        user = 1;
        hands += 1;
        break;
      case 'S':
        cout << "You chose Scissors.\n";
        user = 2;
        hands += 1;
        break;
      case 'Q':
        break;
      default:
        cout << CLEAR_SCREEN << "Invalid choice.\n";
    }

    // determine who won, give points to winner
    if (hands != 0 && choice != 'Q') {
      cout << "Computer chose " << MENU_TEXT[computer] << ".\n";
      if (user == computer)
        cout << "Tie!\n";
      else if (user - computer == 1 || user - computer == -2) {
        cout << "You win!\n";
        uScore += 1;
      } else {
        cout << "You lose!\n";
        cScore += 1;
      }
    }

  } while (choice != 'Q');

  cout << "\nThanks for playing!\n"
       << "Total hands played: " << hands << "\n"
       << "Your score: " << uScore << "\n"
       << "Computer score: " << cScore << "\n"
       << "Winner: ";

  if (uScore > cScore)
    cout << "You!\n";
  else if (uScore < cScore)
    cout << "Computer!\n";
  else
    cout << "Tie!\n";
  return 0;
}

// does what it says
void ProgramGreeting() {
  string temp = "";

  cout << endl << CLEAR_SCREEN << endl;
  cout << "Welcome to " << PROGRAM_NAME << "!\n\n";
  cout << "Written by: " << PROGRAM_AUTHOR << ".\n\n";
  cout << "Press enter to continue...";

  getline(cin, temp);
}

void Menu(char& choice) {
  choice = ' ';
  string input = "";

  // loop until user follows directions
  while (choice == ' ') {
    cout << "\n__Menu__\n";
    for (int i = 0; i < MENU_SIZE; i++)
      cout << "<" << MENU_OPTIONS[i] << "> " << MENU_TEXT[i] << "\n";
    cout << "\nEnter your choice: ";

    // safe input get
    getline(cin, input);
    choice = toupper(input[0]);

    // input validation
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