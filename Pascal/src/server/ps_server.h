//
// Created by georg on 6/14/2023.
//

#ifndef PASCAL_PS_SERVER_H
#define PASCAL_PS_SERVER_H
#include "core/ps_defs.h"

typedef enum ps_protocol
{
    PS_TCP = 0,
    PS_UDP
} ps_protocol;

struct ps_request;
typedef void (*ps_request_callback)(struct ps_request* request);

struct ps_server;
typedef struct ps_server ps_server;

#define PS_DEFAULT_BACKLOG 10

ps_server* init_server(ps_protocol protocol, u32 thread_count);
int server_listen(ps_server* server, u16 port, s32 backlog);
int shutdown_server(ps_server* server);

void server_add_route(ps_server* server, const char* route, ps_request_callback callback);

ps_socket accept_client(ps_server* server);

void _server_add_static_files(ps_server* server, char* folder_path, ...);

#define server_add_static_files(server, folder_path, ...) \
    _server_add_static_files(server, folder_path, __VA_ARGS__, NULL)

void start_request_response_loop(ps_server* server);

#endif //PASCAL_PS_SERVER_H
