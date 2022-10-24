/*
Midterm Question 2
Weston Gibson, CISP 430
23 October 2022

Uses C++17 in accordance with GCC 12.2
*/

// C++ library headers
#include <iostream>  // cin, cout
#include <string>    // string, stoi

// namespace
using namespace std;

// trimmed from figure 4.17
template <typename T>
class Stack {
 private:
  // protect assignment and copy
  void operator=(const Stack&) {}
  Stack(const Stack&) {}

 public:
  // ctor and dtor
  Stack() {}
  virtual ~Stack() {}

  // standard operations
  virtual void push(const T&) = 0;
  virtual T pop() = 0;
};

// Array-based stack implementation
template <typename T>
class AStack : public Stack<T> {
 private:
  int maxSize;
  int top;
  T* list;

 public:
  // ctor and dtor
  AStack(int size = 10) {
    maxSize = size;
    top = 0;
    list = new T[size];
  }
  ~AStack() { delete[] list; }

  // standard operations
  void push(const T& element) {
    if (top == maxSize)
      cout << "Error: Overflow\n";
    else
      list[top++] = element;
  }

  T pop() {
    T temp;
    if (top == 0)
      cout << "Error: Underflow\n";
    else
      temp = list[--top];
    return temp;
  }

  // print stack in reverse
  void midterm() {
    T temp;
    if (top > 0) {
      temp = pop();
      midterm();
    }
    cout << temp;
  }
};

int InToInt(string);

int main() {
  cout << "\033[2J\033[1;1H";
  int count = -1;
  string in;

  // get stuff from user
  while (count < 0) {
    cout << "How many elements are being entered?\n";
    getline(cin, in);
    count = InToInt(in);
  }

  if (count == 0) {
    cout << "Zero size provided. Exiting.";
    return 0;
  }

  // instantiate and initialize
  AStack midterm = AStack<string>(count);

  // get elements from user
  cout << "Enter elements one at-a-time, pressing enter after each element.\n";
  for (int i = 0; i < count; i++) {
    getline(cin, in);
    midterm.push(in);
  }

  // complete
  midterm.midterm();
  return 0;
}

int InToInt(string in) {
  int num;

  try {
    num = stoi(in);
  } catch (const invalid_argument& ia) {
    cout << "Please enter an integer only.\n";
    num = -1;
  } catch (const out_of_range& oor) {
    cout << "Too many elements. Please try a smaller count.\n";
    num = -1;
  } catch (...) {
    cout << "Unhandled exception. Please try again.\n";
    num = -1;
  }

  return num;
}