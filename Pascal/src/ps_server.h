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

typedef u32 ps_socket;

typedef void (*ps_request_callback)(ps_socket socket);

typedef struct ps_server
{
    ps_socket server_socket;
    ps_request_callback request_callback;
    int server_port;
} ps_server;

#define PS_DEFAULT_BACKLOG 10

ps_server* init_server(ps_request_callback request_callback, ps_protocol protocol);
int server_listen(ps_server* server, u16 port, s32 backlog);
int shutdown_server(ps_server* server);
int close_socket(ps_socket socket);

ps_socket accept_client(ps_server* server);
int receive_data_from_client(ps_socket client, char* buffer, int length, int flags);
int send_data_to_client(ps_socket client, char* buffer, int length, int flags);

void start_request_response_loop(ps_server* server);

#endif //PASCAL_PS_SERVER_H
