/*
Assignment 6
Weston Gibson, CISP 430
30 October 2022

Uses C++17 in accordance with GCC 12.2

Clarified Binary Tree as described in the textbook
*/

// C++ library headers
#include <iostream>  // cin, cout
#include <string>    // string

// namespace
using namespace std;

// compile-time constants
constexpr char CLEAR_SCREEN[] = "\033[2J\033[1;1H";
const int DefaultListSize = 10;

// If "val" is false, print a message and terminate the program
void Assert(bool val, string str) {
  if (!val) {
    cout << "Assertion Failed: " << str << endl;
    exit(-1);
  }
}

// Dictionary abstract class
template <typename Key, typename Elem>
class Dictionary {
 private:
  // protect assignment and copy
  void operator=(const Dictionary&) {}
  Dictionary(const Dictionary&) {}

 public:
  // ctor dtor
  Dictionary() {}
  virtual ~Dictionary() {}

  // standard operations
  virtual void clear() = 0;
  virtual void insert(const Key& k, const Elem& e) = 0;
  virtual bool remove(const Key& k, Elem& e) = 0;
  virtual bool find(const Key& k, Elem& e) const = 0;

  // helpers
  virtual int size() = 0;
  virtual Elem removeAny() = 0;
};

// Binary tree node abstract class
template <typename Elem>
class BinNode {
 public:
  // dtor
  virtual ~BinNode() {}

  // getters
  virtual Elem& val() = 0;
  virtual BinNode* left() const = 0;
  virtual BinNode* right() const = 0;

  // setters
  virtual void setVal(const Elem&) = 0;
  virtual void setLeft(BinNode*) = 0;
  virtual void setRight(BinNode*) = 0;

  // helpers
  virtual bool isLeaf() = 0;
};

// Simple binary tree node implementation
template <typename Key, typename Elem>
class BNode : public BinNode<Elem> {
 private:
  Key k;      // The node’s key
  Elem it;    // The node’s value
  BNode* lc;  // Pointer to left child
  BNode* rc;  // Pointer to right child
 public:
  // ctors, dtor
  BNode() { lc = rc = NULL; }
  BNode(Key K, Elem e, BNode* l = NULL, BNode* r = NULL) {
    k = K;
    it = e;
    lc = l;
    rc = r;
  }
  ~BNode() {}

  // getters
  Elem& val() { return it; }
  Key& key() { return k; }
  inline BNode* left() const { return lc; }
  inline BNode* right() const { return rc; }

  // setters
  void setVal(const Elem& e) { it = e; }
  void setKey(const Key& K) { k = K; }
  void setLeft(BinNode<Elem>* b) { lc = (BNode*)b; }
  void setRight(BinNode<Elem>* b) { rc = (BNode*)b; }

  // helpers
  bool isLeaf() { return (lc == NULL) && (rc == NULL); }
};

// Binary Search Tree using Dictionary ADT
template <typename Key, typename Elem>
class BST : public Dictionary<Key, Elem> {
 private:
  BNode<Key, Elem>* root;  // Root of the BST
  int nodecount;           // Number of nodes in the BST

  // helpers
  void clearhelp(BNode<Key, Elem>*);
  BNode<Key, Elem>* inserthelp(BNode<Key, Elem>*, const Key&, const Elem&);
  BNode<Key, Elem>* deletemin(BNode<Key, Elem>*, BNode<Key, Elem>*&);
  BNode<Key, Elem>* removehelp(BNode<Key, Elem>*,
                               const Key&,
                               BNode<Key, Elem>*&);
  bool findhelp(BNode<Key, Elem>*, const Key&, Elem&) const;
  void printhelp(BNode<Key, Elem>*, int) const;
  void InorderPrint(BNode<Key, Elem>*, int) const;
  void PreorderPrint(BNode<Key, Elem>*, int) const;
  void PostorderPrint(BNode<Key, Elem>*, int) const;

 public:
  // ctor dtor
  BST() {
    root = NULL;
    nodecount = 0;
  }
  ~BST() { clearhelp(root); }

  // standard operations
  void clear() {
    clearhelp(root);
    root = NULL;
    nodecount = 0;
  }
  void insert(const Key& k, const Elem& it) {
    root = inserthelp(root, k, it);
    nodecount++;
  }
  bool remove(const Key& K, Elem& it) {
    BNode<Key, Elem>* t = NULL;
    root = removehelp(root, K, t);
    if (t == NULL)
      return false;  // Nothing found
    it = t->val();
    nodecount--;
    delete t;
    return true;
  }
  bool find(const Key& K, Elem& it) const { return findhelp(root, K, it); }
  // Return the number of records in the dictionary.

  // helpers
  int size() { return nodecount; }
  Elem removeAny() {  // Delete min value
    Assert(root != NULL, "Empty tree");
    BNode<Key, Elem>* t;
    root = deletemin(root, t);
    Elem it = t->val();
    delete t;
    nodecount--;
    return it;
  }
  void print() const {  // Print the contents of the BST
    if (root == NULL)
      cout << "The BST is empty.\n";
    else {
      // printhelp(root, 0);

      cout << "\n\nInorder:\n";
      InorderPrint(root, 0);

      cout << "\n\nPreorder:\n";
      PreorderPrint(root, 0);

      cout << "\n\nPostorder:\n";
      PostorderPrint(root, 0);
    }
  }
};

