#include <omp.h>
#include <stdio.h>

#define N 2000000000

double leibniz(int n) {
  double pi_4 = 0.0;

#pragma omp parallel

  {
    printf("THread %d is starting the 1st loop\n", omp_get_thread_num());
#pragma pmp for reduction(+ : pi_4)
    for (int i = 0; i < n; i += 2) {
      pi_4 += 1.0 / (2 * i + 1);
    }
    printf("THread %d is completed the 1st loop\n", omp_get_thread_num());

#pragma omp barrier

    printf("THread %d is starting the 2nd loop\n", omp_get_thread_num());
#pragma omp for reduction(+ : pi_4)
    for (int i = 1; i < n; i += 2) {
      pi_4 -= 1.0 / (2 * i + 1);
    }
    printf("THread %d is completed the 2nd loop\n", omp_get_thread_num());
  }

  return (pi_4 * 4);
}

int main() {
  double pi = leibniz(N);
  printf("Pi = %.10f\n", pi);
  return 0;
}
