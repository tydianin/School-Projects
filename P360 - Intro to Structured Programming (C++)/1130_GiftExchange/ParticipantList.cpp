// Implementation file for the Participantlist class.
#include "ParticipantList.h"
#include <iostream>

using namespace std;

// constructor
ParticipantList::ParticipantList(int n) {
  _participant.reserve(n);
}

// randomly assign a partner to each participant
void ParticipantList::AssignPartners() {
  int partner = rand() % _participant.size();
  bool partnerSelected = _participant[partner]->GetSelected();

  for (unsigned int i = 0; i < _participant.size(); i++) {
    do {
      partner = rand() % _participant.size();
      partnerSelected = _participant[partner]->GetSelected();
    } while (partner == i || partnerSelected == true);
    _participant[i]->SetPartnerLocation(partner);
    _participant[partner]->SetSelected(true);
  }
}

// add a participant to the list
void ParticipantList::AddParticipant(Participant* p) {
  _participant.push_back(p);
}

// increment the index for the GetNext() function
void ParticipantList::IncrementIndex() {
  _index++;
}

// get the next participant in the list
Participant* ParticipantList::GetNext() const {
  int index = _index;
  if (index < _participant.size())
    return _participant[index++];
  else
    return nullptr;
}

// get the partner of the participant at the specified index
Participant* ParticipantList::GetPartner(int index) const {
  if (index != -1)
    return _participant[index];
  else {
    cout << "User managed to elude input validation.";
    exit(1);
  }
}
const