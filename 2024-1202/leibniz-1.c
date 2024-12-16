#include <omp.h>
#include <stdio.h>

#define N 2000000000

double leibniz(int n) {
  double pi_4 = 0.0;

#pragma omp parallel for reduction(+ : pi_4)
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) {
      pi_4 += 1.0 / (2 * i + 1);
    } else {
      pi_4 -= 1.0 / (2 * i + 1);
    }
  }
  return pi_4;
}

int main() {
  double pi = 4 * leibniz(N);
  printf("Pi = %.10f\n", pi);
  return 0;
}
