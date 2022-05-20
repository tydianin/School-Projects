#pragma once

#include "BaseBug.h"

class LeggedBug : public BaseBug {
 private:
  int _legs;

 public:
  // constructor
  LeggedBug(string = "None",
            string = "None",
            string = "None",
            string = "None",
            int = 0);
  // mutator
  void SetLegs(int);
  // accessors
  int GetLegs() const;
  virtual string GetString() const override;
};