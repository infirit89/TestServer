//
// Created by OKAY on 7/6/2023.
//

#include "ps_buffer.h"
#include "ps_assert.h"

#include <stdlib.h>
#include <memory.h>

void buffer_init(ps_buffer* buffer, u32 initial_capacity)
{
    *buffer = (ps_buffer){0};
    buffer->data = (char*)calloc(1, initial_capacity);
    PS_ASSERT(buffer->data, "Couldn't allocate request buffer");
    buffer->capacity = initial_capacity;
}

void buffer_free(ps_buffer* buffer)
{
    PS_ASSERT(buffer, "Buffer is null");
    // hello idiot this gives error and for some fucking reason this line causes it:
    // char* target = strtok_s(context, delimeter, &context);
    free(buffer->data);
    buffer->capacity = 0;
    buffer->size = 0;
    buffer->data = NULL;
}

void buffer_resize(ps_buffer* buffer, u32 capacity)
{
    buffer->capacity = capacity;
    buffer->data = (char*)realloc(buffer->data, buffer->capacity);
    PS_ASSERT(buffer->data, "Couldn't reallocate the buffer's data");
}

void buffer_push_data(ps_buffer* buffer, char* data, u32 size)
{
    if(size + buffer->size >= buffer->capacity)
        buffer_resize(buffer, buffer->size + size);

    memcpy(buffer->data + buffer->size, data, size);
    buffer->size += size;
}

