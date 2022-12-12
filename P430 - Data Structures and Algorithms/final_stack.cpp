/*
Final Exam Part 2 Prompt 1
Weston Gibson, CISP 430
11 December 2022

Implements a standard linked-list stack to reverse a provided string.
*/

#include <iostream>  // cin, cout, getline
#include <string>    // string

using namespace std;

// Node w/ freelist template
template <typename T>
class Node {
 private:
  static Node<T>* freelist;

 public:
  T element;
  Node* next;

  // ctors
  Node(const T& elemVal, Node* nextVal = NULL) {
    element = elemVal;
    next = nextVal;
  }
  Node(Node* nextVal = NULL) { next = nextVal; }

  // override new operator
  void* operator new(size_t) {
    if (freelist == NULL) {
      return ::new Node;
    }
    Node<T>* temp = freelist;
    freelist = freelist->next;
    return temp;
  }

  // override delete operator
  void operator delete(void* ptr) {
    ((Node<T>*)ptr)->next = freelist;
    freelist = (Node<T>*)ptr;
  }
};

// initialize freelist
template <typename T>
Node<T>* Node<T>::freelist = NULL;

// Stack abstract template
template <typename T>
class Stack {
 private:
  void operator=(const Stack&) {}
  Stack(const Stack&) {}

 public:
  Stack() {}
  virtual ~Stack() {}
  virtual void push(const T&) = 0;
  virtual T pop() = 0;
};

// Linked stack template
template <typename T>
class LStack : public Stack<T> {
 private:
  Node<T>* top;

  // helper
  void remove() {
    Node<T>* temp = top;
    top = top->next;
    delete temp;
  }

 public:
  // ctor dtor
  LStack() { top = NULL; }
  ~LStack() {
    while (top != NULL) {
      remove();
    }
  }

  // modifiers
  void push(const T& element) { top = new Node<T>(element, top); }

  T pop() {
    if (top == NULL) {
      cout << "\n\nStack is empty.\n\n";
      return '\n';
    } else {
      T element = top->element;
      remove();
      return element;
    }
  }

  // final
  void final() {
    cout << "\nReversed string: ";
    while (top != NULL) {
      cout << pop();
    }
    cout << '\n' << endl;
  }
};

int main() {
  // get string from user;
  cout << "\033[2J\033[1;1H"
       << "Enter string to reverse: ";
  string in;
  getline(cin, in);

  // create stack
  LStack userString = LStack<char>();
  for (int i = 0; i < in.length(); i++) {
    userString.push(in[i]);
  }

  // complete final
  userString.final();
  return 0;
}