#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
  pid_t p;
  char buf[3];
  int fdesc;
  fdesc = open("tp1q4.txt", O_RDWR, 0);
  if(fdesc==-1)
  {
    exit(EXIT_FAILURE);
  }
  p=fork();
  switch(p)
  {
    case(0):
      write(fdesc, "ab", 2);
      sleep(1);
      lseek(fdesc, -2, SEEK_CUR);
      read(fdesc, buf, 2);
      buf[2] = '\0';
      printf("CHILD: %s\n", buf);
      close(fdesc);
      break;
    case(-1):
      exit(EXIT_FAILURE);
    default:
      sleep(1);
      lseek(fdesc, -2, SEEK_CUR);
      read(fdesc, buf, 2);
      buf[2] = '\0';
      printf("PARENT: %s\n", buf);
      write(fdesc, "AB", 2);
      close(fdesc);
  }
  return 0;  
  
}
