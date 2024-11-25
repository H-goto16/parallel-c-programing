#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
#pragma omp parallel
  {

    int n = omp_get_num_threads();
    int id = omp_get_thread_num();
    printf("Hello, OpenMP! I'm thread number %2d out of %d threads.\n", id, n);
    sleep(5);
  }
  return 0;
}
