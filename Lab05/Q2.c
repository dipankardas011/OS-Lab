#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

  wait(NULL);
  remove(argv[0]);
  return EXIT_SUCCESS;
}