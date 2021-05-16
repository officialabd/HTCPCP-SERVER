#include <iostream>

#define MAX_MESSAGE_SIZE 4096

#define Continue 100
#define Switching_Protocols 101
#define OK 200
#define Created 201
#define Accepted 202
#define Non_Authoritative_Information 203
#define No_Content 204
#define Reset_Content 205
#define Partial_Content 206
#define Multiple_Choices 300
#define Moved_Permanently 301
#define Found 302
#define See_Other 303
#define Not_Modified 304
#define Use_Proxy 305
#define Temporary_Redirect 307
#define Bad_Request 400
#define Unauthorized 401
#define Payment_Required 402
#define Forbidden 403
#define Not_Found 404
#define Method_Not_Allowed 405
#define Not_Acceptable 406
#define Proxy_Authentication_Required 407
#define Request_Time_out 408
#define Conflict 409
#define Gone 410
#define Length_Required 411
#define Precondition_Failed 412
#define Request_Entity_Too_Large 413
#define Request_URI_Too_Large 414
#define Unsupported_Media_Type 415
#define Requested_range_not_satisfiab 416
#define Expectation_Failed 417
#define Im_A_teapot 418
#define Internal_Server_Error 500
#define Not_Implemented 501
#define Bad_Gateway 502
#define Service_Unavailable 503
#define Gateway_Time_out 504
#define HTTP_Version_not_supported 505

/**
 * It finds the response message depends on the status code. 
 * @param status_code int for status code.
 * @return String of the response, If does not exits returns "NO STATUS RESPONSE FOUND".
 */
char* findMessageResponse(int status_code);