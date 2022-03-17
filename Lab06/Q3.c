#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	for (int i = 1; i <= 2; i++) {
		pid_t t = fork();
		
		assert(t >= 0);

		if ( i == 1 ) {
			if (t > 0) {
				sleep(2);
				printf("Parent process pid:%d\tppid:%d\n", getpid(), getppid());
				wait(NULL);
			}else{
				printf("Child process pid: %d\tppid: %d\n", getpid(), getppid());
				exit(0);
			}
		}else {
			system("ps -To pid,ppid,stat,cmd");
			if (t > 0) {
				sleep(0.2);
				printf("Parent process pid:%d\tppid:%d\n", getpid(), getppid());
				wait(NULL);
			} else {
				sleep(1);
				printf("Child process pid: %d\tppid: %d\n", getpid(), getppid());
			}
		}
	}
	return 0;
}
