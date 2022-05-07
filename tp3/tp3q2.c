#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N_MSG 2
#define CHAR_BUF 20
#define READ_CHNL 0
#define WRITE_CHNL 1

int main()
{
    int   pipefds[N_MSG];
    pid_t pid;

    char write_msgs[N_MSG][CHAR_BUF] = {"Hi", "Hello"};
    char read_msgs[CHAR_BUF];

    if (pipe(pipefds) == -1)
    {
        printf("pipe creation error\n");
        return 1;
    }

    pid = fork();

    if (pid == 0)
    {
        for (int i = 0; i < N_MSG; ++i)
        {
            read(pipefds[READ_CHNL], read_msgs, sizeof(read_msgs));
            printf("child; reading; msg%d is %s\n", i + 1, read_msgs);
        }
    } else if (pid > 0)
    {
        for (int i = 0; i < N_MSG; ++i)
        {
            write(pipefds[WRITE_CHNL], write_msgs[i], sizeof(write_msgs[i]));
            printf("parent; writing; msg%d is %s\n", i + 1, write_msgs[i]);
        }
    } else
    {
        printf("forking error\n");
        return 1;
    }
    return 0;
}