// objects.cpp
// Weston Gibson, CISP 360
// 20 November 2021

#include <iostream>
#include <string>
#include "Contact.h"

using namespace std;

const int CONTACTS = 5;

// GetContact() prototype
Contact GetContact(Contact* const contact);

// main
int main() {
  // object array
  Contact phoneBook[CONTACTS];

  // loop to get contact info into phoneBook
  for (int i = 0; i < CONTACTS; i++) {
    phoneBook[i] = GetContact(&phoneBook[i]);
    cout << endl;
  }

  // clear the screen
  cout << "\033[2J\033[1;1H";

  // loop to print contact info
  for (int i = 0; i < CONTACTS; i++) {
    cout << "Contact ID: " << i + 1 << endl;
    cout << phoneBook[i].getFirstName() << endl;
    cout << phoneBook[i].getLastName() << endl;
    cout << phoneBook[i].getPhoneNumber() << endl;
    cout << endl;
  }

  // pause to close
  cout << "Press enter to close...";
  cin.ignore();
  cin.get();

  // end of main
  return 0;
}

// GetContact()
Contact GetContact(Contact* const contact) {
  // variables
  string firstName;
  string lastName;
  string phoneNumber;

  // get first name
  cout << "Enter first name: ";
  cin >> firstName;

  // get last name
  cout << "Enter last name: ";
  cin >> lastName;

  // get phone number
  cout << "Enter phone number: ";
  cin >> phoneNumber;

  // set contact info
  contact->setFirstName(firstName);
  contact->setLastName(lastName);
  contact->setPhoneNumber(phoneNumber);

  return *contact;
}