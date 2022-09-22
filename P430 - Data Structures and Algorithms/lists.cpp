/*
Assignment 3
Weston Gibson, CISP 430
25 September 2022

Uses C++17 in accordance with GCC 12.2
*/

// C++ library headers
#include <iostream>  // cin, cout

// std
using namespace std;

// compile-time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// List ADT from figure 4.1
template <typename Elem>
class List {
 private:
  // protect assignment
  void operator=(const List&) {}

  // protect copy ctor
  List(const List&) {}

 public:
  // ctor
  List() {}

  // dtor
  virtual ~List() {}

  // clear
  virtual void clear() = 0;

  // prepend
  virtual bool insert(const Elem&) = 0;

  // append
  virtual bool append(const Elem&) = 0;

  // pop
  virtual Elem remove() = 0;

  // head
  virtual void movetoStart() = 0;

  // tail
  virtual void movetoEnd() = 0;

  // left
  virtual void prev() = 0;

  // right
  virtual void next() = 0;

  // len
  virtual int leftLength() const = 0;
  virtual int rightLength() const = 0;

  // index
  virtual void movetoPos(int pos) = 0;

  // get
  virtual const Elem& getValue() const = 0;
};

int main(int argc, char* argv[]) {
  // protect from weird invocations
  int argStart = 0;
  // pull args
  for (int i = 0; i < argc; ++i) {
    if (&argv[i][0] != ".")
      continue;
    else

  }
}