#include "node.h"

#include <cassert>
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    theMap[sym] = b;
  }

  else {
    assert(left != NULL && right != NULL);
    BitString bl = b.plusZero();
    left->buildMap(bl, theMap);
    BitString br = b.plusOne();
    right->buildMap(br, theMap);
  }
}
