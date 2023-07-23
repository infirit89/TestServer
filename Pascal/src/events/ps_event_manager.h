//
// Created by georg on 7/17/2023.
//

#ifndef PASCAL_PS_EVENT_MANAGER_H
#define PASCAL_PS_EVENT_MANAGER_H

#include "sc/sc_map.h"
#include "utils/ps_queue.h"

typedef enum ps_event_type
{
    PS_EVENT_TYPE_NONE,
    PS_EVENT_TYPE_EXIT
} ps_event_type;

typedef struct ps_event
{
    ps_event_type event_type;
} ps_event;

typedef ps_queue_def(ps_event) ps_queue_event;

typedef void(*ps_event_listener_callback)(ps_event);

typedef struct ps_event_manager
{
    ps_queue_event event_queue;
    struct sc_map_32v event_listeners;
} ps_event_manager;

void event_manager_init(ps_event_manager* event_manager);
void event_manager_shutdown(ps_event_manager* event_manager);

void event_manager_push_event(ps_event_manager* event_manager, ps_event event);
void event_manager_add_listener(ps_event_manager* event_manager, ps_event_type event_type, ps_event_listener_callback callback);
void event_manager_dispatch_events(ps_event_manager* event_manager);

#endif //PASCAL_PS_EVENT_MANAGER_H
