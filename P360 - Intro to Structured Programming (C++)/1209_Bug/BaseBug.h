#pragma once

#include <string>
using namespace std;

class BaseBug {
 private:
  string _commonName, _taxonomy, _order, _description;

 public:
  // constructor
  BaseBug(string = "None", string = "None", string = "None", string = "None");
  // accessor
  virtual string GetString() const;
};