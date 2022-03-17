/**
 * create 2 child process c1, c2 make sure that only c1 becomes orphan process
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>

int main (int argc, char *argv[]) {
	pid_t t = 0;
	printf("Parent process pid: %d\tppid: %d\n",getpid(), getppid());
	t = fork();
	assert(t >= 0);

	if (t == 0) {
		printf("Child 2 pid: %d\tppid: %d\n", getpid(), getppid());
		exit(0);
	} else {
		wait(NULL);
	}

	t = fork();
	assert(t >= 0);
	if (t == 0) {
		printf("Child 1 pid: %d\tppid: %d\n", getpid(), getppid());
	}
	remove(argv[0]);
	return 0;
}
