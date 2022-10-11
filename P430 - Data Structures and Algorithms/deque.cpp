/*
Assignment 5
Weston Gibson, CISP 430
09 October 2022

Uses C++17 in accordance with GCC 12.2

deque in the form of doubly linked list
*/

// C++ library headers
#include <iostream>  // cin, cout
#include <string>    // string

// namespace
using namespace std;

// compile-time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// douly linked node
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
  virtual void clear() = 0;
  virtual void pushFront(const T&) = 0;
  virtual void pushBack(const T&) = 0;
  virtual T popFront() = 0;
  virtual T popBack() = 0;
};

// deque class
template <typename T>
class Deque : public List<T> {
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
    }
  }

 public:
  // class ctor dtor
  Deque() { init(); }
  ~Deque() { dump(); }

  // adt methods
  void clear() {
    dump();
    init();
  }

  void pushFront(const T& element) {
    // create new head
    Node<T>* temp = Node<T>::create(element);
    
    // update old head
    if (_head == NULL)
      _head = _tail = temp;
    else {
      temp->_next = _head;
      _head->_previous = temp;
      _head = temp;
    }
  }

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
    // head empty
    if (_head == NULL)
      throw -1;

    // deque not empty
    T element = _head->_element;

    // update head
    Node<T>* temp = _head;
    _head = _head->_next;

    // cleanup and return
    _head->_previous = NULL;
    return element;
  }

  T popBack() {
    // tail empty
    if (_tail == NULL)
      throw -1;

    // tail not empty
    T element = _tail->_element;

    // update tail
    Node<T>* temp = _tail;
    _tail = _tail->_previous;

    // cleanup and return
    _tail->_next = NULL;
    return element;
  }

  // print deque contents
  void print() {
    Node<T>* temp = _head;

    cout << "Deque contents: < ";

    while (temp != NULL) {
      cout << temp->_element;
      if (temp->_next != NULL)
        cout << ", ";
      temp = temp->_next;
    }

    cout << " >\n\n";
  }
};

int main() {
  cout << CLEAR_SCREEN;

  // instantiate deque
  Deque D = Deque<int>();

  cout << "Start with element '21'.\n";
  D.pushBack(21);
  D.print();

  cout << "Insert element '18' at front.\n";
  D.pushFront(18);
  D.print();

  cout << "Insert element '25' at back.\n";
  D.pushBack(25);
  D.print();

  cout << "Remove element '18' from front.\n";
  try {
    int temp = D.popFront();
  } catch (int x) {
    if (x == -1)
      cout << "Nothing to remove.\n";
  }
  D.print();

  cout << "Remove element '25' from back.\n";
  try {
    int temp = D.popBack();
  } catch (int x) {
    if (x == -1)
      cout << "Nothing to remove.\n";
  }
  D.print();

  // cleanup
  D.clear();
  return 0;
}