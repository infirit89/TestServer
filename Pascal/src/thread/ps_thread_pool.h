//
// Created by georg on 7/20/2023.
//

#ifndef PASCAL_PS_THREAD_POOL_H
#define PASCAL_PS_THREAD_POOL_H

#include "core/ps_defs.h"

typedef void (*ps_thread_pool_func)(void* arg);

struct ps_thread_pool;
typedef struct ps_thread_pool ps_thread_pool;

ps_thread_pool* ps_thread_pool_create(u32 thread_num);
void ps_thread_pool_destroy(ps_thread_pool* thread_pool);

// issue a stop command to all the working threads
void ps_thread_pool_stop(ps_thread_pool* thread_pool);

// get the number of all threads
u32 ps_thread_pool_get_thread_count(ps_thread_pool* thread_pool);

// get the number of threads that are doing work currently
u32 ps_thread_pool_get_worker_count(ps_thread_pool* thread_pool);

// add work to the work queue
u8 ps_thread_pool_add_work(ps_thread_pool* thread_pool, ps_thread_pool_func thread_func, void* arg);

// wait for all the working threads to finish
void ps_thread_pool_wait(ps_thread_pool* thread_pool);

#endif //PASCAL_PS_THREAD_POOL_H
