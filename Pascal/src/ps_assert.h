//
// Created by georg on 6/8/2023.
//

#ifndef PASCAL_PS_ASSERT_H
#define PASCAL_PS_ASSERT_H
#include "ps_log.h"
#include "ps_debugbreak.h"

#if defined(PS_DEBUG)
#define PS_ASSERT(expression, message) \
    do                                 \
    {                                  \
        if(!(expression))              \
        {                              \
            PS_ERROR(message);         \
            debug_break();             \
        }                              \
    } while(0)
#elif defined(PS_DEBUG)
#define  PS_ASSERT(expression, message)
#endif


#endif //PASCAL_PS_ASSERT_H
