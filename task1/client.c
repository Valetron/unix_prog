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
    socklen_t srvSize;
    struct sockaddr_un* client;
    struct sockaddr_un* server;
    char userInput[128];
    char response[128];
    const char* SERVER_NAME = "/tmp/server_unix.socket";
    const char* CLIENT_NAME = "/tmp/client_unix.socket";

    sckt = socket(AF_UNIX, SOCK_DGRAM, 0);
    client = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
    remove(CLIENT_NAME);
    client->sun_family = AF_UNIX;
    strcpy(client->sun_path, CLIENT_NAME); 

    if (bind(sckt, (struct sockaddr*)client, sizeof(struct sockaddr_un)) < 0)
        handle("error in bind()");

    server = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
    server->sun_family = AF_UNIX;
    strcpy(server->sun_path, SERVER_NAME);

    srvSize = sizeof(struct sockaddr_un);
    
    while (1)
    {
        printf(">> ");
        fgets(userInput, sizeof(userInput), stdin); // FIXME: fflush(stdin) not works

        if (0 == strcmp(userInput, "/exit\n\0"))
        {
            puts("Bye bye!");
            break;
        }

        int bytesSent = sendto(sckt, userInput, strlen(userInput), 0, (struct sockaddr *)server, srvSize);
        //recvfrom(sckt, respons, sizeof(respons), 0, (struct sockaddr*) &server, &srvSize);
        recvfrom(sckt, response, sizeof(response), 0, NULL, NULL);

        printf("Server: %s", response);
    }

    close(sckt);

    return 0;
}

