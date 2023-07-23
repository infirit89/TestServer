//
// Created by georg on 7/20/2023.
//

#include "ps_condition_variable.h"

#if defined(_WIN32) || defined(_WIN64)

#include <synchapi.h>
#include <windows.h>

u32 ps_condition_variable_init(ps_condition_variable* condition_variable)
{
    *condition_variable = (ps_condition_variable){ 0 };
    InitializeConditionVariable(&(condition_variable->cond));
}

u32 ps_condition_variable_wait(ps_condition_variable* condition_variable, ps_mutex* mutex)
{
    u8 ret = SleepConditionVariableCS(&(condition_variable->cond),
                                      &(mutex->mtx), INFINITE);
    if(!ret)
        return GetLastError();

    return 0;
}

u32 ps_condition_variable_wake(ps_condition_variable* condition_variable)
{
    WakeConditionVariable(&(condition_variable->cond));
}

u32 ps_condition_variable_wake_all(ps_condition_variable* condition_variable)
{
    WakeAllConditionVariable(&(condition_variable->cond));
}

void ps_condition_variable_destroy(ps_condition_variable* condition_variable)
{
    (void)condition_variable;
}

#endif