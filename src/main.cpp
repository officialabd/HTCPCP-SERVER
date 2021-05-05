#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#define PORT 9909
#define QUEUE 10

void errorHandler(int val, char *str);

struct ClientData {
    sockaddr_in addr;
    int sck;
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
};

int main() {
    int re = 0;
    // Create a socket
    int server_sck = socket(AF_INET, SOCK_STREAM, 0);
    errorHandler(server_sck, (char *)"Initialize server socket failed");
    std::cout << "1" << std::endl;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);

    // Binding address and port to the socket
    re = bind(server_sck, (sockaddr *)&addr, sizeof(addr));
    errorHandler(re, (char *)"Binding failed");

    // Winsock for listening
    re = listen(server_sck, SOMAXCONN);
    errorHandler(re, (char *)"Listening failed");

    // Wait for a client to connect
    ClientData client;
    socklen_t clientSize = sizeof(client.addr);

    client.sck = accept(server_sck, (sockaddr *)&client.addr, &clientSize);

    memset(client.host, 0, NI_MAXHOST);
    memset(client.service, 0, NI_MAXSERV);

    re = getnameinfo((sockaddr *)&client, sizeof(client), client.host, NI_MAXHOST, client.service, NI_MAXSERV, 0);
    if (re == 0) {
        std::cout << client.host << " connected on port " << client.service << std::endl;
    } else {
        inet_ntop(AF_INET, &client.addr.sin_addr, client.host, NI_MAXHOST);
        std::cout << client.host << " connected on port " << ntohs(client.addr.sin_port) << std::endl;
    }

    // Close listening socket
    close(server_sck);

    // While loop: accept and echo message back to client
    char buf[4096];

    while (true) {
        memset(buf, 0, 4096);

        // Wait for client to send data
        re = recv(client.sck, buf, 4096, 0);
        errorHandler(re, (char *)"recv failed");

        if (re == 0) {
            std::cout << "Client disconnected " << std::endl;
            break;
        }

        std::cout << buf << std::endl;

        // Echo message back to client
        re = send(client.sck, buf, re + 1, 0);
        errorHandler(re, (char *)"send failed");
    }

    // Close the socket
    close(client.sck);

    return 0;
}

void errorHandler(int val, char *str) {
    if (val == -1) {
        perror(str);
        exit(1);
    }
}