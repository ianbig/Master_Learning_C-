#ifndef _BSTMAP_H
#define _BSTMAP_H

#include <iostream>

#include "map.h"
template<typename K, typename V>
class TestMap;

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    Node * left;
    Node * right;
    V val;
    K key;

    Node(Node * left_t, Node * right_t, V val_t, K key_t) :
        left(left_t),
        right(right_t),
        val(val_t),
        key(key_t) {}
  };

  Node * root;

  void destroyTree(Node * node) {
    if (node == NULL) {
      return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
    node = NULL;
  }

  Node * findNode(const K & key) const {
    Node * cur = root;
    while (cur != NULL) {
      if (cur->key == key) {
        return cur;
      }

      else if (cur->key < key) {
        cur = cur->right;
      }

      else {
        cur = cur->left;
      }
    }

    return NULL;
  }

  Node * do_removal(Node * cur) {
    if (cur->left == NULL) {
      Node * ret = cur->right;
      delete cur;
      cur = NULL;
      return ret;
    }

    else if (cur->right == NULL) {
      Node * ret = cur->left;
      delete cur;
      cur = NULL;
      return ret;
    }

    Node *toSwap = cur->right, *tmpRoot = cur->right;
    while (toSwap->left != NULL) {
      toSwap = toSwap->left;
    }

    cur->key = toSwap->key;
    cur->val = toSwap->val;
    cur->right = remove_helper(tmpRoot, toSwap->key);

    return cur;
  }

  Node * remove_helper(Node * cur, const K & key) {
    if (cur == NULL) {
      throw std::invalid_argument("remove fail since no key exist");
    }

    if (cur->key < key) {
      cur->right = remove_helper(cur->right, key);
    }

    else if (cur->key > key) {
      cur->left = remove_helper(cur->left, key);
    }

    else {
      cur = do_removal(cur);
    }

    return cur;
  }

  Node * copy(Node * curNode, Node * copyNode) {
    if (copyNode == NULL) {
      return NULL;
    }

    curNode = new Node(NULL, NULL, copyNode->val, copyNode->key);
    curNode->left = copy(curNode->left, copyNode->left);
    curNode->right = copy(curNode->right, copyNode->right);

    return curNode;
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) {
    Node * tmpNode = NULL;
    tmpNode = copy(tmpNode, rhs.root);
    root = tmpNode;  // ensure strong guarantee
  }
  virtual ~BstMap() { destroyTree(root); }

  virtual void add(const K & key, const V & val) {
    Node ** cur = &root;
    while (*cur != NULL) {
      Node * tmp = *cur;
      if (tmp->key < key) {
        cur = &(tmp->right);
      }

      else if (tmp->key > key) {
        cur = &(tmp->left);
      }

      else {
        tmp->val = val;
        return;  // just modify the value
      }
    }

    *cur = new Node(NULL, NULL, val, key);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * found = findNode(key);
    if (found == NULL) {
      std::cerr << "key " << key << " is not found" << std::endl;
      throw std::invalid_argument("Cannot find corresponding key");
    }

    return found->val;
  }

  virtual void remove(const K & key) { root = remove_helper(root, key); }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      Node * tmpRoot = NULL;
      tmpRoot = copy(tmpRoot, rhs.root);
      destroyTree(root);
      root = tmpRoot;
    }

    return *this;
  }

  friend class TestMap<K, V>;
};

#endif
