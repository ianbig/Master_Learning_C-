#include <cassert>

#include "node.h"

Node * buildTree(uint64_t * counts) {
  // create a priority
  priority_queue_t pq;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  // start to build tree
  while (pq.size() > 1) {
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();
    Node * newNode = new Node(left, right);
    pq.push(newNode);
  }

  assert(pq.size() == 1);

  return pq.top();
}
