#include "LeggedBug.h"

LeggedBug::LeggedBug(string cn, string tx, string od, string de, int le)
    : BaseBug(cn, tx, od, de) {
  SetLegs(le);
}

void LeggedBug::SetLegs(int le) {
  _legs = le;
}

int LeggedBug::GetLegs() const {
  return _legs;
}

string LeggedBug::GetString() const {
  return BaseBug::GetString() + "  Legs...........: " + to_string(_legs) + "\n";
}