#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    int sckt;
    int msgBytes;
    char msg[128];
    struct sockaddr_in srvAddr;
    struct sockaddr_in clntAddr;

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

    clntSocket = accept(srvSocket, NULL, NULL);

    while(1)
    {
//        clntSocket = accept(srvSocket, (struct sockaddr *)&clntAddr, sizeof(clntAddr));

            msgBytes = recv(clntSocket, msg, sizeof(msg), 0);
            printf("Client: %s", msg);
//            write(STDOUT_FILENO, msg, msgBytes);
            send(clntSocket, msg, msgBytes, 0);
        //close(clntSocket);
    }

    close(clntSocket);
    close(srvSocket);

    return EXIT_SUCCESS;
}

