#include <iostream>
#include <string>
#include <vector>

#include "../headers/server/Server.h"

int main(int atgc, char *argv[]) {
    int port = atoi(argv[1]);

    std::cout << "  WELCOME TO COFFEE POT MACHINE\n"
              << "   Enjoy Your Coffee on port (" << port << ")\n"
              << "****************************************"
              << std::endl;

    runServer(port);
    return 0;
}
