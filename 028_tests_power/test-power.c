#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main(int agrc, char ** argv) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(-1, 2, 1);
  run_check(-3, 3, -27);
}
