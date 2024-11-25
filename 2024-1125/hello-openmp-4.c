#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  int n;
  int n_max = omp_get_max_threads();
  printf("This PC can run up to %d threads in parallel.\n", n_max);
#pragma omp parallel num_threads(4)
  {
#pragma omp single
    { n = omp_get_num_threads(); }
    int id = omp_get_thread_num();
    printf("Hello, OpenMP! I'm thread number %2d out of %d threads.\n", id, n);
    sleep(5);
  }
  return 0;
}
