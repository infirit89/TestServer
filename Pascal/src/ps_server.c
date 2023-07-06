//
// Created by georg on 6/14/2023.
//

#include "ps_server.h"
#include <winsock2.h>
#include <stdlib.h>
#include <errno.h>
#include "ps_assert.h"

ps_server* init_server(ps_request_callback request_callback, ps_protocol protocol)
{
    int socket_type = SOCK_STREAM;
    int socket_protocol = IPPROTO_TCP;

    switch (protocol) {
        case PS_TCP:
            socket_type = SOCK_STREAM;
            socket_protocol = IPPROTO_TCP;
            break;
        case PS_UDP:
            socket_type = SOCK_DGRAM;
            socket_protocol = IPPROTO_UDP;
            break;
        default:
            PS_ASSERT(PS_FALSE, "Invalid protocol type");
            return NULL;
    }

    // TODO: maybe allow the user to select a family?
    ps_socket server_socket = socket(AF_INET, socket_type, socket_protocol);
    PS_ASSERT(server_socket, strerror(errno));

    ps_server* server = malloc(sizeof(ps_server));
    server->server_socket = server_socket;
    server->request_callback = request_callback;

    return server;
}


void start_request_response_loop(ps_server* server)
{
    while(TRUE)
    {
        ps_socket client = accept_client(server);
        if(client == PS_INVALID_SOCKET)
            continue;

        ps_request* request = init_request(server, client);
        init_buffer(&(request->buffer), PS_HTTP_REQUEST_INITIAL_BUF_SIZE);
        receive_data_from_client(request);
        // TODO: read from client and parse the raw request
        server->request_callback(request);

        shutdown_request(request);
    }
}

int server_listen(ps_server* server, u16 port, s32 backlog)
{
    server->server_port = port;
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    // TODO: make it possible to specify an address
    server_address.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(server->server_socket, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    PS_ASSERT(!bind_result, "Can't bind the socket");
    if(bind_result)
        return bind_result;

    int listen_result = listen(server->server_socket, backlog ? backlog : PS_DEFAULT_BACKLOG);
    PS_ASSERT(!listen_result, "Listen failed");
    if(listen_result)
        return listen_result;

    start_request_response_loop(server);

    return 0;
}

ps_socket accept_client(ps_server* server)
{
    ps_socket client;
    client = accept(server->server_socket, NULL, NULL);
    PS_ASSERT(client, "Not able to get a new client");

    return client;
}

void receive_data_from_client(ps_request* request)
{
    int bytes = recv(request->client_socket,
             request->buffer.data + request->buffer.length,
             request->buffer.capacity - request->buffer.length, 0);


//    int bytes = 0;
//
//    do
//    {
//        bytes = recv(request->client_socket,
//                     request->buffer.data + request->buffer.length,
//                     request->buffer.capacity - request->buffer.length, 0);
//        if(bytes > 0)
//            request->buffer.length += bytes;
//
//        if(request->buffer.length >= request->buffer.capacity)
//            resize_buffer(&(request->buffer), request->buffer.capacity * 2);
//
//    } while(bytes > 0 && request->buffer.capacity < PS_HTTP_MAX_REQUEST_BUF_SIZE);

//    int bytes = recv(client, buffer, length, flags);
//    return bytes;
    //PS_ASSERT(receive_result == length, "An error occurred while receiving data from client");
}

ps_request* init_request(ps_server* server, ps_socket client_socket)
{
    ps_request* request = (ps_request*)malloc(sizeof(ps_request));
    request->server = server;
    request->client_socket = client_socket;

    return request;
}

void shutdown_request(ps_request* request)
{
    PS_ASSERT(request, "Can't free a request that is null");

    close_socket(request->client_socket);

    free_buffer(&(request->buffer));
    free(request);
}

int send_data_to_client(ps_socket client, char* buffer, int length, int flags)
{
    int send_result = send(client, buffer, length, flags);
    PS_ASSERT(send_result == length, "An error occurred while sending data to client");
    return send_result;
}

int close_socket(ps_socket socket)
{
    int close_result = closesocket(socket);
    PS_ASSERT(!close_result, "Couldn't close the client socket");
    return close_result;
}

int shutdown_server(ps_server* server)
{
    if(server != NULL)
        return -1;

    int close_result = close_socket(server->server_socket);
    free(server);
    return close_result;
}
