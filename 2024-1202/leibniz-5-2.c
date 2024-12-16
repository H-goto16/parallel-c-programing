#include <omp.h>
#include <stdio.h>

#define N 2000000000

double leibniz(int n) {
  double pi_4 = 0.0;

#pragma omp parallel num_threads(4)
  {
#pragma omp sections
    {
#pragma omp section
      {
        for (int i = 0; i < n; i += 2) {
#pragma omp atomic
          pi_4 += 1.0 / (2 * i + 1);
        }
      }

#pragma omp section
      {
        for (int i = 1; i < n; i += 2) {
#pragma omp atomic
          pi_4 -= 1.0 / (2 * i + 1);
        }
      }
    }
  }

  return (pi_4 * 4);
}

int main() {
  double pi = leibniz(N);
  printf("Pi = %.10f\n", pi);
  return 0;
}
