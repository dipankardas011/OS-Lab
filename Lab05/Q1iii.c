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
      printf("P%d\n",i);
      tt = fork();
      if (tt == 0)
        exit(0);
    }
  }
  wait(NULL);
}

int main(int argc, char **argv) {

  pid_t t = 0;
  for (int i = 1; i <= 4; i++)
  {
    printf("P%d\n", i);
    t = fork();
    assert(t >= 0);
    
    if (t == 0) {
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