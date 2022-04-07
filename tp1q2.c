#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
  pid_t p;
  p=fork();

  switch(p){
  case(0):
    //sleep(1);
    printf("Je suis le fils, mon PID est %d et mon PPID est %d\n", getpid(), getppid());
    break;
  case(-1):
    exit(EXIT_FAILURE);
  default:
    //sleep(1);
    printf("Je suis le pere, mon PID est %d, mon PPID est %d, et l'ID de mon fils est %d\n", getpid(), getppid(), p);
  }
  
  return 0;
}
