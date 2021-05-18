#include "../../headers/parser/Parser.h"

char *parse(ParserData *pd) {
    char *message = (char *)calloc(sizeof(char), strlen(pd->message));
    strcpy(message, pd->message);

    std::string temp;
    char *method, *potStr, *server, *additions, *content_type, *body, *tempBodyResponse;
    int potnum, message_size, method_num;
    int status_code = OK;
    ALLOC(method, MAX_MESSAGE_SIZE);
    ALLOC(potStr, MAX_MESSAGE_SIZE);
    ALLOC(server, MAX_MESSAGE_SIZE);
    ALLOC(additions, MAX_MESSAGE_SIZE);
    ALLOC(content_type, MAX_MESSAGE_SIZE);
    ALLOC(body, MAX_MESSAGE_SIZE);
    ALLOC(tempBodyResponse, MAX_MESSAGE_SIZE);

    std::istringstream iss(message); /** Stream of the client request, used to parse the request by lines*/
    int index = 0;
    while (getline(iss, temp, '\n') && (status_code == OK)) {
        temp[temp.size() - 1] = '\0';
        std::istringstream issTemp(temp); /** Stream of the client request, used to parse the lines by spaces*/
        while (getline(issTemp, temp, ' ') && (status_code == OK)) {
            switch (index++) {
                case METHOD: /** Parsing the method*/
                    //std::cout << "method: " << temp << std::endl;
                    if (strlen(temp.c_str()) == 0) {
                        status_code = Bad_Request;
                    } else if (!strcmp(temp.c_str(), BREW)) {
                        strcpy(method, temp.c_str());
                        method_num = NBREW;
                    } else if (!strcmp(temp.c_str(), POST)) {
                        strcpy(method, temp.c_str());
                        method_num = NPOST;
                    } else if (!strcmp(temp.c_str(), PROPFIND)) {
                        strcpy(method, temp.c_str());
                        method_num = NPROPFIND;
                    } else {
                        status_code = Not_Implemented;
                    }
                    break;
                case POT_NUM: /** Parsing the pot number, * for all */
                    //std::cout << "potnum: " << temp << std::endl;
                    if (!strcmp(temp.c_str(), "*")) {
                        potnum = 0;
                    } else if ((strlen(temp.c_str()) == 0) || strcmp(temp.substr(0, 4).c_str(), "pot-")) {
                        status_code = Bad_Request;
                    } else {
                        potnum = atoi((temp.c_str() + 4));
                        if (potnum < 1 || potnum > 5)
                            status_code = Not_Found;
                    }
                    break;
                case SERVER: /** Parsing the server version*/
                    //std::cout << "server: " << temp << std::endl;
                    if (strlen(temp.c_str()) == 0) {
                        status_code = Bad_Request;
                    } else if (strcmp(temp.c_str(), HTCPCP_VERSION)) {
                        status_code = HTTP_Version_not_supported;
                    } else {
                        strcpy(server, temp.c_str());
                    }
                    break;
                case ADDS_HEADER: /** Parsing the addition header*/
                    //std::cout << "adds_header: " << temp << std::endl;
                    if (strcmp(temp.c_str(), "Accept-Additions:") || strlen(temp.c_str()) == 0) {
                        status_code = Bad_Request;
                    }
                    break;
                case ADDS: /** Parsing additions */
                    //std::cout << "additions: " << temp << std::endl;
                    strcpy(additions, temp.c_str());
                    break;
                case TYPE_HEADER: /** Parsing content type header*/
                    //std::cout << "type_header: " << temp << std::endl;
                    if (strcmp(temp.c_str(), "Content-Type:") || (strlen(temp.c_str()) == 0)) {
                        status_code = Bad_Request;
                    }
                    break;
                case TYPE: /** Parsing the content type*/
                    //std::cout << "content_type: " << temp << std::endl;
                    if ((strlen(temp.c_str()) == 0) || strcmp(temp.c_str(), "message/coffeepot")) {
                        status_code = Bad_Request;
                    } else {
                        strcpy(content_type, temp.c_str());
                    }
                    break;
                case SIZE_HEADER: /** Parsing the length header*/
                    //std::cout << "size_header: " << temp << std::endl;
                    if ((strlen(temp.c_str()) == 0) || strcmp(temp.c_str(), "Content-Length:")) {
                        status_code = Bad_Request;
                    }
                    break;
                case SIZE: /** Parsing the length*/
                    //std::cout << "message_size: " << temp << std::endl;
                    message_size = atoi(temp.c_str());
                    if (message_size < 0) {
                        status_code = Length_Required;
                    }
                    break;
                case CRLF: /** Parsing CRLF if it is exits to make sure the structure it right*/
                    //std::cout << "CRFL: " << temp << std::endl;
                    if (strcmp(temp.c_str(), "\0")) {
                        status_code = Bad_Request;
                    }
                    break;
                case BODY: /** Parsing the body message*/
                    //std::cout << "body: " << temp << std::endl;
                    if ((strlen(temp.c_str()) == 0) || strcmp(temp.c_str(), "start") && strcmp(temp.c_str(), "stop")) {
                        status_code = Bad_Request;
                    } else {
                        strcpy(body, temp.c_str());
                    }
                    break;
            }
        }
    }

    if (status_code == OK)
        status_code = parseAdditions(additions, tempBodyResponse);

    return buildResponse(pd, potnum, status_code, additions, method_num, tempBodyResponse);
}

