#include "../../headers/parser/ErrorResponse.h"

char *findMessageResponse(int status_code) {
    switch (status_code) {
        case Continue:
            return (char *)"Continue";
        case Switching_Protocols:
            return (char *)"Switching Protocols";
        case OK:
            return (char *)"OK";
        case Created:
            return (char *)"Created";
        case Accepted:
            return (char *)"Accepted";
        case Non_Authoritative_Information:
            return (char *)"Non-Authoritative Information";
        case No_Content:
            return (char *)"No Content";
        case Reset_Content:
            return (char *)"Reset Content";
        case Partial_Content:
            return (char *)"Partial Content";
        case Multiple_Choices:
            return (char *)"Multiple Choices";
        case Moved_Permanently:
            return (char *)"Moved Permanently";
        case Found:
            return (char *)"Found";
        case See_Other:
            return (char *)"See Other";
        case Not_Modified:
            return (char *)"Not Modified";
        case Use_Proxy:
            return (char *)"Use Proxy";
        case Temporary_Redirect:
            return (char *)"Temporary Redirect";
        case Bad_Request:
            return (char *)"Bad Request";
        case Unauthorized:
            return (char *)"Unauthorized";
        case Payment_Required:
            return (char *)"Payment Required";
        case Forbidden:
            return (char *)"Forbidden";
        case Not_Found:
            return (char *)"Not Found";
        case Method_Not_Allowed:
            return (char *)"Method Not Allowed";
        case Not_Acceptable:
            return (char *)"Not Acceptable";
        case Proxy_Authentication_Required:
            return (char *)"Proxy Authentication Required";
        case Request_Time_out:
            return (char *)"Request Time-out";
        case Conflict:
            return (char *)"Conflict";
        case Gone:
            return (char *)"Gone";
        case Length_Required:
            return (char *)"Length Required";
        case Precondition_Failed:
            return (char *)"Precondition Failed";
        case Request_Entity_Too_Large:
            return (char *)"Request Entity Too Large";
        case Request_URI_Too_Large:
            return (char *)"Request-URI Too Large";
        case Unsupported_Media_Type:
            return (char *)"Unsupported Media Type";
        case Requested_range_not_satisfiab:
            return (char *)"Requested range not satisfiab";
        case Expectation_Failed:
            return (char *)"Expectation Failed";
        case Im_A_teapot:
            return (char *)"Im_A_teapot";
        case Internal_Server_Error:
            return (char *)"Internal Server Error";
        case Not_Implemented:
            return (char *)"Not Implemented";
        case Bad_Gateway:
            return (char *)"Bad Gateway";
        case Service_Unavailable:
            return (char *)"Service Unavailable";
        case Gateway_Time_out:
            return (char *)"Gateway Time-out";
        case HTTP_Version_not_supported:
            return (char *)"HTTP Version not supported";
        default:
            return (char *)"NO STATUS RESPONSE FOUND";
    }
}
