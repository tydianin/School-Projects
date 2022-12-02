/* Midterm Exam 2 Part 2
Weston Gibson, CISP 430
04 December 2022 */

#include <iostream>  // cout

using namespace std;

// Graph abstract class
class Graph {
 private:
  void operator=(const Graph&) {}
  Graph(const Graph&) {}

 public:
  Graph() {}
  virtual ~Graph() {}
  virtual int weight(int v1, int v2) = 0;
  virtual void setEdge(int v1, int v2) = 0;
  virtual void print() = 0;
};

// Matrix implementation
class Matrix : public Graph {
 private:
  int vertices;
  int** matrix;
  int* mark;

 public:
  Matrix(int count) {
    vertices = count;
    mark = new int[count];
    for (int i = 0; i < vertices; i++)
      mark[i] = 0;
    matrix = (int**)new int*[count];
    for (int i = 0; i < vertices; i++)
      matrix[i] = new int[count];
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
  int weight(int v1, int v2) { return matrix[v1][v2]; }
  void setEdge(int v1, int v2) { matrix[v1][v2] = 1; }

  // midterm requirement 1
  void print() {
    cout << "\n\nProvided Adjacency List:\n";
    for (int i = 0; i < vertices; i++) {
      cout << i + 1;
      for (int j = 0; j < vertices; j++)
        if (weight(i, j) > 0)
          cout << "[-]->" << j + 1;
      cout << "[/]\n";
    }
  }

  // midterm requirement 2
  void findNewVertexOfIndegreeZero() {
    int degree = 0;
    cout << "\n\nLocating vertices with indegree zero...\n";
    for (int i = 0; i < vertices; i++) {
      degree = 0;
      for (int j = 0; j < vertices; j++)
        degree += weight(j, i);
      if (degree == 0)
        cout << "Vertex " << i + 1 << " has indegree zero.\n";
    }
  }
};

int main() {
  // initialize matrix to given parameters
  Matrix m(7);
  int temp[12][2] = {0, 1, 0, 2, 0, 3, 1, 3, 1, 4, 2, 5,
                     3, 2, 3, 5, 3, 6, 4, 3, 4, 6, 6, 5};
  for (int i = 0; i < 12; i++)
    m.setEdge(temp[i][0], temp[i][1]);

  // do the midterm
  m.print();
  m.findNewVertexOfIndegreeZero();
  cout << endl;
}