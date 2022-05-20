// Implementation file for the Participant class.
#include "Participant.h"

#include <string>

using namespace std;

// constructor
Participant::Participant(string f, string l) {
  _first = f;
  _last = l;
  _partnerLocation = -1;
  _selected = false;
}

// mutators
void Participant::SetSelected(bool s) {
  _selected = s;
}

void Participant::SetPartnerLocation(int pl) {
  _partnerLocation = pl;
}

// accessors
bool Participant::GetSelected() const {
  return _selected;
}

int Participant::GetPartnerLocation() const {
  return _partnerLocation;
}

string Participant::GetFirstName() const {
  return _first;
}

string Participant::GetLastName() const {
  return _last;
}

string Participant::GetFullName() const {
  return _last + ", " + _first;
}