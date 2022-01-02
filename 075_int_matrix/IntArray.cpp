#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
  // std::cout << "Default Constructor is called" << std::endl;
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
  // std::cout << "Constructor IntArray(n) is called" << std::endl;
}

IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = new int[numElements]();
  for (int i = 0; i < rhs.size(); i++) {
    data[i] = rhs.data[i];
  }
  //std::cout << "Copy Constructor is called" << std::endl;
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    this->numElements = rhs.numElements;
    delete[] this->data;
    this->data = new int[this->numElements]();
    for (int i = 0; i < rhs.size(); i++) {
      data[i] = rhs.data[i];
    }
  }

  return *this;
}
const int & IntArray::operator[](int index) const {
  assert((index < numElements) && (index > -1));
  return this->data[index];
}
int & IntArray::operator[](int index) {
  assert((index < numElements) && (index > -1));
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  bool equalFlags = true;

  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      equalFlags = false;
      break;
    }
  }

  return ((numElements == rhs.numElements) && equalFlags);
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & os, const IntArray & rhs) {
  if (rhs.size() == 0) {
    os << "{"
       << "}";
    return os;
  }

  os << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    os << rhs[i] << ", ";
  }

  os << rhs[rhs.size() - 1] << "}";
  return os;
}
