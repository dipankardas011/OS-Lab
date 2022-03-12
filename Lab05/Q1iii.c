#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sys/wait.h>

void f() {
  pid_t tt = fork();
  if ( tt == 0) {
    for (int i = 5; i < 8; i++)
    {
      printf("P%d\t%d\t%d\n",i, getpid(), getppid());
      tt = fork();
      if (tt == 0)
        exit(0);
    }
  }
  wait(NULL);
}

int main(int argc, char **argv) {

  pid_t t = 0;
  printf("NAME\tPID\tPPID\n");
  printf("P1\t%d\t%d\n", getpid(), getppid());
  for (int i = 1; i <= 4; i++)
  {
    t = fork();
    assert(t >= 0);

    if (t == 0) {
      if ( i != 1 )
        printf("P%d\t%d\t%d\n",i, getpid(), getppid());
      if (i == 3) {
        f();
      }
      break;
    }
  }
  

  wait(NULL);
  remove(argv[0]);
  return EXIT_SUCCESS;
}
