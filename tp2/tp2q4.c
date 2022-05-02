#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

void f(int sig){
  printf("that one\n");
  exit(0);
}

int main(){
  srand(time(NULL));
  signal(SIGALRM, f);
  int i, r = (rand() % 6) + 1;
  alarm(r);
  for(i = 1; i <= 5; i++){
    printf("%d\n", i);
    sleep(1);
  }
  return 0;
}
