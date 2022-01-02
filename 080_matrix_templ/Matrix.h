#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}

  Matrix(int r, int c) :
      numRows(r),
      numColumns(c),
      rows(std::vector<std::vector<T> >(r, std::vector<T>(c))) {}

  Matrix<T>(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    for (int i = 0; i < numRows; i++) {
      rows.push_back(std::vector<T>());
      for (int j = 0; j < numColumns; j++) {
        rows[i].push_back(rhs.rows[i][j]);
      }
    }
  }

  ~Matrix() {}

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = rhs.rows;
    }

    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert((index < numRows) && (index > -1));
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert((index < numRows) && (index > -1));
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    if (!((numColumns == rhs.getColumns()) && (numRows == rhs.getRows()))) {
      return false;
    }

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if (rows[i][j] != rhs.rows[i][j]) {
          return false;
        }
      }
    }

    return true;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert((numRows == rhs.getRows()) && (numColumns == rhs.getColumns()));

    Matrix<T> temp(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        temp[i][j] = rows[i][j] + rhs.rows[i][j];
      }
    }

    return temp;
  }
};

template<typename S>
std::ostream & operator<<(std::ostream & s, const Matrix<S> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    // inner loop for printing elements
    s << "{";
    for (int j = 0; j < rhs.getColumns() - 1; j++) {
      s << rhs[i][j] << ", ";
    }

    s << rhs[i][rhs[i].size() - 1] << "}";

    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";

  return s;
}

#endif
