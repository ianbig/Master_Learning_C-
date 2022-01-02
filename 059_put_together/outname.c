#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  if (inputName == NULL) {
    fprintf(stderr, "Error, passing NULL name\n");
    exit(EXIT_FAILURE);
  }
  size_t const_sz = 7;  // size for count
  size_t input_sz = strlen(inputName);
  // create a new memory for outname
  size_t outname_sz = input_sz + const_sz + 1;  // plus one for \0
  char * outname = malloc(sizeof(*outname) * (outname_sz));
  // copy inputName and constant to outname
  snprintf(outname, outname_sz, "%s.counts", inputName);

  return outname;
}
