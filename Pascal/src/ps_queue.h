//
// Created by georg on 7/12/2023.
//

#ifndef PASCAL_PS_QUEUE_H
#define PASCAL_PS_QUEUE_H
#include "ps_defs.h"

typedef struct ps_queue
{
    char** data;
    u32 head;
    u32 tail;
    u32 size;
    u32 capacity;
} ps_queue;

void queue_init(ps_queue* queue, u32 capacity);
void queue_free(ps_queue* queue);

void queue_enqueue(ps_queue* queue, char* element);
void queue_dequeue(ps_queue* queue);
char* queue_peek(ps_queue* queue);
bool queue_is_empty(ps_queue* queue);

#endif //PASCAL_PS_QUEUE_H
