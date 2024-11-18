#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

double dotproduct(double *a, double *b, int n) {
  double sum = 0.0;
  double *c = (double *)malloc(n * sizeof(double));

#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    c[i] = a[i] * b[i];
  }

#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++) {
    sum += c[i];
  }

  free(c);

  return sum;
}

int main(void) {
  int n = N;
  omp_set_num_threads(2);

  double *a = (double *)malloc(N * sizeof(double));
  double *b = (double *)malloc(N * sizeof(double));

#pragma omp parallel for
  for (int i = 0; i < N; i++) {
    a[i] = (double)(i + 1);
    b[i] = 1.0 / (i + 1);
  }

  double sum = dotproduct(a, b, n);

  printf("Sum = %f\n", sum);

  free(a);
  free(b);

  return 0;
}
