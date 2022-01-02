#include <assert.h>

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "bstset.h"

template<typename T>
class TestSet {
  BstSet<T> set;
  std::string tree;

  void inorder(typename BstSet<T>::Node * node) {
    if (node == NULL) {
      return;
    }

    inorder(node->left);
    std::stringstream sk;
    sk << node->key;
    tree += sk.str() + "/";
    inorder(node->right);
  }

 public:
  void testAdd(T key) { set.add(key); }
  void testContains(T key, bool ans) {
    bool get = set.contains(key);
    assert(get == ans);
    std::cout << "get result: " << get << std::endl;
  }

  void testRemove(const T & key, std::string ans) {
    set.remove(key);
    validateTree(ans);
  }

  void testCopycons(std::string ans) {
    BstSet<T> copy = set;
    validateTree(ans);
  }

  void testAssign(std::string ans) {
    BstSet<T> assign;
    assign = set;
    validateTree(ans);
  }

  void validateTree(std::string ans) {
    if (tree.length() > 0) {
      tree.erase(0, tree.length());
    }

    inorder(set.root);
    std::cout << tree << std::endl;
    assert(ans.compare(tree) == 0);
  }
};

int main() {
  TestSet<int> tester;
  // test add
  tester.testAdd(90);
  tester.validateTree("90/");
  tester.testAdd(90);
  tester.validateTree("90/");  // test update value with same key
  // add left
  tester.testAdd(100);
  tester.validateTree("90/100/");
  // add right
  tester.testAdd(-1);
  tester.validateTree("-1/90/100/");
  // build tree
  tester.testAdd(-20);
  tester.testAdd(80);
  tester.testAdd(40);
  tester.testAdd(99);
  tester.testAdd(201);
  tester.testAdd(300);
  tester.validateTree("-20/-1/40/80/90/99/100/201/300/");

  // testLookup
  tester.testContains(90, true);
  tester.testContains(-1, true);
  tester.testContains(-20, true);
  tester.testContains(80, true);
  tester.testContains(100, true);
  tester.testContains(99, true);
  tester.testContains(201, true);
  tester.testContains(300, true);
  tester.testContains(40, true);
  tester.testContains(1000, false);    // test key not exist
  tester.testContains(100000, false);  // test key not exist
  tester.testContains(2000, false);    // test key not exist
  tester.testContains(109, false);     // test key not exist
  // test remove (left is null, right is null, left, right is not null, key not exist)
  tester.testRemove(300, "-20/-1/40/80/90/99/100/201/");
  tester.testRemove(40, "-20/-1/80/90/99/100/201/");
  tester.testRemove(90, "-20/-1/80/99/100/201/");
  tester.testRemove(-1, "-20/80/99/100/201/");

  // test Copy Constructor
  tester.testCopycons("-20/80/99/100/201/");
  // test assignment
  tester.testAssign("-20/80/99/100/201/");
  std::cout << "testing without error" << std::endl;
}
