#include "WingedBug.h"

WingedBug::WingedBug(string cn,
                     string tx,
                     string od,
                     string de,
                     int le,
                     int wi,
                     int al)
    : LeggedBug(cn, tx, od, de, le) {
  SetWings(wi);
  SetAltitude(al);
}

void WingedBug::SetWings(int wi) {
  _wings = wi;
}

void WingedBug::SetAltitude(int al) {
  _altitude = al;
}

int WingedBug::GetWings() const {
  return _wings;
}

int WingedBug::GetAltitude() const {
  return _altitude;
}

string WingedBug::GetString() const {
  return LeggedBug::GetString() + "  Wings..........: " + to_string(_wings) +
         "\n" + "  Altitude.......: " + to_string(_altitude) + "meters\n";
}