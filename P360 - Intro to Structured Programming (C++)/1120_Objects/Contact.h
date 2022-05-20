// Specification file for the Contact class
#ifndef HEADER_H
#define HEADER_H
#include <string>

using namespace std;

class Contact {
 private:
  // variables
  string firstName;
  string lastName;
  string phoneNumber;

 public:
  // constructor
  Contact() {
    firstName = "";
    lastName = "";
    phoneNumber = "";
  }

  // mutators
  void setFirstName(string f) { firstName = f; }

  void setLastName(string l) { lastName = l; }

  void setPhoneNumber(string p) { phoneNumber = p; }

  // accessors
  string getFirstName() const { return firstName; }

  string getLastName() const { return lastName; }

  string getPhoneNumber() const { return phoneNumber; }
};
#endif