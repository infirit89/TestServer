//
// Created by georg on 6/15/2023.
//
#include "pascal.h"
#include "ps_assert.h"
#include "ps_log.h"
#include "utils/ps_content_type.h"

#include <winsock2.h>

int ps_init()
{
    WSADATA data;
    ps_log_init("Pascal");
    int result = WSAStartup(MAKEWORD(2,2), &data);
    PS_ASSERT(result == 0, "Couldn't initialize winsock");

    if(!result)
        init_extension_content_type_map();
    return result;
}

int ps_shutdown()
{
    term_extension_content_type_map();
    int result = WSACleanup();
    PS_ASSERT(result == 0, "Couldn't cleanup winsock");
    ps_log_shutdown();
    return result;
}

