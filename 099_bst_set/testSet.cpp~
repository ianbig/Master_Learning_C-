#include <assert.h>

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "bstmap.h"

template<typename T, typename V>
class TestMap {
  BstMap<T, V> map;
  std::string tree;

  void inorder(typename BstMap<T, V>::Node * node) {
    if (node == NULL) {
      return;
    }

    inorder(node->left);
    std::stringstream ss, sk;
    ss << node->val;
    sk << node->key;
    tree += sk.str() + ":" + ss.str() + "/";
    inorder(node->right);
  }

 public:
  void testAdd(T key, V val) { map.add(key, val); }
  void testLookUp(T key, V ans) {
    V get = map.lookup(key);
    assert(get == ans);
    std::cout << "Found: key " << key << ", val: " << ans << std::endl;
  }

  void testRemove(const T & key, std::string ans) {
    map.remove(key);
    validateTree(ans);
  }

  void testCopycons(std::string ans) {
    BstMap<T, V> copy = map;
    validateTree(ans);
  }

  void testAssign(std::string ans) {
    BstMap<T, V> assign;
    assign = map;
    validateTree(ans);
  }

  void validateTree(std::string ans) {
    if (tree.length() > 0) {
      tree.erase(0, tree.length());
    }

    inorder(map.root);
    std::cout << tree << std::endl;
    assert(ans.compare(tree) == 0);
  }
};

int main() {
  TestMap<int, int> tester;
  // test add
  tester.testAdd(90, 23);
  tester.validateTree("90:23/");
  tester.testAdd(90, 100);
  tester.validateTree("90:100/");  // test update value with same key
  // add left
  tester.testAdd(100, 200);
  tester.validateTree("90:100/100:200/");
  // add right
  tester.testAdd(-1, 200);
  tester.validateTree("-1:200/90:100/100:200/");
  // build tree
  tester.testAdd(-20, 10);
  tester.testAdd(80, 0);
  tester.testAdd(40, 5);
  tester.testAdd(99, 20);
  tester.testAdd(201, 20);
  tester.testAdd(300, 2);
  tester.validateTree("-20:10/-1:200/40:5/80:0/90:100/99:20/100:200/201:20/300:2/");

  // testLookup
  tester.testLookUp(90, 100);
  tester.testLookUp(-1, 200);
  tester.testLookUp(-20, 10);
  tester.testLookUp(80, 0);
  tester.testLookUp(100, 200);
  tester.testLookUp(99, 20);
  tester.testLookUp(201, 20);
  tester.testLookUp(300, 2);
  tester.testLookUp(40, 5);
  // tester.testLookUp(1000, 2);  // test key not exist
  // test remove (left is null, right is null, left, right is not null, key not exist)
  tester.testRemove(300, "-20:10/-1:200/40:5/80:0/90:100/99:20/100:200/201:20/");
  tester.testRemove(40, "-20:10/-1:200/80:0/90:100/99:20/100:200/201:20/");
  tester.testRemove(90, "-20:10/-1:200/80:0/99:20/100:200/201:20/");
  tester.testRemove(-1, "-20:10/80:0/99:20/100:200/201:20/");

  // test Copy Constructor
  // tester.testCopycons("-20:10/-1:200/80:0/99:20/100:200/201:20/");
  // test assignment
  // tester.testAssign("-20:10/-1:200/80:0/99:20/100:200/201:20/");
}
