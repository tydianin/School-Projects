/*
Assignment 4
Weston Gibson, CISP 430
2 October 2022

Uses C++17 in accordance with GCC 12.2

Had to use array implementation due to stipulation in assignment prompt.
*/

// C++ library headers
#include <iostream>  // cin, cout
#include <string>    // string

// namespace
using namespace std;

// compile-time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// Copied from utility functions appendix A
// DefaultListSize for lists, arrays, etc.
const int DefaultListSize = 10;

// Assert: If "val" is false, print a message and terminate the program
void Assert(bool val, string str) {
  if (!val) {
    cout << "Assertion Failed: " << str << endl;
    exit(-1);
  }
}

// Stack ADT from figure 4.17
template <typename Elem>
class Stack {
 private:
  // Protect assignment
  void operator=(const Stack&) {}

  // Protect copy constructor
  Stack(const Stack&) {}

 public:
  // Default constructor
  Stack() {}

  // Base destructor
  virtual ~Stack() {}

  // Reinitialize the stack. The user is responsible for
  // reclaiming the storage used by the stack elements.
  virtual void clear() = 0;

  // Push an element onto the top of the stack.
  virtual void push(const Elem&) = 0;

  // Remove and return the element at the top of the stack.
  virtual Elem pop() = 0;

  // Return a copy of the top element.
  virtual const Elem& topValue() const = 0;

  // Return the number of elements in the stack.
  virtual int length() const = 0;
};

// Array-based stack implementation
template <typename Elem>
class AStack : public Stack<Elem> {
 private:
  // Maximum size of stack
  int maxSize;

  // Index for top element
  int top;

  // Array holding stack elements
  Elem* listArray;

 public:
  // Constructor
  AStack(int size = DefaultListSize) {
    maxSize = size;
    top = 0;
    listArray = new Elem[size];
  }

  // Destructor
  ~AStack() { delete[] listArray; }

  // Reinitialize
  void clear() { top = 0; }

  // Put "it" on stack
  void push(const Elem& it) {
    Assert(top != maxSize, "Stack is full");
    listArray[top++] = it;
  }

  // Pop top element
  Elem pop() {
    Assert(top != 0, "Stack is empty");
    return listArray[--top];
  }

  // Return top element
  const Elem& topValue() const {
    Assert(top != 0, "Stack is empty");
    return listArray[top - 1];
  }

  // Return length
  int length() const { return top; }
};

bool check(char, AStack<char>&);

int main() {
  cout << CLEAR_SCREEN;

  // instantiate stack
  AStack A = AStack<char>(255);

  // get characters from user
  cout << "Enter string to test\n";
  string in;
  getline(cin, in);

  // move characters to stack
  for (int i = 0; i < in.length(); i++) {
    A.push(in[i]);
  }

  // check string
  bool prog = false;
  while (A.length()) {
    prog = false;
    if (A.length() >= 2)
      prog = check(A.pop(), A);
  }

  // output and cleanup
  prog ? (cout << "True") : (cout << "False");
  A.clear();
  return 0;
}

bool check(char a, AStack<char>& A) {
  bool inner = false, outer = true;
  char b = A.pop();

  if (a == ')')
    inner = b == '(';
  else if (a == '}' || a == ']')
    inner = b == a - 2;

  // drill down, drill across
  while (!inner && A.length()) {
    outer = false;
    inner = check(b, A);
  }
  while (!outer && A.length()) {
    outer = check(a, A);
  }

  return (inner && outer);
}