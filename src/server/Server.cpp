#include "../../headers/server/Server.h"

int count = 0;

void *clientThread(void *arg);

void runServer(int port) {
    int re = 0;

    int server_sck = socket(AF_INET, SOCK_STREAM, 0);
    errorHandler(server_sck, (char *)"Initialize server socket failed");

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    re = bind(server_sck, (sockaddr *)&addr, sizeof(addr));
    errorHandler(re, (char *)"Binding failed");

    re = listen(server_sck, QUEUE);
    errorHandler(re, (char *)"Listening failed");

    std::vector<pthread_t> tids;

    int pots_temp_b[5] = {0, 0, 0, 0, 0};
    int *pot_pb = (int *)calloc(sizeof(int), 5);
    pot_pb = pots_temp_b;

    int pots_temp_p[5] = {0, 0, 0, 0, 0};
    int *pot_pp = (int *)calloc(sizeof(int), 5);
    pot_pp = pots_temp_p;

    while (true) {
        ClientData *client = (ClientData *)calloc(sizeof(ClientData), 1);
        socklen_t clientSize = sizeof(client->addr);
        client->potsAreBrewing = pot_pb;
        client->potsArePooring = pot_pp;
        client->sck = accept(server_sck, (sockaddr *)&client->addr, &clientSize);

        while (count >= 5) {
        }

        pthread_t tid;
        re = pthread_create(&tid, NULL, clientThread, client);
        errorHandler(re, (char *)"Create thread failed");

        tids.push_back(tid);
    }
}

void *clientThread(void *arg) {
    count++;
    ClientData *client = (ClientData *)arg;
    clientHandler(client);
    count--;
    pthread_exit(0);
}
