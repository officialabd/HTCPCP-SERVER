#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#define CHAR_SIZE 1
#define ERROR -1

/**
 * Stores all data of the client and pots needed by coffee pot.
 */
struct ClientData {
    sockaddr_in addr;
    int sck;
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    int* potsAreBrewing;
    int* potsArePooring;
};

/**
 * Handles the client socket, sending and receiving.
 * @param client stores all data required.
 * @return No return value (void).
 */
void clientHandler(ClientData* client);

/**
 * Sends a message to the client on the socket.
 * @param socket the socket of the client.
 * @param buf the message to be sent to the client.
 * @param flags to specify the sending options. 
 * @return No return value (void).
 */
void send(int socket, char* buf, int flags);

/**
 * Receive a message from the client on the socket.
 * @param socket the socket of the client.
 * @param buf the received message from the client.
 * @param flags to specify the receiving options. 
 * @return String of the received message.
 */
char* receive(int socket, char* buf, int flags);

/**
 * Checks the connected clients.
 * @param client Client data (socket, address, ...).
 * @return No return value (void).
 */
void checkConnection(ClientData* client);