//
// Created by OKAY on 7/8/2023.
//

#include "ps_response.h"
#include "ps_assert.h"

#include <stdlib.h>

const char* response_text[] =
{
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 100s
    "Continue", "Switching Protocols", "Processing", "Early Hints",
    "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 200s
    "OK", "Created", "Accepted", "Non-Authoritative Information", "No Content",
    "Reset Content", "Partial Content", "Multi-Status", "Already Reported", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "IM Used", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 300s
    "Multiple Choices", "Moved Permanently", "Found", "See Other", "Not Modified",
    "Use Proxy", "Switch Proxy", "Temporary Redirect", "Permanent Redirect", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
     // 400s
    "Bad Request", "Unauthorized", "Payment Required", "Forbidden", "Not Found",
    "Method Not Allowed", "Not Acceptable", "Proxy Authentication Required", "Request Timeout",
    "Conflict","Gone", "Length Required", "Precondition Failed", "Payload Too Large",
    "URI Too Long", "Unsupported Media Type", "Range Not Satisfiable", "Expectation Failed",
    "I'm a teapot", "","",
    "Misdirected Request", "Unprocessable Entity", "Locked", "Failed Dependency",
    "Too Early", "Upgrade Required", "",
    "Precondition Required", "Too Many Requests","",
    "Request Header Fields Too Large", "", "", "", "", "", "",
    "", "","", "", "", "", "", "", "", "",
    "", "","", "Unavailable For Legal Reasons", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "","", "", "", "", "",
    "", "", "", "", "",
     // 500s
    "Internal Server Error", "Not Implemented", "Bad Gateway", "Service Unavailable",
    "Gateway Timeout", "HTTP Version Not Supported", "Variant Also Negotiates",
    "Insufficient Storage", "Loop Detected", "",
    "Not Extended", "Network Authentication Required", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "",
    "", "", "", ""
};

ps_response* init_response()
{
    ps_response* response = (ps_response*)calloc(1, sizeof(ps_response));
    response->status = PS_HTTP_SUCCESS;
    return response;
}

void response_set_body(ps_response* response, char* body, u32 body_length)
{
    PS_ASSERT(response, "Response is null");
    response->body = body;
    response->body_length = body_length;
}

void set_status(ps_response* response, ps_http_response_status status)
{
    response->status = status;
}

void response_set_header(ps_response* response, char* key, char* value)
{
    PS_ASSERT(response, "Response is null");
    ps_response_header* header = (ps_response_header*)malloc(sizeof(ps_response_header));
    header->key = key;
    header->value = value;
    header->next_header = response->base_header;
    response->base_header = header;
}

void ps_respond(ps_response* response)
{

}
