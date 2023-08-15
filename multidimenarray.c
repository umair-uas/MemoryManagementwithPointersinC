#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%-5d", matrix[i][j]);
    }
    printf("\n");
  }
}

void generateRandomMatrix(int rows,
                          int cols,
                          int array[rows][cols],
                          int min,
                          int max) {
  srand(time(NULL));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      array[i][j] = rand() % (max - min + 1) + min;
    }
  }
}

void transpose(int rows, int cols, int mat[][cols], int Transposed[][rows]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Transposed[j][i] = mat[i][j];
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage : %s <no. of rows> <no. of columns>\n", argv[0]);
    return 1;
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  if (rows <= 0 || cols <= 0) {
    fprintf(stderr, "stderr: Invalid rows or columns\n");
    return 1;
  }

  int A[rows][cols];
  int(*B)[rows][cols] = malloc(sizeof(int[rows][cols]));
  if (B == NULL) {
    perror("Malloc failed");
    return 1;
  }

  generateRandomMatrix(rows, cols, A, 1, 10);
  generateRandomMatrix(rows, cols, *B, 1, 111);
  printf("Random matrix on stack: \n");
  printMatrix(rows, cols, A);
  printf("Random Dynamic Matrix B: \n");
  printMatrix(rows, cols, *B);

  int(*T)[cols][rows] = malloc(sizeof(int[cols][rows]));
  transpose(rows, cols, *B, *T);

  printf("Transpose matrix: \n");
  printMatrix(cols, rows, *T);

  free(B);
  free(T);
  return 0;
}
