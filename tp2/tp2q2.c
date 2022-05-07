#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void f(int sig)
{
    int status;
    printf("zombie child deleted = %d\n", wait(&status));
}

void derail(int sig)
{
    struct sigaction handler;
    handler.sa_handler = f;
    printf("signal %d received and derailed by parent\n", sig);
    if (sigaction(sig, &handler, NULL) == -1)
    {
        perror("sigaction error\n");
        exit(-1);
    }
}

int main()
{
    pid_t p;
    derail(SIGCHLD);
    p = fork();

    switch (p)
    {
        case 0:
            printf("child %d\n", getpid());
            //SIGCHLD is sent to the parent process
            //f is called because of the sigaction() call in derail()
            break;
        case -1:
            perror("fork error\n");
            exit(-1);
        default:
            while (1)
            {
                printf("working...\n");
                sleep(1);
            }
    }
    return 0;
}
