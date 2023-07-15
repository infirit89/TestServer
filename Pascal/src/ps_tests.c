//
// Created by georg on 7/15/2023.
//

#include "ps_tests.h"
#include "ps_log.h"

#include <string.h>

#define SUCASS "[OK]"
#define DONTSUCASS "[FAIL]"

void _check_value_bool(bool value)
{
    if(value)
    {
        PS_INFO(SUCASS);
        return;
    }

    PS_ERROR(DONTSUCASS);
}

void _check_value_str(char* value_to_check, const char* value)
{
    if(strcmp(value_to_check, value) == 0)
    {
        PS_INFO("%s %s", SUCASS, value_to_check);
        return;
    }

    PS_ERROR("%s %s", DONTSUCASS, value_to_check);
}

bool strmatches(char* val1, char* val2)
{
    return strcmp(val1, val2) == 0;
}

void ps_queue_test_1()
{
    ps_queue queue;
    queue_init(&queue, 3);

    const char* values[] =
    {
        "icuq",
        "icuw",
        "icue",
        "icur",
        "icut",
        "icuy",
        "icuu",
        "icui",
        "icuo",
        "icup",
        "icum",
        "icun",
        "icub",
        "icuv",
        "icuc",
        "icux",
        "icuz",

    };

    for (int i = 0; i < 17; ++i) {
        queue_enqueue(&queue, values[i]);
    }

    bool success = PS_FALSE;
    int index = 0;

    while(!queue_is_empty(&queue))
    {
        char* val = queue_peek(&queue);

        _check_value_str(val, values[index]);
        index++;

        queue_dequeue(&queue);
    }

//    _check_value_bool(success);

    queue_free(&queue);
}

void ps_queue_test_2()
{
    ps_queue queue;
    queue_init(&queue, 2);

    _check_value_bool(!queue_dequeue(&queue));

    queue_free(&queue);
}