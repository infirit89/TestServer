//
// Created by georg on 7/20/2023.
//

#ifndef PASCAL_PS_THREAD_H
#define PASCAL_PS_THREAD_H

#include "core/ps_defs.h"
#include "ps_mutex.h"
#include "ps_condition_variable.h"

typedef void* (*ps_thread_fn)(void*);

typedef struct ps_thread
{
    void* id;
    ps_thread_fn fn;

    void* arg;
    void* ret;

    char err[64];

} ps_thread;

u32 ps_thread_start(ps_thread* thread, ps_thread_fn fn, void* arg);
void ps_thread_detach(ps_thread* thread);
u32 ps_thread_join(ps_thread* thread);
u32 ps_get_current_thread_id();


#endif //PASCAL_PS_THREAD_H
