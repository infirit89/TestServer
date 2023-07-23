//
// Created by georg on 7/16/2023.
//


#define PS_QUEUE_TESTS 0
#define PS_EVENT_MANAGER_TESTS 0
#define PS_SERVER_TESTS 1

#if PS_QUEUE_TESTS

#include "queue/ps_queue_tests.h"
#include "../src/pascal.h"

int main()
{
    ps_init();

    ps_queue_test_1();
    ps_queue_test_2();
    ps_queue_test_3();

    ps_shutdown();

    system("pause");

    return 0;
}
#elif PS_EVENT_MANAGER_TESTS
#include "event_manager/ps_event_manager_tests.h"
#include <stdlib.h>

int main()
{
    ps_event_manager_test_1();

    system("pause");
    return 0;
}

#elif PS_SERVER_TESTS

#include "server/ps_queue_server_tests.h"
#include <stdlib.h>

int main()
{
    ps_server_test_1();

    system("pause");
    return 0;
}

#elif 0

#include "thread/ps_thread.h"
#include "thread/ps_thread_pool.h"
#include "core/ps_log.h"

#include <stdio.h>

ps_mutex mutex;
ps_condition_variable cond;
u32 tid = 0;

const u8 thread_count = 4;
const u8 item_count = 100;

void thread_proc(void* arg)
{
    int* val = arg;
    int old = *val;

    (*val) *= 10;

    PS_TRACE("TID: %u; Old: %i; New: %i", ps_get_current_thread_id(), old, *val);

    if(*val % 2)
        Sleep(10000);
}

int main()
{
    ps_log_init("Thread Pool Test");
    s32 vals[100];
    ps_thread_pool* thread_pool = ps_thread_pool_create(thread_count);

    for (int i = 0; i < item_count; ++i) {
        vals[i] = i;
        ps_thread_pool_add_work(thread_pool, thread_proc, vals + i);
    }

    ps_thread_pool_wait(thread_pool);

    for (int i = 0; i < item_count; ++i) {
        PS_TRACE("%i", vals[i]);
    }

//    free(vals);
    ps_thread_pool_destroy(thread_pool);

    PS_INFO("All systems have shutdown");
    system("pause");

    ps_log_shutdown();

    return 0;
}

#endif
