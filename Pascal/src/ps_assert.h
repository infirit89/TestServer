//
// Created by georg on 6/8/2023.
//

#ifndef PASCAL_PS_ASSERT_H
#define PASCAL_PS_ASSERT_H
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#if defined(PS_DEBUG)
#define PS_ASSERT(expression, message) \
    if(!(expression))                  \
    {                                  \
        printf("%s\n", message);       \
        system("pause");               \
        raise(SIGABRT);                \
    }
#elif defined(PS_DEBUG)
#define  PS_ASSERT(expression, message)
#endif


#endif //PASCAL_PS_ASSERT_H
