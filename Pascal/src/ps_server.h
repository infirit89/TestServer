//
// Created by georg on 6/14/2023.
//

#ifndef PASCAL_PS_SERVER_H
#define PASCAL_PS_SERVER_H
#include "ps_defs.h"

typedef enum ps_protocol
{
    PS_TCP,
    PS_UDP
} ps_protocol;

typedef struct ps_server
{
    int server_socket;
    int server_port;
} ps_server;

typedef void(*listen_successful_callback)();

int init_server(ps_server* server, ps_protocol protocol);
void start_listen(ps_server* server, u16 port, listen_successful_callback callback);

#endif //PASCAL_PS_SERVER_H
