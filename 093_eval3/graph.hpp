#ifndef _GRAPH_H
#define _GRAPH_H

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

class Graph {
  std::vector<std::vector<unsigned> > matrix;
  std::map<unsigned, std::set<unsigned> > testList;  // this is for testing graph
  int graphsz;
  void testGraph();

 public:
  // ====== Rule of Three =====
  Graph();
  Graph(int numMatrix);
  Graph(const Graph & rhs);
  Graph & operator=(const Graph & rhs);
  ~Graph();
  // ================
  // print the adjacent matrix out
  void printGraph();
  // return whether page is reference by refBy, if it is return true, else return false
  bool isAdjacent(int page, int refBy);
  // add edege between to nodes, if page or refBy out of range throw exception
  void addEdge(int page, int refBy);
  // for testing
  void test(std::string func, int page, int refBy);
  std::vector<std::vector<unsigned> > getMatrix() { return matrix; }
  size_t getSz() { return graphsz; }
  size_t getSz() const { return graphsz; }
};

// e.g. for 3 * 3 adjacent matrix, create extra column to make the index easier
//   ref by
//        0 1 2 3
// page  0
//       1
//       2
//       3

#endif
