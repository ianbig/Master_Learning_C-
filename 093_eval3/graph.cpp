#include "graph.hpp"

Graph::Graph() : graphsz(0) {
}

Graph::Graph(int numMatrix) : graphsz(numMatrix) {
  for (int i = 0; i <= numMatrix; i++) {
    matrix.push_back(std::vector<unsigned>(numMatrix + 1, 0));
  }
}

Graph::Graph(const Graph & rhs) :
    matrix(rhs.matrix),
    testList(rhs.testList),
    graphsz(rhs.graphsz) {
}

Graph::~Graph() {
}

void Graph::addEdge(int page, int refBy) {
  if (page > graphsz || refBy > graphsz || page < 1 || refBy < 1) {
    throw std::out_of_range("index out of range in addEdge");
  }
  matrix[page][refBy] = 1;
  // TODO: comment out the following since it is for test
  testList[refBy].insert(page);
}

bool Graph::isAdjacent(int page, int refBy) {
  assert((page > 0 && page <= graphsz) && (refBy > 0 && refBy <= graphsz));
  return (matrix[page][refBy] == 1);
}

void Graph::printGraph() {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      std::cout << matrix[i][j] << ", ";
    }
    std::cout << std::endl;
  }
}

Graph & Graph::operator=(const Graph & rhs) {
  if (this != &rhs) {
    matrix = rhs.matrix;
    testList = rhs.testList;
    graphsz = rhs.graphsz;
  }

  return *this;
}

void Graph::testGraph() {
  for (size_t page = 1; page < matrix.size(); page++) {
    for (size_t refBy = 1; refBy < matrix.size(); refBy++) {
      if (matrix[page][refBy] == 1) {
        assert(testList[refBy].find(page) != testList[refBy].end());
      }
    }
  }
}

void Graph::test(std::string func, int page, int refBy) {
  if (func.compare("matrix") == 0) {
    testGraph();
    std::cout << "testing graph without error" << std::endl;
  }

  else if (func.compare("adj") == 0) {
    if (matrix[page][refBy] == 1) {
      assert(isAdjacent(page, refBy) == true);
    }

    else {
      assert(isAdjacent(page, refBy) == false);
    }
  }
}
