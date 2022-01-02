#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int arrayMax(int * array, int n) {
  if (n <= 0 || array == NULL)
    return -1;

  int max = array[0], maxIndex = 0;
  for (int i = 1; i < n; i++) {
    if (max < array[i]) {
      max = array[i];
      maxIndex = i;
    }
  }

  return maxIndex;
}

int breaker(char ** argv) {
  // open file
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    perror("ERROR");
    return -1;
  }
  // parse the statistic
  int stat[26] = {0};
  int fchar = -1;
  // read file
  while ((fchar = fgetc(fptr)) != EOF) {
    if (isalpha(fchar)) {
      fchar = tolower(fchar);
      stat[fchar - 'a'] += 1;
    }
  }
  // find the max val
  int key = arrayMax(stat, 26);

  key = (key - (('e' - 'a')) + 26) % 26;

  printf("%d\n", key);
  fclose(fptr);
  return 0;
}

int main(int argc, char ** argv) {
  // input parsing
  if (argc != 2) {
    fprintf(stderr, "Usage: ./breaker input.txt\n");
    exit(EXIT_FAILURE);
  }
  // break the code
  int res = -2;
  res = breaker(argv);

  if (res != 0) {
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
