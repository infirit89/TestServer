//
// Created by georg on 7/16/2023.
//


#define PS_QUEUE_TESTS 0
#define PS_SERVER_TESTS 0
#define PS_EVENT_MANAGER_TESTS 1

#if PS_QUEUE_TESTS

#include "queue/ps_queue_tests.h"
#include "../src/pascal.h"

int main()
{
    ps_init();

    ps_queue_test_1();
    ps_queue_test_2();
    ps_queue_test_3();

    ps_shutdown();

    system("pause");

    return 0;
}
#elif PS_EVENT_MANAGER_TESTS
#include "event_manager/ps_event_manager_tests.h"
#include <stdlib.h>

int main()
{
    ps_event_manager_test_1();

    system("pause");
    return 0;
}

#elif PS_SERVER_TESTS

#include "server/ps_queue_server_tests.h"
#include <stdlib.h>

int main()
{
    ps_server_test_1();

    system("pause");
    return 0;
}

#endif
