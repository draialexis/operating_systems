#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
  pid_t PIDs[4];
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int i;
  int matrix[4];
  int tmp;

  for(i = 0; i < 4; i++){
    PIDs[i] = fork();
    // printf("%d\n", PIDs[i]);
    if(PIDs[i] == 0){
      break;
    }
  }

  if(PIDs[i] == 0){
    printf("here we go\n");
    switch(i){
    case(0):
      tmp = (a*a)+(b*c);
      printf("0:%d\n", tmp);
    case(1):
      tmp = (a*b)+(b*d);
      printf("1:%d\n", tmp);
    case(2):
      tmp = (a*c)+(d*c);
      printf("2:%d\n", tmp);
    case(3):
      tmp = (b*c)+(d*d);
      printf("3:%d\n", tmp);
    }
  }
  else if(PIDs[i] == -1){
    exit(EXIT_FAILURE);
  } else {
    for(i = 0; i < 4; i++){
      waitpid(PIDs[i], matrix + i, 0);
    }
    // for(i = 0; i < 4; i++){
    //   printf("%d ", WEXITSTATUS(matrix[i]));
    // }
  }

  
  return 0;
}
