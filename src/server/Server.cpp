#include "../../headers/server/Server.h"

void *clientThread(void *arg);

void init(int port) {
    int re = 0;

    int server_sck = socket(AF_INET, SOCK_STREAM, 0);
    errorHandler(server_sck, (char *)"Initialize server socket failed");

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    // inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);

    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    re = bind(server_sck, (sockaddr *)&addr, sizeof(addr));
    errorHandler(re, (char *)"Binding failed");

    re = listen(server_sck, QUEUE);
    errorHandler(re, (char *)"Listening failed");

    int count = 0;
    std::vector<pthread_t> tids;

    while (true) {
        ClientData *client = (ClientData *)calloc(sizeof(ClientData), 1);
        socklen_t clientSize = sizeof(client->addr);

        client->sck = accept(server_sck, (sockaddr *)&client->addr, &clientSize);
        pthread_t tid;
        re = pthread_create(&tid, NULL, clientThread, client);
        errorHandler(re, (char *)"Create thread failed");

        // pthread_detach(tid);
        tids.push_back(tid);
    }
}

void *clientThread(void *arg) {
    printf("JOIND THREAD\n");

    ClientData *client = (ClientData *)arg;
    clientHandler(client);
    printf("EXITED THREAD\n");

    pthread_exit(0);
}
