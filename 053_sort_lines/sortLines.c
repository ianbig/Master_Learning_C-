#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortInput(const char * fileName) {
  char * lineptr = NULL;
  size_t sz = 0, lineCount = 0, defaultLine = 5;
  ssize_t len = -1, totalBytes = 0;
  char ** data = malloc(sizeof(*data) * defaultLine);
  if (data == NULL) {
    fprintf(stderr, "Error: Not enough memory in heap\n");
    exit(EXIT_FAILURE);
  }

  if (fileName == NULL) {
    while ((len = getline(&lineptr, &sz, stdin)) >= 0) {
      if (lineCount >= defaultLine) {
        defaultLine *= 2;
        if ((data = realloc(data, defaultLine * sizeof(*data) + totalBytes)) == NULL) {
          fprintf(stderr, "Error: Request realloc fail!\n");
          exit(EXIT_FAILURE);
        }
      }

      data[lineCount] = malloc(sizeof(*lineptr) * len + 1);
      if (data[lineCount] == NULL) {
        fprintf(stderr, "Error: not enough heap size\n");
        exit(EXIT_FAILURE);
      }

      strncpy(data[lineCount], lineptr, len + 1);
      lineCount++;
      totalBytes += len + 1;  // beacuse /0 is not count in getline
    }

    free(lineptr);
  }

  else {
    FILE * fp = fopen(fileName, "r");
    if (fp == NULL) {
      fprintf(stderr, "Error: unable to open file\n");
      free(data);
      exit(EXIT_FAILURE);
    }
    while ((len = getline(&lineptr, &sz, fp)) >= 0) {
      if (lineCount >= defaultLine) {
        defaultLine *= 2;
        if ((data = realloc(data, defaultLine * sizeof(*data) + totalBytes)) == NULL) {
          fprintf(stderr, "Error: Request realloc fail!\n");
          exit(EXIT_FAILURE);
        }
      }

      data[lineCount] = malloc(sizeof(*lineptr) * len + 1);
      if (data[lineCount] == NULL) {
        fprintf(stderr, "Error: not enough heap size\n");
        exit(EXIT_FAILURE);
      }

      strncpy(data[lineCount], lineptr, len + 1);
      lineCount++;
      totalBytes += len + 1;  // beacuse /0 is not count in getline
    }

    free(lineptr);
    fclose(fp);
  }

  sortData(data, lineCount);
  for (size_t i = 0; i < lineCount; i++) {
    printf("%s", data[i]);
  }

  for (size_t i = 0; i < lineCount; i++) {
    free(data[i]);
  }
  free(data);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    sortInput(NULL);
  }

  else if (argc > 1) {
    for (size_t i = 1; i < argc; i++) {
      sortInput(argv[i]);
    }
  }

  return EXIT_SUCCESS;
}
