#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "handle.h"

#define PORT 12345

void setAddress(struct sockaddr_in* addr);

int main(void)
{
    int srvSocket;
    int clntSocket;
    int msgBytes;
    char msg[128];
    struct sockaddr_in srvAddr;

    srvSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (srvSocket < 0)
        handle("Error in socket()");

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(PORT);
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(srvSocket, (struct sockaddr*)&srvAddr, sizeof(srvAddr)) < 0)
        handle("Error in bind()");

    if (listen(srvSocket, 3) < 0)
        handle("Error in listen()");
    
    puts("[Server] Listening...");

    signal(SIGCHLD, SIG_IGN);

    while(1)
    {
        clntSocket = accept(srvSocket, NULL, NULL);
        if (0 == fork())
        {
            while (1)
            {
                msgBytes = recv(clntSocket, msg, sizeof(msg), 0);
                if (0 == msgBytes) 
                {
                    puts("Client disconnected");
                    break;
                }

                printf("Client: %s", msg);
                send(clntSocket, msg, msgBytes, 0);
            }
            close(clntSocket);
            exit(0);
        }
    }

    close(srvSocket);

    return EXIT_SUCCESS;
}

