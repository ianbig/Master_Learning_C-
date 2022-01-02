#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW 10
#define COL 10

int fillMatrix(char matrix[][COL], FILE * fp) {
  int c = 0;
  size_t row = 0, col = 0, cum = 0;
  while ((c = fgetc(fp)) != EOF && (row <= ROW && col <= COL)) {
    if (c == '\n') {
      if (col != COL) {
        fprintf(stderr, "expect %d cols in %zu rows, but get %zu cols\n", COL, row, col);
        exit(EXIT_FAILURE);
      }
      col = 0;
      row++;
      continue;
    }
    matrix[row][col] = c;
    col++;
    cum++;
  }

  if (cum != ROW * COL) {
    fprintf(stderr, "Error: expect %d elements, but get %zu elements\n", ROW * COL, cum);
    exit(EXIT_FAILURE);
  }

  return 0;
}

int rotateImage(const char * fileName) {
  FILE * fp = fopen(fileName, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: File not exist\n");
    exit(EXIT_FAILURE);
  }

  char matrix[ROW][COL] = {{0}}, newMatrix[ROW][COL] = {{0}};
  fillMatrix(matrix, fp);

  // start to rotate matrix
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      newMatrix[j][COL - 1 - i] = matrix[i][j];
    }
  }

  // print the matrix
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      printf("%c", newMatrix[i][j]);
    }
    printf("\n");
  }

  fclose(fp);
  return 0;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Error: Wrong Argument Number, epxect 2, but get %d\n", argc);
    exit(EXIT_FAILURE);
  }

  int ret = -1;
  ret = rotateImage(argv[1]);

  if (ret == -1) {
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
