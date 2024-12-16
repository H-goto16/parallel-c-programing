#include <stdio.h>
#include <unistd.h>

#define N 100000000

int isPrime(int x)
{
  if (x <= 1)
    return 0;
  if (x == 2)
    return 1;
  if (x % 2 == 0)
    return 0;
  for (int i = 3; i * i <= x; i += 2)
  {
    if (x % i == 0)
      return 0;
  }
  return 1;
}

int main(void)
{
  int n = 0;
  fork();
  for (int i = 0; i < N; i++)
  {
    n += isPrime(i);
  }

  printf("%d prime numbers found.\n", n);
  sleep(5);

  return 0;
}