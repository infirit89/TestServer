//
// Created by georg on 6/14/2023.
//

#include "ps_server.h"
#include <winsock2.h>
#include <stdlib.h>

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
    }

    //server->server_socket = socket
}

void start_listen(ps_server* server, u16 port, listen_successful_callback callback)
{

}