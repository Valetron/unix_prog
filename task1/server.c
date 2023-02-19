#include <stdio.h>
#include <stdlib.h>

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
    srvAddr.sin_addr.s_addr = INADDR_ANY;
    srvAddr.sin_port = htons(PORT);

    if (bind(srvSocket, (struct sockaddr*)&srvAddr, sizeof(srvAddr)) < 0)
        handle("Error in bind()");

    if (listen(srvSocket, 1) < 0)
        handle("Error in listne()");
    
    puts("Server is listening...");

    while(1)
    {
        clntSocket = accept(srvSocket, (struct sockaddr *)&clntAddr, sizeof(clntAddr));
        // if
       msgBytes = recv(clntSocket, msg, sizeof(msg), 0);
//        send(sckt, msg, msgBytes, 0);
        puts("Client is connected... ");
        printf("Recieved - %d", msgBytes);
     //   while(1)
       // {
         //   msgBytes = recv(clntSocket, msg, sizeof(msg), 0);
           // send(clntSocket, msg, msgBytes, 0);
        //}
    }

    close(sckt);

    return EXIT_SUCCESS;
}

void setAddress(struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(PORT);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
}

