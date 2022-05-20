// bug.cpp
// Weston Gibson, CISP 360
// 9 December 2021

#include <iostream>
#include <string>
#include <vector>

#include "BaseBug.h"
#include "LeggedBug.h"
#include "WingedBug.h"

using namespace std;

const int BUG_MENU_SIZE = 5;
const string EXIT_MENU_PROMPT = "Exit Application";

void ClearScreen();
void DisplayBug(BaseBug* aBug);
void DisplayMenu(string menuItems[], int menuSize);
int DisplayAMenu(string menuItems[], int menuSize);
void WriteMenuItem(int itemNum, string itemText);
int GetValidMenuChoice(string menuItems[], int menuSize);

int main() {
  string mainMenuOptions[] = {"Spider", "Ant", "Butterfly", "Snail",
                              EXIT_MENU_PROMPT};

  int selectedMenuItem;
  BaseBug* anyBug = nullptr;

  vector<BaseBug*> bugList;

  selectedMenuItem = DisplayAMenu(mainMenuOptions, BUG_MENU_SIZE);

  while (selectedMenuItem < BUG_MENU_SIZE) {
    switch (selectedMenuItem) {
      case 1:
        anyBug = new LeggedBug("Spider", "Aranae", "Aranae",
                               "Air-breathing arthropods with fangs generally "
                               "able to inject venom.",
                               8);
        break;
      case 2:
        anyBug = new LeggedBug("Ant", "Formicidae", "Hymenoptera",
                               "Eusocial insects easily identified by their "
                               "geniculate antennae and node-like structure.",
                               6);
        break;
      case 3:
        anyBug = new WingedBug("Butterfly", "Rhopalocera", "Lepidoptera",
                               "Insects with large, often brightly coloured "
                               "wings and conspicuous, fluttering flight.",
                               6, 2, 6000);
        break;
      case 4:
        anyBug = new BaseBug(
            "Snail", "Gastropoda",
            "Gastropoda are a class, higher than an order.",
            "In loose terms, a shelled gastropod. A name most often applied to "
            "terrestial pulmonate gastropod molluscs.");
      default:
        break;
    }
    bugList.push_back(anyBug);
    selectedMenuItem = DisplayAMenu(mainMenuOptions, BUG_MENU_SIZE);
  }

  for (unsigned int i = 0; i < bugList.size(); i++) {
    DisplayBug(bugList[i]);
  }

  return 0;
}

void ClearScreen() {
  cout << "\033[2J\033[1;1H";
}

void DisplayBug(BaseBug* aBug) {
  cout << aBug->GetString() << endl;
}

int DisplayAMenu(string menuOptions[], int menuSize) {
  int menuChoice = 0;

  ClearScreen();
  menuChoice = GetValidMenuChoice(menuOptions, menuSize);

  return menuChoice;
}

void DisplayMenu(string menuItems[], int menuSize) {
  for (int i = 0; i < menuSize; i++) {
    WriteMenuItem((i + 1), menuItems[i]);
  }

  cout << "Enter Menu Item Number: ";
}

void WriteMenuItem(int itemNum, string itemText) {
  cout << itemNum << ") " << itemText << "\n";
}

int GetValidMenuChoice(string menuItems[], int menuSize) {
  int menuChoice = 0;

  DisplayMenu(menuItems, menuSize);
  cin >> menuChoice;

  while ((menuChoice < 1) || (menuChoice > (menuSize))) {
    ClearScreen();

    cout << "Please select a menu choice between 1 and " << menuSize << endl;
    DisplayMenu(menuItems, menuSize);
    cin >> menuChoice;

    ClearScreen();
  }

  return menuChoice;
}