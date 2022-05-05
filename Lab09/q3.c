/**
 * Write a program that opens a file with open system call and then calls the folks to create a new processes
 * both the child and parent process access the file descriptor returned by open. 
 * What happens when they are writing to the file concurrently at the same time
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
  char *c = (char *) calloc(100, sizeof(char));
  /**
   * NOTE: if the open() before fork()
   * OP:
   * ((Parent))Read contents: Hi I am Dipanka
   * ((Child))Read contents: r Das
   * 
   * 
   */
  int fd = open("foo.txt", O_RDONLY | O_CREAT | O_WRONLY | O_APPEND);
  pid_t tt = fork();
  assert(tt >= 0);
  if (tt == 0) {
    // child
    int sz = read(fd, c, 22);
    c[sz] = '\0';
    printf("((Child))Read contents: %s\n", c);
    sz = write(fd, "HELLO MATRIXCH\n", strlen("HELLO MATRIXCH\n")); 

  }
  else
  {
    int sz = read(fd, c, 22);
    c[sz] = '\0';
    printf("((Parent))Read contents: %s\n", c);
    sz = write(fd, "HELLO MATRIX\n", strlen("HELLO MATRIX\n")); 
    
    wait(NULL);
  }
  close(fd);
  remove(argv[0]);
  return 0;
}
