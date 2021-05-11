#include <iostream>
#include <string>
#include <vector>

#include "../headers/server/Server.h"

int main(int atgc, char *argv[]) {
    int port = strtol("9905", NULL, 10);
    init(port);
    return 0;
}
