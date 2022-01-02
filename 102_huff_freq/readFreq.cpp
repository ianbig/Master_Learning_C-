#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream fs(fname, std::ifstream::in);
  if (!fs.is_open()) {
    std::cerr << "Error on opening file" << std::endl;
  }

  int c = 0;
  uint64_t * ret = new uint64_t[257]();
  while ((c = fs.get()) != EOF) {
    ret[c]++;
  }

  if (fs.eof()) {
    ret[256] = 1;
  }

  fs.close();

  return ret;
}
