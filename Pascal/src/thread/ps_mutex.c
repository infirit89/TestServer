//
// Created by georg on 7/17/2023.
//

#include "ps_mutex.h"

void ps_mutex_init(ps_mutex* mutex)
{
    *mutex = (ps_mutex){ 0 };
#if defined(WIN32) || defined(WIN64)
    InitializeCriticalSection(&(mutex->mtx));
#endif
}

void ps_mutex_destroy(ps_mutex* mutex)
{
#if defined(WIN32) || defined(WIN64)
    DeleteCriticalSection(&(mutex->mtx));
#endif
}

void ps_mutex_lock(ps_mutex* mutex)
{
#if defined(WIN32) || defined(WIN64)
    EnterCriticalSection(&(mutex->mtx));
#endif
}

void ps_mutex_unlock(ps_mutex* mutex)
{
#if defined(WIN32) || defined(WIN64)
    LeaveCriticalSection(&(mutex->mtx));
#endif
}
