// Specification file for the ParticipantList class.
#pragma once

#ifndef PARTICIPANTLIST_H
#define PARTICIPANTLIST_H

#include "Participant.h"

#include <vector>

using namespace std;

class ParticipantList {
 private:
  // variables
  vector<Participant*> _participant;
  unsigned int _index = 0;

 public:
  // constructor
  ParticipantList(int);

  // mutators located in ParticipantList.cpp
  void AssignPartners();
  void AddParticipant(Participant*);
  void IncrementIndex();

  // accessors located in ParticipantList.cpp
  Participant* GetNext() const;
  Participant* GetPartner(int) const;
};
#endif