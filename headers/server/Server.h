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

#include "../handlers/ClientHandler.h"
#include "../handlers/ErrorHandler.h"

#define QUEUE 5

/**
 * It initializes the server on the port and run it to accept client. For each client it create a thread to handle the client.
 * @param port int of the port, to run the server on.
 * @return No return value (void).
 */
void runServer(int port);
