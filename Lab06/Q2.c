/**
 * create 2 child process c1, c2 make sure that only c1 becomes orphan process
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	pid_t t = 0;
	printf("Parent process pid: %d\tppid: %d\n", getpid(), getppid());

	t = fork();

	if (t == 0) {
		printf("Child 2 pid: %d\tppid: %d\n", getpid(), getppid());
		exit(0);
	}
	
	while (wait(NULL) != -1);
	

	t = fork();
	if (t > 0)
		exit(0);
		
	sleep(1);
	printf("Child 1 pid: %d\tppid: %d\n", getpid(), getppid());
	

	return 0;
}
