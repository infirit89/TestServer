//
// Created by georg on 7/11/2023.
//

#include "ps_socket_utils.h"
#include "ps_assert.h"

#include <winsock2.h>

void _write_to_socket(ps_socket client_socket, ps_buffer* buffer, s32 flags)
{
    int send_result = send(client_socket, buffer->data, buffer->size, flags);
    PS_ASSERT(send_result == buffer->size, "An error occurred while sending data to client");

    // TODO?
}

void _receive_from_socket(ps_socket client_socket, ps_buffer* buffer, s32 flags)
{
    int bytes;

    do
    {
        bytes = recv(client_socket,
                     buffer->data + buffer->size,
                     buffer->capacity - buffer->size, 0);

        if(bytes > 0)
            buffer->size += bytes;

        if(buffer->size >= buffer->capacity)
            buffer_resize(buffer, buffer->capacity * 2);
        else
            break;

    } while (bytes > 0 && buffer->capacity < PS_HTTP_MAX_REQUEST_BUF_SIZE);
}