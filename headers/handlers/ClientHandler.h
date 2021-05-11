#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#define ERROR -1
#define MAX_MESSAGE_SIZE 4096

struct ClientData {
    sockaddr_in addr;
    int sck;
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
};

void clientHandler(ClientData* client);

void send(int socket, char* buf, int flags);

char* receive(int socket, char* buf, int flags);

int checkConnection(ClientData* client);