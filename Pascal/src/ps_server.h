//
// Created by georg on 6/14/2023.
//

#ifndef PASCAL_PS_SERVER_H
#define PASCAL_PS_SERVER_H
#include "ps_defs.h"
#include "ps_buffer.h"
#include "ps_request.h"
#include "sc/sc_map.h"

typedef enum ps_protocol
{
    PS_TCP = 0,
    PS_UDP
} ps_protocol;

struct ps_request;
typedef void (*ps_request_callback)(struct ps_request* request);

typedef struct ps_server
{
    ps_socket server_socket;
//    ps_request_callback request_callback;
    int server_port;
    struct sc_map_sv route_map;
} ps_server;

#define PS_DEFAULT_BACKLOG 10

ps_server* init_server(ps_protocol protocol);
int server_listen(ps_server* server, u16 port, s32 backlog);
int shutdown_server(ps_server* server);
int close_socket(ps_socket socket);

void server_add_route(ps_server* server, const char* route, ps_request_callback callback);

ps_request* init_request(ps_server* server, ps_socket client_socket);
void shutdown_request(ps_request* request);

ps_socket accept_client(ps_server* server);

void start_request_response_loop(ps_server* server);

#endif //PASCAL_PS_SERVER_H
