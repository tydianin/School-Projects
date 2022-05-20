/*
monopoly.cpp
Weston Gibson, CISP 400
27 April 2022
*/

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Property {
  string name;
  int count = 0;
};

// compile time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";
constexpr char PROGRAM_NAME[] = "Monopoly Monte Carlo";
constexpr char PROGRAM_AUTHOR[] = "Weston Gibson";
const int COMMUNITY = 2;
const int CHANCE = 9;

// programming prototypes
void ProgramGreeting();
int StringToInt(string);

// runtime prototypes
void CommunityChance(int, int&);

int main(int argc, char* argv[]) {
  string temp = "";
  int iterations = 0;
  int space = 0;

  ProgramGreeting();

  // captures argv
  if (argc > 1) {
    temp = argv[1];
    iterations = StringToInt(temp);
  }

  // if no argv or less than 1, try again
  while (iterations < 1) {
    cout << "Please enter the number of iterations.\n";
    getline(cin, temp);
    iterations = StringToInt(temp);
  }

  // seed rng
  srand(time(0));

  // main vector for game
  Property board[40] = {{"Go", 0},
                        {"Mediterranean Avenue", 0},
                        {"Community Chest", 0},
                        {"Baltic Avenue", 0},
                        {"Income Tax", 0},
                        {"Reading Railroad", 0},
                        {"Oriental Avenue", 0},
                        {"Chance", 0},
                        {"Vermont Avenue", 0},
                        {"Connecticut Avenue", 0},
                        {"Just Visiting", 0},
                        {"St. Charles Place", 0},
                        {"Electric Company", 0},
                        {"States Avenue", 0},
                        {"Virginia Avenue", 0},
                        {"Pennsylvania Railroad", 0},
                        {"St. James Place", 0},
                        {"Community Chest", 0},
                        {"Tennessee Avenue", 0},
                        {"New York Avenue", 0},
                        {"Free Parking", 0},
                        {"Kentucky Avenue", 0},
                        {"Chance", 0},
                        {"Indiana Avenue", 0},
                        {"Illinois Avenue", 0},
                        {"B & O Railroad", 0},
                        {"Atlantic Avenue", 0},
                        {"Ventnor Avenue", 0},
                        {"Water Works", 0},
                        {"Marvin Gardens", 0},
                        {"Jail", 0},
                        {"Pacific Avenue", 0},
                        {"North Carolina Avenue", 0},
                        {"Community Chest", 0},
                        {"Pennsylvania Avenue", 0},
                        {"Short Line", 0},
                        {"Chance", 0},
                        {"Park Place", 0},
                        {"Luxury Tax", 0},
                        {"Boardwalk", 0}};

  // main loop
  for (int i = 0; i < iterations; ++i) {
    // roll the dice
    space += (1 + rand() % 6) + (1 + rand() % 6);

    // reset if reach/pass go
    if (space > 39)
      space -= 40;

    // community/chance
    if (board[space].name == "Chance")
      CommunityChance(CHANCE, space);
    while (board[space].name == "Community Chest") {
      CommunityChance(COMMUNITY, space);
    }

    // count the property
    board[space].count += 1;

    // change for jail
    if (space == 30)
      space = 10;
  }

  // sort the array by count
  sort(board, board + 39,
       [](const Property& a, const Property& b) { return a.count > b.count; });

  // print out results
  cout << "Tadah\n\n";
  for (int i = 0; i < 33; ++i)
    cout << setw(21) << board[i].name << ": " << setw(10) << board[i].count
         << "\n";
  cout << endl;

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
  cout << endl << CLEAR_SCREEN << endl;
}

// converts string to int
int StringToInt(string input) {
  int output;
  try {
    output = stoi(input);
  } catch (...) {
    cout << "Please enter a valid number greater than 0.\n";
    output = 0;
  }
  return output;
};

// handles both community chest and chance
void CommunityChance(int deck, int& space) {
  int card = rand() % deck;

  switch (card) {
    case 0:
      // advance to go
      space = 0;
    case 1:
      // go to jail
      space = 10;
    case 2:
      // go back 3 spaces
      space -= 3;
    case 3:
      // reading railroad
      space = 5;
    case 4:
      // st. charles place
      space = 11;
    case 5:
      // illinois avenue
      space = 24;
    case 6:
      // boardwalk
      space = 39;
    case 7:
      // nearest utility
      if (space > 27 || space < 12)
        space = 12;
      else
        space = 27;
    case 8:
      // nearest railroad
      if (space > 34 || space < 5)
        space = 5;
      else if (space < 15)
        space = 15;
      else if (space < 25)
        space = 25;
      else
        space = 35;
  }
}