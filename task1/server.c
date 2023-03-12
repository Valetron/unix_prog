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
    socklen_t clntSize;
    int msgBytes;
    char msg[128];
    const char* SERVER_NAME = "/tmp/server_unix.socket";
    struct sockaddr_un* srvAddr;
    struct sockaddr_un* clntAddr;

    srvSocket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (srvSocket < 0)
        handle("Error in socket()");

    unlink(SERVER_NAME);
    srvAddr = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
    srvAddr->sun_family = AF_UNIX;
    strcpy(srvAddr->sun_path, SERVER_NAME);

    if (bind(srvSocket, (struct sockaddr*)srvAddr, sizeof(struct sockaddr_un)) < 0)
        handle("Error in bind()");
    
    puts("[Server] Listening...");

//    signal(SIGCHLD, SIG_IGN);
    clntAddr = (struct sockaddr_un* )malloc(sizeof(struct sockaddr_un));
    clntSize = sizeof(struct sockaddr_un);

    while(1)
    {
        int bytesReceived = recvfrom(srvSocket, msg, sizeof(msg), 0, (struct sockaddr*) clntAddr, &clntSize);
        if (bytesReceived < 0)
        {
            handle("Error in recvfrom()");
            break;
        }

        printf("Client: %s", msg);
        if (sendto(srvSocket, msg, sizeof(msg), 0, (struct sockaddr*) clntAddr, clntSize) == -1)
        {
            handle("Error in sendto()");
            break;
        }
    }

    unlink(SERVER_NAME);

    return EXIT_SUCCESS;
}

