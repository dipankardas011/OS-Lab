#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  printf("P1\n");
  for (int i = 1; i < 4; i++)
  {
    pid_t t = fork();
    if (t == 0) {
      printf("P%d\n", i+1);
      exit(0);
    }
  }

  wait(NULL);
  remove(argv[0]);
  return EXIT_SUCCESS;
}