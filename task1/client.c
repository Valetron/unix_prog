#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#include "handle.h"

#define PORT 12345

char* handleInput(char* input);

int main()
{
    int sckt;
    int srvSize;
    struct sockaddr_un address;
    struct sockaddr_un server;
    char userInput[128];
    char respons[128];
    const char* SERVER_NAME = "/tmp/test_unix.socket";
    const char* CLIENT_NAME = "/tmp/client_socket.socket";

    sckt = socket(AF_UNIX, SOCK_DGRAM, 0);
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, CLIENT_NAME, sizeof(address) - 1); 
    
    server.sun_family = AF_UNIX;
    strncpy(server.sun_path, SERVER_NAME, sizeof(address) - 1);

    srvSize = sizeof(server);

    while (1)
    {
        printf(">> ");
        fgets(userInput, sizeof(userInput), stdin); // FIXME: fflush(stdin) not works

        if (0 == strcmp(userInput, "/exit\n\0"))
        {
            puts("Bye bye!");
            break;
        }

        sendto(sckt, userInput, strlen(userInput), 0, (struct sockaddr *)&server, sizeof(server));
        recvfrom(sckt, respons, sizeof(respons), 0, (struct sockaddr*) &server, &srvSize);

        printf("Server: %s", respons);
    }

    close(sckt);

    return 0;
}

