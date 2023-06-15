//
// Created by georg on 6/15/2023.
//
#include "pascal.h"
#include <winsock2.h>
#include "ps_assert.h"

int ps_init()
{
    WSADATA data;
    int result = WSAStartup(MAKEWORD(2,2), &data);
    PS_ASSERT(result == 0, "Couldn't initialize winsock");
    return result;
}

int ps_shutdown()
{
    int result = WSACleanup();
    PS_ASSERT(result == 0, "Couldn't cleanup winsock");
    return result;
}

