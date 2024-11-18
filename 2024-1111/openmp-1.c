#include <omp.h>
#include <stdio.h>

int main(void) {
  int n = 2000000000;
  double sum = 0.0;

#pragma omp parallel for reduction(+ : sum) num_threads(4)
  for (int i = 1; i <= n; i++) {
    sum += 1.0 / (i + 1);
  }

  printf("Sum = %f\n", sum);

  return 0;
}
