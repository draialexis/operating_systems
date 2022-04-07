#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  pid_t p;
  int x = 10;
  printf("OUT(x=%d)\n", x);
  p = fork();
  switch(p){
  case(0):
    //sleep(1);
    printf("this=child, pid=%d, ppid=%d\n", getpid(), getppid());
    x += 5;
    printf("CHILD(x=%d)...(should be 15)\n", x);
    break;
  case(-1):
    exit(EXIT_FAILURE);
  default:
    sleep(1);
    printf("this=parent, pid=%d, ppid=%d, child_id=%d\n", getpid(), getppid(), p);
    x *= 15;
    printf("PARENT(x=%d)...(should be 150)\n", x);
  }
  printf("AFTER(x=%d)\n", x);
  return 0;
}
