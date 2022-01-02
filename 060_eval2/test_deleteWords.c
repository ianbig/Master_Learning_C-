#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    return EXIT_FAILURE;
  }

  catarray_t * cats = NULL;
  cats = parseCats(argv[1], 1);
  // hardcoded testing
  category_t * cat = NULL;
  cat = findCat("animal", cats);
  deleteWords(cat, "dragon");
  printWords(cats);
  cat = findCat("place", cats);
  deleteWords(cat, "cave");
  printWords(cats);
  freeCats(cats);
}
