//
// Created by georg on 7/17/2023.
//

#include "ps_event_manager.h"
#include "vec/vec.h"

/*
 * event manager impl:
 *
 * event_type : enum
 *  - EVENT_TYPE_0
 *  - EVENT_TYPE_1
 *  - EVENT_TYPE_2
 *
 * event : struct
 *  - event_type
 *  - event_params (maybe?)
 *
 * event_listener_callback(event): void
 *
 * event_manager : struct
 *  - event_queue
 *  - event_listeners_map
 *
 * push_event(event_manager, event):
 *  event_manager.event_queue.push(event)
 *
 *  add_listener(event_manager, event_type, listener):
 *      event_manager.event_listeners_map.push(event_type, listener)
 *
 *  dispatch_events(event_manager):
 *      while event_manager.event_queue is not empty:
 *          event = event_manager.event_queue.pop()
 *          listeners = event_manager.event_listeners_map[event.type]
 *          for listener : listeners:
 *              listener()
 *
 * */

#define EVENT_QUEUE_INITIAL_CAPACITY 8
#define EVENT_LISTENERS_INITIAL_CAPACITY 6


typedef vec_t(ps_event_listener_callback) vec_elc_t;

void event_manager_init(ps_event_manager* event_manager)
{
    *event_manager = (ps_event_manager){ 0 };
    queue_init(&(event_manager->event_queue), EVENT_QUEUE_INITIAL_CAPACITY);
    sc_map_init_32v(&(event_manager->event_listeners), EVENT_LISTENERS_INITIAL_CAPACITY, 0);
}

bool _event_manager_get_callbacks(ps_event_manager* event_manager, ps_event_type event_type, vec_elc_t** callbacks)
{
    *callbacks = sc_map_get_32v(&(event_manager->event_listeners), event_type);
    return sc_map_found(&(event_manager->event_listeners));
}

void event_manager_shutdown(ps_event_manager* event_manager)
{
    queue_free(&(event_manager->event_queue));

    void* value;
    sc_map_foreach_value(&(event_manager->event_listeners), value)
    {
        vec_elc_t* callbacks = value;
        vec_deinit(callbacks);
        free(callbacks);
    }

    sc_map_term_32v(&(event_manager->event_listeners));
}

void event_manager_push_event(ps_event_manager* event_manager, ps_event event)
{
    queue_enqueue(&(event_manager->event_queue), event);
}

void event_manager_add_listener(ps_event_manager* event_manager, ps_event_type event_type, ps_event_listener_callback callback)
{
    vec_elc_t* callbacks;
    if(!_event_manager_get_callbacks(event_manager, event_type, &callbacks))
    {
        // allocate the callbacks vector
        callbacks = (vec_elc_t*)malloc(sizeof(vec_elc_t));
        vec_init(callbacks);
    }

    vec_push(callbacks, callback);
    sc_map_put_32v(&(event_manager->event_listeners), event_type, callbacks);
}

void event_manager_dispatch_events(ps_event_manager* event_manager)
{
    while(!queue_is_empty(&(event_manager->event_queue)))
    {
        ps_event event = queue_peek(&(event_manager->event_queue));
        queue_dequeue(&(event_manager->event_queue));

        vec_elc_t* callbacks;
        if(!_event_manager_get_callbacks(event_manager, event.event_type, &callbacks))
            continue;

        int iter;
        ps_event_listener_callback callback;

        vec_foreach(callbacks, callback, iter)
            callback(event);
    }
}