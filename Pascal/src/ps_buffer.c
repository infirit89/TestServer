//
// Created by OKAY on 7/6/2023.
//

#include "ps_buffer.h"
#include "ps_assert.h"
#include <stdlib.h>

void init_buffer(ps_buffer* buffer, u32 initial_capacity)
{
    *buffer = (ps_buffer){0};
    buffer->data = (char*)calloc(1, initial_capacity);
    PS_ASSERT(buffer->data, "Couldn't allocate request buffer");
    buffer->capacity = initial_capacity;
}

void free_buffer(ps_buffer* buffer)
{
    PS_ASSERT(buffer, "Buffer is null");
    free(buffer->data);
    buffer->capacity = 0;
    buffer->length = 0;
    buffer->data = NULL;
}

void resize_buffer(ps_buffer* buffer, u32 capacity)
{
    buffer->capacity = capacity;
    buffer->data = (char*)realloc(buffer->data, buffer->capacity);
    PS_ASSERT(buffer->data, "Couldn't reallocate the buffer's data");
}

