//
// Created by georg on 7/17/2023.
//

#ifndef PASCAL_PS_MUTEX_H
#define PASCAL_PS_MUTEX_H

#if defined(_WIN32) || defined(_WIN64)
#include <synchapi.h>

typedef struct ps_mutex 
{
    CRITICAL_SECTION mtx;
} ps_mutex;
#endif

void ps_mutex_init(ps_mutex* mutex);
void ps_mutex_destroy(ps_mutex* mutex);

void ps_mutex_lock(ps_mutex* mutex);
void ps_mutex_unlock(ps_mutex* mutex);

#endif //PASCAL_PS_MUTEX_H
