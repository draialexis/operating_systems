#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t PIDs[4];
    int   a = 1;
    int   b = 2;
    int   c = 3;
    int   d = 4;
    int   i;
    int   matrix[4];
    int   tmp;

    for (i = 0; i < 4; i++)
    {
        PIDs[i] = fork();
        // printf("%d\n", PIDs[i]);
        if (PIDs[i] == 0) // pid=0 ==> child
        {
            break;
        }
    }

    if (PIDs[i] == 0)
    {
        switch (i)
        {
            case (0):
                tmp = (a * a) + (b * c);
                printf("%d\t", tmp);
                break;
            case (1):
                tmp = (a * b) + (b * d);
                printf("%d\n", tmp);
                break;
            case (2):
                tmp = (a * c) + (d * c);
                printf("%d\t", tmp);
                break;
            case (3):
                tmp = (b * c) + (d * d);
                printf("%d\n", tmp);
                break;
        }
    } else if (PIDs[i] == -1)
    {
        exit(EXIT_FAILURE);
    } else
    {
        for (i = 0; i < 4; i++)
        {
            waitpid(PIDs[i], matrix + i, 0);
        }
        for (i = 0; i < 4; i++)
        {
            printf("%d ", WEXITSTATUS(matrix[i]));
        }
    }


    return 0;
}
