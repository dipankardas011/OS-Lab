#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("PID: %d\tPPID: %d\n",getpid(), getppid());
  int fd[2];
  char message[10] = {0};
  assert(pipe(fd) == 0);

  pid_t id = fork();
  assert(id >= 0);
  if (id > 0) {
    // parent
    close(fd[0]);
    printf("PID: %d PPID: %d\tParent\n", getpid(), getppid());
    write(fd[1], "Dipankar", 8);
    wait(NULL);
  } else {
    close(fd[1]);
    printf("CHild\n");
    read(fd[0], &message, 10);
    printf("PID: %d PPID: %d\tMessage: %s\n", getpid(), getppid(), message);
  }
  return 0;
}