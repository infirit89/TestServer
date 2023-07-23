//
// Created by georg on 7/20/2023.
//

#ifndef PASCAL_PS_CONDITION_VARIABLE_H
#define PASCAL_PS_CONDITION_VARIABLE_H

#include "core/ps_defs.h"
#include "ps_mutex.h"

#if defined(_WIN32) || defined(_WIN64)
#include <synchapi.h>

typedef struct ps_condition_variable
{
    CONDITION_VARIABLE cond;
} ps_condition_variable;
#endif

u32 ps_condition_variable_init(ps_condition_variable* condition_variable);
u32 ps_condition_variable_wait(ps_condition_variable* condition_variable, ps_mutex* mutex);
u32 ps_condition_variable_wake(ps_condition_variable* condition_variable);
u32 ps_condition_variable_wake_all(ps_condition_variable* condition_variable);
void ps_condition_variable_destroy(ps_condition_variable* condition_variable);

#endif //PASCAL_PS_CONDITION_VARIABLE_H
