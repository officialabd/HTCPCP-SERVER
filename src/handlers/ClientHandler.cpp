#include "../../headers/handlers/ClientHandler.h"

void clientHandler(ClientData* client) {
    char* buf = (char*)calloc(sizeof(char), MAX_MESSAGE_SIZE);

    checkConnection(client);
    while (true) {
        memset(buf, 0, MAX_MESSAGE_SIZE);

        if (receive(client->sck, buf, 0) != NULL) {
            if (strlen(buf) > 0) {
                std::cout << buf << std::endl;
                send(client->sck, buf, 0);
            }
        } else {
            break;
        }
    }
    free(buf);
    close(client->sck);
}

void send(int socket, char* buf, int flags) {
    if (send(socket, buf, strlen(buf), flags) == ERROR) {
        perror("Server (sending failed)");
    }
}

char* receive(int socket, char* buf, int flags) {
    if (recv(socket, buf, MAX_MESSAGE_SIZE, flags) == 0) {
        std::cout << "Client disconnected " << std::endl;
        return NULL;
    } else {
        return buf;
    }
}

int checkConnection(ClientData* client) {
    int re = getnameinfo((sockaddr*)&client, sizeof(client), client->host, NI_MAXHOST, client->service, NI_MAXSERV, 0);
    if (re == 0) {
        std::cout << client->host << " connected on port " << client->service << std::endl;
        return 1;
    } else {
        inet_ntop(AF_INET, &client->addr.sin_addr, client->host, NI_MAXHOST);
        std::cout << client->host << " connected on port " << ntohs(client->addr.sin_port) << std::endl;
        return 1;
    }
}