#include <stdio.h>
#include <unistd.h>

#include <signal.h>

int main(int argc, char** argv)
{
    printf("ppid - %d\n", getpid());

    signal(SIGINT, SIG_IGN);

    while (1)
    {
        puts("kill me");
    }

    return 0;
}

