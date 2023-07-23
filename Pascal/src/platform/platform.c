//
// Created by georg on 7/20/2023.
//

#include "platform.h"

#if defined(_WIN32) || defined(_WIN64)

#include <errhandlingapi.h>

u32 ps_get_last_error()
{
    return GetLastError();
}

#endif
