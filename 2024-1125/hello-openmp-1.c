#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
#pragma omp parallel
  {
    printf("Hello, OpenMP!\n");
    sleep(5);
  }
  return 0;
}
