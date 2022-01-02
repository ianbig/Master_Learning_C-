#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  // open the file
  FILE * fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "countFile: unable to open file\n");
    exit(EXIT_FAILURE);
  }

  counts_t * counts = createCounts();
  char * lineptr = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  char * val = NULL;
  // get line and count
  while ((len = getline(&lineptr, &sz, fp)) != -1) {
    strtok(lineptr, "\n");
    val = lookupValue(kvPairs, lineptr);
    addCount(counts, val);
  }

  free(lineptr);
  fclose(fp);

  return counts;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "Error: wrong format\n");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv_pairs = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (size_t i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * counts = countFile(argv[i], kv_pairs);
    //compute the output file name from argv[i] (call this outName)
    char * outname = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * fout = fopen(outname, "w+");
    if (fout == NULL) {
      fprintf(stderr, "Unable to open file in main");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(counts, fout);
    //close f
    fclose(fout);
    //free the memory for outName and c
    freeCounts(counts);
    free(outname);
  }
  //free the memory for kv
  freeKVs(kv_pairs);
  return EXIT_SUCCESS;
}
