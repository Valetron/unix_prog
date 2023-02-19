#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "handle.h"

#define PORT 12345

int main()
{
    int sckt;
    struct sockaddr_in address;
    char message[128];

    sckt = socket(AF_INET, SOCK_STREAM, 0);
    
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(sckt, (struct sockaddr*)&address, sizeof(address));

//    while(1)
//    {
        printf(">> ");
        scanf("%s", message);
        printf("mmsg = %s", message);
        send(sckt, message, sizeof(message), 0);
        //recv(sckt, );
  //  }

    return 0;
}

