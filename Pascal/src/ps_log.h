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

bool ps_log_init(const char* logger_name);
void ps_log_shutdown();
void ps_log(ps_log_level log_level, const char* fmt, ...);

#define PS_TRACE(fmt, ...) ps_log(PS_LOG_TRACE, fmt, __VA_ARGS__)
#define PS_INFO(fmt, ...) ps_log(PS_LOG_INFO, fmt, __VA_ARGS__)
#define PS_WARNING(fmt, ...) ps_log(PS_LOG_WARNING, fmt, __VA_ARGS__)
#define PS_ERROR(fmt, ...) ps_log(PS_LOG_ERROR, fmt, __VA_ARGS__)

#endif //PASCAL_PS_LOG_H
