
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>

#include "../parser/ErrorResponse.h"

#define ALLOC(pointer, size) (pointer) = (char *)calloc((size), sizeof(*pointer))
#define MAX_MESSAGE_SIZE 4096
#define BREW "BREW"
#define POST "POST"
#define PROPFIND "PROPFIND"
#define HTCPCP_VERSION "HTCPCP/1.0"
#define NBREW 1
#define NPOST 2
#define NPROPFIND 3

#define METHOD 0
#define POT_NUM 1
#define SERVER 2
#define ADDS_HEADER 3
#define ADDS 4
#define TYPE_HEADER 5
#define TYPE 6
#define SIZE_HEADER 7
#define SIZE 8
#define CRLF 9
#define BODY 10

#define NPOORING 1
#define NBREWING 1
#define NO "-"
#define YES "YES"

#define BREWING_TIME 5
#define POORING_TIME 2

/**
 * Stores all data needed be parser.
 */
struct ParserData {
    int sck;
    char *message;
    bool isItBrewing;
    bool isItPooring;
    int *potsAreBrewing;
    int *potsArePooring;
};

/**
 * This function parse the client request and maintain the response.
 * @param pd Stores the data of all pots and message and the socket.
 * @return String The response.
 */
char *parse(ParserData *pd);

/**
 * This function parse the client additions.
 * @param additions String of all additions.
 * @param bodyResponse if no addition found stores the list of the additions available in bodyResponse, otherwise do nothing with bodyResponse.
 * @return int response code number.
 */
int parseAdditions(char *additions, char *bodyResponse);

/**
 * This function checks if addition (temp) exits.
 * @param temp temp string of the addition. 
 * @return boolean if it exits or not.
 */
bool findAddition(const char *temp);

/**
 * This function takes all data required to build the response to the client.
 * @param pd Stores the data of all pots and message and the socket.
 * @param potnum The current used potnum.
 * @param status_code Used to get the status message to build response.
 * @param additions Currenlty useless!
 * @param method_num The method that client used. Used to specify response.
 * @param bodyResponse String of the body message.
 * @return String of the response.
 */
char *buildResponse(ParserData *pd, int potnum, int status_code, char *additions, int method_num, char *bodyResponse);

/**
 * This function makes coffee for the client.
 * @param pd Stores the data of all pots and message and the socket, used to update all data.
 * @param potnum The current pot used to make coffee.
 * @param additions to add them on the coffee.
 * @return String of the coffee.
 */
char *makeCoffee(ParserData *pd, int potnum, char *additions);