template <typename Key, typename Elem>
void BST<Key, Elem>::clearhelp(BNode<Key, Elem>* root) {
  if (root == NULL)
    return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}

template <typename Key, typename Elem>
BNode<Key, Elem>* BST<Key, Elem>::inserthelp(BNode<Key, Elem>* root,
                                             const Key& k,
                                             const Elem& it) {
  // Empty tree: create node
  if (root == NULL)
    return new BNode<Key, Elem>(k, it, NULL, NULL);
  if (k < root->key())
    root->setLeft(inserthelp(root->left(), k, it));
  else
    root->setRight(inserthelp(root->right(), k, it));
  // Return tree with node inserted
  return root;
}

template <typename Key, typename Elem>
BNode<Key, Elem>* BST<Key, Elem>::deletemin(BNode<Key, Elem>* root,
                                            BNode<Key, Elem>*& S) {
  // Found min
  if (root->left() == NULL) {
    S = root;
    return root->right();
    // Continue left
  } else {
    root->setLeft(deletemin(root->left(), S));
    return root;
  }
}

// Return in "R" the element (if any) with value "K"
// Return the updated subtree with "R" removed from the tree
template <typename Key, typename Elem>
BNode<Key, Elem>* BST<Key, Elem>::removehelp(BNode<Key, Elem>* root,
                                             const Key& K,
                                             BNode<Key, Elem>*& R) {
  // K is not in tree
  if (root == NULL)
    return NULL;
  else if (K < root->key())
    root->setLeft(removehelp(root->left(), K, R));
  else if (K > root->key())
    root->setRight(removehelp(root->right(), K, R));
  // Found: remove it
  else {
    BNode<Key, Elem>* temp;
    R = root;
    // Only a right child so point to right
    if (root->left() == NULL)
      root = root->right();
    // Only a left child so point to left
    else if (root->right() == NULL)
      root = root->left();
    // Both children are non-empty
    else {
      root->setRight(deletemin(root->right(), temp));
      Elem te = root->val();
      root->setVal(temp->val());
      temp->setVal(te);
      R = temp;
    }
  }
  return root;
}

template <typename Key, typename Elem>
bool BST<Key, Elem>::findhelp(BNode<Key, Elem>* root,
                              const Key& K,
                              Elem& e) const {
  // Empty tree
  if (root == NULL)
    return false;
  // Check left
  else if (K < root->key())
    return findhelp(root->left(), K, e);
  // Check right
  else if (K > root->key())
    return findhelp(root->right(), K, e);
  // Found it
  else {
    e = root->val();
    return true;
  }
}

template <typename Key, typename Elem>
void BST<Key, Elem>::printhelp(BNode<Key, Elem>* root, int level) const {
  // Empty tree
  if (root == NULL)
    return;
  // Do left subtree
  printhelp(root->left(), level + 1);
  // Indent to level
  for (int i = 0; i < level; i++)
    cout << " ";
  // Print node value
  cout << root->key() << "\n";
  // Do right subtree
  printhelp(root->right(), level + 1);
}

template <typename Key, typename Elem>
void BST<Key, Elem>::InorderPrint(BNode<Key, Elem>* root, int level) const {
  // Empty tree
  if (root == NULL)
    return;
  // Do left subtree
  InorderPrint(root->left(), ++level);
  // Print node value with indent
  cout << string(level, ' ') << root->key() << "\n";
  // Do right subtree
  InorderPrint(root->right(), ++level);
}

template <typename Key, typename Elem>
void BST<Key, Elem>::PreorderPrint(BNode<Key, Elem>* root, int level) const {
  // Empty tree
  if (root == NULL)
    return;
  // Print node value with indent
  cout << string(level, ' ') << root->key() << "\n";
  // Do left subtree
  PreorderPrint(root->left(), ++level);
  // Do right subtree
  PreorderPrint(root->right(), ++level);
}

template <typename Key, typename Elem>
void BST<Key, Elem>::PostorderPrint(BNode<Key, Elem>* root, int level) const {
  // Empty tree
  if (root == NULL)
    return;
  // Do left subtree
  PostorderPrint(root->left(), ++level);
  // Do right subtree
  PostorderPrint(root->right(), ++level);
  // Print node value with indent
  cout << string(level, ' ') << root->key() << "\n";
}

int main() {
  // instantiate BST
  BST<char, int> tree;

  // initialize BST with a randomized A-Z string
  int i = 0;
  // for (char a : "ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
  for (char a : "ZXFACMUGIRHDQVLTOPYBJSEKWN") {
    tree.insert(a, i++);
  }

  // perform operations
  cout << CLEAR_SCREEN;
  tree.print();

  // cleanup
  tree.clear();
  return 0;
}