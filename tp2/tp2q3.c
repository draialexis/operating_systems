#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t p;
  int status;
  printf("starting...\n");
  p = fork();
  switch(p){
  case 0:
    printf("child 1\n");
    sleep(1);
    kill(getppid(), SIGCONT);
    kill(getpid(), SIGSTOP);
    printf("child 2\n");
    sleep(1);
    kill(getppid(), SIGCONT);
    break;
  case -1:
    perror("fork error\n");
    exit(-1);
  default:
    kill(getpid(), SIGSTOP);
    printf("parent 1\n");
    sleep(1);
    kill(p, SIGCONT);
    kill(getpid(), SIGSTOP);
    printf("parent 2\n");
    wait(&status);
    exit(0);
    break;
  }
  return 0;
}
