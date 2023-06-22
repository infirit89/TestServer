//
// Created by georg on 6/14/2023.
//

#include "ps_server.h"
#include <winsock2.h>
#include <stdlib.h>
#include <errno.h>
#include "ps_assert.h"

int init_server(ps_server* server, ps_protocol protocol)
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
            return EINVAL;
    }

    // TODO: maybe allow the user to select a family?
    server->server_socket = socket(AF_INET, socket_type, socket_protocol);
    PS_ASSERT(server->server_socket, strerror(errno));
    if(server->server_socket == 0)
        return errno;

    return 0;
}

int start_listen(ps_server* server, u16 port, s32 backlog)
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

    return 0;
}

ps_socket accept_client(ps_server* server)
{
    ps_socket client;
    client = accept(server->server_socket, NULL, NULL);
    PS_ASSERT(client, "Not able to get a new client");

    return client;
}

int receive_data_from_client(ps_socket client, char* buffer, int length, int flags)
{
    int receive_result = recv(client, buffer, length, flags);
    //PS_ASSERT(receive_result == length, "An error occurred while receiving data from client");
    return receive_result;
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
    int close_result = close_socket(server->server_socket);
    return close_result;
}
