#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class IndexOutOfRange : public std::exception {};
template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * prev;
    Node * next;
    Node() : prev(NULL), next(NULL) {}
    Node(T data_t) : data(data_t), prev(NULL), next(NULL) {}
    Node(T data_t, Node * prev_t, Node * next_t) :
        data(data_t),
        prev(prev_t),
        next(next_t) {}
  };

  Node * head;
  Node * tail;
  int size;

 public:
  friend class Tester;  // TODO: delete this after testing
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {
    for (int i = 0; i < rhs.getSize(); i++) {
      this->addBack(rhs[i]);
    }
  }

  LinkedList<T> & operator=(const LinkedList<T> & rhs) {
    if (this != &rhs) {
      LinkedList<T> tmp = rhs;
      // delete original list
      Node *cur = head, *rm = head;
      while (rm != NULL) {
        cur = cur->next;
        delete rm;
        rm = cur;
      }

      head = tmp.head;
      tail = tmp.tail;
      size = rhs.getSize();
      tmp.head = NULL;
      tmp.tail = NULL;
    }

    return *this;
  }

  bool remove(const T & item) {
    Node ** cur = &head;
    while (*cur != NULL && (*cur)->data != item) {
      cur = &((*cur)->next);
    }

    // find item
    if (*cur != NULL) {
      Node * rm = *cur;
      *cur = (*cur)->next;
      if (*cur != NULL) {
        (*cur)->prev = rm->prev;
      }

      else {
        tail = rm->prev;  // meaing remove last item
      }

      rm->next = NULL;
      rm->prev = NULL;
      delete rm;
      size--;
      return true;
    }

    return false;
  }

  ~LinkedList() {
    Node * cur = head;
    Node * rm = head;
    while (cur != NULL) {
      cur = cur->next;
      rm->next = NULL;
      rm->prev = NULL;
      delete rm;
      rm = cur;
    }
  }

  int getSize() const { return size; }

  void addFront(const T & item) {
    try {
      head = new Node(item, NULL, head);
      if (tail == NULL) {
        tail = head;
      }

      else {
        Node * originHead = head->next;
        originHead->prev = head;
      }

      size++;
    }

    catch (std::bad_alloc & e) {
      std::cerr << "Error: allocation fail in addFront" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  void addBack(const T & item) {
    try {
      tail = new Node(item, tail, NULL);
      if (head == NULL) {
        head = tail;
      }

      else {
        Node * ot = tail->prev;
        ot->next = tail;
      }

      size++;
    }

    catch (std::bad_alloc & e) {
      std::cerr << "Error: allocation fail in addFront" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  int find(const T & item) {
    Node * mv = head;
    int pos = 0;
    while (mv != NULL) {
      if (mv->data == item) {
        return pos;
      }

      mv = mv->next;
      pos++;
    }

    return -1;
  }

  const T & operator[](int index) const {
    if (index > size) {
      throw IndexOutOfRange();
    }

    Node * cur = head;
    while (index > 0) {
      cur = cur->next;
      index--;
    }

    return cur->data;
  }

  T & operator[](int index) {
    if (index > size) {
      throw IndexOutOfRange();
    }

    Node * cur = head;
    while (index > 0) {
      cur = cur->next;
      index--;
    }

    return cur->data;
  }
};

#endif
