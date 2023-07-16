//
// Created by georg on 7/12/2023.
//

#ifndef PASCAL_PS_QUEUE_H
#define PASCAL_PS_QUEUE_H
#include "ps_defs.h"
#include <memory.h>
#include <stdlib.h>

#define ps_queue_def(T) \
struct                  \
{                       \
    T* data;            \
    u32 head;           \
    u32 tail;           \
    u32 size;           \
    u32 capacity;       \
}

void _expand_queue(char** data, u32* capacity, u32* head, u32* tail, u32 size, u64 memsize);

#define queue_init(queue, init_capacity)                             \
    memset((queue), 0, sizeof(*(queue)));                            \
    (queue)->data = calloc((init_capacity), sizeof(*(queue)->data)); \
    (queue)->capacity = (init_capacity)

#define queue_free(queue)   \
    free((queue)->data);    \
    memset((queue), 0, sizeof(*queue))

#define queue_unpack(queue) \
    (char**)&(queue)->data, &(queue)->capacity, &(queue)->head, &(queue)->tail, (queue)->size, sizeof(*(queue)->data)

#define queue_enqueue(queue, element) \
    if((queue)->size >= (queue)->capacity) \
        _expand_queue(queue_unpack(queue));\
    (queue)->data[(queue)->tail] = element;\
    (queue)->tail = ((queue)->tail + 1) % (queue)->capacity; \
    (queue)->size++

#define queue_dequeue(queue)                                         \
    do                                                               \
    {                                                                \
        if((queue)->size > 0)                                        \
        {                                                            \
            (queue)->head = ((queue)->head + 1) % (queue)->capacity; \
            (queue)->size--;                                         \
        }                                                            \
    } while(0)

#define queue_peek(queue) \
    (queue)->data[(queue)->head]

#define queue_is_empty(queue) \
    ((queue)->size <= 0)

#define queue_foreach(queue, value) \
    for(u32 i = (queue)->head, _b = 0; i  != (queue)->tail; i = ((i + 1) % (queue)->capacity)) \
        for((value) = (queue)->data[i], _b = 1; _b == 1; _b = 0)


typedef ps_queue_def(const char*) ps_queue_const_str;
typedef ps_queue_def(char*) ps_queue_str;
typedef ps_queue_def(s32) ps_queue_s32;

#endif //PASCAL_PS_QUEUE_H
