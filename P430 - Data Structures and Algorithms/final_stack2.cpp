/*
Final Exam Part 2 Prompt 2
Weston Gibson, CISP 430
11 December 2022

Implements a FIFO linked-list stack to reverse a provided string.
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
  Node<T>* head;
  Node<T>* tail;

  // helper
  void remove() {
    Node<T>* temp = head;
    head = head->next;
    delete temp;
  }

 public:
  // ctor dtor
  LStack() { head = tail = NULL; }
  ~LStack() {
    while (head != NULL) {
      remove();
    }
  }

  // modifiers
  void push(const T& element) {
    Node<T>* temp = new Node<T>(element, NULL);
    if (head == NULL) {
      head = tail = temp;
    } else {
      tail->next = temp;
      tail = temp;
    }
  }

  T pop() {
    if (head == NULL) {
      cout << "\n\nStack is empty.\n\n";
      return '\n';
    } else {
      T element = head->element;
      remove();
      return element;
    }
  }

  // final
  void final() {
    cout << "\nUnreversed string: ";
    while (head != NULL) {
      cout << pop();
    }
    cout << '\n' << endl;
  }
};

int main() {
  // get string from user;
  cout << "\033[2J\033[1;1H"
       << "Enter string to reprint: ";
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