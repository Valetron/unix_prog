#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

#include "handle.h"

#define PORT 12345

void setAddress(struct sockaddr_in* addr);

int main(void)
{
    int srvSocket;
    int clntSize;
    int msgBytes;
    char msg[128];
    const char* SERVER_NAME = "/tmp/test_unix.socket";
    struct sockaddr_un srvAddr;
    struct sockaddr_un clntAddr;

    srvSocket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (srvSocket < 0)
        handle("Error in socket()");

    srvAddr.sun_family = AF_UNIX;
    strncpy(srvAddr.sun_path, SERVER_NAME, sizeof(srvAddr.sun_path) - 1);

    unlink(SERVER_NAME);
    if (bind(srvSocket, (struct sockaddr*)&srvAddr, sizeof(srvAddr)) < 0)
        handle("Error in bind()");
    
    puts("[Server] Listening...");

    clntSize = sizeof(clntAddr);
//    signal(SIGCHLD, SIG_IGN);

    while(1)
    {
        
        if (recvfrom(srvSocket, msg, sizeof(msg), 0, (struct sockaddr*) &clntAddr, &clntSize) < 0)
        {
            handle("Error in recvfrom()");
            break;
        }

        printf("Client: %s", msg);
        if (sendto(srvSocket, msg, strlen(msg), 0, (struct sockaddr*)&clntAddr, clntSize) < 0)
        {
            handle("Error in sendto()");
            break;
        }
    }

    unlink(SERVER_NAME);

    return EXIT_SUCCESS;
}

