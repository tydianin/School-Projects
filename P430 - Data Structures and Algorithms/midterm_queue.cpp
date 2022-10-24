/*
Midterm Question 3
Weston Gibson, CISP 430
23 October 2022

Uses C++17 in accordance with GCC 12.2
*/

// C++ library headers
#include <iostream>  // cin, cout
#include <string>    // string

// namespace
using namespace std;

// compile-time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// doubly linked node
template <typename T>
struct Node {
  T _element;
  Node* _previous;
  Node* _next;

  // new
  static Node* create(T element) {
    Node* temp = new Node;
    temp->_element = element;
    temp->_previous = temp->_next = NULL;
    return temp;
  }
};

// list adt
template <typename T>
class List {
 private:
  // protect assignment and copy constructors
  void operator=(const List&) {}
  List(const List&) {}

 public:
  // base ctor dtor
  List() {}
  virtual ~List() {}

  // base methods
  virtual void pushBack(const T&) = 0;
  virtual T popFront() = 0;
};

// queue class
template <typename T>
class Queue : public List<T> {
 private:
  Node<T>* _head;
  Node<T>* _tail;

  // creates empty deque
  void init() { _head = _tail = NULL; }

  // deletes elements until deque is empty
  void dump() {
    _tail = NULL;
    while (_head != NULL) {
      Node<T>* temp = _head;
      _head = _head->_next;
      delete temp;
    }
  }

 public:
  // class ctor dtor
  Queue() { init(); }
  ~Queue() { dump(); }

  void pushBack(const T& element) {
    // create new tail
    Node<T>* temp = Node<T>::create(element);

    // update old tail
    if (_tail == NULL)
      _tail = _head = temp;
    else {
      temp->_previous = _tail;
      _tail->_next = temp;
      _tail = temp;
    }
  }

  T popFront() {
    T element = _head->_element;

    // update head
    Node<T>* temp = _head;
    _head = _head->_next;

    // cleanup and return
    return element;
  }

  // print num even odd
  void midterm() {
    int temp = 0, odd = 0, even = 0;

    while (_head != NULL) {
      temp = popFront();
      temp % 2 == 0 ? even++ : odd++;
    }

    // workaround cause I'm tired
    odd--;

    cout << "Even: " << even << "\n"
         << "Odd: " << odd << "\n";
  }
};

int InToInt(string, bool&);

int main() {
  cout << CLEAR_SCREEN;
  string in = "x";
  int num;
  bool success;

  // instantiate queue
  Queue midterm = Queue<int>();

  cout << "Enter numbers. When done, press enter without data.\n";
  // get stuff from user
  while (in != "") {
    getline(cin, in);

    if (!in.empty())
      num = InToInt(in, success);

    if (success)
      midterm.pushBack(num);
  }

  // complete
  midterm.midterm();
  return 0;
}

int InToInt(string in, bool& success) {
  int num;

  try {
    num = stoi(in);
    success = true;
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