//
// Created by georg on 7/15/2023.
//

#ifndef PASCAL_PS_LOG_H
#define PASCAL_PS_LOG_H

#include "ps_defs.h"

// basic thread unsafe logger
// it supports only windows
typedef enum ps_log_level
{
    PS_LOG_TRACE = 0,
    PS_LOG_INFO,
    PS_LOG_WARNING,
    PS_LOG_ERROR
} ps_log_level;

b8 ps_log_init(const char* logger_name);
void ps_log_shutdown();
void ps_log(ps_log_level log_level, const char* fmt, ...);

#define PS_TRACE(...) ps_log(PS_LOG_TRACE, __VA_ARGS__)
#define PS_INFO(...) ps_log(PS_LOG_INFO, __VA_ARGS__)
#define PS_WARNING(...) ps_log(PS_LOG_WARNING, __VA_ARGS__)
#define PS_ERROR(...) ps_log(PS_LOG_ERROR, __VA_ARGS__)

#endif //PASCAL_PS_LOG_H
