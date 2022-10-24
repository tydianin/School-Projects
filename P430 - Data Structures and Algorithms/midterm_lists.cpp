/*
Midterm Question 1
Weston Gibson, CISP 430
23 October 2022

Uses C++17 in accordance with GCC 12.2
*/

// headers
#include <iostream>  // cin, cout

// namespace
using namespace std;

// trimmed from figure 4.1
template <typename T>
class List {
 private:
  // protect assignment and copy
  void operator=(const List&) {}
  List(const List&) {}

 public:
  // ctor dtor
  List() {}
  virtual ~List() {}

  // standard operations
  virtual void append(const T&) = 0;
  virtual void start() = 0;
  virtual void next() = 0;
};

// trimmed from figure 4.11
template <typename T>
class Node {
 private:
  static Node* freelist;

 public:
  T value;
  Node* next;

  // ctors
  Node(const T& element, Node* nextPtr = NULL) {
    value = element;
    next = nextPtr;
  }
  Node(Node* nextPtr = NULL) { next = nextPtr; }

  // overloaded new
  void* operator new(size_t) {
    if (freelist == NULL)
      return ::new Node;
    Node<T>* temp = freelist;
    freelist = freelist->next;
    return temp;
  }

  // delete
  void operator delete(void* ptr) {
    ((Node<T>*)ptr)->next = freelist;
    freelist = (Node<T>*)ptr;
  }
};

// initialize freelist
template <typename T>
Node<T>* Node<T>::freelist = NULL;

// trimmed from figure 4.8
template <typename T>
class LList : public List<T> {
 private:
  Node<T>* head;
  Node<T>* fence;
  Node<T>* tail;
  int left;
  int right;

  void init() {
    fence = tail = head = new Node<T>;
    left = right = 0;
  }

  // used during cleanup
  void removeall() {
    while (head != NULL) {
      fence = head;
      head = head->next;
      delete fence;
    }
  }

 public:
  // ctor dtor
  LList(int size = 10) { init(); }
  ~LList() { removeall(); }

  // append
  void append(const int& element) {
    tail = tail->next = new Node<T>(element, NULL);
    right++;
  }

  // traverse list
  void start() {
    fence = head;
    right += left;
    left = 0;
  }

  void next() {
    if (fence != tail) {
      fence = fence->next;
      right--;
      left++;
    }
  }

  // print list total
  void getTotal() {
    int sum = 0;

    start();
    while (fence != tail) {
      sum += fence->next->value;
      next();
    }

    cout << "List Total: " << sum;
  }
};

int main() {
  cout << "\033[2J\033[1;1H";

  // instantiate and initialize
  LList midterm = LList<int>(5);
  for (int i : {2, 23, 15, 5, 9}) {
    cout << "Appending: " << i << "\n";
    midterm.append(i);
  }

  // complete
  midterm.getTotal();
  return 0;
}