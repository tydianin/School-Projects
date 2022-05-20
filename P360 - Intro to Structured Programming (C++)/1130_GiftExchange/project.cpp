// giftExchange.cpp
// Weston Gibson, CISP 360
// 30 November 2021

#include "Participant.h"
#include "ParticipantList.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void ClearScreen() {
  cout << "\033[2J\033[1;1H";
}

int main() {
  // variables
  ParticipantList* pList;
  Participant* aPerson;

  unsigned int n = 0;
  int partner = 0;

  string first;
  string last;

  // request list size from user
  // require an even number of participants
  while (n <= 1 || n % 2 != 0 || !cin.good()) {
    ClearScreen();
    cout << "Please provide an even number greater than zero." << endl
         << "How many participants would you like to add?" << endl
         << "> ";
    cin >> n;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  // dynamically create list of participants
  pList = new ParticipantList(n);
  for (unsigned int i = 0; i < n; i++) {
    cout << endl;
    cout << "Participant " << i + 1 << "'s first name: ";
    cin >> first;
    cout << "Participant " << i + 1 << "'s last name: ";
    cin >> last;
    aPerson = new Participant(first, last);
    pList->AddParticipant(aPerson);
  }

  // randomly assign partners
  pList->AssignPartners();

  // print out results
  ClearScreen();
  cout << "Gift Exchange List" << endl;
  cout << string(80, '*') << endl;
  aPerson = pList->GetNext();
  pList->IncrementIndex();
  while (aPerson != nullptr) {
    partner = aPerson->GetPartnerLocation();
    cout << "Participant: " << setw(27) << left << aPerson->GetFullName()
         << " Partner: " << setw(30) << left
         << pList->GetPartner(partner)->GetFullName() << endl;
    aPerson = pList->GetNext();
  }

  // clean up
  delete pList;
  return 0;
}