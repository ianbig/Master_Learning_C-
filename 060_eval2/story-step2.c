#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Error: wrong format for step 2\n");
    return EXIT_FAILURE;
  }

  catarray_t * cats = NULL;
  cats = parseCats(argv[1], 1);
  freeCats(cats);

  return EXIT_SUCCESS;
}
