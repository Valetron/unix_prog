#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <signal.h>

int num;

void handler(int sig)
{
    FILE* file = fopen("file.txt", "wb");
    char strNum[1];

    puts("Writing a number...");

    fwrite(&num, sizeof(int), 1, file);
    fclose(file);

    exit(0);
}

int main(int argc, char** argv)
{
    // signal(SIGINT, SIG_IGN);
    signal(SIGINT, handler);

    FILE* file = fopen("file.txt", "rb");

    fread(&num, sizeof(int), 1, file);
    printf("last number - %d\n", num);
    fclose(file);

    while (1)
    {
        printf("%d\n", num++);
        sleep(1);
    }

    return 0;
}

