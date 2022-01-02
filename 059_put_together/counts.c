#include "counts.h"

#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * count_table = malloc(sizeof(*count_table));
  if (count_table == NULL) {
    fprintf(stderr, "createCounts: unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  count_table->one_array = NULL;
  count_table->sz = 0;
  count_table->unknwon_sz = 0;

  return count_table;
}
// expect /0 in name
one_count_t * create_count(const char * name) {
  one_count_t * count = malloc(sizeof(*count));
  if (count == NULL) {
    fprintf(stderr, "create_count: unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  size_t len = strlen(name);
  count->str = malloc(sizeof(*count->str) * (len + 1));  // include null terminated
  if (count->str == NULL) {
    fprintf(stderr, "create_count: unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  strncpy(count->str, name, len);
  count->str[len] = '\0';
  count->count = 1;

  return count;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknwon_sz += 1;
    return;
  }

  for (size_t i = 0; i < c->sz; i++) {
    one_count_t * count = c->one_array[i];
    if (strcmp(count->str, name) == 0) {
      count->count += 1;
      return;
    }
  }

  // create new count, and add it array
  c->sz += 1;
  c->one_array = realloc(c->one_array, sizeof(*c->one_array) * (c->sz));
  if (c->one_array == NULL) {
    fprintf(stderr, "Error: fail to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  one_count_t * element = create_count(name);
  c->one_array[c->sz - 1] = element;
}
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->sz; i++) {
    one_count_t * count = c->one_array[i];
    fprintf(outFile, "%s: %zu\n", count->str, count->count);
  }

  if (c->unknwon_sz > 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->unknwon_sz);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->sz; i++) {
    one_count_t * count = c->one_array[i];
    free(count->str);
    free(count);
  }

  free(c->one_array);
  free(c);
}
