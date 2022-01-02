#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "Error: wrong command line format\n");
    exit(EXIT_FAILURE);
  }

  int opt = 0, cats_index = 1, file_index = 2, n_opt = 0;
  while ((opt = getopt(argc, argv, "n")) != -1) {
    switch (opt) {
      case 'n':
        if (optind != 2) {
          fprintf(stderr, "Error: wrong format\n");
          exit(EXIT_FAILURE);
        }
        n_opt = 1;
        cats_index = 2;
        file_index = 3;
        break;
      default:
        fprintf(stderr, "not exist option\n");
        exit(EXIT_FAILURE);
        break;
    }
  }

  catarray_t * cats = NULL;
  char * out = NULL;
  // build up category
  cats = parseCats(argv[cats_index], 0);
  // build up output from template
  out = parseFile(argv[file_index], cats, n_opt);
  printf("%s\n", out);

  freeCats(cats);
  free(out);

  return EXIT_SUCCESS;
}
