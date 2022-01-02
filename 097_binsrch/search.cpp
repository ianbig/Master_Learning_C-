#include <climits>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high) {
    exit(EXIT_FAILURE);
  }

  if (low == high) {
    return low;
  }

  int ret = INT_MIN, mid = 0;
  high = high - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    ret = f->invoke(mid);

    if (ret < 0) {
      low = mid + 1;
    }

    else if (ret > 0) {
      high = mid - 1;
    }

    else {
      return mid;  // eqaul to 0
    }
  }

  if (ret > 0 && mid > low) {
    return mid - 1;
  }

  return mid;
}
