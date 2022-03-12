#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  printf("NAME\tPID\tPPID\n");
  for (int i = 0; i < 4; i++) {
    printf("P%d\t%d\t%d\n",i+1, getpid(), getppid());
    pid_t t = fork();
    assert(t >= 0);
    if (t != 0)
      break;
  }

  wait(NULL);
  remove(argv[0]);
  return EXIT_SUCCESS;
}