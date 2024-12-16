#include <omp.h>
#include <stdio.h>

#define N 2000000000

double leibniz(int n) {
  double pi_4 = 0.0;
#pragma pmp parallel for num_threads(4) reduction(+ : pi_4)
  for (int i = 0; i < n; i += 2) {
    pi_4 += 1.0 / (2 * i + 1);
  }

#pragma omp parallel for num_threads(4) reduction(+ : pi_4)
  for (int i = 1; i < n; i += 2) {
    pi_4 -= 1.0 / (2 * i + 1);
  }
  return (pi_4 * 4);
}

int main() {
  double pi = leibniz(N);
  printf("Pi = %.10f\n", pi);
  return 0;
}
