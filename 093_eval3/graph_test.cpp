#include "graph.hpp"

int main() {
  Graph ref(10);
  ref.printGraph();
  std::cout << "=====graph after init====" << std::endl;
  // test add edge
  ref.addEdge(2, 1);
  ref.addEdge(3, 1);
  ref.addEdge(5, 1);
  ref.addEdge(4, 2);
  ref.addEdge(6, 2);
  ref.addEdge(7, 2);
  ref.addEdge(1, 3);
  ref.addEdge(2, 3);
  ref.addEdge(5, 3);
  ref.addEdge(6, 5);
  ref.addEdge(7, 5);
  ref.addEdge(10, 5);
  ref.printGraph();
  ref.test("matrix", -1, -1);
  /*
  for (size_t i = 1; i < ref.getSz(); i++) {
    for (size_t j = 1; j < ref.getSz(); j++) {
      ref.test("adj", j, i);
    }
  }
  std::cout << "testing isAdjacent() without error" << std::endl;
  */

  // test copy constructor
  Graph copy = ref;
  copy.printGraph();
  ref.test("matrix", -1, -1);
  for (size_t i = 1; i < ref.getSz(); i++) {
    for (size_t j = 1; j < ref.getSz(); j++) {
      ref.test("adj", i, j);
    }
  }

  copy.addEdge(3, 10);
  copy.addEdge(5, 9);
  copy.addEdge(4, 7);
  copy.addEdge(1, 9);
  // copy.addEdge(0, 10);  // throw exception
  // copy.addEdge(11, 10);  // throw exception
  // copy.addEdge(1, 11);  // throw exception
  // copy.addEdge(1, 0);  // throw exception

  // test assignment operator
  Graph assign;
  assign = copy;
  assign.printGraph();
}
