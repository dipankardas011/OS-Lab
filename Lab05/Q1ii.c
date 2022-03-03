#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  
  for (int i = 0; i < 4; i++)
  {
    printf("P%d\n",i+1);
    pid_t t = fork();
    assert(t >= 0);
    if (t != 0)
      exit(0);
  }

  wait(NULL);
  remove(argv[0]);
  return EXIT_SUCCESS;
}