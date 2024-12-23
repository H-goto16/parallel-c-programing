#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  printf("私は親プロセスのmain関数です。PIDは%dです。\n", getpid());

  pid_t pid = fork();

  if (pid < 0)
  {
    printf("forkに失敗しました。\n");
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  {
    printf("私は子プロセスです。PIDは%dです。\n", getpid());
    sleep(5);
    printf("私は子プロセス%dです。これから終了します。\n", getpid());
    exit(EXIT_SUCCESS);
  }
  else
  {
    printf("私は親プロセスです。私のPIDは%d, 子プロセスのPIDは%dです。\n", getpid(), pid);
    wait(NULL);
    printf("私は親プロセス%dです。子プロセスが終了しました。\n", getpid());
  }

  printf("私のPIDは%dです。main関数を終了します。\n", getpid());
  return 0;
}