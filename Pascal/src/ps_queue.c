//
// Created by georg on 7/12/2023.
//

#include "ps_queue.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void queue_init(ps_queue* queue, u32 capacity)
{
    *queue = (ps_queue){0};
    queue->data = calloc(capacity, sizeof(char*));
    queue->capacity = capacity;
}
void queue_free(ps_queue* queue)
{
    while (!queue_is_empty(queue))
        queue_dequeue(queue);

    free(queue->data);
    *queue = (ps_queue){0};
}

static void _copy_queue_elements(ps_queue* queue, char** new_data)
{
    u32 source_index = queue->head;
    u32 destination_index = 0;

    for (int i = 0; i < queue->size; ++i) {
        new_data[destination_index] = malloc(sizeof(queue->data[source_index]));
        strcpy(new_data[destination_index], queue->data[source_index]);
        source_index = (source_index + 1) % queue->capacity;
        destination_index++;
    }
}

static void _expand_queue(ps_queue* queue)
{
    char** temp_data = calloc(queue->capacity * 2, sizeof(char*));
    _copy_queue_elements(queue, temp_data);
    free(queue->data);
    queue->capacity *= 2;
    queue->data = temp_data;
    queue->head = 0;
    queue->tail = queue->size;
}

void queue_enqueue(ps_queue* queue, char* element)
{
    if(queue->size >= queue->capacity)
        _expand_queue(queue);

    queue->data[queue->tail] = malloc(strlen(element));
    strcpy(queue->data[queue->tail], element);
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;
}

void queue_dequeue(ps_queue* queue)
{
    printf("%s\n", queue->data[queue->head]);

    free(queue->data[queue->head]);
    queue->data[queue->head] = NULL;
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
}

char* queue_peek(ps_queue* queue)
{
    char* result = queue->data[queue->head];
    return result;
}

bool queue_is_empty(ps_queue* queue)
{
    return queue->size <= 0;
}
