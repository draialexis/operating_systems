#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 1
#define READ_CHNL 0
#define WRITE_CHNL 1

int  size = 0;
char buff[N + 1];

void pipe_capac()
{
    printf("pipe capacity = %d\n", size);
    wait(NULL);
    exit(EXIT_SUCCESS);
}

int main()
{
    pid_t pid;
    int   p[2];

    for (int i = 0; i < N; ++i)
    {
        buff[i] = 'c';
    }

    if (pipe(p) == -1)
    {
        printf("pipe creating error\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == 0)
    {
        sleep(1);
        close(p[WRITE_CHNL]);
    } else if (pid > 0)
    {
        struct sigaction action_p;
        action_p.sa_handler = pipe_capac;
        sigaction(SIGPIPE, &action_p, NULL);
        while (1)
        {
            close(p[READ_CHNL]); // brutal
            write(p[WRITE_CHNL], buff, N);
            size++;
            printf("size=%d\n", size);
        }
    } else
    {
        printf("forking error\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}