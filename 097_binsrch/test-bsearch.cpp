#include <assert.h>

#include <cmath>
#include <cstdio>
#include <iostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int max = 0;
  if (high > low) {
    max = log2(high - low) + 1;
  }
  else {
    max = 1;
  }

  CountedIntFn fn(max, f, mesg);
  int ans = binarySearchForZero(&fn, low, high);
  std::cout << mesg << ": get: " << ans << ", expected:" << expected_ans << std::endl;
  assert(ans == expected_ans);
}

class testFunc : public Function<int, int> {
 public:
  // virtual int invoke(int arg) { return arg; }
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

int main() {
  testFunc * testf = new testFunc();
  check(testf, 0, 150000, 52359, "0 to 150000");
  check(testf, 150000, 150000, 150000, "0 to 150000");
  // check(testf, 1, 6, 1, "1 to 6");
  // check(testf, -4, -1, -2, "-4 to -1");
  // check(testf, -4, 1, 0, "-4 to 1");
  // check(testf, -4, -4, -4, "all negative high == low");
  // check(testf, -4, -1, -2, "-4 to -1");
  // check(testf, 0, 10, 9, "0 to 10");
  // check(testf, 1, 10, 9, "1 to 10");
}
