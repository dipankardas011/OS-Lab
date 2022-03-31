#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("PID: %d\tPPID: %d\n",getpid(), getppid());
  int fd1[2];
  int fd2[2];
  char message[10] = {0};
  assert(pipe(fd1) == 0);
  assert(pipe(fd2) == 0);

  pid_t id = fork();
  assert(id >= 0);
  if (id > 0) {
    // parent
    close(fd1[0]);
    write(fd1[1], "Dipankar", 8);


    wait(NULL);

    close(fd2[1]);
    read(fd2[0], message, 10);
    printf("PID: %d PPID: %d\tMessage: %s\n", getpid(), getppid(), message);

  } else {

    close(fd1[1]);
    read(fd1[0], message, 10);
    printf("PID: %d PPID: %d\tMessage: %s\n", getpid(), getppid(), message);

    // second message
    write(fd2[1], "Das", 3);
  }
  return 0;
}