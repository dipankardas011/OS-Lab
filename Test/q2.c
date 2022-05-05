#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
  pid_t t = fork();
  if (t == 0) {
    printf("I am student of CSE branch\n");
  } else {
    sleep(2);
    printf("My roll no is 20051554\n");
  }
  return 0;
}
