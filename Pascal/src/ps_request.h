//
// Created by OKAY on 7/6/2023.
//

#ifndef PASCAL_PS_REQUEST_H
#define PASCAL_PS_REQUEST_H

#include "ps_defs.h"
#include "ps_buffer.h"

typedef enum ps_request_method
{
    PS_GET = 0,
    PS_POST,
    PS_UPDATE,
    PS_DELETE
} ps_request_method;

const char* request_method_to_str(ps_request_method method);

struct ps_server;
typedef struct ps_request
{
    ps_socket socket;
    ps_request_method method;
    char* target;
    struct ps_server* server;
    ps_buffer buffer;
} ps_request;

void parse_raw_request_data(ps_request* request);

#endif //PASCAL_PS_REQUEST_H
