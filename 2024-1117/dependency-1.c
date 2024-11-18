#include <omp.h>
#include <stdio.h>

#define N 1000

int a[N], b[N];

int main(void) {
#pragma omp parallel for num_threads(2)
  for (int i = 0; i < N; i++) {
    a[i] = i;
  }

  b[0] = 0;

#pragma omp parallel for num_threads(2)
  for (int i = 1; i < N; i++) {
    b[i] = b[i - 1] + 1;
  }
  for (int i = 0; i < N; i++) {
    if (a[i] != b[i]) {
      printf("error found: a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
      break;
    }
  }

  return 0;
}
