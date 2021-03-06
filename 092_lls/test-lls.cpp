#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

typedef LinkedList<int> IntList;

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
    assert(il.head->data == 0 && il.head->data == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL && il.head->prev == NULL);
    assert(il.getSize() == 1);
    assert(il.head == il.tail);

    il.addFront(1);
    assert(il.head->data == 1 && il.tail->data == 0);
    assert(il.tail->prev == il.head);
    assert(il.head->next == il.tail);
    assert(il.getSize() == 2);

    il.addFront(2);
    assert(il.head->data == 2 && il.tail->data == 0);
    assert(il.head != il.tail);
    assert(il.head->next->next == il.tail);
    assert(il.tail->prev->prev == il.head);
    assert(il.getSize() == 3);
    std::cout << "=========== test addFront completed without error" << std::endl;
  }

  // many more tester methods
  void testAddBack() {
    IntList il;
    il.addBack(0);
    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.head == il.tail);
    assert(il.head->data == 0 && il.tail->data == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 1);

    il.addBack(1);
    assert(il.head->data == 0);
    assert(il.tail->data == 1);
    assert(il.head != il.tail);
    assert(il.tail->prev == il.head);
    assert(il.head->next == il.tail);
    assert(il.getSize() == 2);

    il.addBack(2);
    assert(il.head->data == 0);
    assert(il.tail->data == 2);
    assert(il.head != il.tail);
    assert(il.head->next->next == il.tail);
    assert(il.tail->prev->prev == il.head);
    assert(il.getSize() == 3);
    std::cout << "=========== test addBack completed without error" << std::endl;
  }

  void testFind() {
    IntList il;
    il.addBack(100);
    il.addBack(101);
    il.addBack(200);
    il.addFront(100);
    il.addFront(200);

    for (int i = 300; i < 1000; i++) {
      il.addBack(i);
    }

    assert(il.find(100) == 1);
    assert(il.find(200) == 0);
    assert(il.find(101) == 3);
    for (int i = 300; i < 1000; i++) {
      assert(il.find(i) == i - 300 + 5);
    }

    assert(il.find(-100) == -1);
    assert(il.find(3000) == -1);
    std::cout << "=========== test addFind completed without error" << std::endl;
  }

  void testOperator() {
    IntList li;
    li.addBack(10);
    li.addBack(11);
    li.addBack(12);
    li.addBack(13);

    assert(li[0] == 10);
    assert(li[1] == 11);
    assert(li[2] == 12);
    assert(li[3] == 13);

    std::cout << "value of li" << std::endl;
    for (int i = 0; i < 4; i++) {
      std::cout << li[i] << std::endl;
    }
    // TODO: do this test after building copy constructor
    const IntList cli = li;
    assert(cli[0] == 10);
    assert(cli[1] == 11);
    assert(cli[2] == 12);
    assert(cli[3] == 13);

    std::cout << "value of cli" << std::endl;
    for (int i = 0; i < 4; i++) {
      std::cout << li[i] << std::endl;
    }

    std::cout << "=========== test operator[] completed without error" << std::endl;
  }

  void testCopCtor() {
    IntList il1;
    IntList il2 = il1;
    assert(il2.getSize() == il1.getSize() && il2.head == NULL && il2.tail == NULL);
    il1.addFront(0);
    il1.addBack(1);
    il1.addBack(2);
    IntList il3 = il1;
    assert(il3[0] == 0);
    assert(il3[1] == 1);
    assert(il3[2] == 2);
    assert(il3.getSize() == il1.getSize());
    assert(il3.head != il1.head);
    assert(il3.tail != il1.tail);

    for (int i = 0; i < il2.getSize(); i++) {
      std::cout << il2[i] << std::endl;
    }

    std::cout << "=========== test Copy Constructor completed without error" << std::endl;
  }

  void testAssign() {
    IntList il1;
    il1.addFront(0);
    il1.addBack(1);
    il1.addBack(2);
    il1 = il1;
    assert(il1[0] == 0);
    assert(il1[1] == 1);
    assert(il1[2] == 2);
    assert(il1.getSize() == il1.getSize());

    IntList il2;
    il2 = il1;
    assert(il2[0] == 0);
    assert(il2[1] == 1);
    assert(il2[2] == 2);
    assert(il2.getSize() == il1.getSize());
    assert(il2.head != il1.head && il2.tail != il1.tail);

    IntList il3;
    il1 = il3;
    assert(il1.getSize() == 0 && il1.head == NULL && il1.tail == NULL);

    std::cout << "=========== test assignment operator completed without error"
              << std::endl;
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
    std::cout << "=========== test remove completed without error" << std::endl;
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testFind();
  t.testOperator();
  t.testCopCtor();
  t.testAssign();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
