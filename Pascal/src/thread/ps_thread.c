//
// Created by georg on 7/20/2023.
//

#include "ps_thread.h"
#include "platform/platform.h"

#if defined(_WIN32) || defined(_WIN64)

#include <processthreadsapi.h>
#include <synchapi.h>
#include <windows.h>

static unsigned long __stdcall thread_proc(void* args)
{
    ps_thread* thread = args;

    thread->ret = thread->fn(thread->arg);
    return 0;
}

u32 ps_thread_start(ps_thread* thread, ps_thread_fn fn, void* arg)
{
    *thread = (ps_thread){ 0 };

    thread->fn = fn;
    thread->arg = arg;

    thread->id = CreateThread(NULL, 0, thread_proc, thread, 0, NULL);
    if(!thread->id)
        return ps_get_last_error();

    return 0;
}

void ps_thread_detach(ps_thread* thread)
{
    CloseHandle(thread->id);
}

u32 ps_thread_join(ps_thread* thread)
{
    u32 ret;
    ret = WaitForSingleObject(thread->id,INFINITE);
    if(ret == WAIT_FAILED)
        return ps_get_last_error();

    ret = CloseHandle(thread->id);
    if(!ret)
        return ps_get_last_error();

    return 0;
}

u32 ps_get_current_thread_id()
{
    return GetCurrentThreadId();
}

// TODO: Linux

#endif

