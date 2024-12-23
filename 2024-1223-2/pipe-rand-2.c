#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

#define FIFO_PATH "mypipe"
#define N 1000

int main(void)
{
  mkfifo(FIFO_PATH, 0666);
  int fd = open(FIFO_PATH, O_WRONLY);
  if (fd == -1)
  {
    printf("open() failed\n");
    exit(EXIT_FAILURE);
  }
  srand(time(NULL));

  int num;

  for (int i = 0; i < N; i++)
  {
    num = rand();
    if (write(fd, &num, sizeof(num)) == -1)
    {
      printf("write() failed\n");
      close(fd);
      exit(EXIT_FAILURE);
    }
  }

  printf("%d random numbers created and sent.\n", N);
  close(fd);

  return 0;
}