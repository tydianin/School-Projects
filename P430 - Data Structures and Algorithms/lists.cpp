/*
Assignment 3
Weston Gibson, CISP 430
25 September 2022

Uses C++17 in accordance with GCC 12.2

Went with Linked List implementation as we have a good amount of
experience with arrays and LL is more common in the working world
due to dynamic memory allocation and O(1) insertion.
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

// List ADT from figure 4.1
template <typename Elem>
class List {
 private:
  // Protect assignment
  void operator=(const List&) {}

  // Protect copy constructor
  List(const List&) {}

 public:
  // Default constructor
  List() {}

  // Base destructor
  virtual ~List() {}

  // Reinitialize the list. The client is responsible for
  // reclaiming the storage used by the list elements.
  virtual void clear() = 0;

  // Insert an element at the front of the right partition.
  // Return true if the insert was successful, false otherwise.
  virtual bool insert(const Elem&) = 0;

  // Append an element at the end of the right partition.
  // Return true if the append was successful, false otherwise.
  virtual bool append(const Elem&) = 0;

  // Remove and return the first element of right partition.
  virtual Elem remove() = 0;

  // Place fence at list start, making left partition empty.
  virtual void movetoStart() = 0;

  // Place fence at list end, making right partition empty.
  virtual void movetoEnd() = 0;

  // Move fence one step left; no change if at beginning.
  virtual void prev() = 0;

  // Move fence one step right; no change if already at end.
  virtual void next() = 0;

  // Return length of left or right partition, respectively.
  virtual int leftLength() const = 0;
  virtual int rightLength() const = 0;

  // Set fence so that left partition has "pos" elements.
  virtual void movetoPos(int pos) = 0;

  // Return the first element of the right partition.
  virtual const Elem& getValue() const = 0;
};

// Linked List Node with freelist template from figure 4.11
template <typename Elem>
class Link {
 private:
  // Reference to freelist head
  static Link<Elem>* freelist;

 public:
  // Value for this node
  Elem element;

  // Point to next node in list
  Link* next;

  // Constructors
  Link(const Elem& elemval, Link* nextval = NULL) {
    element = elemval;
    next = nextval;
  }

  Link(Link* nextval = NULL) { next = nextval; }

  // Overloaded new operator
  // improve by implementing ptr = ::new Link[100]
  // see page 117
  void* operator new(size_t) {
    if (freelist == NULL) {
      return ::new Link;
    }
    Link<Elem>* temp = freelist;
    freelist = freelist->next;
    return temp;
  }

  // Overloaded delete operator
  void operator delete(void* ptr) {
    ((Link<Elem>*)ptr)->next = freelist;
    freelist = (Link<Elem>*)ptr;
  }
};

// Create freelist head pointer
template <typename Elem>
Link<Elem>* Link<Elem>::freelist = NULL;

// Linked List template from figure 4.8
template <typename Elem>
class LList : public List<Elem> {
 private:
  // Pointer to list header
  Link<Elem>* head;

  // Pointer to last Elem in list
  Link<Elem>* tail;

  // Last element on left side
  Link<Elem>* fence;

  // Size of left partition
  int leftcnt;

  // Size of right partition
  int rightcnt;

  // Intialization helper method
  void init() {
    fence = tail = head = new Link<Elem>;
    leftcnt = rightcnt = 0;
  }

  // Return link nodes to free store
  void removeall() {
    while (head != NULL) {
      fence = head;
      head = head->next;
      delete fence;
    }
  }

 public:
  // Constructor
  LList(int size = DefaultListSize) { init(); }

  // Destructor
  ~LList() { removeall(); }

  // Print list contents
  void print(int position = 0) {
    movetoStart();
    cout << "<";
    
    while (rightLength() > position) {
      cout << getValue();
      next();
      if (rightLength() > position)
        cout << ", ";
    }

    cout << " | ";

    while (rightLength() > 0) {
      cout << getValue();
      next();
      if (rightLength() > 0)
        cout << ", ";
    }
    cout << ">\n";
  };

  // Clear list
  void clear() {
    removeall();
    init();
  }

  // Insert "it" at front of right partition
  bool insert(const Elem& it) {
    fence->next = new Link<Elem>(it, fence->next);
    if (tail == fence)
      tail = fence->next;
    rightcnt++;
    return true;
  }

  // Append "it" to list
  bool append(const Elem& it) {
    tail = tail->next = new Link<Elem>(it, NULL);
    rightcnt++;
    return true;
  }

  // Place fence at list start
  void movetoStart() {
    fence = head;
    rightcnt += leftcnt;
    leftcnt = 0;
  }

  // Place fence at list end
  void movetoEnd() {
    fence = tail;
    leftcnt += rightcnt;
    rightcnt = 0;
  }

  // Remove and return first Elem in right partition
  Elem remove() {
    Assert(rightLength() > 0, "Nothing to remove");
    Elem it = fence->next->element;
    Link<Elem>* ltemp = fence->next;
    fence->next = ltemp->next;
    if (tail == ltemp)
      tail = fence;
    delete ltemp;
    rightcnt--;
    return it;
  }

  // Move fence one step left; no change if left is empty
  void prev() {
    if (fence == head)
      return;
    Link<Elem>* temp = head;
    while (temp->next != fence)
      temp = temp->next;
    fence = temp;
    leftcnt--;
    rightcnt++;
  }

  // Move fence one step right; no change if right is empty
  void next() {
    if (fence != tail) {
      fence = fence->next;
      rightcnt--;
      leftcnt++;
    }
  }

  // Return length of left or right partition, respectively.
  int leftLength() const { return leftcnt; }
  int rightLength() const { return rightcnt; }

  // Set the size of left partition to "pos"
  void movetoPos(int pos) {
    Assert((pos >= 0) && (pos <= rightcnt + leftcnt), "Position out of range");
    rightcnt = rightcnt + leftcnt - pos;
    leftcnt = pos;
    fence = head;
    for (int i = 0; i < pos; i++)
      fence = fence->next;
  }

  // Return current Elem
  const Elem& getValue() const {
    Assert(rightLength() > 0, "Nothing to get");
    return fence->next->element;
  }
};

int main() {
  // instantiate list
  LList L = LList<int>(5);

  // initialize values
  for (int i : {2, 23, 15, 5, 9}) {
    L.append(i);
  }

  // confirm initialization
  cout << "List prior to operation: ";
  L.print(5);

  // delete first element with value 15
  int remNum = 15;
  int position = 0;
  bool success = false;

  for (L.movetoStart(); L.rightLength() > 0; L.next()) {
    if (L.getValue() == remNum) {
      L.remove();
      success = true;
      cout << "\nElement removed successfully.\n";
      break;
    }
    position++;
  }

  if (success != true)
    cout << "\nElement not found.\n";

  cout << "\nList after operation: ";
  L.print(position);

  // replace the element
  L.movetoPos(2);
  L.insert(15);

  // confirm replacement
  cout << "\nList prior to operation: ";
  L.print(5);

  // interchange first two elements
  L.movetoStart();
  int temp = L.remove();
  L.next();
  L.insert(temp);
  position = L.rightLength();

  // confirm placement
  cout << "\nList after operation: ";
  L.print(position);

  L.clear();
  return 0;
}