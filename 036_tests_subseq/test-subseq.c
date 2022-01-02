#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t ans) {
  size_t cal = maxSeq(array, n);

  if (cal != ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  int arr2[] = {5, 4, 3, 2, 1};
  int arr3[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int arr4[] = {1, 1, 1, 1, 1};
  int arr5[] = {-1, -2, -3, -4, -5};
  int arr6[] = {1, -1, 2, -2, 3, -3};
  int arr7[] = {1, 2, 3, -5, -4, -2, -1, 0};

  run_check(NULL, 0, 0);
  run_check(arr2, 5, 1);
  run_check(arr3, 10, 4);
  run_check(arr4, 5, 1);
  run_check(arr5, 5, 1);
  run_check(arr6, 6, 2);
  run_check(arr7, 8, 5);

  return EXIT_SUCCESS;
}
