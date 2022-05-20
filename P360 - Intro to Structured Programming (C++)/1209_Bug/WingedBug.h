#pragma once

#include "LeggedBug.h"

class WingedBug : public LeggedBug {
 private:
  int _wings;
  int _altitude;

 public:
  // constructor
  WingedBug(string = "None",
            string = "None",
            string = "None",
            string = "None",
            int = 0,
            int = 0,
            int = 0);
  // mutators
  void SetWings(int);
  void SetAltitude(int);
  // accessors
  int GetWings() const;
  int GetAltitude() const;
  virtual string GetString() const override;
};