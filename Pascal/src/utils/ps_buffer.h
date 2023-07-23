//
// Created by OKAY on 7/6/2023.
//

#ifndef PASCAL_PS_BUFFER_H
#define PASCAL_PS_BUFFER_H

#include "../core/ps_defs.h"

typedef struct ps_buffer
{
    char* data;
    u32 capacity;
    u32 size;
} ps_buffer;

void buffer_init(ps_buffer* buffer, u32 initial_capacity);
void buffer_free(ps_buffer* buffer);
void buffer_resize(ps_buffer* buffer, u32 capacity);
void buffer_push_data(ps_buffer* buffer, char* data, u32 size);

/*
 * buf: ptr + size
 * max_size: capacity - size
 */

#endif //PASCAL_PS_BUFFER_H
