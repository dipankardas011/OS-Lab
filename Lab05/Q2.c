/**
 * @Assumption 
 *    that there are 6 processes
 *    input is given in sorted order i.e. inorder traversal
 * @input
 * 0 0 2
 * 1 0 0
 * 1 1 2
 * 2 0 0
 * 2 1 1
 * 3 0 0
 * @example
 *           P1 {0,0,2}
 *          / \
 * {1,0,0} P2  P3 {1,1,2}
 *            /  \
 *   {2,0,0} P4  P5 {2,1,1}
 *               |
 *              P6 {3,0,0}
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define NOPROC 6

struct procContent{
  int level, idx, children;
};

struct procContent proc[NOPROC];

void createProcess(int index) {
  int nChild = proc[index].children;
  printf("P%d\t%d\t%d\n", index+1, getpid(), getppid());

  for (int i = 1; i <= nChild; i++) {
    pid_t t = fork();
    if (t == 0) {
      createProcess(index + i);
      break;
    }
  }
  wait(NULL);
}

int main(int argc, char **argv)
{
  printf("Enter the levelno, indexNO, number of children\n");
  for (int i = 0; i < NOPROC; i++) {
    scanf("%d %d %d", &proc[i].level, &proc[i].idx, &proc[i].children);
  }

  printf("Process\tPID\tPPID\n");
  createProcess(0);

  wait(NULL);
  remove(argv[0]);
  return EXIT_SUCCESS;
}