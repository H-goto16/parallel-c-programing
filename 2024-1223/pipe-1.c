#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

int main(void)
{
  // パイプのファイルディスクリプタ
  int pipefd[2];

  pipe(pipefd);

  pid_t pid = fork();

  if (pid == 0)
  {
    close(pipefd[0]);

    for (int i = 0; i < N; i++)
    {
      write(pipefd[1], &i, sizeof(i));
    }

    close(pipefd[1]);
    printf("子プロセスが終了します。\n");
  }
  else
  {
    close(pipefd[1]);
    int num;
    while (read(pipefd[0], &num, sizeof(num)) > 0)
    {
      printf("%dを受信しました。\n", num);
    }
    close(pipefd[0]);

    wait(NULL);

    printf("親プロセスが終了します。\n");
    while (read(pipefd[0], &num, sizeof(num)) > 0)
    {
      printf("%dを受信しました。\n", num);
    }

    return 0;
  }
}