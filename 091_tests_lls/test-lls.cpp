#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(0);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il[0] == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 1);
    assert(il.head == il.tail);

    il.addFront(1);
    assert(il[0] == 1);
    assert(il[1] == 0);
    assert(il.tail->prev == il.head);
    assert(il.head->next == il.tail);
    assert(il.getSize() == 2);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    il.addBack(0);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il[0] == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 1);
    assert(il.head == il.tail);

    il.addBack(1);
    assert(il[0] == 0);
    assert(il[1] == 1);
    assert(il.head != il.tail);
    assert(il.tail->prev == il.head);
    assert(il.head->next == il.tail);
    assert(il.getSize() == 2);
  }

  void testCopCtor() {
    IntList il1;
    IntList il2 = il1;
    assert(il2.getSize() == il1.getSize() && il2.head == NULL && il2.tail == NULL);
    il1.addFront(0);
    il1.addBack(1);
    il1.addBack(2);
    IntList il3 = il1;
    assert(il3[0] == 0 && il3[1] == 1 && il3[2] == 2 && il3.getSize() == il1.getSize());
    assert(il3.head != il1.head);
    assert(il3.tail != il1.tail);
  }

  void testAssign() {
    IntList il1;
    il1.addFront(0);
    il1.addBack(1);
    il1.addBack(2);
    IntList il2;
    IntList il3;
    il1 = il1;
    assert(il1[0] == 0 && il1[1] == 1 && il1[2] == 2 && il1.getSize() == il1.getSize());
    il2 = il1;
    assert(il2[0] == 0 && il2[1] == 1 && il2[2] == 2 && il2.getSize() == il1.getSize() &&
           il2.head != il1.head && il2.tail != il1.tail);
    il1 = il3;
    assert(il1.getSize() == 0 && il1.head == NULL && il1.tail == NULL);
  }

  void testRemove() {
    IntList l1;
    bool retb = l1.remove(1);
    assert(retb == false);

    l1.addBack(0);
    l1.addBack(1);
    l1.addBack(2);
    l1.addBack(11);  // [0, 1, 2, 11]
    assert(l1.getSize() == 4);

    l1.remove(0);
    assert(l1.head != NULL && l1.tail != NULL);
    assert(l1[0] == 1 && l1[1] == 2 && l1[2] == 11 && l1.getSize() == 3);
    assert(l1.head->prev == NULL);

    l1.remove(11);
    assert(l1.head != NULL && l1.tail != NULL);
    assert(l1[0] == 1 && l1[1] == 2 && l1.getSize() == 2);
    assert(l1.tail->next == NULL);  // [1,2]

    l1.addBack(3);  // [1,2,3]
    l1.remove(2);
    assert(l1.head != NULL && l1.tail != NULL);
    assert(l1[0] == 1 && l1[1] == 3 && l1.getSize() == 2);
    assert(l1.head->next == l1.tail);
    assert(l1.tail->prev == l1.head);  // [1,3]

    l1.remove(1);
    assert(l1.head == l1.tail && l1.tail != NULL);
    assert(l1[0] == 3 && l1.getSize() == 1);
    l1.remove(1);

    l1.remove(3);
    assert(l1.head == NULL && l1.tail == NULL);
    assert(l1.getSize() == 0);
    l1.remove(100);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopCtor();
  t.testAssign();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
