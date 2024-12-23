#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>

#define FIFO_PATH "mypipe"
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
  int fd = open(FIFO_PATH, O_RDONLY);
  if (fd == -1)
  {
    printf("open() failed\n");
    exit(EXIT_FAILURE);
  }

  int count = 0;
  int num;
  while (read(fd, &num, sizeof(num)) > 0)
  {
    if (isPrime(num))
    {
      count++;
      printf("%d is a prime number\n", num);
    }
  }

  printf("%d prime numbers found.\n", count);

  close(fd);
  unlink(FIFO_PATH);
  return 0;
}