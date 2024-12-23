#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define N 1000

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
  int pipefd[2];

  if (pipe(pipefd) == -1)
  {
    printf("pipe not created.\n");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  if (pid == -1)
  {
    printf("fork() failed.\n");
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  {
    close(pipefd[0]);
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
      int num = rand();

      if (write(pipefd[1], &num, sizeof(num)) == -1)
      {
        printf("write() failed\n");

        close(pipefd[1]);
        exit(EXIT_FAILURE);
      }
    }

    printf("%d random numbers created and send.\n", N);

    close(pipefd[1]);
    exit(EXIT_SUCCESS);
  }
  else
  {
    close(pipefd[1]);

    int count = 0;
    int num;

    while (read(pipefd[0], &num, seizeof(num)) > 0)
    {
      if (isPrime(num))
      {
        count++;
        printf("%d is a prime number.\n", num);
      }
    }
    printf("%d prime numbers found.\n", count);
    close(pipefd[0]);
  }

  return 0;
}