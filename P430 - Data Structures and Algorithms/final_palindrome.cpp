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
        int temp = number;
        while (temp != 0) {
          reverse = 10 * reverse + temp % 10;
          temp /= 10;
        }
        number == reverse ? success = true : success = false;
        cout << "\n" << number << " is ";
      }

      // uses pinsir to check if list is palindromic
      else {
        // stops running when fences are on same element
        while (head2 != tail2 && success) {
          // break when two sides aren't the same
          if (head2->element != tail2->element) {
            success == false;
          }
          // otherwise continue
          else {
            head2 = head2->next;
            tail2 = tail2->previous;
          }
        }
        cout << "\nProvided list is ";
      }

      success ? cout << "a palindrome!\n\n" : cout << "not a palindrome.\n\n";
    }
  }
};

int InToInt(string, bool&);

int main() {
  // get situated
  string input = " ";
  int number, counter = 1;
  bool success = false;
  LList final = LList<int>();

  // prompt the user
  cout << "\033[2J\033[1;1H"
       << "Please enter a list of integers.\n"
       << "Press enter after each integer.\n"
       << "When finished, press enter without entering data.\n\n";

  // get the stuff
  while (input != "") {
    success = false;
    cout << "Number " << counter << ": ";
    getline(cin, input);

    if (!input.empty()) {
      number = InToInt(input, success);
    }

    if (success) {
      final.push(number);
      counter++;
    }
  }

  // complete
  final.final();
  return 0;
}

int InToInt(string input, bool& success) {
  int number = -1;

  // tries to stoi, catches errors or negatives
  try {
    number = stoi(input);
    if (number >= 0) {
      success = true;
    } else {
      cout << "Please enter positive integers only.\n";
    }
  } catch (const invalid_argument& ia) {
    cout << "Please enter an integer only.\n";
  } catch (const out_of_range& oor) {
    cout << "Too many digits. Please try a smaller integer.\n";
  } catch (...) {
    cout << "Unhandled exception. Please try again.\n";
  }

  return number;
}