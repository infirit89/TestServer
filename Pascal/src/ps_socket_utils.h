//
// Created by georg on 7/11/2023.
//

#ifndef PASCAL_PS_SOCKET_UTILS_H
#define PASCAL_PS_SOCKET_UTILS_H

#include "ps_defs.h"
#include "ps_buffer.h"

void _write_to_socket(ps_socket client_socket, ps_buffer* buffer, s32 flags);
void _receive_from_socket(ps_socket client_socket, ps_buffer* buffer, s32 flags);

#define write_to_socket_f(client_socket, buffer, flags) \
    _write_to_socket(client_socket, buffer, flags)

#define write_to_socket(client_socket, buffer) \
    _write_to_socket(client_socket, buffer, 0)

#define receive_from_socket_f(client_socket, buffer, flags) \
    _receive_from_socket(client_socket, buffer, flags)

#define receive_from_socket(client_socket, buffer) \
    _receive_from_socket(client_socket, buffer, 0)

#endif //PASCAL_PS_SOCKET_UTILS_H
