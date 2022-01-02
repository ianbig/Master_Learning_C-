#include <stdio.h>

size_t maxSeq(int * array, size_t n) {
  if (array == NULL || n <= 0)
    return 0;

  size_t maxCount = 1;  // start from 1
  size_t count = 1;     // start from 1

  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      count++;
      maxCount = (maxCount > count) ? maxCount : count;
    }

    else {
      count = 1;
    }
  }

  return maxCount;
}
