#pragma once

// Specification file for the Person class
#ifndef HEADER_H
#define HEADER_H
#include <string>

using namespace std;

class Person {
 private:
  // variables
  string _first;
  string _last;

 public:
  // overloaded constructor
  Person(string f, string l) {
    _first = f;
    _last = l;
  }

  // GetFullName
  string GetFullName() { return _first + " " + _last; }

  // overloaded + operator
  string operator+(const Person& other) { return other._first + " " + _last; }
};
#endif