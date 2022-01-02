#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Error format: program [file to parsed]\n");
    exit(EXIT_FAILURE);
  }
  // parse file
  char * parsedLine = NULL;
  parsedLine = parseFile(argv[1], NULL, 0);
  printf("%s\n", parsedLine);
  free(parsedLine);
  return EXIT_SUCCESS;
}
