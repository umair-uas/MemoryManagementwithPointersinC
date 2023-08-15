/**
 * Wired Brain Coffee - Espresso Machine Metrics
 *
 * This Wired Brain Coffee C program expects one argument from the command line
 *that constitues the size of an array. From this size, it constructs three,
 *variable-length arrays and stores some calculations for metrics of the
 *espresso machine.
 *
 * Currently, when too large a size is passed into the program, a stack overflow
 *occurs as too much memory is being allocated on the stack for the
 *variable-length arrays.
 *
 * In the program below, the exercise is to convert these three variable-length
 *arrays into dynamically allocated arrays such that memory is allocated on the
 *heap instead of the stack.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SIZE 1000

double get_random_number();

void gather_metrics(size_t size, double* metric_arr);

int main(int argc, char* argv[]) {
  int array_size = DEFAULT_SIZE;

  if (argc > 1) {
    array_size = strtol(argv[1], NULL, 10);
  }

  double *heat_distribution_metrics =
             (double*)malloc(array_size * sizeof(double)),
         *grinder_metrics = (double*)malloc(array_size * sizeof(double)),
         *pour_metrics = (double*)malloc(array_size * sizeof(double));

  if (!heat_distribution_metrics)
    heat_distribution_metrics = (double*)malloc(DEFAULT_SIZE * sizeof(double));

  if (!grinder_metrics)
    heat_distribution_metrics = (double*)malloc(DEFAULT_SIZE * sizeof(double));

  if (!pour_metrics)
    heat_distribution_metrics = (double*)malloc(DEFAULT_SIZE * sizeof(double));

  double* metrics_matrix[3] = {heat_distribution_metrics, grinder_metrics,
                               pour_metrics};

  for (int i = 0; i < 3; i++) {
    gather_metrics(array_size, metrics_matrix[i]);
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < array_size; j++) {
      printf("Row/Col: %d/%d ===> Value: %f\n", i + 1, j + 1,
             metrics_matrix[i][j]);
    }
  }

  for (int i = 0; i < 3; i++) {
    free(metrics_matrix[i]);
  }

  return 0;
}

void gather_metrics(size_t size, double* metric_arr) {
  for (int i = 0; i < size; i++) {
    metric_arr[i] = get_random_number();
  }
}

double get_random_number() {
  return rand() / (RAND_MAX / 2.5);
}