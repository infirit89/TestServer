//
// Created by OKAY on 7/6/2023.
//

#ifndef PASCAL_PS_REQUEST_H
#define PASCAL_PS_REQUEST_H

#include "core/ps_defs.h"
#include "utils/ps_buffer.h"

typedef enum ps_request_method
{
    PS_NONE = 0,
    PS_GET,
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

ps_request* init_request(struct ps_server* server, ps_socket client_socket);
void shutdown_request(ps_request* request);

#endif //PASCAL_PS_REQUEST_H
