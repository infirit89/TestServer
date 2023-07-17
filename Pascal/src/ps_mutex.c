//
// Created by georg on 7/17/2023.
//

#include "ps_mutex.h"

#if defined(WIN32) || defined(WIN64)
#include "synchapi.h"
#endif

void mutex_init(ps_mutex* mutex)
{
    *mutex = (ps_mutex){ 0 };

#if defined(WIN32) || defined(WIN64)
    InitializeCriticalSection((LPCRITICAL_SECTION)(&mutex->mtx));
#endif
}

void mutex_shutdown(ps_mutex* mutex)
{
#if defined(WIN32) || defined(WIN64)
    DeleteCriticalSection((LPCRITICAL_SECTION)(&mutex->mtx));
#endif
}

void mutex_lock(ps_mutex* mutex)
{
#if defined(WIN32) || defined(WIN64)
    EnterCriticalSection((LPCRITICAL_SECTION)(&mutex->mtx));
#endif
}

void mutex_unlock(ps_mutex* mutex)
{
#if defined(WIN32) || defined(WIN64)
    LeaveCriticalSection((LPCRITICAL_SECTION)(&mutex->mtx));
#endif
}
