#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) :
    numRows(r),
    numColumns(c),
    rows(new IntArray *[r]()) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[numRows]();
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*rhs.rows[i]);
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    numRows = rhs.getRows();
    numColumns = rhs.getColumns();
    // copy content
    IntArray ** temp = new IntArray *[numRows]();
    for (int i = 0; i < numRows; i++) {
      temp[i] = new IntArray(*rhs.rows[i]);
    }

    // delete original content
    if (rows != NULL) {
      for (int i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
    }
    rows = temp;
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert((index < numRows) && (index > -1));
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert((index < numRows) && (index > -1));
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (!((numColumns == rhs.getColumns()) && (numRows == rhs.getRows()))) {
    return false;
  }

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      if ((*this)[i][j] != rhs[i][j]) {
        return false;
      }
    }
  }

  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((numRows == rhs.getRows()) && (numColumns == rhs.getColumns()));

  IntMatrix temp(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      temp[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }

  return temp;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";

  return s;
}
