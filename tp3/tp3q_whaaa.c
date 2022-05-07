#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

#define RESET_COLOR "\033[0m"
#define RED "\033[1m\033[31m"
#define WHITE "\033[1m\033[37m"

#define MSG_SIZE 65536

struct message_
{
    char msg_txt[MSG_SIZE];
} typedef msg;

void error_display(char *culprit)
{
    printf(RED "%s error\n" RESET_COLOR, culprit);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{

    pid_t pid;
    int   status;
    int   tmp_count;
    int   count = 0;
    int   is_go = 1;

    int msgqid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    if (msgqid == -1) error_display("msgget");

    printf(WHITE "msgqid = %d\n" RESET_COLOR, msgqid);
    pid = fork();

    switch (pid)
    {
        case (-1):
            error_display("fork");
            break;

        case (0):
            sleep(1);
            printf(WHITE "child; data: \n" RESET_COLOR);
            printf("PID\tPPID\tUID\tGID\n");
            printf("%d\t%d\t%d\t%d\n\n", getpid(), getppid(), getuid(), getgid());
            msg msg2;

            while (is_go)
            {
                tmp_count = msgrcv(msgqid, &msg2, MSG_SIZE, 0, 0);
                if (tmp_count == -1) error_display("msgrcv");
                if (strcmp(msg2.msg_txt, "exit") != 0)
                {
                    count += tmp_count;
                    printf("child; received: %s\n", msg2.msg_txt);
                } else
                {
                    is_go = 0;
                }
                sleep(1);
            }
            printf("\n%d bytes received in total\n", count);
            printf("child: terminating\n");
            break;

        default:
            printf(WHITE "parent; data: \n" RESET_COLOR);
            printf("PID\tPPID\tUID\tGID\n");
            printf("%d\t%d\t%d\t%d\n\n", getpid(), getppid(), getuid(), getgid());
            sleep(1);

            msg msg1;
            msg1.msg_type = 10;

            printf("\nenter content, enter 'exit' to exit\n");

            while (strcmp(msg1.msg_txt, "exit\n") != 0)
            {
                sleep(1);
                printf("\n>_");
                fgets(msg1.msg_txt, MSG_SIZE, stdin);

                if (msgsnd(msgqid, &msg1, (strlen(msg1.msg_txt) * sizeof(char)) + 1, 0) == -1)
                {
                    error_display("msgsnd");
                }
            }
            sleep(1);
            if (msgctl(msgqid, IPC_RMID, NULL) == -1) error_display("msgctl");
            if (wait(&status) == -1) error_display("wait");
            printf("parent: terminating\n");
            break;
    }

    printf("Fin du processus %d\n\n", getpid());

    exit(EXIT_SUCCESS);
}
