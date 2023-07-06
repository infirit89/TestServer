//
// Created by georg on 6/14/2023.
//

#ifndef PASCAL_PS_SERVER_H
#define PASCAL_PS_SERVER_H
#include "ps_defs.h"
#include "ps_buffer.h"

#define PS_HTTP_REQUEST_INITIAL_BUF_SIZE 1024
#define PS_HTTP_MAX_REQUEST_BUF_SIZE 8388608

typedef enum ps_protocol
{
    PS_TCP,
    PS_UDP
} ps_protocol;

typedef enum ps_request_method
{
    PS_GET,
    PS_POST,
    PS_UPDATE,
    PS_DELETE
} ps_request_method;

typedef u32 ps_socket;
#define PS_INVALID_SOCKET (ps_socket)~0

struct ps_request;
typedef void (*ps_request_callback)(struct ps_request* request);

typedef struct ps_server
{
    ps_socket server_socket;
    ps_request_callback request_callback;
    int server_port;
} ps_server;

typedef struct ps_request
{
    ps_socket client_socket;
    ps_request_method method;
    char* target;
    ps_server* server;
    ps_buffer buffer;
} ps_request;

#define PS_DEFAULT_BACKLOG 10

ps_server* init_server(ps_request_callback request_callback, ps_protocol protocol);
int server_listen(ps_server* server, u16 port, s32 backlog);
int shutdown_server(ps_server* server);
int close_socket(ps_socket socket);

ps_request* init_request(ps_server* server, ps_socket client_socket);
void shutdown_request(ps_request* request);

ps_socket accept_client(ps_server* server);
void receive_data_from_client(ps_socket client_socket, ps_buffer* buffer);
int send_data_to_client(ps_socket client, char* buffer, int length, int flags);

void start_request_response_loop(ps_server* server);

#endif //PASCAL_PS_SERVER_H
