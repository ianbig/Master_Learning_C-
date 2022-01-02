#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function could split key and val
// @line: the line to split
// @len: the length of line, should include the \0
kvpair_t * split_key_val(char * line, ssize_t len) {
  kvpair_t * pair = malloc(sizeof(*pair));
  if (pair == NULL) {
    fprintf(stderr, "split_key_val: unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  // find the delmeter
  char * del = line;
  while (del != NULL && *del != '=') {
    del++;
  }
  // copy key to key in pair
  size_t key_len = del - line + 1;  // need to also include del
  pair->key = malloc(sizeof(*pair->key) * key_len);
  if (pair->key == NULL) {
    fprintf(stderr, "split_key_val: unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  strncpy(pair->key, line, key_len);
  pair->key[key_len - 1] = '\0';  // turn = to \0

  // copy value to value in piar
  char * val_head = del + 1;
  ssize_t val_len = len - key_len;

  pair->val = malloc(sizeof(*pair->val) * val_len);
  if (pair->val == NULL) {
    fprintf(stderr, "split_key_val: unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  strncpy(pair->val, val_head, val_len);  // the \0 is included in para line
  pair->val[val_len - 2] = '\0';  // since the string is ...\n\0, by -2 turn \n to \0

  return pair;
}

void kv_print_pair_info(kvpair_t * pair) {
  printf("kv_print_info key: %s, val: %s\n", pair->key, pair->val);
}

void kv_add_pair(kvarray_t * kv_array, kvpair_t * pair) {
  // increase size of kvarray
  kv_array->sz += 1;
  // re-allocate size
  if ((kv_array->kvArr =
           realloc(kv_array->kvArr, sizeof(*kv_array->kvArr) * kv_array->sz)) == NULL) {
    fprintf(stderr, "kv_add_pair: unable to realloc memory\n");
    exit(EXIT_FAILURE);
  }
  kv_array->kvArr[kv_array->sz - 1] = pair;
}

kvarray_t * init_array() {
  kvarray_t * kv_array = malloc(sizeof(*kv_array));
  if (kv_array == NULL) {
    fprintf(stderr, "readKVs: unable to allocate memory\n");
    exit(EXIT_FAILURE);
  }

  kv_array->kvArr = NULL;
  kv_array->sz = 0;

  return kv_array;
}

kvarray_t * readKVs(const char * fname) {
  // open file fname
  FILE * fp = fopen(fname, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: Unable to opne %s\n", fname);
    exit(EXIT_FAILURE);
  }
  // read lines
  char * lineptr = NULL;
  size_t linesz = 0;
  ssize_t len = -1;
  kvpair_t * pair = NULL;
  kvarray_t * kv_array = init_array();

  while ((len = getline(&lineptr, &linesz, fp)) != -1) {
    // split into key value
    pair = split_key_val(
        lineptr,
        len +
            1);  // since the length of getline do not include /0, but the string is null-terminated
    // add result to array
    kv_add_pair(kv_array, pair);
  }
  free(lineptr);

  if (fclose(fp) != 0) {
    fprintf(stderr, "split_key_val: unable to close file\n");
    exit(EXIT_FAILURE);
  }

  return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->sz; i++) {
    kvpair_t * pair = pairs->kvArr[i];
    free(pair->key);
    free(pair->val);
    free(pair);
  }
  free(pairs->kvArr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->sz; i++) {
    kvpair_t * pair = pairs->kvArr[i];
    printf("key = '%s' value = '%s'\n", pair->key, pair->val);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->sz; i++) {
    kvpair_t * pair = pairs->kvArr[i];
    if (strcmp(pair->key, key) == 0) {
      return pair->val;
    }
  }

  return NULL;
}
