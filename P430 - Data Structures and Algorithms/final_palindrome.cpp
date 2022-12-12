/*
Final Exam Part 2 Prompt 3
Weston Gibson, CISP 430
11 December 2022

Checks if a linked list of integers is a palindrome.
*/

#include <iostream>  // cin, cout, getline
#include <string>    // string, stoi
#include <typeinfo>  // typeid()

using namespace std;

// Node w/ freelist template
template <typename T>
class Node {
 private:
  static Node<T>* freelist;

 public:
  T element;
  Node* previous;
  Node* next;

  // ctors
  Node(const T& elemVal, Node* prevVal = NULL, Node* nextVal = NULL) {
    element = elemVal;
    previous = prevVal;
    next = nextVal;
  }
  Node(Node* prevVal = NULL, Node* nextVal = NULL) {
    previous = prevVal;
    next = nextVal;
  }

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

// Linked List abstract template
template <typename T>
class LList : public Node<T> {
 private:
  Node<T>* head;
  Node<T>* tail;

  void remove() {
    Node<T>* temp = head;
    head = head->next;
    delete temp;
  }

 public:
  // ctor dtor
  LList() { head = tail = NULL; }
  ~LList() {
    while (head != NULL) {
      remove();
    }
  }

  // modifier
  void push(const T& element) {
    Node<T>* temp = new Node<T>(element, tail, NULL);
    if (head == NULL) {
      head = tail = temp;
    } else {
      tail->next = temp;
      tail = temp;
    }
  }

  // final
  void final() {
    int reverse = 0;

    // check if list is empty
    if (head == NULL) {
      cout << "\nList is empty.\n\n";
    }

    // list is not of type int
    else if (typeid(T) != typeid(reverse)) {
      cout << "\nList is not of type int.\n\n";
    }

    // list is not empty and is of type int
    else {
      Node<T>* head2 = head;
      Node<T>* tail2 = tail;
      bool success = true;

      // check if single int is palindromic
      if (head == tail) {
        int number = head->element;
        while (number != 0) {
          reverse = 10 * reverse + number % 10;
        }
        number == reverse ? success = true : success = false;
      }

      // check if a list of ints is palindromic
      else {
        while (head2 != tail2 && success) {
          // break when two sides aren't the same
          if (head2->element != tail2->element) {
            success == false;
          }
            // ends loop if odd number of elements
          else if (head2->next != tail2->previous) {
            head2 = head2->next;
            tail2 = tail2->previous;
          }
        }
      }

      success ? cout << "\nPalindrome!\n\n"
              : cout << "\nNot a palindrome...\n\n";
    }
  }
};

int InToInt(string, bool&);

int main() {
  // get situated
  string in;
  int num;
  bool success;

  LList final = LList<int>();
  // LList final = LList<char>();

  // get the stuff
  cout << "\033[2J\033[1;1H"
       << "Enter numbers. When done, press enter without data.\n";  
  do {
    getline(cin, in);
    // for (int i = 0; i < in.length(); i++) {
    //   final.push(in[i]);
    // }

    if (!in.empty()) {
      num = InToInt(in, success);
    }

    if (success) {
      final.push(num);
    }
  } while (in != "");

  // complete
  final.final();
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
    cout << "Too many elements. Please try a smaller number.\n";
    num = -1;
  } catch (...) {
    cout << "Unhandled exception. Please try again.\n";
    num = -1;
  }

  return num;
}