//
// Created by georg on 7/12/2023.
//

#include "ps_queue.h"
#include "ps_string.h"
#include "ps_assert.h"

#include <stdlib.h>
#include <string.h>

#if 1
//void queue_init(ps_queue* queue, u32 capacity)
//{
//    *queue = (ps_queue){0};
//    queue->data = calloc(capacity, sizeof(char*));
//    queue->capacity = capacity;
//}
//void queue_free(ps_queue* queue)
//{
//    while (!queue_is_empty(queue))
//        queue_dequeue(queue);
//
//    free(queue->data);
//    *queue = (ps_queue){0};
//}

//static void _copy_queue_elements(ps_queue* queue, char** new_data)
//{
//    u32 source_index = queue->head;
//    u32 destination_index = 0;
//
//    for (int i = 0; i < queue->size; ++i) {
//        new_data[destination_index] = malloc(strlen(queue->data[source_index]) + 1);
//        strcpy(new_data[destination_index], queue->data[source_index]);
//        free(queue->data[source_index]);
//        source_index = (source_index + 1) % queue->capacity;
//        destination_index++;
//    }
//}

void _expand_queue(char** data, u32* capacity, u32* head, u32* tail, u32 size, u64 memsize)
{
//    char** temp_data = calloc(queue->capacity * 2, sizeof(char*));
//    _copy_queue_elements(queue, temp_data);
//    free(queue->data);
    void* temp = (char**)realloc(*data, (*(capacity) * 2) * memsize);
    PS_ASSERT(temp, "Couldn't reallocate the queue's data");

    if(temp)
        *data = temp;

    *capacity *= 2;
//    queue->data = temp_data;
    *head = 0;
    *tail = size;
}

//void queue_enqueue(ps_queue* queue, char* element)
//{
//    if(queue->size >= queue->capacity)
//        _expand_queue(queue);
//
//    queue->data[queue->tail] = ps_string_copy(element);
//    queue->tail = (queue->tail + 1) % queue->capacity;
//    queue->size++;
//}

//bool queue_dequeue(ps_queue* queue)
//{
//    if(!queue->data[queue->head])
//        return PS_FALSE;
//
//    free(queue->data[queue->head]);
//    queue->data[queue->head] = NULL;
//    queue->head = (queue->head + 1) % queue->capacity;
//    queue->size--;
//    return PS_TRUE;
//}

//char* queue_peek(ps_queue* queue)
//{
//    char* result = queue->data[queue->head];
//    return result;
//}

//bool queue_is_empty(ps_queue* queue)
//{
//    return queue->size <= 0;
//}

#endif