int parseAdditions(char *additions, char *bodyResponse) {
    std::istringstream iss((strcat(additions, "#") + 1));
    std::string temp;

    while (getline(iss, temp, ';')) {
        if ((strlen(temp.c_str()) == 0) || !findAddition(temp.c_str())) {
            strcpy(bodyResponse, "\r\nOnly these additions allowed: \n(Cream),       (Half-and-half),       (Whole-milk),\n(Part-Skim),   (Skim),                (Non-Dairy),\n(Vanilla),     (Almond),              (Raspberry),\n(Whisky),      (Rum),                 (Kahlua),\n(Aquavit)");
            return Not_Acceptable;
        }
        getline(iss, temp, '#');
        int add_cap = atoi(temp.c_str());
        if (add_cap == 0) {
            return Bad_Request;
        }
        if (add_cap < 1 || add_cap > 5) {
            strcpy(bodyResponse, "\r\n1-5 Only Allowed");
            return Not_Acceptable;
        }
    }
    return OK;
}

bool findAddition(const char *temp) {
    char pot_adds[13][15] = {"Cream", "Half-and-half", "Whole-milk", "Part-Skim", "Skim", "Non-Dairy", "Vanilla", "Almond", "Raspberry", "Whisky", "Rum", "Kahlua", "Aquavit"};
    for (int i = 0; i < 13; i++) {
        if (!strcmp(temp, pot_adds[i])) {
            return true;
        }
    }
    return false;
}

char *buildResponse(ParserData *pd, int potnum, int status_code, char *additions, int method_num, char *bodyMessage) {
    char *response;
    ALLOC(response, MAX_MESSAGE_SIZE * 4);
    sprintf(response, "%s %d %s\r\n", HTCPCP_VERSION, status_code, findMessageResponse(status_code));
    if ((bodyMessage != NULL) && (status_code != OK)) {
        strcat(response, bodyMessage);
    }
    if (status_code == OK) {
        switch (method_num) {
            case NBREW:
            case NPOST:
                if (pd->potsAreBrewing[potnum - 1] || pd->potsArePooring[potnum - 1]) {
                    char *ptemp;
                    ALLOC(ptemp, MAX_MESSAGE_SIZE);
                    strcat(ptemp, "Retry-After: 5\r\n\r\nPlease brew your coffee\r\n");
                    strcat(response, ptemp);
                } else {
                    strcat(response, makeCoffee(pd, potnum, additions));
                }
                break;
            case NPROPFIND:
                if (!potnum) {
                    char *tempPot = (char *)calloc(sizeof(char), 128);
                    strcat(response, "Retry-After: 5\r\n\r\nPOT\t\tBREWING\t\tPOORING\n");
                    char *brewing = (char *)calloc(sizeof(char), 10);
                    char *pooring = (char *)calloc(sizeof(char), 10);

                    for (int i = 0; i < 5; i++) {
                        memset(brewing, 0, 10);
                        memset(pooring, 0, 10);

                        if (pd->potsAreBrewing[i])
                            strcpy(brewing, YES);
                        else
                            strcpy(brewing, NO);
                        if (pd->potsArePooring[i])
                            strcpy(pooring, YES);
                        else
                            strcpy(pooring, NO);

                        sprintf(tempPot, "%d%16s%16s\r\n", (i + 1), brewing, pooring);
                        strcat(response, tempPot);
                    }

                } else {
                    if (pd->isItBrewing) {
                        strcat(response, "\r\nBrewing your coffee\r\n");
                    } else if (pd->potsAreBrewing[potnum - 1] || pd->potsArePooring[potnum - 1]) {
                        char *tempPot = (char *)calloc(sizeof(char), 128);
                        sprintf(tempPot, "\r\npot %d in use\r\n", potnum);
                        strcat(response, tempPot);
                    } else {
                        char *tempPot = (char *)calloc(sizeof(char), 128);
                        sprintf(tempPot, "\r\npot %d ready to use\r\n", potnum);
                        strcat(response, tempPot);
                    }
                    break;
                }
        }
    }
    return response;
}

char *makeCoffee(ParserData *pd, int potnum, char *additions) {
    pd->isItBrewing = true;
    pd->potsAreBrewing[potnum - 1] = 1;
    char *coffee = (char *)"\n         {\n      {   }\n       }_{ __{\n    .-{   }   }-.\n   (   }     {   )\n   | -.._____..- |\n   |             ;--.\n   |            (__  \n   |             | )  )\n   |             |/  /\n   |             /  /\n   |            (  /\n   |             /\n    -.._____..-/";
    sleep(BREWING_TIME);
    pd->isItBrewing = false;
    pd->potsAreBrewing[potnum - 1] = 0;
    pd->potsArePooring[potnum - 1] = 1;
    pd->isItPooring = true;
    sleep(POORING_TIME);
    pd->potsArePooring[potnum - 1] = 0;
    pd->isItPooring = false;

    return coffee;
}