#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#define MAX_ERROR_MESSAGE 1024
#define ERROR -1
#define CHAR_SIZE 1

/**
 * Prints the message error to the output, that checks if val is -1 then there is error
 * @param val int for the error.
 * @param err the error message.
 * @return No return value (void).
 */
void errorHandler(int val, char *err);
