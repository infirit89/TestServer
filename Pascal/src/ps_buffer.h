//
// Created by OKAY on 7/6/2023.
//

#ifndef PASCAL_PS_BUFFER_H
#define PASCAL_PS_BUFFER_H

#include "ps_defs.h"

typedef struct ps_buffer
{
    char* data;
    u32 capacity;
    u32 length;
} ps_buffer;

void init_buffer(ps_buffer* buffer, u32 initial_capacity);
void free_buffer(ps_buffer* buffer);
void resize_buffer(ps_buffer* buffer, u32 capacity);

/*
 * buf: ptr + size
 * max_size: capacity - size
 */

#endif //PASCAL_PS_BUFFER_H
