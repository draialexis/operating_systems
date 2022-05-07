#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int x = 0;

void f()
{
    printf("that one : %d\n", x + 1); // [0; 4] -> [1; 5]
    exit(0);
}

int main()
{
    struct sigaction sigact;

    sigact.sa_handler = f;
    sigemptyset(&sigact.sa_mask);
    sigaction(SIGALRM, &sigact, NULL);

    alarm(1);
    while (1) x = (x + 1) % 5;
    return 0;
}
