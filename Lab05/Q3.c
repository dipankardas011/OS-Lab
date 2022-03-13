#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>


int main(int argc, char const *argv[]) {
  int N;
  printf("Enter the N: ");
  scanf("%d", &N);
  int even = 0, odd = 0;
  pid_t t = fork();
  assert(t >= 0);
  if (t == 0) {
    // child
    for (int i = 1; i <= N; i++) 
      if (i & 1)
        odd += i;
    printf("Odd Sum: %d\n", odd);
    exit(0);
  }
  else {
    // parent
    for (int i = 2; i <= N; i++) 
      if (!(i & 1))
        even += i;
  }
  wait(NULL);
  printf("Even Sum: %d\n", even);
  remove(argv[0]);
  return 0;
}