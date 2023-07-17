//
// Created by georg on 7/17/2023.
//

#ifndef PASCAL_PS_MUTEX_H
#define PASCAL_PS_MUTEX_H

typedef struct ps_mutex
{
    void* mtx;
}ps_mutex;

void mutex_init(ps_mutex* mutex);
void mutex_shutdown(ps_mutex* mutex);

void mutex_lock(ps_mutex* mutex);
void mutex_unlock(ps_mutex* mutex);

#endif //PASCAL_PS_MUTEX_H
