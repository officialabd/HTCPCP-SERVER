#include "../../headers/handlers/ClientHandler.h"

#include "../../headers/parser/Parser.h"

void* parsingThread(void* arg);

void clientHandler(ClientData* client) {
    std::cout << "-------------------------------------->>" << std::endl;

    char* buf = (char*)calloc(sizeof(char), MAX_MESSAGE_SIZE);

    checkConnection(client);
    ParserData* pd = (ParserData*)calloc(sizeof(ParserData), 1);
    pd->isItBrewing = false;
    pd->sck = client->sck;
    pd->message = (char*)calloc(sizeof(char), MAX_MESSAGE_SIZE);
    pd->potsAreBrewing = client->potsAreBrewing;
    pd->potsArePooring = client->potsArePooring;

    while (true) {
        memset(buf, 0, MAX_MESSAGE_SIZE);
        pthread_t tid = 0;
        if (receive(client->sck, buf, 0) != NULL) {
            std::cout << "-----------------//\n"
                      << buf << "\n//-----------------" << std::endl;
            strcpy(pd->message, buf);

            pthread_create(&tid, NULL, parsingThread, pd);
            sleep(1);
        } else {
            break;
        }
    }
    std::cout << "<<--------------------------------------" << std::endl;

    free(buf);
    close(client->sck);
}

void* parsingThread(void* arg) {
    ParserData* pd = (ParserData*)arg;
    send(pd->sck, parse(pd), 0);
    pthread_exit(0);
}

void send(int socket, char* buf, int flags) {
    if (send(socket, buf, strlen(buf), flags) == ERROR) {
        perror("Server (sending failed)");
    }
}

char* receive(int socket, char* buf, int flags) {
    if (recv(socket, buf, MAX_MESSAGE_SIZE, flags) == 0) {
        std::cout << "\nClient disconnected\n"
                  << std::endl;
        return NULL;
    } else {
        return buf;
    }
}

void checkConnection(ClientData* client) {
    int re = getnameinfo((sockaddr*)&client, sizeof(client), client->host, NI_MAXHOST, client->service, NI_MAXSERV, 0);
    if (re == 0) {
        std::cout << client->host << " connected on port " << client->service << std::endl
                  << std::endl;

    } else {
        inet_ntop(AF_INET, &client->addr.sin_addr, client->host, NI_MAXHOST);
        std::cout << client->host << " connected on port " << ntohs(client->addr.sin_port) << std::endl
                  << std::endl;
    }
}