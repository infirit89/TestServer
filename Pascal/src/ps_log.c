//
// Created by georg on 7/15/2023.
//

#include "ps_log.h"
#include "stdio.h"
#include "ps_defs.h"
#include "ps_mutex.h"

#include <windows.h>

struct ps_logger
{
    const char* name;
    ps_log_level log_level;

    // for windows
    void* console_handle;

    void* output;
};

static b8 s_initialized;
static struct ps_logger s_logger;
static ps_mutex mutex;

#define WIN_CONSOLE_COLOR_GREEN 10
#define WIN_CONSOLE_COLOR_RED 12
#define WIN_CONSOLE_COLOR_YELLOW 14
#define WIN_CONSOLE_COLOR_WHITE 15

b8 ps_log_init(const char* logger_name)
{
    if(s_initialized)
        return PS_FALSE;

    mutex_init(&mutex);
    s_initialized = PS_TRUE;
    s_logger = (struct ps_logger){0 };
    s_logger.name = logger_name;
    s_logger.console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    s_logger.output = stderr;
    return PS_TRUE;
}

static SYSTEMTIME get_time()
{
    SYSTEMTIME local_time;
    GetLocalTime(&local_time);
    return local_time;
}

void ps_log_shutdown()
{
    if(!s_initialized)
        return;

    s_initialized = PS_FALSE;
    s_logger = (struct ps_logger){0 };
    mutex_shutdown(&mutex);
}

void ps_log(ps_log_level log_level, const char* fmt, ...)
{
    if(!s_initialized)
        return;

    va_list args;

    SYSTEMTIME time = get_time();

    va_start(args, fmt);

    mutex_lock(&mutex);
    switch(log_level)
    {
        case PS_LOG_TRACE:
            SetConsoleTextAttribute(s_logger.console_handle, WIN_CONSOLE_COLOR_WHITE);
            break;
        case PS_LOG_INFO:
            SetConsoleTextAttribute(s_logger.console_handle, WIN_CONSOLE_COLOR_GREEN);
            break;
        case PS_LOG_WARNING:
            SetConsoleTextAttribute(s_logger.console_handle, WIN_CONSOLE_COLOR_YELLOW);
            break;
        case PS_LOG_ERROR:
            SetConsoleTextAttribute(s_logger.console_handle, WIN_CONSOLE_COLOR_RED);
            break;
    }



    fprintf(s_logger.output, "[%02d:%02d:%02d] ", time.wHour, time.wMinute, time.wSecond);
    fprintf(s_logger.output, "%s: ", s_logger.name);
    vfprintf(s_logger.output, fmt, args);
    fprintf(s_logger.output, "\n");
    fflush(s_logger.output);

    va_end(args);

    SetConsoleTextAttribute(s_logger.console_handle, WIN_CONSOLE_COLOR_WHITE);
    mutex_unlock(&mutex);
}

