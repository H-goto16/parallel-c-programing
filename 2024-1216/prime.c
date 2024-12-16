#include <stdio.h>

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
  int x;

  while (scanf("%d", &x))
  {
    if (isPrime(x))
      printf("%d\n", x);
  }
}