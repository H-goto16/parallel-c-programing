#include <omp.h>
#include <stdio.h>

#define N 2000

int A[N][N], B[N][N], C[N][N];

void initialize(void) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = B[i][j] = (i == j);
    }
  }
}

void multiply(void) {
#pragma omp parallel for num_threads(2)
  for (int i = 0; i < N; i++) {
#pragma omp parallel for num_threads(2)
    for (int j = 0; j < N; j++) {
      C[i][j] = 0;
      for (int k = 0; k < N; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}
void check(void) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (C[i][j] != (i == j)) {
        printf("Error found: C[%d][%d] = %d\n", i, j, C[i][j]);
        break;
      }
    }
  }
}

int main(void) {
  initialize();
  double start_time = omp_get_wtime();
  multiply();
  double end_time = omp_get_wtime();
  check();

  printf("Time for matrix multiplication: %.10f seconds\n",
         end_time - start_time);
  return 0;
}
