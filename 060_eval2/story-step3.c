#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Error: wrong command format\n");
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = NULL;
  cats = parseCats(argv[1], 0);
  char * parsedLine = NULL;
  parsedLine = parseFile(argv[2], cats, 0);
  printf("%s\n", parsedLine);

  freeCats(cats);
  free(parsedLine);

  return EXIT_SUCCESS;
}
