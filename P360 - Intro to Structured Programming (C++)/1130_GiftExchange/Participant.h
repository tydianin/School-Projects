// Specification file for the Participant class.
#pragma once

#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>

using namespace std;

class Participant {
 private:
  // variables
  bool _selected = false;
  int _partnerLocation = -1;
  string _first;
  string _last;

 public:
  // constructor located in Participant.cpp
  Participant(string, string);

  // mutators located in Participant.cpp
  void SetSelected(bool);
  void SetPartnerLocation(int);

  // accessors located in Participant.cpp
  bool GetSelected() const;
  int GetPartnerLocation() const;
  string GetFirstName() const;
  string GetLastName() const;
  string GetFullName() const;
};
#endif