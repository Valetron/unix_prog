#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "handle.h"

#define PORT 12345

char* handleInput(char* input);

int main()
{
    int sckt;
    struct sockaddr_in address;
    char userInput[128];
    char respons[128];
    
    sckt = socket(AF_INET, SOCK_STREAM, 0);
    
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    
    connect(sckt, (struct sockaddr*) &address, sizeof(address));

    while (1)
    {
        printf(">> ");
        fgets(userInput, sizeof(userInput), stdin); // FIXME: fflush(stdin) not works

        if (0 == strcmp(userInput, "/exit\n\0"))
        {
            puts("Bye bye!");
            break;
        }

        write(sckt, userInput, sizeof(userInput));
        read(sckt, respons, sizeof(userInput));

        printf("Server: %s", respons);
    }

    close(sckt);

    return 0;
}

