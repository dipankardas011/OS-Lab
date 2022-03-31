#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  char message[10] = {0};
  assert(pipe(fd) == 0);

  pid_t id = fork();
  assert(id >= 0);
  if (id > 0) {
    // parent
    close(fd[0]);
    printf("Parent\n");
    write(fd[1], "Dipankar", 8);
    wait(NULL);
  } else {
    close(fd[1]);
    printf("CHild\n");
    read(fd[0], &message, 10);
    printf("Message: %s\n", message);
  }
  return 0;
}