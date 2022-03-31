#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

int main() {
  int fd[2];
  char message[10] = {0};
  assert(pipe(fd) == 0);
  write (fd[1], "Hello", 5);
  read(fd[0], &message, 5);
  printf("%s\n", message);

  write(fd[1], "World", 5);
  read(fd[0], &message, 5);
  printf("%s\n", message);
}