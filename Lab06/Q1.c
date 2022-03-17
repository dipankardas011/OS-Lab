/**
 * parent process has to wait till the complete of all the child process so that no child process will become orphan
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>

int main(int argc, char *argv[]) {
	int N;
	printf("Enter the number of child processes to be created: ");
	scanf("%d",&N);
	pid_t t = 0;

	for (int i = 0; i<N;i++) {
		t = fork();
		assert(t >= 0);
		if (t == 0) {
			printf("Child Process pid: %d\tppid: %d\n",getpid(), getppid());
			exit(0);
		} else {
			printf("Parent Process pid: %d\tppid: %d\n",getpid(), getppid());
			//wait(NULL);
		}
	}
	while (wait(NULL) != -1);
	remove(argv[0]);
	return 0;
}
