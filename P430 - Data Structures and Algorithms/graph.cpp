/*
Assignment 7
Weston Gibson, CISP 430
05 November 2022

Uses C++17 in accordance with GCC 12.2

Graph as described in the textbook
*/

// C++ library headers
#include <iostream>  // cin, cout

// used STRICTLY as a stack to save space since we've already used it
#include <vector>  // int vector

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

// Graph abstract class
class Graph {
 private:
  // protect assignment and copy
  void operator=(const Graph&) {}
  Graph(const Graph&) {}

 public:
  // ctor dtor
  Graph() {}
  virtual ~Graph() {}

  // accessors
  virtual int v() = 0;
  virtual int e() = 0;
  virtual int weight(int v1, int v2) = 0;  // edge weight
  virtual int getMark(int v) = 0;          // vertex mark
  virtual int first(int v) = 0;            // first neighbor
  virtual int next(int v1, int v2) = 0;    // next neighbor

  // modifiers
  virtual void setEdge(int v1, int v2, int w) = 0;  // store edge
  virtual void setMark(int v, int val) = 0;         // set vertex mark
  virtual void delEdge(int v1, int v2) = 0;         // delete edge
};

// Matrix implementation
class Matrix : public Graph {
 private:
  int vertices, edges;
  int** matrix;
  int* mark;

 public:
  // ctor dtor
  Matrix(int count) {
    vertices = count;
    edges = 0;

    // initialize array
    mark = new int[count];
    for (int i = 0; i < vertices; i++)
      mark[i] = 0;

    // create matrix
    matrix = (int**)new int*[count];
    for (int i = 0; i < vertices; i++)
      matrix[i] = new int[count];

    // initialize matrix to 0
    for (int i = 0; i < count; i++)
      for (int j = 0; j < count; j++)
        matrix[i][j] = 0;
  }

  ~Matrix() {
    delete[] mark;
    for (int i = 0; i < vertices; i++)
      delete[] matrix[i];
    delete[] matrix;
  }

  // accessors
  int v() { return vertices; }
  int e() { return edges; }
  int weight(int v1, int v2) { return matrix[v1][v2]; }
  int getMark(int v) { return mark[v]; }

  int first(int v) {
    for (int i = 0; i < vertices; i++)
      if (matrix[v][i] != 0)
        return i;
    return vertices;
  }

  int next(int v1, int v2) {
    for (int i = v2 + 1; i < vertices; i++)
      if (matrix[v1][i] != 0)
        return i;
    return vertices;
  }

  // modifiers
  void setEdge(int v1, int v2, int w) {
    Assert(w > 0, "Illegal weight value");
    if (matrix[v1][v2] == 0)
      edges++;
    matrix[v1][v2] = w;
  }

  void makeEdge(int v1, int v2) {
    if (matrix[v1][v2] == 0)
      edges++;
    matrix[v1][v2] = 1;
  }

  void setMark(int v, int val) { mark[v] = val; }

  void delEdge(int v1, int v2) {
    if (matrix[v1][v2] != 0)
      edges--;
    matrix[v1][v2] = 0;
  }

  void print() {
    // columns
    cout << "  ";
    for (int i = 0; i < vertices; i++)
      cout << " " << i + 1 << " ";

    // rows
    for (int i = 0; i < vertices; i++) {
      cout << "\n" << i + 1 << " ";
      for (int j = 0; j < vertices; j++)
        cout << "[" << weight(i, j) << "]";
    }
  }
};

void traverse(Matrix&, int, int, vector<int>&);
void DFS(Matrix&, int, int, vector<int>&);

int main() {
  // initialize matrix to given parameters
  Matrix m(6);
  int temp[9][2] = {0, 1, 1, 3, 2, 0, 2, 1, 2, 4, 3, 5, 4, 1, 4, 3, 4, 5};
  for (int i = 0; i < 9; i++)
    m.makeEdge(temp[i][0], temp[i][1]);

  // print the matrix
  cout << CLEAR_SCREEN << "Provided Matrix:\n";
  m.print();
  cout << "\n\n";

  // do the homework
  int s = 2;
  int d = 5;

  // catch no-move
  if (s == d)
    cout << "\n\nSource and Destination are the same. No traversal needed.\n";

  // actual program
  else {
    cout << "Attempting to path " << s + 1 << " to " << d + 1 << "...";
    // int stack and recursive calls to traverse all available paths
    vector<int> stack;
    traverse(m, s, d, stack);
  }

  // cleanup
  return 0;
}

void traverse(Matrix& M, int s, int d, vector<int>& stack) {
  // store vertex and set mark
  stack.push_back(s);
  M.setMark(s, 1);

  // traverse the vertex's graph
  for (int i = M.first(s); i < M.v(); i = M.next(s, i))
    if (M.getMark(i) == 0)
      traverse(M, i, d, stack);

  // reset marks for further searching
  for (int i = 0; i < M.v(); i++)
    M.setMark(i, 0);

  // print successful search
  if (s == d) {
    cout << "\n\nPath found!\n";
    for (int i = 0; i < stack.size() - 1; i++)
      cout << stack[i] + 1 << " -> ";
    cout << stack.back() + 1 << "\n";
  }

  // remove vertex from stack
  stack.pop_back();
}